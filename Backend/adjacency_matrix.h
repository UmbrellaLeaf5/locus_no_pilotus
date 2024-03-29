#pragma once

#include <vector>

// Структура для хранения двух минимумов строки/столбца
struct Minimums {
  double first;
  double second;
};

class AdjacencyMatrix {
 public:
  AdjacencyMatrix(size_t size) : _size{size}, _min_numbers(_size + _size) {
    _matrix.resize(_size + 1);
    for (auto& elem : _matrix) {
      elem.resize(_size + 1, 0.0);
    }
    for (size_t i = 0; i < _size; ++i) {
      _matrix[i][_size] = i;
      _matrix[_size][i] = i;
    }
    _min_numbers.resize(_size + _size);
  }

  // Конструктор по вектору векторов
  // Зависит от того, является ли полученная матрица минором
  AdjacencyMatrix(std::vector<std::vector<double>> nums, bool is_minor = false);

  enum Mins { Rows, Columns };

  // Копирующее присваивание для матрицы
  AdjacencyMatrix& operator=(const AdjacencyMatrix& m);

  // Изменение элемента матрицы
  void SetMatrixValue(size_t i, size_t j, double num);

  // Возвращает размер матрицы
  size_t GetSize() const { return _size; }

  // Возвращает элемент матрицы
  double GetMatrixValue(size_t i, size_t j) const { return _matrix[i][j]; }

  // Возвращает оценку расстояния
  double GetBottomLineEvaluation() const { return _evaluation; }

  // Возвращает выбранное на данной итерации
  // ребро для последующего рассмотрения
  std::pair<size_t, size_t> GetSelectedEdge() const { return _selected_edge; }

  // Возвращает выбранное на данной итерации
  // значение матрицы для последующего рассмотрения
  std::pair<size_t, size_t> GetSelectedValue() const { return _selected_value; }
  // Возвращает минор матрицы(без i-той строки и j-того столбца)
  AdjacencyMatrix Minor(size_t i, size_t j);

  // Возвращает редуцированную версию матрицы
  AdjacencyMatrix Reducted();

  // Считает данные для матрицы
  void CalculateData();

 private:
  // Размер матрицы
  size_t _size;
  // Матрица
  std::vector<std::vector<double>> _matrix;
  // Редуцированная версия матрицы
  std::vector<std::vector<double>> _reducted_matrix;
  // Минимальный элемент в каждой строке и в каждом столбце
  std::vector<double> _min_numbers;
  // Оценка пути для данной матрицы
  double _evaluation = 0;
  // Ребро, которое выбирается для следующего шага в алгоритме Литтла
  std::pair<size_t, size_t> _selected_edge;
  // Значение матрицы, которое выбирается для следующего шага в алгоритме
  // Литтла
  std::pair<size_t, size_t> _selected_value;

  // Найти 2 минимума в строке или столбце
  Minimums FindTwoMinimums(Mins type, size_t index) const;

  // Редуцирует матрицу сначала по строкам, затем по столбцам
  // Находит нижнюю оценку для матрицы
  double BottomLineEvaluation();

  // Возвращает позицию нуля с наибольшей степенью(сумма минимального элемента
  // в этой же строке и в этом же столбце)
  std::pair<size_t, size_t> HighestPowerOfZero() const;
};
