// Напишите программу, которая будет находить расстояния в неориентированном взвешенном графе с неотрицательными длинами ребер, от указанной вершины до всех остальных. Программа должна работать быстро для больших разреженных графов.

// Формат ввода
// В первой строке входных данных задано число NUM — количество различных запусков алгоритма Дейкстры (на разных графах). Далее следуют NUM блоков, каждый из которых имеет следующую структуру.
// Первая строка блока содержит два числа N и M, разделенные пробелом — количество вершин и количество ребер графа. Далее следуют M строк, каждая из которых содержит по три целых числа, разделенные пробелами. Первые два из них в пределах от 0 до N - 1 каждое и обозначают концы соответствующего ребра, третье — в пределах от 0 до 20000 и обозначает длину этого ребра. Далее, в последней строке блока, записанное единственное число от 0 до N - 1 — вершина, расстояния от которой надо искать.
// Количество различных графов в одном тесте NUM не превышает 5. Количество вершин не превышает 60000, рёбер — 200000.
// Формат вывода
// Выведите в стандартный вывод NUM строк, в каждой из которых по Ni чисел, разделенных пробелами — расстояния от указанной начальной вершины взвешенного неориентированного графа до его 0-й, 1-й, 2-й и т. д. вершин (допускается лишний пробел после последнего числа). Если некоторая вершина недостижима от указанной начальной, вместо расстояния выводите число 2009000999 (гарантировано, что все реальные расстояния меньше).

#include <iostream>
#include <vector>
#include <algorithm>

class Edge {
 public:
  size_t first_ver_;
  size_t second_ver_;
  size_t weight_;
  Edge() = default;
  Edge(size_t first_ver, size_t second_ver, size_t weight)
      : first_ver_(first_ver), second_ver_(second_ver), weight_(weight) {
  }
};

class Heap {
 private:
  std::vector<std::pair<size_t, size_t>> heap_;
  int size_ = 0;

 public:
  void SiftUp(int index) {
    while ((index - 1) / 2 >= 0 && index > 0 && heap_[index].first < heap_[(index - 1) / 2].first) {
      std::swap(heap_[index], heap_[(index - 1) / 2]);
      index = (index - 1) / 2;
    }
  }

  void SiftDown(int index) {
    int left, right, j;
    while (2 * index + 1 < size_) {
      left = 2 * index + 1;
      right = 2 * index + 2;
      j = left;
      if (right < size_ && heap_[right].first < heap_[left].first) {
        j = right;
      }
      if (heap_[index].first <= heap_[j].first) {
        break;
      }
      std::swap(heap_[index], heap_[j]);
      index = j;
    }
  }

  void Insert(std::pair<size_t, size_t> ver) {
    heap_.push_back(ver);
    ++size_;
    SiftUp(size_ - 1);
  }

  std::pair<size_t, size_t> ExtractMin() {
    --size_;
    std::pair<size_t, size_t> root = heap_[0];
    heap_[0] = heap_.back();
    heap_.pop_back();
    SiftDown(0);
    return root;
  }

  bool Empty() const {
    return size_ == 0;
  }
};

class Graph {
 public:
  explicit Graph(size_t size) : adj_list_(size), dist_(size, max_dist_) {
  }

  void AddNoOrientEdge(size_t first_ver, size_t second_ver, size_t weight) {
    adj_list_[first_ver].emplace_back(first_ver, second_ver, weight);
    adj_list_[second_ver].emplace_back(second_ver, first_ver, weight);
  }

  void Dijkstra(size_t ver) {
    dist_[ver] = 0;
    std::vector<int> prev(adj_list_.size(), -1);
    std::vector<bool> used(adj_list_.size(), false);
    Heap heap;
    for (size_t i = 0; i < adj_list_.size(); ++i) {
      heap.Insert(std::make_pair(dist_[i], i));
    }
    std::pair<size_t, size_t> pair;
    while (!heap.Empty()) {
      pair = heap.ExtractMin();
      if (dist_[pair.second] != pair.first) {
        continue;
      }
      used[pair.second] = true;
      for (auto &u : adj_list_[pair.second]) {
        if (!used[u.second_ver_] && u.weight_ + dist_[pair.second] < dist_[u.second_ver_]) {
          prev[u.second_ver_] = static_cast<int>(pair.second);
          dist_[u.second_ver_] = u.weight_ + dist_[pair.second];
          heap.Insert(std::make_pair(dist_[u.second_ver_], u.second_ver_));
        }
      }
    }
  }

  void PrintDistance() {
    for (auto &dist : dist_) {
      std::cout << dist << " ";
    }
    std::cout << "\n";
  }

 private:
  const size_t max_dist_ = 2009000999;
  std::vector<std::vector<Edge>> adj_list_;
  std::vector<size_t> dist_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t num, start;
  size_t amount_of_vertexes, amount_of_edges;
  size_t first_vertex, second_vertex, value_of_edge;
  std::cin >> num;
  for (size_t j = 0; j < num; ++j) {
    std::cin >> amount_of_vertexes >> amount_of_edges;
    Graph graph(amount_of_vertexes);
    for (size_t i = 0; i < amount_of_edges; ++i) {
      std::cin >> first_vertex >> second_vertex >> value_of_edge;
      graph.AddNoOrientEdge(first_vertex, second_vertex, value_of_edge);
    }
    std::cin >> start;
    graph.Dijkstra(start);
    graph.PrintDistance();
  }
  return 0;
}