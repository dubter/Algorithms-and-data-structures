// Вам нужно распространить новость о посвяте среди всех первокурсников. Известно, что первокурсники общаются друг с другом через чаты, при этом если новость вброшена в чат, то гарантируется что все его участники прочтут новость (эх, было бы так не только в условии этой задачи).
// Так как у вас уже и так очень много своих чатов, вы хотите вступить в как можно меньшее их количество, чтобы все первокурсники узнали, что посвят уже скоро. При этом вам неизвестны составы чатов, но до вас дошли сведения, что некоторые пары первокурсников гарантированно сидят в одном чате. Более того, если студент сидит в чате и видит новость, то он пересылает сообщение с важной информации во все остальные чаты, где он есть.

// Формат ввода
// Во входном файле записано два числа N — число первокурсников и M — число известных вам пар первокурсников, сидящих в одном чате (1 ≤ N ≤ 100000, 0 ≤ M ≤ 100000). В следующих M строках записаны по два числа i и j (1 ≤ i, j ≤ N), которые означают, что первокурсники с номерами i и j в одном чате.
// Формат вывода
// В первой строчке выходного файла выведите количество чатов, куда вам надо вступить. Далее выведите группы студентов, которые узнают о новости для каждого вступления в чат: в первой строке количество студентов в такой группе в компоненте, во второй — номера студентов в произвольном порядке.

#include <iostream>
#include <vector>

enum COLOUR { WHITE, GREY, BLACK };

class Graph {
 private:
  std::vector<COLOUR> colours_;
  std::vector<std::vector<size_t>> vertexes_;
  size_t count_of_connectivity_components_;
  std::vector<std::vector<size_t>> vertexes_in_component_;

 private:
  void DFS(size_t ver) {
    colours_[ver] = GREY;
    for (size_t neighbour : vertexes_[ver]) {
      if (colours_[neighbour] == WHITE) {
        DFS(neighbour);
      }
    }
    colours_[ver] = BLACK;
    vertexes_in_component_[count_of_connectivity_components_].push_back(ver);
  }

 public:
  explicit Graph(size_t size) : colours_(size, WHITE), vertexes_(size), count_of_connectivity_components_(0) {
  }

  void AddNoOrientEdge(size_t ver1, size_t ver2) {
    vertexes_[ver1].push_back(ver2);
    vertexes_[ver2].push_back(ver1);
  }

  size_t CountOfConnectivityComponents() const {
    return count_of_connectivity_components_;
  }

  void BypassGraph() {
    for (size_t i = 0; i < vertexes_.size(); ++i) {
      if (colours_[i] == WHITE) {
        vertexes_in_component_.emplace_back();
        DFS(i);
        count_of_connectivity_components_++;
      }
    }
  }

  const std::vector<std::vector<size_t>> &GetVertexesInComponent() const {
    return vertexes_in_component_;
  }
};

int main() {
  size_t amount_of_pekuses, amount_of_pairs;
  size_t first_pekus, second_pekus;
  std::cin >> amount_of_pekuses >> amount_of_pairs;
  Graph graph(amount_of_pekuses);
  for (size_t i = 0; i < amount_of_pairs; ++i) {
    std::cin >> first_pekus >> second_pekus;
    graph.AddNoOrientEdge(--first_pekus, --second_pekus);
  }
  graph.BypassGraph();
  std::cout << graph.CountOfConnectivityComponents() << "\n";
  std::vector<std::vector<size_t>> vertexes_in_component = graph.GetVertexesInComponent();
  for (size_t i = 0; i < vertexes_in_component.size(); ++i) {
    std::cout << vertexes_in_component[i].size() << "\n";
    for (size_t j = 0; j < vertexes_in_component[i].size(); ++j) {
      std::cout << vertexes_in_component[i][j] + 1 << " ";
    }
    std::cout << "\n";
  }
  return 0;
}