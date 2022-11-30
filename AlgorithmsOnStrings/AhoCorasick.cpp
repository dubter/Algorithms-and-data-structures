#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <queue>

struct Node {
  std::map<char, u_int32_t> next;
  bool is_terminal = false;
  std::shared_ptr<Node> suff_ref;
  std::shared_ptr<Node> exit_link;
  u_int32_t index;
  u_int32_t len;
};

class Pair {
 public:
  Pair (char symbol, std::shared_ptr<Node> &shared_ptr) {
    symbol_ = symbol;
    shared_ptr_ = shared_ptr;
  }
  char symbol_;
  std::shared_ptr<Node> shared_ptr_;
};

class SetString {
 public:
  explicit SetString(u_int32_t size) : result_(size){};
  void Insert(std::string &str, u_int32_t index) {
    if (tree_.empty()) {
      tree_.emplace_back(std::make_shared<Node>(Node{}));
    }
    std::shared_ptr<Node> cur_node = tree_[0];
    for (auto &symbol : str) {
      u_int32_t next_id = cur_node->next[symbol];
      if (next_id == 0) {
        tree_.emplace_back(std::make_shared<Node>(Node{}));
        cur_node->next[symbol] = tree_.size() - 1;
        next_id = cur_node->next[symbol];
      }
      cur_node = tree_[next_id];
    }
    cur_node->is_terminal = true;
    cur_node->index = index;
    cur_node->len = str.size();
  }
  void BuildSuffixReferences() {
    tree_[0]->suff_ref = nullptr;
    std::queue<std::pair<Pair, u_int32_t>> q;
    for (auto &symbol : tree_[0]->next) {
      q.push(std::make_pair(Pair(symbol.first, tree_[0]), symbol.second));
    }
    std::shared_ptr<Node> suff;
    std::shared_ptr<Node> node;
    std::shared_ptr<Node> parent;
    while (!q.empty()) {
      char s = q.front().first.symbol_;
      parent = q.front().first.shared_ptr_;
      node = tree_[q.front().second];
      q.pop();
      suff = parent->suff_ref;
      while (suff != nullptr && suff->next.find(s) == suff->next.end()) {
        suff = suff->suff_ref;
      }
      node->suff_ref = (suff == nullptr) ? tree_[0] : tree_[suff->next[s]];
      for (auto &symbol : node->next) {
        q.push(std::make_pair(Pair(symbol.first, node), symbol.second));
      }
    }
  }
  void BuildExitLinks() {
    tree_[0]->exit_link = nullptr;
    std::queue<u_int32_t> q;
    for (auto &symbol : tree_[0]->next) {
      q.push(symbol.second);
    }
    std::shared_ptr<Node> suff;
    std::shared_ptr<Node> node;
    while (!q.empty()) {
      node = tree_[q.front()];
      q.pop();
      suff = node->suff_ref;
      if (suff != tree_[0]) {
        node->exit_link = (suff->is_terminal) ? suff : suff->exit_link;
      }
      for (auto &symbol : node->next) {
        q.push(symbol.second);
      }
    }
  }
  std::shared_ptr<Node> NextState(std::shared_ptr<Node> &node, char symbol) {
    while (node != nullptr && node->next.find(symbol) == node->next.end()) {
      node = node->suff_ref;
    }
    return (node == nullptr) ? tree_[0] : tree_[node->next[symbol]];
  }

  void AhoCorasick(std::string &str) {
    BuildSuffixReferences();
    BuildExitLinks();
    std::shared_ptr<Node> node = tree_[0];
    std::shared_ptr<Node> cur_node;
    for (u_int32_t i = 0; i < str.size(); ++i) {
      cur_node = NextState(node, str[i]);
      node = cur_node;
      if (!cur_node->is_terminal) {
        cur_node = cur_node->exit_link;
      }
      while (cur_node != nullptr) {
        result_[cur_node->index].push_back(i - cur_node->len + 1);
        cur_node = cur_node->exit_link;
      }
    }
  }
  void PrintResult() {
    for (u_int16_t i = 0; i < result_.size(); ++i) {
      std::cout << result_[i].size() << " ";
      for (u_int16_t j = 0; j < result_[i].size(); ++j) {
        std::cout << result_[i][j] + 1 << " ";
      }
      std::cout << "\n";
    }
  }

 private:
  std::vector<std::shared_ptr<Node>> tree_;
  std::vector<std::vector<u_int32_t>> result_;
};

int main() {
  std::string str;
  std::cin >> str;
  u_int32_t n = 0;
  std::cin >> n;
  SetString s(n);
  for (u_int32_t i = 0; i < n; ++i) {
    std::string str_cur;
    std::cin >> str_cur;
    s.Insert(str_cur, i);
  }
  s.AhoCorasick(str);
  s.PrintResult();
  return 0;
}