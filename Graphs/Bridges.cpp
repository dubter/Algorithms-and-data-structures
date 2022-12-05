// Дан неориентированный граф. Требуется найти все мосты в нем.

// Формат ввода
// В первой строке входного файла два натуральных числа n и m (1 ≤ n ≤ 20000, 1 ≤ m ≤ 200000) –количество вершин и рёбер в графе соответственно. Далее в m строках перечислены рёбра графа. Каждое ребро задается парой чисел – номерами начальной и конечной вершин соответственно.
// Формат вывода
// Первая строка выходного файла должна содержать одно натуральное число b – количество мостов в заданном графе. На следующей строке выведите b чисел – номера ребер, которые являются мостами, в возрастающем порядке. Ребра нумеруются с единицы в том порядке, в котором они заданы во входном файле.

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

enum COLOURS { WHITE, GRAY, BLACK };

class Graph {
 private:
  std::vector<std::vector<std::pair<size_t, size_t>>> adjacency_list_;
  std::vector<std::vector<size_t>> vertexes_without_index_;
  std::vector<COLOURS> colours_;
  std::vector<size_t> time_in_;
  std::vector<size_t> time_up_;
  std::set<size_t> bridges_;

 public:
  explicit Graph(size_t size)
      : adjacency_list_(size), vertexes_without_index_(size), colours_(size, WHITE), time_in_(size), time_up_(size) {
  }

  void AddNewNoOrientEdge(size_t ver_first, size_t ver_second, size_t index) {
    adjacency_list_[ver_second].emplace_back(index, ver_first);
    adjacency_list_[ver_first].emplace_back(index, ver_second);
    vertexes_without_index_[ver_second].push_back(ver_first);
    vertexes_without_index_[ver_first].push_back(ver_second);
  }

  void DFS(size_t ver, size_t time, int parent) {
    colours_[ver] = GRAY;
    time_in_[ver] = time_up_[ver] = time++;
    size_t u_ver, u_index_of_edge;
    for (std::pair u : adjacency_list_[ver]) {
      u_ver = u.second;
      u_index_of_edge = u.first;
      if (u_ver != static_cast<size_t>(parent) && colours_[u_ver] == GRAY) {
        time_up_[ver] = std::min(time_up_[ver], time_in_[u_ver]);
      }
      if (colours_[u_ver] == WHITE) {
        DFS(u_ver, time, static_cast<int>(ver));
        time_up_[ver] = std::min(time_up_[ver], time_up_[u_ver]);
        if (time_in_[ver] < time_up_[u_ver]) {
          if (bridges_.find(u_index_of_edge) == bridges_.end()) {
            if (std::count(vertexes_without_index_[ver].begin(), vertexes_without_index_[ver].end(), u_ver) == 1) {
              bridges_.emplace(u_index_of_edge);
            }
          }
        }
      }
    }
    colours_[ver] = BLACK;
  }

  void CountAllBridges() {
    for (size_t ver = 0; ver < adjacency_list_.size(); ++ver) {
      if (colours_[ver] == WHITE) {
        DFS(ver, 0, -1);
      }
    }
  }

  size_t GetAmountBridges() const {
    return bridges_.size();
  }

  void PrintAllBridgesInSortedOrder() {
    for (size_t u : bridges_) {
      std::cout << u << "\n";
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
    graph.AddNewNoOrientEdge(--ver_first, --ver_second, i + 1);
  }
  graph.CountAllBridges();
  std::cout << graph.GetAmountBridges() << "\n";
  graph.PrintAllBridgesInSortedOrder();
  return 0;
}