/*
 Даны строки s и t. Постройте сжатое суффиксное дерево, которое содержит все суффиксы строки s и строки t. Найдите такое дерево, которое содержит минимальное количество вершин. Порадуйтесь за то, что кажется у героев предыдущей задачи все в жизни получилось.

Формат ввода
В первой строке записана строка s (1 ≤ |s| ≤ 10^5), последний символ строки равен `$', остальные символы строки — маленькие латинские буквы.

Во второй строке записана строка t (1 ≤ |t| ≤ 10^5), последний символ строки равен `#', остальные символы строки — маленькие латинские буквы.

Формат вывода
В первой строке выведите количество вершин n в дереве.

Далее выведите ребра дерева в формате "from symbol length to", где 0 ≤ from, to ≤ n - 1 - номера начала и конца ребра соответственно, symbol - первый символ подстроки, по которой осуществляется переход, length - длина ребра (количество символов в подстроке).

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
  friend class SuffixTrie;
};

class SuffixTrie {

  struct Node {
    std::map<char, int> next;
    size_t begin, length;
  };

  std::vector<Node> n_;
  std::string str_;

 public:

  explicit SuffixTrie(const std::string &s) : str_(s) {
    // Резервирование памяти и инициализация суфф. автомата
    SuffixAutomaton s_a(s.length());

    // Построение "префиксного" автомата (суфф. автомата строки наоборот)
    for (auto i = s.rbegin(); i != s.rend(); i++) {
      s_a.AddChar(*i);
    }

    // Выделение памяти под ноды суфф. дерева
    n_ = std::vector<Node>(s_a.n_.size());

    // Первая нода соответствует пустой строке
    n_[0].begin = -1;
    n_[0].length = 0;
    // Переходы из нее пока неизвестны, будут определены в след. цикле...

    // Последующие ноды обрабатываем друг за другом...
    for(size_t i = 1; i < s_a.n_.size(); i++) {
      // Extract transition:
      int suffix = s_a.n_[i].link; // Суфф ссылка от исследуемой ноды
      n_[i].begin = s.size() - 1 - (s_a.n_[i].e_p - s_a.n_[suffix].len);
      n_[i].length = s_a.n_[i].len - s_a.n_[suffix].len;
      n_[suffix].next[s[n_[i].begin]] = i;
    }
  }

  void DebugPrint() {
    std::size_t size = str_.find('$');
    std::cout << n_.size() << std::endl;
    for (size_t i = 0; i < n_.size(); i++) {
      for (auto k : n_[i].next) {
        size_t index = n_[k.second].begin;
        if (index <= size && size <= index + n_[k.second].length - 1) {
          n_[k.second].next.clear();
          std::cout << i << " " << k.first << " ";
          std::cout << size - index + 1 << " " << k.second << std::endl;
        } else {
          std::cout << i << " " << k.first << " ";
          std::cout << n_[k.second].length << " " << k.second << std::endl;
        }
      }
    }
  }
};

int main() {
  std::string inp1;
  std::string inp2;
  std::cin >> inp1 >> inp2;
  SuffixTrie s_t(inp1 + inp2);
  s_t.DebugPrint();
  return 0;
}