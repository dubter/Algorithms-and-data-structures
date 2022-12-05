// Ford Falkerson
// Задан ориентированный граф, каждое ребро которого обладает целочисленной пропускной способностью. Найдите максимальный поток из вершины с номером 1 в вершину с номером n.
// В этой задаче необходимо реализовать алгоритм Форда-Фалкерсона.

// Формат ввода
// Первая строка входного файла содержит n и m — количество вершин и количество ребер графа (2 ≤ n ≤ 100, 1 ≤ m ≤ 1000). Следующие m строк содержат по три числа: номера вершин, которые соединяет соответствующее ребро графа и его пропускную способность. Пропускные способности не превосходят 105.
// Формат вывода
// В выходной файл выведите одно число — величину максимального потока из вершины с номером 1 в вершину с номером n.

#include <iostream>
#include <vector>

enum COLOUR { WHITE, GRAY, BLACK };

class Edge {
 public:
  Edge(size_t from, size_t to, size_t flow, size_t bandwidth, size_t back_edge)
      : from_(from), to_(to), flow_(flow), bandwidth_(bandwidth), back_edge_(back_edge){};
  size_t from_;
  size_t to_;
  size_t flow_;
  size_t bandwidth_;
  size_t back_edge_;
};

class Graph {
 public:
  explicit Graph(size_t size) : adjacency_list_(size), colours_(size){};

  void InsertOrientEdge(size_t from, size_t to, size_t bandwidth) {
    adjacency_list_[from].emplace_back(from, to, 0, bandwidth, adjacency_list_[to].size());
    adjacency_list_[to].emplace_back(to, from, 0, 0, adjacency_list_[from].size() - 1);
  }

  size_t FindFlow(size_t cur_ver, size_t finish, size_t cur_flow) {
    if (cur_ver == finish) {
      return cur_flow;
    }
    colours_[cur_ver] = GRAY;
    for (auto &cur_edge : adjacency_list_[cur_ver]) {
      if (colours_[cur_edge.to_] == WHITE && cur_edge.bandwidth_ - cur_edge.flow_ > 0) {
        size_t result_flow = FindFlow(cur_edge.to_, finish, std::min(cur_flow, cur_edge.bandwidth_ - cur_edge.flow_));
        if (result_flow > 0) {
          cur_edge.flow_ += result_flow;
          adjacency_list_[cur_edge.to_][cur_edge.back_edge_].flow_ -= result_flow;
          return result_flow;
        }
      }
    }
    colours_[cur_ver] = BLACK;
    return 0;
  }

  size_t MaxFlow(size_t start, size_t finish) {
    size_t max_flow = 0;  // 0 шаг
    for (;;) {
      UpdateColours();
      size_t flow = FindFlow(start, finish, max_flow_);  // 1 шаг
      max_flow += flow;                                  // 2 шаг
      if (flow == 0) {                                   // 3 шаг
        return max_flow;
      }
    }
  }

  void UpdateColours() {
    for (auto &colour : colours_) {
      colour = WHITE;
    }
  }

 private:
  std::vector<std::vector<Edge>> adjacency_list_;
  std::vector<COLOUR> colours_;
  const size_t max_flow_ = 100000001;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t number_vertexes, number_edges;
  size_t ver_from, ver_to, bandwidth;
  std::cin >> number_vertexes >> number_edges;
  Graph graph(number_vertexes);
  for (size_t i = 0; i < number_edges; ++i) {
    std::cin >> ver_from >> ver_to >> bandwidth;
    graph.InsertOrientEdge(--ver_from, --ver_to, bandwidth);
  }
  std::cout << graph.MaxFlow(0, number_vertexes - 1);
  return 0;
}