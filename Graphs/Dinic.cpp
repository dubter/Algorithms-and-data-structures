// Dinitsa

// Задан ориентированный граф, каждое ребро которого обладает целочисленной пропускной способностью. Найдите максимальный поток из вершины с номером 1 в вершину с номером n.

// В этой задаче необходимо реализовать алгоритм Диница.

// Формат ввода
// Первая строка входного файла содержит n и m — количество вершин и количество ребер графа (2 ≤ n ≤ 500, 1 ≤ m ≤ 10000). Следующие m строк содержат по три числа: номера вершин, которые соединяет соответствующее ребро графа и его пропускную способность. Пропускные способности не превосходят 109.
// Формат вывода
// В выходной файл выведите одно число - величину максимального потока из вершины с номером 1 в вершину с номером n.

#include <iostream>
#include <queue>
#include <vector>

class Edge {
 public:
  Edge(int64_t flow, int64_t bandwidth) : flow_(flow), bandwidth_(bandwidth){};
  Edge() = default;
  int64_t flow_;
  int64_t bandwidth_;
};

class Graph {
 public:
  explicit Graph(int64_t size) : adj_list_(size, std::vector<Edge>(size)), dist_(size, max_value_) {
  }

  void InsertOrientEdge(int64_t from, int64_t to, int64_t bandwidth) {
    if (from != to) {
      adj_list_[from][to].bandwidth_ = bandwidth;
    }
  }
  void UpdateDistance() {
    for (auto &elem : dist_) {
      elem = max_value_;
    }
  }

  bool BuildNetwork(int64_t start_ver, int64_t finish) {
    int64_t ver;
    std::queue<int64_t> queue;
    UpdateDistance();
    queue.push(start_ver);
    dist_[start_ver] = 0;
    while (!queue.empty()) {
      ver = queue.front();
      queue.pop();
      for (int64_t i = 0; i < static_cast<int64_t>(adj_list_.size()); ++i) {
        if (dist_[i] == max_value_ && adj_list_[ver][i].flow_ < adj_list_[ver][i].bandwidth_) {
          queue.push(i);
          dist_[i] = dist_[ver] + 1;
        }
      }
    }
    return dist_[finish] != max_value_;
  }

  int64_t FindFlow(int64_t ver, int64_t finish, int64_t cur_flow) {
    if (cur_flow == 0) {
      return 0;
    }
    if (ver == static_cast<int64_t>(finish)) {
      return cur_flow;
    }
    for (int64_t to = 0; to < static_cast<int64_t>(adj_list_.size()); ++to) {
      if (dist_[to] != dist_[ver] + 1) {
        continue;
      }
      int64_t new_flow =
          FindFlow(to, finish, std::min(cur_flow, adj_list_[ver][to].bandwidth_ - adj_list_[ver][to].flow_));
      if (new_flow != 0) {
        adj_list_[ver][to].flow_ += new_flow;
        adj_list_[to][ver].flow_ -= new_flow;
        return new_flow;
      }
    }
    return 0;
  }

  int64_t Dinic(int64_t start, int64_t finish) {
    int64_t max_flow = 0;
    for (;;) {
      if (!BuildNetwork(start, finish)) {
        break;
      }
      for (;;) {
        int64_t new_flow = FindFlow(start, finish, max_value_);
        if (new_flow == 0) {
          break;
        }
        max_flow += new_flow;
      }
    }
    return max_flow;
  }

 private:
  const int64_t max_value_ = 5000000000001;
  std::vector<std::vector<Edge>> adj_list_;
  std::vector<int64_t> dist_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t number_vertexes, number_edges;
  int64_t first_ver, second_ver, bandwidth;
  std::cin >> number_vertexes >> number_edges;
  const int64_t start = 0, finish = number_vertexes - 1;
  Graph graph(number_vertexes);
  for (int64_t i = 0; i < number_edges; ++i) {
    std::cin >> first_ver >> second_ver >> bandwidth;
    graph.InsertOrientEdge(--first_ver, --second_ver, bandwidth);
  }
  std::cout << graph.Dinic(start, finish);
  return 0;
}