#include "Adjacency matrix.h"

#include <cmath>

float AdjacencyMatrix::ReductionLine() {
  float mins_sum = 0;
  for (int i = 0; i < rows; ++i) {
    float min_num = matrix[i][0];
    for (int j = 0; j < cols; ++j) {
      if (matrix[i][j] < min_num) {
        min_num = matrix[i][j];
      }
    }
    for (int j = 0; j < cols; ++j) {
      matrix[i][j] -= min_num;
    }
    mins_sum += min_num;
  }

  return mins_sum;
}

float AdjacencyMatrix::ReductionColumn() {
  float mins_sum = 0;
  float second_min = INFINITY;
  for (int i = 0; i < rows; ++i) {
    float min_num = matrix[0][i];
    for (int j = 0; j < cols; ++j) {
      if (matrix[j][i] < min_num) {
        min_num = matrix[i][j];
      }
    }
    for (int j = 0; j < cols; ++j) {
      matrix[j][i] -= min_num;
    }
    mins_sum += min_num;
  }

  return mins_sum;
}

AdjacencyMatrix AdjacencyMatrix::Minor(int i, int j) {
  std::vector<std::vector<float>> new_matrix(cols - 1);
  for (int k = 0; k < rows; ++k) {
    std::vector<float> row(rows - 1);
    if (k != i) {
      for (int l = 0; l < cols; ++l) {
        if (l != j) {
          new_matrix[k][j] = matrix[k][l];
        }
      }
    }
  }
  AdjacencyMatrix minor{new_matrix};
  return minor;
}
