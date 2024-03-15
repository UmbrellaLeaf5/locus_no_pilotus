#include "adjacency_matrix.h"

#include <cfloat>

void AdjacencyMatrix::SetMatrixValue(int i, int j, float num) {
  matrix[i][j] = num;
}

std::pair<float, float> AdjacencyMatrix::GetBottomLineEvaluations() const {
  return evaluation;
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

void AdjacencyMatrix::BottomLineEvaluations() {
  evaluation.first = ReductionLine() + ReductionColumn();
  std::pair<int, int> zero_pos = HighestPowerOfZero();
  matrix[zero_pos.first][zero_pos.second] = FLT_MAX;
  evaluation.second = ReductionLine() + ReductionColumn();
}

Minimums AdjacencyMatrix::FindTwoMinimums(Mins type) const {
  Minimums result;
  float first_min = FLT_MAX;
  float second_min = FLT_MAX;
  switch (type) {
    case Mins::Rows: {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          if (matrix[i][j] < first_min) {
            second_min = first_min;
            first_min = matrix[i][j];
          } else if (matrix[i][j] < second_min) {
            second_min = matrix[i][j];
          }
        }
      }
      result.first = first_min;
      result.second = second_min;
      break;
    }

    case Mins::Columns: {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          if (matrix[j][i] < first_min) {
            second_min = first_min;
            first_min = matrix[j][i];
          } else if (matrix[j][i] < second_min) {
            second_min = matrix[j][i];
          }
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
    Minimums twoMins = FindTwoMinimums(Mins::Rows);
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
    Minimums twoMins = FindTwoMinimums(Mins::Columns);
    float first_min = twoMins.first;
    float second_min = twoMins.second;
    for (int j = 0; j < n; ++j) {
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
  float min = FLT_MAX;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
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
