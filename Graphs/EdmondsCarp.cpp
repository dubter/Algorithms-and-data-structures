// Edmonds Carp
// Задан ориентированный граф, каждое ребро которого обладает целочисленной пропускной способностью. Найдите максимальный поток из вершины с номером 1 в вершину с номером n.
// В этой задаче необходимо реализовать алгоритм Эдмондса-Карпа.

// Формат ввода
// Первая строка входного файла содержит n и m — количество вершин и количество ребер графа (2 ≤ n ≤ 500, 1 ≤ m ≤ 10000). Следующие m строк содержат по три числа: номера вершин, которые соединяет соответствующее ребро графа и его пропускную способность. Пропускные способности не превосходят 109.
// Формат вывода
// В выходной файл выведите одно число - величину максимального потока из вершины с номером 1 в вершину с номером n.


#include <iostream>
#include <queue>
#include <map>
#include <vector>

class Graph {
 public:
  explicit Graph(size_t size) : adj_list_(size), prev_(size, -1){};

  void InsertOrientEdge(size_t first_ver, size_t second_ver, size_t bandwidth) {
    adj_list_[first_ver][second_ver] = bandwidth;
  }

  void UpdatePrevs() {
    for (auto &elem : prev_) {
      elem = -1;
    }
  }

  size_t FindFlow(size_t start, size_t finish) {
    UpdatePrevs();
    std::queue<std::pair<size_t, size_t>> queue;
    queue.push(std::make_pair(start, max_flow_));
    prev_[start] = -2;
    size_t flow, cur_ver;
    size_t new_flow;
    while (!queue.empty()) {
      flow = queue.front().second;
      cur_ver = queue.front().first;
      queue.pop();
      for (auto neighbours : adj_list_[cur_ver]) {
        if (prev_[neighbours.first] == -1 && neighbours.second != 0) {  // условие: ещё не встречали данную вершину
          prev_[neighbours.first] = static_cast<int>(cur_ver);
          new_flow = std::min(flow, neighbours.second);
          if (neighbours.first == finish) {
            return new_flow;
          }
          queue.emplace(std::make_pair(neighbours.first, new_flow));
        }
      }
    }
    return 0;
  }

  size_t EdmondsCarp(size_t start, size_t finish) {
    size_t max_flow = 0;  // 0 шаг
    int parent;
    size_t cur_ver;
    for (;;) {
      size_t flow = FindFlow(start, finish);  // 1 шаг
      max_flow += flow;                       // 2 шаг
      if (flow == 0) {                        // 3 шаг
        return max_flow;
      }
      cur_ver = finish;
      while (cur_ver != start) {
        parent = prev_[cur_ver];
        adj_list_[parent][cur_ver] -= flow;
        adj_list_[cur_ver][parent] += flow;
        cur_ver = parent;
      }
    }
  }

 private:
  const size_t max_flow_ = 1000000001;
  std::vector<std::map<size_t, size_t>> adj_list_;
  std::vector<int> prev_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t number_vertexes, number_edges;
  size_t first_ver, second_ver, bandwidth;
  std::cin >> number_vertexes >> number_edges;
  const size_t start = 0, finish = number_vertexes - 1;
  Graph graph(number_vertexes);
  for (size_t i = 0; i < number_edges; ++i) {
    std::cin >> first_ver >> second_ver >> bandwidth;
    graph.InsertOrientEdge(--first_ver, --second_ver, bandwidth);
  }
  std::cout << graph.EdmondsCarp(start, finish);
  return 0;
}