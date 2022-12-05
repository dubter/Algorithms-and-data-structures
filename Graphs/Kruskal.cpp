// Дан связный неориентированный граф, в котором надо найти остовное дерево минимального веса с помощью алгоритма Краскала. Гарантируется, что ребра будут отсортированы по весу по неубыванию.

// Формат ввода
// В первой строке идут два натуральных числа N и M (2 ≤ N ≤ 5 ⋅ 10^4, 1 ≤ M ≤ 2 ⋅ 10^6). Далее идет M строк — описания ребер в формате u, v, w (1 ≤ u < v ≤ N, 1 ≤ w ≤ 10^4) — ребро между вершинами u и v веса w.
// Формат вывода
// Вывести вес минимального остового дерева.


#include <iostream>
#include <vector>

class DSU {
 public:
  explicit DSU(int size);
  void MakeSet(int ver);
  int FindSet(int ver);
  int UnionSets(int ver_first, int ver_second);

 private:
  std::vector<int> parent_;
  std::vector<int> size_;
};

int DSU::UnionSets(int ver_first, int ver_second) {
  ver_first = FindSet(ver_first);
  ver_second = FindSet(ver_second);
  if (ver_second != ver_first) {
    if (size_[ver_first] < size_[ver_second]) {
      std::swap(ver_first, ver_second);
    }
    parent_[ver_second] = ver_first;
    size_[ver_first] += size_[ver_second];
  }
  return size_[ver_first];
}

DSU::DSU(int size) : parent_(size), size_(size, 1) {
  for (int i = 0; i < size; ++i) {
    parent_[i] = i;
  }
}

void DSU::MakeSet(int ver) {
  parent_[ver] = ver;
  size_[ver] = 1;
}

int DSU::FindSet(int ver) {
  if (ver == parent_[ver]) {
    return ver;
  }
  return parent_[ver] = FindSet(parent_[ver]);
}

struct Edge {
  int from;
  int to;
  int weight;
};

class Graph {
 public:
  explicit Graph(int size) : adjacency_list_(size), sets_(size){};
  void InsertNoOrientEdge(int from, int to, int cap);
  int64_t Kruskal();

 private:
  std::vector<Edge> adjacency_list_;
  DSU sets_;
};

int64_t Graph::Kruskal() {
  int64_t min_weight = 0;
  for (auto &edge : adjacency_list_) {
    if (sets_.FindSet(edge.from) != sets_.FindSet(edge.to)) {
      sets_.UnionSets(edge.from, edge.to);
      min_weight += edge.weight;
    }
  }
  return min_weight;
}

void Graph::InsertNoOrientEdge(int from, int to, int cap) {
  Edge edg = {from, to, cap};
  adjacency_list_.push_back(edg);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Graph g(n);
  for (int i = 0; i < m; ++i) {
    int ver_first = 0;
    int ver_second = 0;
    int weight = 0;
    std::cin >> ver_first >> ver_second >> weight;
    g.InsertNoOrientEdge(--ver_first, --ver_second, weight);
  }
  std::cout << g.Kruskal();
  return 0;
}