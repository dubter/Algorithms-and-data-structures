// Полный ориентированный взвешенный граф задан матрицей смежности. Постройте матрицу кратчайших путей между его вершинами. Гарантируется, что в графе нет циклов отрицательного веса.

// Формат ввода
// В первой строке вводится единственное число N (1 ≤ N ≤ 100) — количество вершин графа. В следующих N строках по N чисел задается матрица смежности графа (j-е число в i-й строке соответствует весу ребра из вершины i в вершину j). Все числа по модулю не превышают 100. На главной диагонали матрицы всегда нули.
// Формат вывода
// Выведите N строк по N чисел — матрицу кратчайших расстояний между парами вершин. j-е число в i-й строке должно быть равно весу кратчайшего пути из вершины i в вершину j.

#include <iostream>
#include <vector>

class Graph {
 private:
  std::vector<std::vector<int>> arj_matrix_;
  std::vector<std::vector<int>> shortest_weights_;

 public:
  explicit Graph(std::vector<std::vector<int>> &arj_matrix) : arj_matrix_(arj_matrix), shortest_weights_(arj_matrix) {
  }
  std::vector<std::vector<int>> &FLoydWarshall() {
    for (size_t k = 0; k < arj_matrix_.size(); ++k) {
      for (size_t x = 0; x < arj_matrix_.size(); ++x) {
        for (size_t y = 0; y < arj_matrix_.size(); ++y) {
          shortest_weights_[x][y] =
              std::min(shortest_weights_[x][y], shortest_weights_[x][k] + shortest_weights_[k][y]);
        }
      }
    }
    return shortest_weights_;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t number_vertexes;
  std::cin >> number_vertexes;
  std::vector<std::vector<int>> arj_matrix(number_vertexes);
  for (size_t i = 0; i < number_vertexes; ++i) {
    arj_matrix[i].resize(number_vertexes);
  }
  for (size_t i = 0; i < number_vertexes; ++i) {
    for (size_t j = 0; j < number_vertexes; ++j) {
      std::cin >> arj_matrix[i][j];
    }
  }
  Graph graph(arj_matrix);
  std::vector<std::vector<int>> weights(graph.FLoydWarshall());
  for (size_t i = 0; i < number_vertexes; ++i) {
    for (size_t j = 0; j < number_vertexes; ++j) {
      std::cout << weights[i][j] << " ";
    }
    std::cout << "\n";
  }
  return 0;
}