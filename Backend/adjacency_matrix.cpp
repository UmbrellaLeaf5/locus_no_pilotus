#include "adjacency_matrix.h"

AdjacencyMatrix AdjacencyMatrix::WithExtraRowCol(
    std::vector<std::vector<double>> nums) {
  AdjacencyMatrix m(nums);
  m.matrix_.resize(m.size_ + 1);
  m.matrix_[m.size_].resize(m.size_ + 1);
  for (std::size_t i = 0; i < m.size_; ++i) {
    m.matrix_[i].resize(m.size_ + 1);
    m.matrix_[i][m.size_] = i;
    m.matrix_[m.size_][i] = i;
  }
  m.CalculateData();
  return m;
}

AdjacencyMatrix& AdjacencyMatrix::operator=(const AdjacencyMatrix& m) {
  size_ = m.size_;
  matrix_ = m.matrix_;
  reducted_matrix_ = m.reducted_matrix_;
  min_numbers_ = m.min_numbers_;
  evaluation_ = m.evaluation_;
  selected_value_ = m.selected_value_;
  selected_edge_ = m.selected_edge_;
  return *this;
}

void AdjacencyMatrix::SetMatrixValue(std::size_t i, std::size_t j, double num) {
  matrix_[i][j] = num;
  CalculateData();
}

AdjacencyMatrix AdjacencyMatrix::Minor(std::size_t i, std::size_t j) {
  std::vector<std::vector<double>> minor_matrix = matrix_;
  minor_matrix.erase(minor_matrix.begin() + i);
  for (std::size_t k = 0; k < size_; ++k) {
    minor_matrix[k].erase(minor_matrix[k].begin() + j);
  }
  AdjacencyMatrix minor(minor_matrix);
  minor.size_--;
  minor.CalculateData();
  return minor;
}

AdjacencyMatrix AdjacencyMatrix::Reducted() {
  AdjacencyMatrix reducted = *this;
  reducted.matrix_ = reducted_matrix_;
  return reducted;
}

AdjacencyMatrix::AdjacencyMatrix(std::vector<std::vector<double>> nums)
    : matrix_{nums},
      size_{nums.size()},
      num_of_flyers_{1},
      min_numbers_(size_ + size_) {}

Minimums AdjacencyMatrix::FindTwoMinimums(Mins type, std::size_t index) const {
  Minimums result;
  double first_min = inf;
  double second_min = inf;
  switch (type) {
    case Mins::Rows: {
      for (std::size_t j = 0; j < size_; ++j) {
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
      for (std::size_t i = 0; i < size_; ++i) {
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
  for (std::size_t i = 0; i < size_; ++i) {
    Minimums twoMins = FindTwoMinimums(Mins::Rows, i);
    double first_min = twoMins.first;
    double second_min = twoMins.second;
    for (std::size_t j = 0; j < size_; ++j) {
      if (reducted_matrix_[i][j] != inf) reducted_matrix_[i][j] -= first_min;
    }
    second_min -= first_min;
    min_numbers_[i] = second_min;
    mins_sum += first_min;
  }

  for (std::size_t i = 0; i < size_; ++i) {
    Minimums twoMins = FindTwoMinimums(Mins::Columns, i);
    double first_min = twoMins.first;
    double second_min = twoMins.second;
    for (std::size_t j = 0; j < size_; ++j) {
      if (reducted_matrix_[j][i] == min_numbers_[j])
        min_numbers_[j] -= first_min;
      if (reducted_matrix_[i][j] != inf) reducted_matrix_[j][i] -= first_min;
    }
    second_min -= first_min;
    min_numbers_[size_ + i] = second_min;
    mins_sum += first_min;
  }

  return mins_sum;
}

std::pair<std::size_t, std::size_t> AdjacencyMatrix::HighestPowerOfZero()
    const {
  std::size_t row = 0, col = 0;
  double max = 0;
  for (std::size_t i = 0; i < size_; ++i) {
    for (std::size_t j = 0; j < size_; ++j) {
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
  selected_edge_ = std::make_pair(matrix_[selected_value_.first][size_],
                                  matrix_[size_][selected_value_.second]);
}
