// Дан связный неориентированный граф, в котором надо найти остовное дерево минимального веса с помощью алгоритма Борувки.

// Формат ввода
// В первой строке идут два натуральных числа N и M (2 ≤ N ≤ 5 ⋅ 10^4, 1 ≤ M ≤ 2 ⋅ 10^6). Далее идет M строк — описания ребер в формате u, v, w (1 ≤ u < v ≤ N, 1 ≤ w ≤ 10^9) — ребро между вершинами u и v веса w.
// Формат вывода
// Вывести вес минимального остового дерева.

#include <iostream>
#include <map>
#include <vector>

class DSU {
 public:
  explicit DSU(int size);
  int FindSet(int ver);
  int Union(int ver_first, int ver_second);
  int SetCount() const;

 private:
  std::vector<int> parent_;
  std::vector<int> size_;
  int set_count_;
};

int DSU::SetCount() const {
  return set_count_;
}

int DSU::Union(int ver_first, int ver_second) {
  ver_first = FindSet(ver_first);
  ver_second = FindSet(ver_second);
  if (ver_second != ver_first) {
    if (size_[ver_first] < size_[ver_second]) {
      std::swap(ver_first, ver_second);
    }
    parent_[ver_second] = ver_first;
    size_[ver_first] += size_[ver_second];
    --set_count_;
  }
  return size_[ver_first];
}

DSU::DSU(int size) : parent_(size), size_(size, 1) {
  for (int i = 0; i < size; ++i) {
    parent_[i] = i;
  }
  set_count_ = size;
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
  explicit Graph(int size) : size_(size), sets_(size){};
  void InsertNoOrientEdge(int from, int to, int cap);
  int64_t Boruvka();
  std::pair<int, int> ReturnEdges(int ver_first, int ver_second) const;

 private:
  std::vector<Edge> graph_;
  int size_;
  DSU sets_;
  const int max_weight_ = 1000000001;
};

int64_t Graph::Boruvka() {
  int64_t min_weight = 0;
  std::map<std::pair<int, int>, int> mst;
  while (sets_.SetCount() > 1) {
    std::vector<Edge> min_edges(size_, {-1, -1, max_weight_});
    for (auto &edge : graph_) {
      int component_u = sets_.FindSet(edge.from);
      int component_v = sets_.FindSet(edge.to);
      if (component_u != component_v) {
        if (edge.weight < min_edges[component_u].weight) {
          min_edges[component_u] = edge;
        }
        if (edge.weight < min_edges[component_v].weight) {
          min_edges[component_v] = edge;
        }
      }
    }
    for (auto &e : min_edges) {
      if (e.weight != max_weight_) {
        mst[ReturnEdges(e.from, e.to)] = e.weight;
        sets_.Union(e.from, e.to);
      }
    }
  }
  for (auto &u : mst) {
    min_weight += u.second;
  }
  return min_weight;
}

std::pair<int, int> Graph::ReturnEdges(int ver_first, int ver_second) const {
  if (ver_first > ver_second) {
    return std::make_pair(ver_second, ver_first);
  }
  return std::make_pair(ver_first, ver_second);
}

void Graph::InsertNoOrientEdge(int from, int to, int cap) {
  Edge edg = {from, to, cap};
  graph_.push_back(edg);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int amount_of_vertexes, amount_of_edges;
  int ver_first, ver_second, weight;
  std::cin >> amount_of_vertexes >> amount_of_edges;
  Graph graph(amount_of_vertexes);
  for (int i = 0; i < amount_of_edges; ++i) {
    std::cin >> ver_first >> ver_second >> weight;
    graph.InsertNoOrientEdge(--ver_first, --ver_second, weight);
  }
  std::cout << graph.Boruvka();
  return 0;
}