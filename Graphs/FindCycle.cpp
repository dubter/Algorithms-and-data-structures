// Дан ориентированный невзвешенный граф. Необходимо определить есть ли в нём циклы, и если есть, то вывести любой из них.

// Формат ввода
// В первой строке входного файла находятся два натуральных числа N и M (1 ≤ N ≤ 100000, M ≤ 100000) — количество вершин и рёбер в графе соответственно. Далее в M строках перечислены рёбра графа. Каждое ребро задаётся парой чисел — номерами начальной и конечной вершин соответственно.
// Формат вывода
// Если в графе нет цикла, то вывести NO, иначе — YES и затем перечислить все вершины в порядке обхода цикла.

#include <iostream>
#include <vector>

enum COLOR {
  WHITE,
  GREY,
  BLACK,
};

class Graph {
 public:
  explicit Graph(size_t size) {
    vertexes_.resize(size);
    colors_.resize(size, WHITE);
  }
  void PrintCycle() const {
    size_t end = cycle_.back();
    size_t index = cycle_.size() - 2;
    while (cycle_[index] != end) {
      --index;
    }
    for (; index < cycle_.size() - 1; index++) {
      std::cout << cycle_[index] + 1 << " ";
    }
  }

  void InsertEdgeOrient(size_t ver_first, size_t ver_second) {
    vertexes_[ver_first].push_back(ver_second);
  }

  void Dfs(size_t ver) {
    if (is_cycle_) {
      return;
    }
    colors_[ver] = GREY;
    cycle_.push_back(ver);
    for (auto u : vertexes_[ver]) {
      if (colors_[u] == WHITE) {
        Dfs(u);
      } else if (colors_[u] == GREY) {
        is_cycle_ = true;
        cycle_.push_back(u);
        return;
      }
      if (is_cycle_) {
        return;
      }
    }
    colors_[ver] = BLACK;
    cycle_.pop_back();
  }

  bool HasCycle() {
    for (size_t v = 0; v < colors_.size(); ++v) {
      if (colors_[v] == WHITE) {
        Dfs(v);
        if (is_cycle_) {
          break;
        }
      }
    }
    return is_cycle_;
  }

 private:
  bool is_cycle_ = false;
  std::vector<COLOR> colors_;
  std::vector<std::vector<size_t>> vertexes_;
  std::vector<size_t> cycle_;
};

int main() {
  size_t amount_of_vertexes, amount_of_edges;
  size_t ver_first, ver_second;
  std::cin >> amount_of_vertexes >> amount_of_edges;
  Graph graph(amount_of_vertexes);
  for (size_t i = 0; i < amount_of_edges; ++i) {
    std::cin >> ver_first >> ver_second;
    ver_first--;
    ver_second--;
    graph.InsertEdgeOrient(ver_first, ver_second);
  }
  if (graph.HasCycle()) {
    std::cout << "YES\n";
    graph.PrintCycle();
  } else {
    std::cout << "NO";
  }
  return 0;
}