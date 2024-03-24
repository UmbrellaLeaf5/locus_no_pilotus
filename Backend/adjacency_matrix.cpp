#include "adjacency_matrix.h"

#include <cfloat>

AdjacencyMatrix& AdjacencyMatrix::operator=(const AdjacencyMatrix& m) {
  n = m.GetSize();
  matrix = m.matrix;
  return *this;
}

void AdjacencyMatrix::SetMatrixValue(int i, int j, float num) {
  matrix[i][j] = num;
}

int AdjacencyMatrix::GetSize() const { return n; }

float AdjacencyMatrix::GetBottomLineEvaluation() const { return evaluation; }

std::pair<int, int> AdjacencyMatrix::GetSelectedEdge() const {
  return selected_edge;
}

AdjacencyMatrix AdjacencyMatrix::Minor(int i, int j) {
  AdjacencyMatrix minor{n - 1};
  for (int k = 0; k < n; ++k) {
    if (k != i) {
      for (int l = 0; l < n; ++l) {
        if (l != j) {
          minor.SetMatrixValue(i, j, matrix[i][j]);
        }
      }
    }
  }
  return minor;
}

void AdjacencyMatrix::BottomLineEvaluation() {
  evaluation = ReductionLine() + ReductionColumn();
  selected_edge = HighestPowerOfZero();
}

Minimums AdjacencyMatrix::FindTwoMinimums(Mins type, int index) const {
  Minimums result;
  float first_min = FLT_MAX;
  float second_min = FLT_MAX;
  switch (type) {
    case Mins::Rows: {
      for (int j = 0; j < n; ++j) {
        if (matrix[index][j] < first_min) {
          second_min = first_min;
          first_min = matrix[index][j];
        } else if (matrix[index][j] < second_min) {
          second_min = matrix[index][j];
        }
      }
      result.first = first_min;
      result.second = second_min;
      break;
    }

    case Mins::Columns: {
      for (int i = 0; i < n; ++i) {
        if (matrix[i][index] < first_min) {
          second_min = first_min;
          first_min = matrix[i][index];
        } else if (matrix[i][index] < second_min) {
          second_min = matrix[i][index];
        }
      }
      result.first = first_min;
      result.second = second_min;
      break;
    }

    default: {
      result.first = first_min;
      result.second = second_min;
      break;
    }
  }
  return result;
}

float AdjacencyMatrix::ReductionLine() {
  float mins_sum = 0;
  for (int i = 0; i < n; ++i) {
    Minimums twoMins = FindTwoMinimums(Mins::Rows, i);
    float first_min = twoMins.first;
    float second_min = twoMins.second;
    for (int j = 0; j < n; ++j) {
      matrix[i][j] -= first_min;
    }
    second_min -= first_min;
    min_numbers[i] = second_min;
    mins_sum += first_min;
  }

  return mins_sum;
}

float AdjacencyMatrix::ReductionColumn() {
  float mins_sum = 0;
  for (int i = 0; i < n; ++i) {
    Minimums twoMins = FindTwoMinimums(Mins::Columns, i);
    float first_min = twoMins.first;
    float second_min = twoMins.second;
    for (int j = 0; j < n; ++j) {
      if (matrix[j][i] == min_numbers[j]) min_numbers[j] -= first_min;
      matrix[j][i] -= first_min;
    }
    second_min -= first_min;
    min_numbers[n + i] = second_min;
    mins_sum += first_min;
  }

  return mins_sum;
}

std::pair<int, int> AdjacencyMatrix::HighestPowerOfZero() const {
  int row, col;
  float max = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (matrix[i][j] == 0) {
        if ((min_numbers[i] + min_numbers[n + j]) > max) {
          max = min_numbers[i] + min_numbers[n + j];
          row = i;
          col = j;
        }
      }
    }
  }
  return std::make_pair(row, col);
}
