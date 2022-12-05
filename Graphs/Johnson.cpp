// Урбанист Варлам Ильинов каждый день катается на своем велосипеде по городу, оценивая качество велосипедных дорог, а также доступность его любимых кофеен. За годы своих трудов он смог составить подробную карту каждого района и выяснить за какое время он сможет добраться от одной кофейни до другой. Кроме того, если от одной кофейни до другой есть трамвайная линия, то он впадает в неистовый восторг и считает, что время на этом пути не тратится, а наоборот приобретается.
// Теперь он хочет измерить удобность транспортной инфраструктуры. Чем меньше максимальное расстояние между кофейнями, тем более удобным считается город. При этом, если от одной кофейни нельзя добраться до другой ни по велосипедным дорожкам, ни с помощью трамвая, то такая (упорядоченная) пара игнорируется при подсчете удобности.
// Необходимо найти пару кофеен, кратчайшее расстояние от одной из которых до другой максимально среди всех пар, между которыми есть какой-либо путь.

// Формат ввода
// В первой строке вводятся числа N и M (1 ≤ N ≤ 10^3, 1 ≤ M ≤ 5 ⋅ N) — количество кофеен и общее количество велосипедных дорожек и трамвайных путей. В следующих M строках задаются числа a, b, w, что означает наличие пути от кофейни a до кофейни b длины w ∈ [-100, 100] (но не наоборот!). Кофейни нумеруются с 0. Кольцевых трамвайных линий в городе не предусмотрено.
// Формат вывода
// Выведите искомое максимальное конечное кратчайшее расстояние между кофейнями.

#include <iostream>
#include <vector>
#include <algorithm>

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

class Heap {
 private:
  std::vector<std::pair<int, size_t>> heap_;
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

  void Insert(std::pair<int, size_t> ver) {
    heap_.push_back(ver);
    ++size_;
    SiftUp(size_ - 1);
  }

  std::pair<int, size_t> ExtractMin() {
    --size_;
    std::pair<int, size_t> root = heap_[0];
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
  explicit Graph(size_t size) : adjacency_list_(size), matrix_dist_(size - 1), distance_(size, max_dist_) {
    for (size_t i = 0; i < size - 1; ++i) {
      matrix_dist_[i].resize(size, max_dist_);
    }
  }

  void AddOrientEdge(size_t first_ver, size_t second_ver, int value) {
    adjacency_list_[first_ver].emplace_back(first_ver, second_ver, value);
  }

  void Dijkstra(size_t ver) {
    distance_.assign(adjacency_list_.size(), max_dist_);
    distance_[ver] = 0;
    std::vector<int> prev(adjacency_list_.size(), -1);
    std::vector<bool> used(adjacency_list_.size(), false);
    Heap heap;
    for (size_t i = 0; i < adjacency_list_.size(); ++i) {
      heap.Insert(std::make_pair(distance_[i], i));
    }
    std::pair<int, size_t> pair;
    while (!heap.Empty()) {
      pair = heap.ExtractMin();
      if (distance_[pair.second] != pair.first) {
        continue;
      }
      used[pair.second] = true;
      for (auto &neighbour_edge : adjacency_list_[pair.second]) {
        if (!used[neighbour_edge.second_ver_] &&
            neighbour_edge.weight_ + distance_[pair.second] < distance_[neighbour_edge.second_ver_]) {
          prev[neighbour_edge.second_ver_] = static_cast<int>(pair.second);
          distance_[neighbour_edge.second_ver_] = neighbour_edge.weight_ + distance_[pair.second];
          heap.Insert(std::make_pair(distance_[neighbour_edge.second_ver_], neighbour_edge.second_ver_));
        }
      }
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
    for (size_t i = 0; i < distance_.size(); ++i) {
      for (size_t k = 0; k < distance_.size(); ++k) {
        for (auto &edge : adjacency_list_[k]) {
          Relax(edge);
        }
      }
    }
  }

  void Johnson() {
    for (size_t i = 1; i < adjacency_list_.size(); ++i) {
      adjacency_list_[0].emplace_back(0, i, 0);
    }
    BellmanFord(0);
    potential_ = distance_;
    for (auto &ver : adjacency_list_) {
      for (auto &edge : ver) {
        edge.weight_ = edge.weight_ + potential_[edge.first_ver_] - potential_[edge.second_ver_];
      }
    }
    for (size_t ver = 1; ver < adjacency_list_.size(); ++ver) {
      Dijkstra(ver);
      for (size_t i = 1; i < adjacency_list_.size(); ++i) {
        if (distance_[i] != max_dist_) {
          matrix_dist_[ver - 1][i - 1] = distance_[i] + potential_[i] - potential_[ver];
        }
      }
    }
  }

  int MaxShortestDistance() {
    int max = -100;
    for (size_t i = 0; i < adjacency_list_.size() - 1; ++i) {
      for (size_t j = 0; j < adjacency_list_.size() - 1; ++j) {
        if (max < matrix_dist_[i][j] && matrix_dist_[i][j] != max_dist_) {
          max = matrix_dist_[i][j];
        }
      }
    }
    return max;
  }

 private:
  const int max_dist_ = 100001;
  std::vector<std::vector<Edge>> adjacency_list_;
  std::vector<std::vector<int>> matrix_dist_;
  std::vector<int> distance_;
  std::vector<int> potential_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t number_coffee, number_roads;
  size_t first_ver, second_ver;
  int value;
  std::cin >> number_coffee >> number_roads;
  Graph graph(number_coffee + 1);
  for (size_t i = 0; i < number_roads; ++i) {
    std::cin >> first_ver >> second_ver >> value;
    graph.AddOrientEdge(first_ver + 1, second_ver + 1, value);
  }
  graph.Johnson();
  std::cout << graph.MaxShortestDistance();
  return 0;
}