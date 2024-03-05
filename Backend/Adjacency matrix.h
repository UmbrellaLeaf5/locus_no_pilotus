#include <vector>

class AdjacencyMatrix {
 public:
  // Тут будет конструктор по умолчанию(наверное)
  AdjacencyMatrix(std::vector<std::vector<float>> nums)
      : matrix{nums}, rows{nums.size()}, cols{nums[0].size()} {}
  int CalculateTraectory();

 private:
  size_t rows, cols;
  std::vector<std::vector<float>> matrix;

  float ReductionLine();

  float ReductionColumn();

  // Возвращает минор матрицы(без i-той строки и j-того столбца)
  AdjacencyMatrix Minor(int i, int j);
};
