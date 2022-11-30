// Вам дан неориентированный граф. Найдите кратчайший путь от вершины a до вершины b.

// Формат ввода
// В первой строке входного файла идут целые числа n и m (1 ≤ n ≤ 50 000, 1 ≤ m ≤ 100 000) — количества вершин и рёбер соответственно. Во второй строке идут целые числа a и b — стартовая и конечная вершины соответственно. Далее идут m строк, описывающих рёбра.
// Формат вывода
// Если пути между a и b нет, выведите единственное число -1. Иначе выведите в первой строке число l — длину кратчайшего пути между этими двумя вершинами в рёбрах, а во второй строке выведите l + 1 число — вершины этого пути.

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

class Graph {
 public:
  explicit Graph(size_t size) {
    vertexes_.resize(size);
    parent_.resize(size);
    dist_.resize(size, max_dist_);
  }
  void BFS(int ver) {
    std::queue<int> queue;
    int parent;
    queue.push(ver);
    dist_[ver] = 0;
    parent_[ver] = -1;
    while (!queue.empty()) {
      parent = queue.front();
      queue.pop();
      for (size_t i = 0; i < vertexes_[parent].size(); ++i) {
        if (dist_[vertexes_[parent][i]] == max_dist_) {
          dist_[vertexes_[parent][i]] = dist_[parent] + 1;
          parent_[vertexes_[parent][i]] = parent;
          queue.push(vertexes_[parent][i]);
        }
      }
    }
  }

  void AddUndirectedEdge(size_t first, size_t second) {
    if (std::find(vertexes_[first].begin(), vertexes_[first].end(), second) == vertexes_[first].end()) {
      vertexes_[first].push_back(second);
      vertexes_[second].push_back(first);
    }
  }

  int GetTheSmallestDistance(int ver) {
    if (dist_[ver] == max_dist_) {
      return -1;
    }
    return dist_[ver];
  }

  void PrintWay(int ver) {
    if (parent_[ver] == -1) {
      std::cout << ver + 1 << " ";
      return;
    }
    PrintWay(parent_[ver]);
    std::cout << ver + 1 << " ";
  }

 private:
  std::vector<std::vector<size_t>> vertexes_;
  std::vector<int> parent_;
  std::vector<int> dist_;
  const int max_dist_ = 500001;
};

int main() {
  size_t n, m;
  int a, b;
  size_t first, second;
  std::cin >> n >> m;
  std::cin >> a >> b;
  --a;
  --b;
  Graph graph(n);
  for (size_t i = 0; i < m; ++i) {
    std::cin >> first >> second;
    --first;
    --second;
    graph.AddUndirectedEdge(first, second);
  }
  graph.BFS(a);
  int dist = graph.GetTheSmallestDistance(b);
  std::cout << dist << "\n";
  if (dist != -1) {
    graph.PrintWay(b);
  }
}