// Во время контрольной работы профессор Флойд заметил, что некоторые студенты обмениваются записками. Сначала он хотел поставить им всем двойки, но в тот день профессор был добрым, а потому решил разделить студентов на две группы: списывающих и дающих списывать, и поставить двойки только первым.
// У профессора записаны все пары студентов, обменявшихся записками. Требуется определить, сможет ли он разделить студентов на две группы так, чтобы любой обмен записками осуществлялся от студента одной группы студенту другой группы.

// Формат ввода
// В первой строке находятся два числа N и M — количество студентов и количество пар студентов, обменивающихся записками (1 ≤ N ≤ 100, 0 ≤ M ≤ N ⋅ (N - 1) / 2). Далее в M строках расположены описания пар студентов: два числа, соответствующие номерам студентов, обменивающихся записками (нумерация студентов идёт с 1). Каждая пара студентов перечислена не более одного раза.
// Формат вывода
// Необходимо вывести ответ на задачу профессора Флойда. Если возможно разделить студентов на две группы — выведите YES; иначе выведите NO.

#include <algorithm>
#include <iostream>
#include <vector>

enum COLOR {
  WHITE,
  GREY,
  BLACK,
};

class Graph {
 public:
  explicit Graph(int size) : vertexes_(size), colors_(size, WHITE), tones_(size){};

  void InsertEdgeNoOrient(int ver_first, int ver_second) {
    if (std::find(vertexes_[ver_second].begin(), vertexes_[ver_second].end(), ver_first) ==
        vertexes_[ver_second].end()) {
      vertexes_[ver_second].push_back(ver_first);
    }
    if (std::find(vertexes_[ver_first].begin(), vertexes_[ver_first].end(), ver_second) == vertexes_[ver_first].end()) {
      vertexes_[ver_first].push_back(ver_second);
    }
  }

  bool IsTwoToneGraph() const {
    return is_able_two_tone_;
  }

  void Dfs(int ver, int tone) {
    colors_[ver] = GREY;
    tones_[ver] = tone;
    for (auto u : vertexes_[ver]) {
      if (colors_[u] == WHITE) {
        Dfs(u, -tone);
      } else if (tones_[ver] == tones_[u]) {
        is_able_two_tone_ = false;
        return;
      }
    }
    colors_[ver] = BLACK;
  }

  void IsAbleTwoTones() {
    for (int i = 0; i < static_cast<int>(vertexes_.size()); ++i) {
      if (colors_[i] == WHITE) {
        Dfs(i, 1);
      }
    }
  }

 private:
  std::vector<std::vector<int>> vertexes_;
  std::vector<COLOR> colors_;
  std::vector<int> tones_;
  bool is_able_two_tone_ = true;
};

int main() {
  int amount_of_students = 0;
  int amount_of_pairs = 0;
  int ver_first, ver_second;
  std::cin >> amount_of_students >> amount_of_pairs;
  Graph graph(amount_of_students);
  for (int i = 0; i < amount_of_pairs; ++i) {
    std::cin >> ver_first >> ver_second;
    graph.InsertEdgeNoOrient(--ver_first, --ver_second);
  }
  graph.IsAbleTwoTones();
  if (graph.IsTwoToneGraph()) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  return 0;
}