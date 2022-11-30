/*
 She's into superstitions

Black cats and voodoo dolls

I feel a premonition

That girl's gonna make me fall

Уно, дос, кватро, поехали! Ослу и Коту в сапогах нужно держать ритм песни, а значит, прежде всего, следует определить ее рефрен (так называется определённый музыкальный материал, неоднократно повторяющийся на протяжении произведения, например, припев в песнях).В общих чертах методика поиска рефрена интуитивна — рассматривается последовательность
 n целых чисел от 1 до m. Подпоследовательность подряд идущих чисел называется рефреном, если произведение её длины на количество вхождений в последовательность максимально.

От вас требуется две вещи:

1) По заданной последовательности найти её рефрен.

2) Оценить дуэт Осла и Кота в сапогах в примечании.

 Формат ввода
Первая строка входного файла содержит два целых числа:
n и m
Вторая строка содержит
n целых чисел от 1 до m.

Формат вывода
Первая строка выходного файла должна содержать произведение длины рефрена на количество ее вхождений. Вторая строка должна содержать длину рефрена. Третья строка должна содержать последовательность которая является рефреном.
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>

struct Node {
  std::unordered_map<char, int64_t> next;
  int64_t len = 0;
  int64_t suff_link = -1;
  bool is_terminal = false;
  int64_t size = 0;
  std::pair<int64_t, char> prev;
};

class SuffMachine {
 public:
  explicit SuffMachine(std::string &str) {
    tree_.push_back(Node{});
    cur_str_ = str;
    cur_last_ = 0;
  }
  void DFSVisit(int64_t ver) {
    used_[ver] = true;
    if (tree_[ver].next.empty()) {
      tree_[ver].size = 1;
    }
    for (auto &symbol : tree_[ver].next) {
      if (!used_[symbol.second]) {
        DFSVisit(symbol.second);
      }
      tree_[ver].size += tree_[symbol.second].size;
    }
  }
  void AddSymbol(char symbol) {
    tree_.emplace_back(Node{});
    int64_t cur_node = tree_.size() - 1;
    int64_t parent = cur_last_;
    tree_[cur_node].len = tree_[parent].len + 1;
    tree_[cur_node].prev = std::make_pair(cur_last_, symbol);
    while (parent != -1 && tree_[parent].next.find(symbol) == tree_[parent].next.end()) {
      tree_[parent].next[symbol] = cur_node;
      parent = tree_[parent].suff_link;
    }
    if (parent == -1) {
      tree_[cur_node].suff_link = 0;
      cur_last_ = cur_node;
      return;
    }
    int64_t next = tree_[parent].next[symbol];
    if (tree_[next].len == tree_[parent].len + 1) {
      tree_[cur_node].suff_link = next;
      cur_last_ = cur_node;
      return;
    }
    tree_.emplace_back(Node{});
    int64_t clone = tree_.size() - 1;
    tree_[clone].len = tree_[parent].len + 1;
    tree_[clone].prev = std::make_pair(parent, symbol);
    while (parent != -1 && tree_[parent].next[symbol] == next) {
      tree_[parent].next[symbol] = clone;
      parent = tree_[parent].suff_link;
    }
    tree_[clone].next = tree_[next].next;
    tree_[clone].suff_link = tree_[next].suff_link;
    tree_[next].suff_link = clone;
    tree_[cur_node].suff_link = clone;
    cur_last_ = cur_node;
  }
  void FindRefren() {
    int64_t max_substr_index = 0;
    for (int64_t i = 0; i < static_cast<int64_t>(tree_.size()); ++i) {
      if (tree_[i].size * tree_[i].len > tree_[max_substr_index].size * tree_[max_substr_index].len) {
        if (tree_[i].prev.second != '#') {
          max_substr_index = i;
        }
      }
    }
    std::string result;
    int64_t id = max_substr_index;
    for (int64_t i = 0; i < tree_[max_substr_index].len; ++i) {
      result += tree_[id].prev.second;
      id = tree_[id].prev.first;
    }
    std::reverse(result.begin(), result.end());
    std::cout << result.size() * tree_[max_substr_index].size << "\n";
    std::cout << result.size() << "\n";
    for (auto &s : result) {
      std::cout << s - '0' + 1 << " ";
    }
  }
  void Build() {
    for (auto &symbol : cur_str_) {
      AddSymbol(symbol);
    }
    AddSymbol('#');
    used_.assign(tree_.size(), false);
    DFSVisit(0);
  }

 private:
  std::vector<Node> tree_;
  int64_t cur_last_;
  std::string cur_str_;
  std::vector<bool> used_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  std::string str;
  std::cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    int num = 0;
    std::cin >> num;
    str += std::to_string(--num);
  }
  SuffMachine machine(str);
  machine.Build();
  machine.FindRefren();
  return 0;
}