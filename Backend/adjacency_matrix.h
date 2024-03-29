#pragma once

#include <vector>

// Структура для хранения двух минимумов строки/столбца
struct Minimums {
  float first;
  float second;
};

class AdjacencyMatrix {
 public:
  AdjacencyMatrix(size_t size) : n{size} {
    matrix.resize(n + 1);
    for (auto& elem : matrix) {
      elem.resize(n + 1, 0.0);
    }
    for (size_t i = 0; i < n; ++i) {
      matrix[i][n] = i;
      matrix[n][i] = i;
    }
    min_numbers.resize(n + n);
  }

  // Конструктор по вектору векторов
  // Зависит от того, является ли полученная матрица минором
  AdjacencyMatrix(std::vector<std::vector<float>> nums, bool is_minor = false);

  enum Mins { Rows, Columns };

  // Копирующее присваивание для матрицы
  AdjacencyMatrix& operator=(const AdjacencyMatrix& m);

  // Изменение элемента матрицы
  void SetMatrixValue(int i, int j, float num);

  // Возвращает размер матрицы
  int GetSize() const;

  // Возвращает оценку расстояния
  float GetBottomLineEvaluation() const;

  // Возвращает выбранное на данной итерации
  // ребро для последующего рассмотрения
  std::pair<int, int> GetSelectedEdge() const;

  // Возвращает выбранное на данной итерации
  // значение матрицы для последующего рассмотрения
  std::pair<int, int> GetSelectedValue() const;

  // Возвращает минор матрицы(без i-той строки и j-того столбца)
  AdjacencyMatrix Minor(int i, int j);

  // Возвращает редуцированную версию матрицы
  AdjacencyMatrix Reducted();

  // Считает данные для матрицы
  void CalculateData();

 private:
  // Размер матрицы
  size_t n;

  std::vector<std::vector<float>> matrix;
  // Редуцированная версия матрицы
  std::vector<std::vector<float>> reducted_matrix;
  // Минимальный элемент в каждой строке и в каждом столбце
  std::vector<float> min_numbers;
  // Оценка пути для данной матрицы
  float evaluation = 0;
  // Ребро, которое выбирается для следующего шага в алгоритме Литтла
  std::pair<int, int> selected_edge;
  // Значение матрицы, которое выбирается для следующего шага в алгоритме
  // Литтла
  std::pair<int, int> selected_value;

  // Найти 2 минимума в строке или столбце
  Minimums FindTwoMinimums(Mins type, int index) const;

  // Редуцирует матрицу сначала по строкам, затем по столбцам
  // Находит нижнюю оценку для матрицы
  float BottomLineEvaluation();

  // Возвращает позицию нуля с наибольшей степенью(сумма минимального элемента
  // в этой же строке и в этом же столбце)
  std::pair<int, int> HighestPowerOfZero() const;
};
