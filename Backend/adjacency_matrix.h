#include <vector>

// Структура для хранения двух минимумов строки/столбца
struct Minimums {
  float first;
  float second;
};

class AdjacencyMatrix {
 public:
  AdjacencyMatrix(size_t size) : n{size} {
    matrix.resize(n);
    for (auto elem : matrix) {
      elem.resize(n, 0.0);
    }
  }

  AdjacencyMatrix(std::vector<std::vector<float>> nums)
      : matrix{nums}, n{nums.size()} {
    min_numbers.resize(n + n);
    BottomLineEvaluations();
  }
  enum Mins { Rows, Columns };

  // Изменение элемента матрицы
  void SetMatrixValue(int i, int j, float num);

  // Возвращает 2 числа: первую и вторую(без одного ребра) оценки расстояний
  std::pair<float, float> GetBottomLineEvaluations() const;

  // Возвращает минор матрицы(без i-той строки и j-того столбца)
  AdjacencyMatrix Minor(int i, int j);

 private:
  // Размер матрицы
  size_t n;

  std::vector<std::vector<float>> matrix;
  // Минимальный элемент в каждой строке и в каждом столбце
  std::vector<float> min_numbers;
  // Оценки пути для данной матрицы(первая и более точная)
  std::pair<float, float> evaluation;

  // Возвращает 2 числа: Первая оценка снизу и вторая, более точная оценка снизу
  void BottomLineEvaluations();

  // Найти 2 минимума в стоке или столбце
  Minimums FindTwoMinimums(Mins type, int index) const;

  // Вычитает из каждой строки минимальный элемент этой строки, находит
  // второй минимальный элемент. Возвращаеет сумму минимальных элементов по
  // строкам
  float ReductionLine();

  // Вычитает из каждого столбца минимальный элемент этого столбца, находит
  // второй минимальный элемент. Возвращаеет сумму минимальных элементов по
  // столбцам
  float ReductionColumn();

  // Возвращает позицию нуля с наибольшей степенью(сумма минимального элемента в
  // этой же строке и в этом же столбце)
  std::pair<int, int> HighestPowerOfZero() const;
};
