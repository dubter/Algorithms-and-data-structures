// Дан ориентированный граф, в котором могут быть кратные ребра и петли. Каждое ребро имеет вес, выражающийся целым числом (возможно, отрицательным). Гарантируется, что циклы отрицательного веса отсутствуют.
// Требуется посчитать длины кратчайших путей от вершины номер 1 до всех остальных вершин.

// Формат ввода
// Программа получает сначала число N (1 ≤ N ≤ 100) — количество вершин графа и число M (0 ≤ M ≤ 10000) — количество ребер. В следующих строках идет M троек чисел, описывающих ребра: начало ребра, конец ребра и вес (вес — целое число от -100 до 100).
// Формат вывода
// Программа должна вывести N чисел — расстояния от вершины номер 1 до всех вершин графа. Если пути до соответствующей вершины не существует, вместо длины пути выведите число 30000.

#include <iostream>
#include <vector>

class Edge {
 public:
  size_t first_ver_;
  size_t second_ver_;
  int weight_;
  Edge() = default;
  Edge(size_t first_ver, size_t second_ver, int weight)
      : first_ver_(first_ver), second_ver_(second_ver), weight_(weight) {
  }
};

class Graph {
 private:
  std::vector<int> distance_;
  std::vector<Edge> edges_;
  const int max_dist_ = 30000;

 public:
  explicit Graph(size_t size) : distance_(size, 30000) {
  }

  void AddOrientEdge(size_t first_ver, size_t second_ver, int weight) {
    if (first_ver != second_ver) {
      edges_.emplace_back(first_ver, second_ver, weight);
    }
  }

  bool Relax(const Edge &edge) {
    if (distance_[edge.first_ver_] != max_dist_) {
      if (distance_[edge.second_ver_] > distance_[edge.first_ver_] + edge.weight_) {
        distance_[edge.second_ver_] = distance_[edge.first_ver_] + edge.weight_;
        return true;
      }
    }
    return false;
  }

  void BellmanFord(size_t ver) {
    distance_[ver] = 0;
    for (size_t k = 0; k < distance_.size(); ++k) {
      for (auto &edge : edges_) {
        Relax(edge);
      }
    }
  }

  void PrintDistance() {
    BellmanFord(0);
    for (auto &dist : distance_) {
      std::cout << dist << " ";
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t number_vertexes, number_edges;
  size_t first_ver, second_ver;
  int weight;
  std::cin >> number_vertexes >> number_edges;
  Graph graph(number_vertexes);
  for (size_t i = 0; i < number_edges; ++i) {
    std::cin >> first_ver >> second_ver >> weight;
    graph.AddOrientEdge(--first_ver, --second_ver, weight);
  }
  graph.PrintDistance();
  return 0;
}
