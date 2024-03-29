#include "adjacency_matrix.h"

#include <cfloat>

AdjacencyMatrix::AdjacencyMatrix(std::vector<std::vector<double>> nums,
                                 bool is_minor)
    : _matrix{nums},
      _size{nums.size() - is_minor},
      _min_numbers(_size + _size) {
  if (!is_minor) {
    _matrix.resize(_size + 1);
    _matrix[_size].resize(_size + 1);
    for (size_t i = 0; i < _size; ++i) {
      _matrix[i].resize(_size + 1);
      _matrix[i][_size] = i;
      _matrix[_size][i] = i;
    }
  }
  CalculateData();
}

AdjacencyMatrix& AdjacencyMatrix::operator=(const AdjacencyMatrix& m) {
  _size = m._size;
  _matrix = m._matrix;
  _reducted_matrix = m._reducted_matrix;
  _min_numbers = m._min_numbers;
  _evaluation = m._evaluation;
  _selected_value = m._selected_value;
  _selected_edge = m._selected_edge;
  return *this;
}

void AdjacencyMatrix::SetMatrixValue(size_t i, size_t j, double num) {
  _matrix[i][j] = num;
  CalculateData();
}

AdjacencyMatrix AdjacencyMatrix::Minor(size_t i, size_t j) {
  std::vector<std::vector<double>> minor_matrix = _matrix;
  minor_matrix.erase(minor_matrix.begin() + i);
  for (size_t k = 0; k < _size + 1; ++k) {
    minor_matrix[k].erase(minor_matrix[k].begin() + j);
  }
  AdjacencyMatrix minor(minor_matrix, true);
  minor.CalculateData();
  return minor;
}

AdjacencyMatrix AdjacencyMatrix::Reducted() {
  AdjacencyMatrix reducted = *this;
  reducted._matrix = _reducted_matrix;
  return reducted;
}

Minimums AdjacencyMatrix::FindTwoMinimums(Mins type, size_t index) const {
  Minimums result;
  double first_min = FLT_MAX;
  double second_min = FLT_MAX;
  switch (type) {
    case Mins::Rows: {
      for (size_t j = 0; j < _size; ++j) {
        if (_reducted_matrix[index][j] < first_min) {
          second_min = first_min;
          first_min = _reducted_matrix[index][j];
        } else if (_reducted_matrix[index][j] < second_min) {
          second_min = _reducted_matrix[index][j];
        }
      }
      result.first = first_min;
      result.second = second_min;
      break;
    }

    case Mins::Columns: {
      for (size_t i = 0; i < _size; ++i) {
        if (_reducted_matrix[i][index] < first_min) {
          second_min = first_min;
          first_min = _reducted_matrix[i][index];
        } else if (_reducted_matrix[i][index] < second_min) {
          second_min = _reducted_matrix[i][index];
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
  _reducted_matrix = _matrix;
  double mins_sum = 0;
  for (size_t i = 0; i < _size; ++i) {
    Minimums twoMins = FindTwoMinimums(Mins::Rows, i);
    double first_min = twoMins.first;
    double second_min = twoMins.second;
    for (size_t j = 0; j < _size; ++j) {
      _reducted_matrix[i][j] -= first_min;
    }
    second_min -= first_min;
    _min_numbers[i] = second_min;
    mins_sum += first_min;
  }

  for (size_t i = 0; i < _size; ++i) {
    Minimums twoMins = FindTwoMinimums(Mins::Columns, i);
    double first_min = twoMins.first;
    double second_min = twoMins.second;
    for (size_t j = 0; j < _size; ++j) {
      if (_reducted_matrix[j][i] == _min_numbers[j])
        _min_numbers[j] -= first_min;
      _reducted_matrix[j][i] -= first_min;
    }
    second_min -= first_min;
    _min_numbers[_size + i] = second_min;
    mins_sum += first_min;
  }

  return mins_sum;
}

std::pair<size_t, size_t> AdjacencyMatrix::HighestPowerOfZero() const {
  size_t row = 0, col = 0;
  double max = 0;
  for (size_t i = 0; i < _size; ++i) {
    for (size_t j = 0; j < _size; ++j) {
      if (_reducted_matrix[i][j] == 0) {
        if ((_min_numbers[i] + _min_numbers[_size + j]) > max) {
          max = _min_numbers[i] + _min_numbers[_size + j];
          row = i;
          col = j;
        }
      }
    }
  }
  return std::make_pair(row, col);
}

void AdjacencyMatrix::CalculateData() {
  _evaluation = BottomLineEvaluation();
  _selected_value = HighestPowerOfZero();
  _selected_edge = std::make_pair(_matrix[_selected_value.first][_size],
                                  _matrix[_size][_selected_value.second]);
}
