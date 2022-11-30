/*
 — Неужели вы всю жизнь хотите быть злодеями?
— Но мы же злодеи! Мы больше ничего не умеем.
— Неужели вам не хочется стать чем-то иным?
— Тебе легко говорить. Ты не заколдованное злое дерево. Трудно найти честную работу, когда весь мир настроен против тебя.

Но этому дереву мы предлагаем дать шанс. Итак — постройте суффиксное дерево для заданной строки s.

Формат ввода
На вход подается строка s, состоящая из строчных латинских букв.

Формат вывода
В первой строке выведите количество вершин n в дереве.

Далее выведите ребра дерева в формате "
from
symbol
length
to", где
0≤from,to≤n−1 - номера начала и конца ребра соответственно,
symbol - первый символ подстроки, по которой осуществляется переход,
length - длина ребра (количество символов в подстроке).

Начальное состояние должно иметь номер 0. В качестве завершающего символа используйте '#'.

Переходы выводите по одному на строку.
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>

class SuffixAutomaton {

  struct Node {
    std::map<char, int> next;
    int link;
    size_t len;
    size_t e_p;

    Node(size_t max_suffix_length, size_t end_pos) {
      len = max_suffix_length;
      e_p = end_pos;
    }

    bool Connected(char c) {
      return next.find(c) != next.end();
    }
  };

  int last_;
  std::vector<Node> n_;

 public:
  explicit SuffixAutomaton(size_t str_len) : n_() {
    n_.reserve(str_len * 2);
    n_.emplace_back(0, -1);
    n_[0].link = -1;
    last_ = 0;
  }

  void AddChar(char c) {
    size_t cur = n_.size();
    n_.emplace_back(n_[last_].len + 1, n_[last_].e_p + 1);

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
  friend class SuffixTree;
};

class SuffixTree {

  struct Node {
    std::map<char, int> next;
    size_t begin, length;
  };

  std::vector<Node> n_;
  std::string str_;

 public:

  explicit SuffixTree(const std::string &s) : str_(s) {
    SuffixAutomaton s_a(s.length());

    for (auto i = s.rbegin(); i != s.rend(); i++) {
      s_a.AddChar(*i);
    }

    n_ = std::vector<Node>(s_a.n_.size());

    n_[0].begin = -1;
    n_[0].length = 0;

    for(size_t i = 1; i < s_a.n_.size(); i++) {
      int suffix = s_a.n_[i].link; // Суфф ссылка от исследуемой ноды
      n_[i].begin = s.size() - 1 - (s_a.n_[i].e_p - s_a.n_[suffix].len);
      n_[i].length = s_a.n_[i].len - s_a.n_[suffix].len;
      n_[suffix].next[s[n_[i].begin]] = i;
    }
  }

  void DebugPrint() {
    std::cout << n_.size() << '\n';
    for (size_t i = 0; i < n_.size(); i++) {
      for (auto j : n_[i].next) {
        std::cout << i << " " << j.first << " " << n_[j.second].length << " " << j.second << '\n';
      }
    }
  }
};

int main() {
  std::string inp;
  std::cin >> inp;
  inp.push_back('#');
  SuffixTree s_t(inp);
  s_t.DebugPrint();
  return 0;
}