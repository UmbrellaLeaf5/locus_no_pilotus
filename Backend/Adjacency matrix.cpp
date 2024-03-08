#include "Adjacency matrix.h"

#include <cfloat>

std::pair<float, float> AdjacencyMatrix::GetBottomLineAssessments() const {
  return assessment;
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

void AdjacencyMatrix::BottomLineAssessments() {
  assessment.first = ReductionLine() + ReductionColumn();
  std::pair<int, int> zero_pos = HighestPowerOfZero();
  matrix[zero_pos.first][zero_pos.second] = FLT_MAX;
  assessment.second = ReductionLine() + ReductionColumn();
}

float AdjacencyMatrix::ReductionLine() {
  float mins_sum = 0;
  for (int i = 0; i < rows; ++i) {
    float first_min = FLT_MAX;
    float second_min = FLT_MAX;  // Найти второй минимум по строке
    for (int j = 0; j < cols; ++j) {
      if (matrix[i][j] < first_min) {
        second_min = first_min;
        first_min = matrix[i][j];
      } else if (matrix[i][j] < second_min) {
        second_min = matrix[i][j];
      }
    }
    for (int j = 0; j < cols; ++j) {
      matrix[i][j] -= first_min;
      second_min -= first_min;
    }
    min_numbers[i] = second_min;
    mins_sum += first_min;
  }

  return mins_sum;
}

float AdjacencyMatrix::ReductionColumn() {
  float mins_sum = 0;
  for (int i = 0; i < rows; ++i) {
    float first_min = FLT_MAX;
    float second_min = FLT_MAX;  // Второй минимум по столбцу
    for (int j = 0; j < cols; ++j) {
      if (matrix[j][i] < first_min) {
        second_min = first_min;
        first_min = matrix[j][i];
      } else if (matrix[j][i] < second_min) {
        second_min = matrix[j][i];
      }
    }
    for (int j = 0; j < cols; ++j) {
      matrix[j][i] -= first_min;
      second_min -= first_min;
    }
    min_numbers[cols + i] = second_min;
    mins_sum += first_min;
  }

  return mins_sum;
}

std::pair<int, int> AdjacencyMatrix::HighestPowerOfZero() const {
  int row, col;
  float min = FLT_MAX;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (matrix[i][j] == 0) {
        if (min_numbers[i + j] < min) {
          min = min_numbers[i + j];
          row = i;
          col = j;
        }
      }
    }
  }
  return std::make_pair(row, col);
}
