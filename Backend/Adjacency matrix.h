#include <vector>

class AdjacencyMatrix {
 public:
  AdjacencyMatrix(std::vector<std::vector<float>> nums)
      : matrix{nums}, rows{nums.size()}, cols{nums[0].size()} {
    min_numbers.resize(rows + cols);
  }

  // Возвращает 2 числа: первую и вторую(без одного ребра) оценки расстояний
  std::pair<float, float> GetBottomLineAssessments() const;

  // Возвращает минор матрицы(без i-той строки и j-того столбца)
  AdjacencyMatrix Minor(int i, int j);

 private:
  size_t rows, cols;
  std::vector<std::vector<float>> matrix;
  // Минимальный элемент в каждой строке и в каждом столбце
  std::vector<float> min_numbers;
  // Оценки пути для данной матрицы(первая и более точная)
  std::pair<float, float> assessment;

  // Возвращает 2 числа: Первая оценка снизу и вторая, более точная оценка снизу
  void BottomLineAssessments();

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
