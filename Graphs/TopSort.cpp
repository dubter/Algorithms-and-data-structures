// Дан ориентированный невзвешенный граф. Необходимо его топологически отсортировать.

// Формат ввода
// В первой строке входного файла даны два целых числа N и M (1 ≤ N ≤ 100000, 0 ≤ M ≤ 100000) — количества вершин и рёбер в графе соответственно. Далее в M строках перечислены рёбра графа. Каждое ребро задаётся парой чисел - номерами начальной и конечной вершин соответственно.
// Формат вывода
// Вывести любую топологическую сортировку графа в виде последовательности номеров вершин. Если граф невозможно топологически отсортировать, вывести -1.

#include <iostream>
#include <vector>

enum COLOUR { WHITE, GRAY, BLACK };

class Graph {
 private:
  std::vector<COLOUR> colours_;
  std::vector<std::vector<size_t>> adjacency_list_;
  std::vector<size_t> sorted_arr_;
  size_t count_;
  bool is_able_to_sort_ = true;

 private:
  void DFS(size_t ver) {
    colours_[ver] = GRAY;
    for (size_t neighbour : adjacency_list_[ver]) {
      if (colours_[neighbour] == WHITE) {
        DFS(neighbour);
      } else if (colours_[neighbour] == GRAY) {
        is_able_to_sort_ = false;
      }
    }
    colours_[ver] = BLACK;
    sorted_arr_[count_] = ver;
    count_--;
  }

 public:
  explicit Graph(size_t size) : colours_(size, WHITE), adjacency_list_(size), sorted_arr_(size), count_(size - 1) {
  }

  void AddOrientEdge(size_t ver1, size_t ver2) {
    adjacency_list_[ver1].push_back(ver2);
  }

  void BypassGraph() {
    for (size_t i = 0; i < adjacency_list_.size(); ++i) {
      if (colours_[i] == WHITE) {
        DFS(i);
      }
    }
  }

  void PrintSortedGraph() {
    if (is_able_to_sort_) {
      for (size_t i = 0; i < sorted_arr_.size(); i++) {
        std::cout << sorted_arr_[i] + 1 << " ";
      }
    } else {
      std::cout << -1;
    }
  }
};

int main() {
  size_t amount_of_pekuses, amount_of_pairs;
  size_t first_pekus, second_pekus;
  std::cin >> amount_of_pekuses >> amount_of_pairs;
  Graph graph(amount_of_pekuses);
  for (size_t i = 0; i < amount_of_pairs; ++i) {
    std::cin >> first_pekus >> second_pekus;
    graph.AddOrientEdge(--first_pekus, --second_pekus);
  }
  graph.BypassGraph();
  graph.PrintSortedGraph();
  return 0;
}