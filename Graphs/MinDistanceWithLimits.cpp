// Абитуриент Василий решил подать документы в ФПМИ. Так как Василий живёт достаточно далеко, он решил спланировать своё путешествие заранее.
// В результате долгих размышлений он пришёл к выводу, что на дорогу у него есть не более T минут, так как приёмная комиссия скоро закроется. Бюджет будущего студента также ограничен, поэтому он хочет ещё и потратить на своё путешествие поменьше денег.
// После ещё более долгих размышлений Василий составил карту из всех возможных путей с промежуточными пунктами (станции общественного транспорта или другие значимые для него объекты, до которых он гарантированно может добраться из дома). Карта представляет собой список из N пунктов, где дом Василия — это пункт с номером 1, а N -й пункт — приёмная комиссия. Между пунктами существует M переходов. Для каждого из них он написал стоимость Pi и время Ti. При этом гарантируется, что он всегда может добраться до приёмной комиссии.
// Между любыми двумя пунктами в карте Василия имеется не более одного прямого перехода. Некоторые из переходов могут быть бесплатными или занимать пренебрежительно малое время. При этом любой переход двусторонний, то есть стоимость перехода и время не зависят от того, движется ли Василий из пункта с номером A в пункт с номером B, или в обратном направлении.
// Помогите Василию найти минимальную стоимость маршрута, благодаря которому он сможет успеть подать документы и на который он потратит меньше всего денег.

// Формат ввода
// В первой строке даны три числа: N — число пунктов (1 ≤ N ≤ 10^3), M — число переходов (1 ≤ M ≤ 5 ⋅ 10^4), T — максимальное время (0 ≤ T ≤ 10^3).
// Далее идут M строк, содержащих по четыре целых неотрицательных числа — описание перехода:

//     Ai — номер пункта, откуда идёт переход;
//     Bi — номер пункта, куда приведёт переход (1 ≤ Ai, Bi ≤ N; );
//     Pi — стоимость перехода (0 ≤ Pi ≤ 10^6);
//     Ti — продолжительность перехода (0 ≤ Ti ≤ 10^3).

// Формат вывода
// Если добраться за отведённое время до приёмной комиссии невозможно, выведите единственное число −1.
// В противном случае, в первой строке выведите минимальное количество денег, требуемое для того, чтобы Василий успел подать документы.
// Во второй строке выведите L — число переходов, по которым Василию нужно пройти, чтобы успеть.
// В третьей строке выведите L чисел, которые задают порядок пунктов, по которому должен пройти Василий, чтобы успеть и потратить меньше всего денег.


#include <iostream>
#include <vector>
#include <algorithm>

class Edge {
 public:
  size_t first_ver_;
  size_t second_ver_;
  size_t weight_;
  size_t time_;
  Edge() = default;
  Edge(size_t first_ver, size_t second_ver, size_t weight, size_t time)
      : first_ver_(first_ver), second_ver_(second_ver), weight_(weight), time_(time) {
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
  explicit Graph(size_t size, size_t max_time)
      : size_(size)
      , max_time_(max_time)
      , adj_list_(size)
      , dp_(max_time + 1, std::vector<size_t>(size, max_dist_))
      , parent_(max_time + 1, std::vector<std::pair<int, int>>(size, std::make_pair(-1, -1))) {
  }

  void AddNoOrientEdge(size_t first_ver, size_t second_ver, size_t weight, size_t time) {
    adj_list_[first_ver].emplace_back(first_ver, second_ver, weight, time);
    adj_list_[second_ver].emplace_back(second_ver, first_ver, weight, time);
  }

  void BellmanFord(size_t start) {
    dp_[0][start] = 0;
    Dijkstra(start);
    for (size_t t = 0; t <= max_time_; ++t) {
      for (size_t i = 0; i < size_; ++i) {
        for (auto &edge : adj_list_[i]) {
          if (t + edge.time_ <= max_time_ && dp_[t][edge.first_ver_] != max_dist_ &&
              dp_[t][edge.first_ver_] + edge.weight_ < dp_[t + edge.time_][edge.second_ver_]) {
            dp_[t + edge.time_][edge.second_ver_] = dp_[t][edge.first_ver_] + edge.weight_;
            parent_[t + edge.time_][edge.second_ver_].first = static_cast<int>(edge.first_ver_);
            parent_[t + edge.time_][edge.second_ver_].second = static_cast<int>(edge.time_);
          }
        }
      }
    }
  }

  void Dijkstra(size_t start) {
    std::vector<bool> used(size_, false);
    Heap heap;
    heap.Insert(std::make_pair(dp_[0][start], start));
    while (!heap.Empty()) {
      std::pair<size_t, size_t> ver = heap.ExtractMin();
      if (dp_[0][ver.second] != ver.first) {
        continue;
      }
      used[ver.second] = true;
      for (auto &u : adj_list_[ver.second]) {
        if (u.time_ == 0) {
          if (dp_[0][ver.second] != max_dist_ && !used[u.second_ver_] &&
              dp_[0][u.second_ver_] > dp_[0][ver.second] + u.weight_) {
            dp_[0][u.second_ver_] = dp_[0][ver.second] + u.weight_;
            parent_[0][u.second_ver_].first = static_cast<int>(ver.second);
            parent_[0][u.second_ver_].second = 0;
            heap.Insert(std::make_pair(dp_[0][u.second_ver_], u.second_ver_));
          }
        }
      }
    }
  }

  void PrintPath(size_t finish) const {
    size_t min_dist = max_dist_;
    size_t min_time = max_dist_;
    for (size_t t = 0; t < max_time_ + 1; ++t) {
      if (dp_[t][finish] < min_dist) {
        min_dist = dp_[t][finish];
        min_time = t;
      }
    }
    if (min_dist == max_dist_) {
      std::cout << -1;
    } else {
      std::cout << min_dist << "\n";
      auto curr_time = static_cast<int>(min_time);
      auto curr_ver = static_cast<int>(finish);
      int ver;
      std::vector<size_t> path;
      while (curr_ver != -1 && curr_time >= 0) {
        path.push_back(curr_ver + 1);
        ver = curr_ver;
        curr_ver = parent_[curr_time][curr_ver].first;
        curr_time -= parent_[curr_time][ver].second;
      }
      std::reverse(path.begin(), path.end());
      std::cout << path.size() << "\n";
      for (size_t elem : path) {
        std::cout << elem << " ";
      }
    }
  }

 private:
  const size_t max_dist_ = INT64_MAX;
  size_t size_;
  size_t max_time_;
  std::vector<std::vector<Edge>> adj_list_;
  std::vector<std::vector<size_t>> dp_;
  std::vector<std::vector<std::pair<int, int>>> parent_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t amount_of_vertexes, amount_of_edges, max_time;
  size_t first_vertex, second_vertex, weight, time;
  std::cin >> amount_of_vertexes >> amount_of_edges >> max_time;
  const size_t start = 0, finish = amount_of_vertexes - 1;
  Graph graph(amount_of_vertexes, max_time);
  for (size_t i = 0; i < amount_of_edges; ++i) {
    std::cin >> first_vertex >> second_vertex >> weight >> time;
    graph.AddNoOrientEdge(--first_vertex, --second_vertex, weight, time);
  }
  graph.BellmanFord(start);
  graph.PrintPath(finish);
  return 0;
}