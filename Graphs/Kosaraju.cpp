// Вам задан ориентированный граф с N вершинами и M ребрами (1 ≤ N ≤ 20000, 1 ≤ M ≤ 200000). Найдите компоненты сильной связности заданного графа и топологически отсортируйте его конденсацию.

// Формат ввода
// Граф задан во входном файле следующим образом: первая строка содержит числа N и M. Каждая из следующих M строк содержит описание ребра — два целых числа из диапазона от 1 до N — номера начала и конца ребра.
// Формат вывода
// На первой строке выведите число K — количество компонент сильной связности в заданном графе. На следующей строке выведите N чисел — для каждой вершины выведите номер компоненты сильной связности, которой принадлежит эта вершина. Компоненты сильной связности должны быть занумерованы таким образом, чтобы для любого ребра номер компоненты сильной связности его начала не превышал номера компоненты сильной связности его конца.

#include <vector>
#include <iostream>
#include <list>

enum COLOUR { WHITE, GRAY, BLACK };

class Graph {
 private:
  std::vector<std::vector<int>> adjacency_list_;
  std::vector<COLOUR> colours_;
  std::vector<std::vector<int>> transposed_vertexes_;
  std::vector<int> scc_;
  std::list<int> sorted_vertexes_;
  int count_components_strong_connectivity_ = 0;

 public:
  explicit Graph(int size) : adjacency_list_(size), colours_(size, WHITE), transposed_vertexes_(size), scc_(size) {
  }

  void AddOrientEdge(int first_ver, int second_ver) {
    adjacency_list_[first_ver].push_back(second_ver);
    transposed_vertexes_[second_ver].push_back(first_ver);
  }

  void DFS(int ver) {
    colours_[ver] = GRAY;
    for (int neighbour : adjacency_list_[ver]) {
      if (colours_[neighbour] == WHITE) {
        DFS(neighbour);
      }
    }
    colours_[ver] = BLACK;
    sorted_vertexes_.push_front(ver);
  }

  void TopSort() {
    for (int i = 0; i < static_cast<int>(adjacency_list_.size()); ++i) {
      if (colours_[i] == WHITE) {
        DFS(i);
      }
    }
  }

  void KosarajuDFS(int ver) {
    colours_[ver] = GRAY;
    for (int neighbour : transposed_vertexes_[ver]) {
      if (colours_[neighbour] == WHITE) {
        KosarajuDFS(neighbour);
      }
    }
    colours_[ver] = BLACK;
    scc_[ver] = count_components_strong_connectivity_ + 1;
  }

  void Kosaraju() {
    TopSort();
    for (size_t i = 0; i < colours_.size(); ++i) {
      colours_[i] = WHITE;
    }
    for (auto ver : sorted_vertexes_) {
      if (colours_[ver] == WHITE) {
        KosarajuDFS(ver);
        count_components_strong_connectivity_++;
      }
    }
  }

  int GetCountComponentsOfConnectivity() const {
    return count_components_strong_connectivity_;
  }

  std::vector<int> &GetSCC() {
    return scc_;
  }
};

int main() {
  int amount_of_vertexes, amount_of_edges;
  int first_ver, second_ver;
  std::cin >> amount_of_vertexes >> amount_of_edges;
  Graph graph(amount_of_vertexes);
  for (int i = 0; i < amount_of_edges; ++i) {
    std::cin >> first_ver >> second_ver;
    graph.AddOrientEdge(--first_ver, --second_ver);
  }
  graph.Kosaraju();
  std::cout << graph.GetCountComponentsOfConnectivity() << "\n";
  std::vector<int> scc = graph.GetSCC();
  for (size_t i = 0; i < scc.size(); ++i) {
    std::cout << scc[i] << " ";
  }
  return 0;
}