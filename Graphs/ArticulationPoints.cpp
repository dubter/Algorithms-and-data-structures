// Найдите точки сочленения в неориентированном графе.

// Формат ввода
// Первая строка входного файла содержит два натуральных числа n и m — количества вершин и рёбер графа соответственно (1 ≤ n ≤ 20000, 1 ≤ m ≤ 200000).
// Ребро номер i описывается двумя натуральными числами bi, ei — номерами концов ребра (1 ≤ bi, ei ≤ n).
// Формат вывода
// Первая строка выходного файла должна содержать одно натуральное число b — количество точек сочленения в заданном графе. На следующих b строках выведите b целых чисел — номера вершин, которые являются точками сочленения, в возрастающем порядке.

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

enum COLOURS { WHITE, GRAY, BLACK };

class Graph {
 private:
  std::vector<std::vector<size_t>> adjacency_list_;
  std::vector<COLOURS> colours_;
  std::vector<size_t> time_in_;
  std::vector<size_t> time_up_;
  std::set<size_t> articulation_points_;

 public:
  explicit Graph(size_t size) : adjacency_list_(size), colours_(size, WHITE), time_in_(size), time_up_(size) {
  }

  void AddNewNoOrientEdge(size_t ver_first, size_t ver_second) {
    adjacency_list_[ver_second].push_back(ver_first);
    adjacency_list_[ver_first].push_back(ver_second);
  }

  void DFS(size_t ver, bool is_root, size_t time, size_t amount_of_children) {
    colours_[ver] = GRAY;
    time_in_[ver] = time_up_[ver] = time++;
    for (size_t u : adjacency_list_[ver]) {
      if (colours_[u] == GRAY) {
        time_up_[ver] = std::min(time_up_[ver], time_in_[u]);
      }
      if (colours_[u] == WHITE) {
        if (is_root) {
          ++amount_of_children;
        }
        DFS(u, false, time, amount_of_children);
        time_up_[ver] = std::min(time_up_[ver], time_up_[u]);
        if (!is_root && time_in_[ver] <= time_up_[u]) {
          if (articulation_points_.find(ver) == articulation_points_.end()) {
            articulation_points_.emplace(ver);
          }
        }
      }
    }
    if (is_root && amount_of_children > 1) {
      if (articulation_points_.find(ver) == articulation_points_.end()) {
        articulation_points_.emplace(ver);
      }
    }
    colours_[ver] = BLACK;
  }

  void CountAllArticulationPoints() {
    for (size_t ver = 0; ver < adjacency_list_.size(); ++ver) {
      if (colours_[ver] == WHITE) {
        DFS(ver, true, 0, 0);
      }
    }
  }

  size_t GetAmountArticulationPoints() const {
    return articulation_points_.size();
  }

  void PrintAllArticulationPointsInSortedOrder() {
    for (size_t u : articulation_points_) {
      std::cout << u + 1 << "\n";
    }
  }
};

int main() {
  size_t amount_of_vertexes, amount_of_edges;
  size_t ver_first, ver_second;
  std::cin >> amount_of_vertexes >> amount_of_edges;
  Graph graph(amount_of_vertexes);
  for (size_t i = 0; i < amount_of_edges; ++i) {
    std::cin >> ver_first >> ver_second;
    graph.AddNewNoOrientEdge(--ver_first, --ver_second);
  }
  graph.CountAllArticulationPoints();
  std::cout << graph.GetAmountArticulationPoints() << "\n";
  graph.PrintAllArticulationPointsInSortedOrder();
  return 0;
}