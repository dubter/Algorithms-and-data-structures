// Дан ориентированный взвешенный граф. Найдите кратчайшее расстояние от одной заданной вершины до другой.

// Формат ввода
// В первой строке входного файла два числа: N и M (1 ≤ N ≤ 100, 1 ≤ M ≤ 10000), где N — количество вершин графа, а M — количество ребер.
// В следующей строке заданы числа S и F — начальная и конечная вершины.
// Далее следует M троек чисел Ai, Bi, Ti (1 ≤ Ti ≤ 10) — номера вершин соединенных ребром и вес данного ребра.
// Формат вывода
// Вывести искомое расстояние или -1, если пути между указанными вершинами не существует.

#include <iostream>
#include <queue>
#include <vector>

class Graph {
 public:
  explicit Graph(int size_n) : distance_(size_n, max_distance_), is_visited_(size_n, false), adj_(size_n){};
  void InsertEdgeOrient(uint16_t ver_first, uint16_t ver_second, uint16_t weight);
  void MinDistance(uint16_t start_ver);
  int GetDistance(int end_ver) const;

 private:
  struct Ver {
    uint16_t ver;
    uint16_t weight;
  };
  const int max_distance_ = 5000;
  std::vector<int> distance_;
  std::vector<bool> is_visited_;
  std::vector<std::vector<Ver>> adj_;
};

void Graph::InsertEdgeOrient(uint16_t ver_first, uint16_t ver_second, uint16_t weight) {
  Ver new_ver = {ver_second, weight};
  adj_[ver_first].push_back(new_ver);
}

void Graph::MinDistance(uint16_t start_ver) {
  distance_[start_ver] = 0;
  std::vector<std::queue<uint16_t>> q(max_distance_);
  q[0].push(start_ver);
  for (int i = 0; i < static_cast<int>(q.size()); ++i) {
    while (!q[i].empty()) {
      int v = q[i].front();
      q[i].pop();
      if (is_visited_[v]) {
        continue;
      }
      is_visited_[v] = true;
      for (auto &u : adj_[v]) {
        int to = u.ver;
        if (distance_[to] > distance_[v] + u.weight) {
          distance_[to] = distance_[v] + u.weight;
          q[distance_[to]].push(to);
        }
      }
    }
  }
}

int Graph::GetDistance(int end_ver) const {
  if (distance_[end_ver] == max_distance_) {
    return -1;
  }
  return distance_[end_ver];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  uint16_t ver_first = 0;
  uint16_t ver_second = 0;
  uint16_t weight = 0;
  std::cin >> n >> m;
  int start_ver = 0;
  int end_ver = 0;
  std::cin >> start_ver >> end_ver;
  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    std::cin >> ver_first >> ver_second >> weight;
    graph.InsertEdgeOrient(--ver_first, --ver_second, weight);
  }
  graph.MinDistance(--start_ver);
  std::cout << graph.GetDistance(--end_ver);
  return 0;
}