// Дан ориентированный граф. Определить, есть ли в нем цикл отрицательного веса, и если да, то вывести его.

// Формат ввода
// В первой строке содержится число N (1 ≤ N ≤ 100) — количество вершин графа. В следующих N строках находится по N чисел — матрица смежности графа. Веса ребер по модулю меньше 100000. Если ребра нет, соответствующее значение равно 100000.
// Формат вывода
// В первой строке выведите YES, если цикл существует, или NO, в противном случае.
// При наличии цикла выведите во второй строке количество вершин в нем (считая одинаковые — первую и последнюю), а в третьей строке — вершины, входящие в этот цикл, в порядке обхода. Если циклов несколько, то выведите любой из них.

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
  std::vector<int> parent_;
  std::vector<Edge> edges_;
  size_t last_relaxed_ = 0;
  const int max_dist_ = 100000;

 public:
  explicit Graph(size_t size) : distance_(size, 100000), parent_(size, -1) {
  }

  void AddOrientEdge(size_t first_ver, size_t second_ver, int weight) {
    edges_.emplace_back(first_ver, second_ver, weight);
  }

  bool Relax(const Edge &edge) {
    if (distance_[edge.first_ver_] != max_dist_) {
      if (distance_[edge.second_ver_] > distance_[edge.first_ver_] + edge.weight_) {
        distance_[edge.second_ver_] = distance_[edge.first_ver_] + edge.weight_;
        parent_[edge.second_ver_] = static_cast<int>(edge.first_ver_);
        last_relaxed_ = edge.second_ver_;
        return true;
      }
    }
    return false;
  }

  bool HasNegativeCycle(size_t ver) {
    distance_[ver] = 0;
    for (size_t k = 0; k < distance_.size(); ++k) {
      for (auto &edge : edges_) {
        Relax(edge);
      }
    }
    for (auto &edge : edges_) {
      if (Relax(edge)) {
        return true;
      }
    }
    return false;
  }

  void PrintNegativeCycle() {
    bool check_some_components_of_connectivity = false;
    for (size_t i = 0; i < distance_.size(); ++i) {
      if (HasNegativeCycle(i)) {
        check_some_components_of_connectivity = true;
        break;
      }
    }
    if (check_some_components_of_connectivity) {
      std::cout << "YES\n";
      size_t ver = last_relaxed_;
      for (size_t i = 0; i < distance_.size() - 1; ++i) {
        ver = parent_[ver];
      }
      std::vector<size_t> cycle;
      cycle.push_back(ver);
      size_t start = parent_[ver];
      while (start != ver) {
        cycle.push_back(start);
        start = parent_[start];
      }
      cycle.push_back(ver);
      std::cout << cycle.size() << "\n";
      for (size_t i = 0; i < cycle.size(); ++i) {
        std::cout << cycle[cycle.size() - i - 1] + 1 << " ";
      }
    } else {
      std::cout << "NO\n";
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  const size_t limit = 100000;
  size_t number_vertexes;
  int elem_from_adj;
  std::cin >> number_vertexes;
  Graph graph(number_vertexes);
  for (size_t i = 0; i < number_vertexes; ++i) {
    for (size_t j = 0; j < number_vertexes; ++j) {
      std::cin >> elem_from_adj;
      if (elem_from_adj != limit) {
        graph.AddOrientEdge(i, j, elem_from_adj);
      }
    }
  }
  graph.PrintNegativeCycle();
  return 0;
}
