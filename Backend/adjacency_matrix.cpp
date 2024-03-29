#include "adjacency_matrix.h"

#include <cfloat>

AdjacencyMatrix::AdjacencyMatrix(std::vector<std::vector<double>> nums,
                                 bool is_minor)
    : matrix_{nums},
      size_{nums.size() - is_minor},
      min_numbers_(size_ + size_) {
  if (!is_minor) {
    matrix_.resize(size_ + 1);
    matrix_[size_].resize(size_ + 1);
    for (size_t i = 0; i < size_; ++i) {
      matrix_[i].resize(size_ + 1);
      matrix_[i][size_] = i;
      matrix_[size_][i] = i;
    }
  }
  CalculateData();
}

AdjacencyMatrix& AdjacencyMatrix::operator=(const AdjacencyMatrix& m) {
  size_ = m.size_;
  matrix_ = m._matrix;
  reducted_matrix_ = m.reducted_matrix_;
  min_numbers_ = m.min_numbers_;
  evaluation_ = m.evaluation_;
  selected_value_ = m.selected_value_;
  selected_edge_ = m.selected_edge_;
  return *this;
}

void AdjacencyMatrix::SetMatrixValue(size_t i, size_t j, double num) {
  matrix_[i][j] = num;
  CalculateData();
}

AdjacencyMatrix AdjacencyMatrix::Minor(size_t i, size_t j) {
  std::vector<std::vector<double>> minor_matrix = matrix_;
  minor_matrix.erase(minor_matrix.begin() + i);
  for (size_t k = 0; k < size_ + 1; ++k) {
    minor_matrix[k].erase(minor_matrix[k].begin() + j);
  }
  AdjacencyMatrix minor(minor_matrix, true);
  minor.CalculateData();
  return minor;
}

AdjacencyMatrix AdjacencyMatrix::Reducted() {
  AdjacencyMatrix reducted = *this;
  reducted._matrix = reducted_matrix_;
  return reducted;
}

Minimums AdjacencyMatrix::FindTwoMinimums(Mins type, size_t index) const {
  Minimums result;
  double first_min = FLT_MAX;
  double second_min = FLT_MAX;
  switch (type) {
    case Mins::Rows: {
      for (size_t j = 0; j < size_; ++j) {
        if (reducted_matrix_[index][j] < first_min) {
          second_min = first_min;
          first_min = reducted_matrix_[index][j];
        } else if (reducted_matrix_[index][j] < second_min) {
          second_min = reducted_matrix_[index][j];
        }
      }
      result.first = first_min;
      result.second = second_min;
      break;
    }

    case Mins::Columns: {
      for (size_t i = 0; i < size_; ++i) {
        if (reducted_matrix_[i][index] < first_min) {
          second_min = first_min;
          first_min = reducted_matrix_[i][index];
        } else if (reducted_matrix_[i][index] < second_min) {
          second_min = reducted_matrix_[i][index];
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
  reducted_matrix_ = matrix_;
  double mins_sum = 0;
  for (size_t i = 0; i < size_; ++i) {
    Minimums twoMins = FindTwoMinimums(Mins::Rows, i);
    double first_min = twoMins.first;
    double second_min = twoMins.second;
    for (size_t j = 0; j < size_; ++j) {
      reducted_matrix_[i][j] -= first_min;
    }
    second_min -= first_min;
    min_numbers_[i] = second_min;
    mins_sum += first_min;
  }

  for (size_t i = 0; i < size_; ++i) {
    Minimums twoMins = FindTwoMinimums(Mins::Columns, i);
    double first_min = twoMins.first;
    double second_min = twoMins.second;
    for (size_t j = 0; j < size_; ++j) {
      if (reducted_matrix_[j][i] == min_numbers_[j])
        min_numbers_[j] -= first_min;
      reducted_matrix_[j][i] -= first_min;
    }
    second_min -= first_min;
    min_numbers_[size_ + i] = second_min;
    mins_sum += first_min;
  }

  return mins_sum;
}

std::pair<size_t, size_t> AdjacencyMatrix::HighestPowerOfZero() const {
  size_t row = 0, col = 0;
  double max = 0;
  for (size_t i = 0; i < size_; ++i) {
    for (size_t j = 0; j < size_; ++j) {
      if (reducted_matrix_[i][j] == 0) {
        if ((min_numbers_[i] + min_numbers_[size_ + j]) > max) {
          max = min_numbers_[i] + min_numbers_[size_ + j];
          row = i;
          col = j;
        }
      }
    }
  }
  return std::make_pair(row, col);
}

void AdjacencyMatrix::CalculateData() {
  evaluation_ = BottomLineEvaluation();
  selected_value_ = HighestPowerOfZero();
  selected_edge_ = std::make_pair(_matrix[selected_value_.first][size_],
                                  matrix_[size_][selected_value_.second]);
}
