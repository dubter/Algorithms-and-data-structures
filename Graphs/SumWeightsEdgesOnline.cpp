// В неориентированный взвешенный граф добавляют ребра. Напишите программу, которая в некоторые моменты находит сумму весов ребер в компоненте связности.

// Формат ввода
// В первой строке записано два числа n и m (1 ≤ n, m ≤ 10^6) — количество вершин в графе и количество производимых добавлений и запросов. Далее следует m строк с описанием добавления или запроса. Каждая строка состоит из двух или четырех чисел.
// Первое из чисел обозначает код операции. Если первое число 1, то за ним следует еще три числа x, y, w. Это означает, что в граф добавляется ребро xy веса w (1 ≤ x < y ≤ n, 1 ≤ w ≤ 1000). Кратные ребра допустимы.
// Если первое число 2, то за ним следует ровно одно число x. Это означает, что необходимо ответить на вопрос, какова сумма весов ребер в компоненте связности, которой принадлежит вершина x (1 ≤ x ≤ n).
// Формат вывода
// Для каждой операции с кодом 2 выведите ответ на поставленную задачу. Ответ на каждый запрос выводите на отдельной строке.

#include <iostream>
#include <vector>

class DSU {
 private:
  std::vector<size_t> parents_;
  std::vector<size_t> rank_;
  std::vector<size_t> sum_;

 public:
  explicit DSU(size_t size) {
    parents_.resize(size);
    for (size_t i = 0; i < size; ++i) {
      parents_[i] = i;
    }
    rank_.resize(size, 0);
    sum_.resize(size, 0);
  }

  size_t FindSet(size_t x) {
    if (x == parents_[x]) {
      return x;
    }
    return parents_[x] = FindSet(parents_[x]);
  }

  void Union(size_t x, size_t y, size_t value) {
    x = FindSet(x);
    y = FindSet(y);
    if (rank_[x] < rank_[y]) {
      parents_[x] = y;
      sum_[y] += sum_[x] + value;
    } else if (rank_[x] > rank_[y]) {
      parents_[y] = x;
      sum_[x] += sum_[y] + value;
    } else {
      parents_[x] = y;
      rank_[y]++;
      sum_[y] += sum_[x] + value;
    }
  }

  void IncreaseSum(size_t x, size_t value) {
    x = FindSet(x);
    sum_[x] += value;
  }

  size_t SumOfValuesOnComponent(size_t x) {
    x = FindSet(x);
    return sum_[x];
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t amount_of_vertexes, amount_of_edges;
  size_t first_vertex, second_vertex, value_of_edge;
  size_t mode, checked_vertex;
  std::cin >> amount_of_vertexes >> amount_of_edges;
  DSU dsu(amount_of_vertexes);
  for (size_t i = 0; i < amount_of_edges; ++i) {
    std::cin >> mode;
    if (mode == 1) {
      std::cin >> first_vertex >> second_vertex >> value_of_edge;
      first_vertex--;
      second_vertex--;
      if (dsu.FindSet(first_vertex) != dsu.FindSet(second_vertex)) {
        dsu.Union(first_vertex, second_vertex, value_of_edge);
      } else {
        dsu.IncreaseSum(first_vertex, value_of_edge);
      }
    } else if (mode == 2) {
      std::cin >> checked_vertex;
      std::cout << dsu.SumOfValuesOnComponent(--checked_vertex) << "\n";
    }
  }
  return 0;
}
