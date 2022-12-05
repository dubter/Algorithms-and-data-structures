// Требуется найти в связном графе остовное дерево минимального веса. Задачу решайте с помощью алгоритма Прима

// Формат ввода
// Первая строка входного файла содержит два натуральных числа n и m — количество вершин и ребер графа соответственно (1 ≤ n ≤ 20000, 0 ≤ m ≤ 100000). Следующие m строк содержат описание ребер по одному на строке. Ребро номер i описывается тремя натуральными числами bi, ei и wi — номера концов ребра и его вес соответственно (1 ≤ bi, ei ≤ n, 0 ≤ wi ≤ 100000).
// Формат вывода
// Выведите единственное целое число — вес минимального остовного дерева.

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

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
 private:
  std::vector<std::vector<size_t>> adjacency_list_;
  std::map<std::pair<size_t, size_t>, size_t> weight_of_edges_;
  std::vector<std::pair<size_t, size_t>> min_ost_tree_;

 public:
  explicit Graph(size_t size) : adjacency_list_(size) {
  }

  std::pair<size_t, size_t> ReturnEdge(size_t first_ver, size_t second_ver) const {
    if (first_ver > second_ver) {
      return std::make_pair(second_ver, first_ver);
    }
    return std::make_pair(first_ver, second_ver);
  }

  void AddNoOrientEdge(size_t first_ver, size_t second_ver, size_t value) {
    if (weight_of_edges_.find(ReturnEdge(first_ver, second_ver)) == weight_of_edges_.end()) {
      adjacency_list_[first_ver].push_back(second_ver);
      adjacency_list_[second_ver].push_back(first_ver);
      weight_of_edges_[ReturnEdge(first_ver, second_ver)] = value;
    } else {
      weight_of_edges_[ReturnEdge(first_ver, second_ver)] =
          std::min(weight_of_edges_[ReturnEdge(first_ver, second_ver)], value);
    }
  }

  size_t Prim() {
    size_t weight_of_min_ost = 0;
    const size_t max_weight = 100001;
    std::vector<size_t> dist(adjacency_list_.size(), max_weight);
    dist[0] = 0;
    std::vector<int> prev(adjacency_list_.size(), -1);
    std::vector<bool> used(adjacency_list_.size(), false);
    Heap heap;
    for (size_t i = 0; i < adjacency_list_.size(); ++i) {
      heap.Insert(std::make_pair(dist[i], i));
    }
    std::pair<size_t, size_t> pair;
    while (!heap.Empty()) {
      pair = heap.ExtractMin();
      if (dist[pair.second] != pair.first) {
        continue;
      }
      used[pair.second] = true;
      if (prev[pair.second] != -1) {
        min_ost_tree_.push_back(ReturnEdge(prev[pair.second], pair.second));
      }
      for (auto &u : adjacency_list_[pair.second]) {
        if (!used[u] && weight_of_edges_[ReturnEdge(u, pair.second)] < dist[u]) {
          prev[u] = static_cast<int>(pair.second);
          dist[u] = weight_of_edges_[ReturnEdge(u, pair.second)];
          heap.Insert(std::make_pair(dist[u], u));
        }
      }
    }
    for (auto edge : min_ost_tree_) {
      weight_of_min_ost += weight_of_edges_[edge];
    }
    return weight_of_min_ost;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t amount_of_vertexes, amount_of_edges;
  size_t first_vertex, second_vertex, value_of_edge;
  std::cin >> amount_of_vertexes >> amount_of_edges;
  Graph graph(amount_of_vertexes);
  for (size_t i = 0; i < amount_of_edges; ++i) {
    std::cin >> first_vertex >> second_vertex >> value_of_edge;
    graph.AddNoOrientEdge(--first_vertex, --second_vertex, value_of_edge);
  }
  std::cout << graph.Prim();
  return 0;
}
