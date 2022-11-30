/*
 "Одна слезинка и ваш суффиксный автомат построится" — написано на визитке Феи-крёстной.

В чем-то Крестная права — есть такие слёзы, которые надо выплакать обязательно, в любое время дня и ночи, выплакать, чтобы всё внутри перегорело. По этой причине задача построить суффиксный автомат для заданной строки
s
s является обязательной в этом году.

Формат ввода
На вход подается строка s, состоящая из строчных латинских букв.

Формат вывода
В первой строке выведите количество вершин n в автомате.

Далее выведите переходы построенного суффиксного автомата в формате
 "from symbol to", где

0≤from,to≤n−1 - номера начала и конца ребра соответственно,
symbol - буква, по которой осуществляется переход.

Начальное состояние должно иметь номер 0.
Переходы выводите по одному на строку.
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>

struct Node {
  std::map<char, int> next;
  int link;
  size_t len;

  explicit Node(size_t max_suffix_length) {
    len = max_suffix_length;
  }

  bool Connected(char c) {
    return next.find(c) != next.end();
  }
};

class SuffixAutomaton {
 public:
  int last_;
  std::vector<Node> n_;

  explicit SuffixAutomaton(size_t str_len) : n_() {
    n_.reserve(str_len * 2);
    n_.emplace_back(0);
    n_[0].link = -1;
    last_ = 0;
  }

  void AddChar(char c) {
    size_t cur = n_.size();
    n_.emplace_back(n_[last_].len + 1);
    int p = last_;
    while (p != -1 && !n_[p].Connected(c)) {
      n_[p].next[c] = cur;
      p = n_[p].link;
    }

    last_ = cur;
    if (p == -1) {
      n_[cur].link = 0;
      return;
    }

    int q = n_[p].next[c];

    if (n_[q].len == n_[p].len + 1) {
      n_[cur].link = q;
    } else {
      size_t copy = n_.size();
      n_.emplace_back(n_[q]);
      n_[copy].len = n_[p].len + 1;
      n_[q].link = n_[cur].link = copy;
      while (p != -1 && n_[p].next[c] == q) {
        n_[p].next[c] = copy;
        p = n_[p].link;
      }
    }
  }

  void DebugPrint() {
    std::cout << n_.size() << "\n";
    for (size_t i = 0; i < n_.size(); i++) {
      for (auto &[c, j] : n_[i].next) {
        std::cout << i << " " << c << " " << j << "\n";
      }
    }
  }
};

int main() {
  std::string input_string;
  std::cin >> input_string;
  SuffixAutomaton s_a(input_string.length());
  for (const auto &x : input_string) {
    s_a.AddChar(x);
  }
  s_a.DebugPrint();
  return 0;
}