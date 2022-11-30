/*
 Реализуйте структуру «множество строк», поддерживающие добавление (+) и поиск (?) элементов в множестве.

Формат ввода
Каждая строка, подаваемая на вход программе, содержит команду (+ или ?) и строку, длина каждой строки не превосходит 10^5. При добавлении НЕ гарантируется, что строка ещё не содержится в множестве. Ввод завершается символом «#».

Формат вывода
На каждый запрос «?» выведите «YES», если строка содержится в множестве и «NO» иначе.
 */

#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

struct Node {
  std::unordered_map<char, int64_t> next;
  bool is_terminal = false;
};

class Trie {
 public:
  void Insert(std::string &string) {
    if (tree_.empty()) {
      tree_.emplace_back(std::make_shared<Node>(Node{}));
    }
    std::shared_ptr<Node> cur_node = tree_[0];
    for (auto &symbol : string) {
      int64_t next_id = cur_node->next[symbol];
      if (next_id == 0) {
        tree_.emplace_back(std::make_shared<Node>(Node{}));
        cur_node->next[symbol] = tree_.size() - 1;
        next_id = cur_node->next[symbol];
      }
      cur_node = tree_[next_id];
    }
    cur_node->is_terminal = true;
  }

  bool Find(std::string &string) {
    if (tree_.empty()) {
      return false;
    }
    std::shared_ptr<Node> cur_node = tree_[0];
    for (auto &symbol : string) {
      int64_t next_id = cur_node->next[symbol];
      if (next_id == 0) {
        return false;
      }
      cur_node = tree_[next_id];
    }
    return cur_node->is_terminal;
  }

 private:
  std::vector<std::shared_ptr<Node>> tree_;
};




int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  char mode = ' ';
  Trie trie;
  std::string string;
  while (std::cin >> mode) {
    if (mode == '+') {
      std::cin >> string;
      trie.Insert(string);
    } else if (mode == '?') {
      std::cin >> string;
      if (trie.Find(string)) {
        std::cout << "YES\n";
      } else {
        std::cout << "NO\n";
      }
    } else {
      break;
    }
  }
  return 0;
}