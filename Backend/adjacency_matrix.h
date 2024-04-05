#pragma once

#include <limits>
#include <vector>

#define inf std::numeric_limits<double>::infinity()

// Структура для хранения двух минимумов строки/столбца
struct Minimums {
  double first;
  double second;
};

class AdjacencyMatrix {
 public:
  AdjacencyMatrix(std::size_t size) : size_{size}, min_numbers_(size_ + size_) {
    matrix_.resize(size_ + 1);
    for (auto& elem : matrix_) {
      elem.resize(size_ + 1, 0.0);
    }
    for (std::size_t i = 0; i < size_; ++i) {
      matrix_[i][size_] = i;
      matrix_[size_][i] = i;
    }
    min_numbers_.resize(size_ + size_);
  }

  // Конструктор по вектору векторов
  AdjacencyMatrix(std::vector<std::vector<double>> nums);

  // Конструктор по вектору векторов с добавлением
  // строки и столбца номеров вершин
  static AdjacencyMatrix WithExtraRowCol(std::vector<std::vector<double>> nums);

  enum Mins { Rows, Columns };

  // Копирующее присваивание для матрицы
  AdjacencyMatrix& operator=(const AdjacencyMatrix& m);

  // Изменение элемента матрицы
  void SetMatrixValue(std::size_t i, std::size_t j, double num);

  // Возвращает размер матрицы
  std::size_t GetSize() const { return size_; }

  // Возвращает элемент матрицы
  double GetMatrixValue(std::size_t i, std::size_t j) const {
    return matrix_[i][j];
  }

  // Возвращает оценку расстояния
  double GetBottomLineEvaluation() const { return evaluation_; }

  // Возвращает выбранное на данной итерации
  // ребро для последующего рассмотрения
  std::pair<std::size_t, std::size_t> GetSelectedEdge() const {
    return selected_edge_;
  }

  // Возвращает выбранное на данной итерации
  // значение матрицы для последующего рассмотрения
  std::pair<std::size_t, std::size_t> GetSelectedValue() const {
    return selected_value_;
  }
  // Возвращает минор матрицы(без i-той строки и j-того столбца)
  AdjacencyMatrix Minor(std::size_t i, std::size_t j);

  // Возвращает редуцированную версию матрицы
  AdjacencyMatrix Reducted();

  // Считает данные для матрицы
  void CalculateData();

 private:
  // Размер матрицы
  std::size_t size_;
  // Матрица
  std::vector<std::vector<double>> matrix_;
  // Редуцированная версия матрицы
  std::vector<std::vector<double>> reducted_matrix_;
  // Минимальный элемент в каждой строке и в каждом столбце
  std::vector<double> min_numbers_;
  // Оценка пути для данной матрицы
  double evaluation_ = 0;
  // Ребро, которое выбирается для следующего шага в алгоритме Литтла
  std::pair<std::size_t, std::size_t> selected_edge_;
  // Значение матрицы, которое выбирается для следующего шага в алгоритме
  // Литтла
  std::pair<std::size_t, std::size_t> selected_value_;

  // Найти 2 минимума в строке или столбце
  Minimums FindTwoMinimums(Mins type, std::size_t index) const;

  // Редуцирует матрицу сначала по строкам, затем по столбцам
  // Находит нижнюю оценку для матрицы
  double BottomLineEvaluation();

  // Возвращает позицию нуля с наибольшей степенью(сумма минимального элемента
  // в этой же строке и в этом же столбце)
  std::pair<std::size_t, std::size_t> HighestPowerOfZero() const;
};
