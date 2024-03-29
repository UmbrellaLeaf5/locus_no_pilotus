#include "adjacency_matrix.h"

#include <cfloat>

AdjacencyMatrix::AdjacencyMatrix(std::vector<std::vector<double>> nums,
                                 bool is_minor)
    : matrix{nums}, n{nums.size() - is_minor} {
  if (!is_minor) {
    matrix.resize(n + 1);
    matrix[n].resize(n + 1);
    for (size_t i = 0; i < n; ++i) {
      matrix[i].resize(n + 1);
      matrix[i][n] = i;
      matrix[n][i] = i;
    }
  }
  min_numbers.resize(n + n);
  CalculateData();
}

AdjacencyMatrix& AdjacencyMatrix::operator=(const AdjacencyMatrix& m) {
  n = m.n;
  matrix = m.matrix;
  reducted_matrix = m.reducted_matrix;
  min_numbers = m.min_numbers;
  evaluation = m.evaluation;
  selected_value = m.selected_value;
  selected_edge = m.selected_edge;
  return *this;
}

void AdjacencyMatrix::SetMatrixValue(int i, int j, double num) {
  matrix[i][j] = num;
  CalculateData();
}

int AdjacencyMatrix::GetSize() const { return n; }

double AdjacencyMatrix::GetMatrixValue(int i, int j) const {
  return matrix[i][j];
}

double AdjacencyMatrix::GetBottomLineEvaluation() const { return evaluation; }

std::pair<int, int> AdjacencyMatrix::GetSelectedEdge() const {
  return selected_edge;
}

std::pair<int, int> AdjacencyMatrix::GetSelectedValue() const {
  return selected_value;
}

AdjacencyMatrix AdjacencyMatrix::Minor(int i, int j) {
  std::vector<std::vector<double>> minor_matrix = matrix;
  minor_matrix.erase(minor_matrix.begin() + i);
  for (size_t k = 0; k < n + 1; ++k) {
    minor_matrix[k].erase(minor_matrix[k].begin() + j);
  }
  AdjacencyMatrix minor(minor_matrix, true);
  minor.CalculateData();
  return minor;
}

AdjacencyMatrix AdjacencyMatrix::Reducted() {
  AdjacencyMatrix reducted = *this;
  reducted.matrix = reducted_matrix;
  return reducted;
}

Minimums AdjacencyMatrix::FindTwoMinimums(Mins type, int index) const {
  Minimums result;
  double first_min = FLT_MAX;
  double second_min = FLT_MAX;
  switch (type) {
    case Mins::Rows: {
      for (int j = 0; j < n; ++j) {
        if (reducted_matrix[index][j] < first_min) {
          second_min = first_min;
          first_min = reducted_matrix[index][j];
        } else if (reducted_matrix[index][j] < second_min) {
          second_min = reducted_matrix[index][j];
        }
      }
      result.first = first_min;
      result.second = second_min;
      break;
    }

    case Mins::Columns: {
      for (int i = 0; i < n; ++i) {
        if (reducted_matrix[i][index] < first_min) {
          second_min = first_min;
          first_min = reducted_matrix[i][index];
        } else if (reducted_matrix[i][index] < second_min) {
          second_min = reducted_matrix[i][index];
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

double AdjacencyMatrix::BottomLineEvaluation() {
  reducted_matrix = matrix;
  double mins_sum = 0;
  for (int i = 0; i < n; ++i) {
    Minimums twoMins = FindTwoMinimums(Mins::Rows, i);
    double first_min = twoMins.first;
    double second_min = twoMins.second;
    for (int j = 0; j < n; ++j) {
      reducted_matrix[i][j] -= first_min;
    }
    second_min -= first_min;
    min_numbers[i] = second_min;
    mins_sum += first_min;
  }

  for (int i = 0; i < n; ++i) {
    Minimums twoMins = FindTwoMinimums(Mins::Columns, i);
    double first_min = twoMins.first;
    double second_min = twoMins.second;
    for (int j = 0; j < n; ++j) {
      if (reducted_matrix[j][i] == min_numbers[j]) min_numbers[j] -= first_min;
      reducted_matrix[j][i] -= first_min;
    }
    second_min -= first_min;
    min_numbers[n + i] = second_min;
    mins_sum += first_min;
  }

  return mins_sum;
}

std::pair<int, int> AdjacencyMatrix::HighestPowerOfZero() const {
  int row = 0, col = 0;
  double max = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (reducted_matrix[i][j] == 0) {
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

void AdjacencyMatrix::CalculateData() {
  evaluation = BottomLineEvaluation();
  selected_value = HighestPowerOfZero();
  selected_edge = std::make_pair(matrix[selected_value.first][n],
                                 matrix[n][selected_value.second]);
}
