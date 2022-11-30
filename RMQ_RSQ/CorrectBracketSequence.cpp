/*
 Весь мир — как почта. Мало того, что мы шлём не то и не тем, так это ещё и не доходит...

Лосяш разработал новый язык — язык скобочных последовательностей, словом в котором является строка
s
s длины
n
n, состоящая из символов <<(>> и <<)>>.

Естественно, Лосяш заметил, что в его языке есть \textit{правильные} слова (для остального мира это всеми любимые правильные скобочные последовательности). Наш герой подготовил целую речь на новом языке, но он расстроен тем, что в ней слишком много \textit{неправильных} фрагментов.

Вам нужно утешить смешарика и написать программу, которая по фрагменту из речи сможет сказать размер наидлиннейшего \textit{правильного} подслова в нем.

Формат ввода
Первая строка содержит речь Лосяша — скобочная последовательность длины n.

Вторая строка содержит целое число m — количество запросов к написанной вами программе.

Каждая из следующих m строк содержит пару целых чисел.
В i-й строке записаны числа l_i, r_i — границы i-го фрагмента.

Формат вывода
Выведите ответ на каждый запрос в отдельной строке. Ответы выводите в порядке следования запросов во входных данных.
 */

#include <iostream>
#include <vector>

class Node {
 public:
  Node() {
    opened_ = 0;
    closed_ = 0;
    ready_ = 0;
  };
  Node(size_t opened, size_t closed, size_t ready) : opened_(opened), closed_(closed), ready_(ready) {
  }
  size_t opened_;
  size_t closed_;
  size_t ready_;
};

class SegmentTree {
 public:
  explicit SegmentTree(const std::string &string) {
    std::vector<Node> tmp;
    tmp.reserve(string.size());
    size_t opened;
    size_t closed;
    for (uint32_t i = 0; i < string.size(); ++i) {
      if (string[i] == '(') {
        opened = 1;
        closed = 0;
      } else {
        opened = 0;
        closed = 1;
      }
      Node node(opened, closed, 0);
      tmp.emplace_back(node);
    }
    size_t size = 1;
    while (size < string.size()) {
      size *= 2;
    }
    segment_tree_.resize(2 * size - 1);
    for (uint32_t i = 0; i < string.size(); ++i) {
      segment_tree_[i + size - 1] = tmp[i];
    }
    for (int32_t i = size - 2; i >= 0; --i) {
      segment_tree_[i].ready_ = segment_tree_[Left(i)].ready_ + segment_tree_[Right(i)].ready_ +
          std::min(segment_tree_[Right(i)].closed_, segment_tree_[Left(i)].opened_);
      segment_tree_[i].opened_ = segment_tree_[Left(i)].opened_ + segment_tree_[Right(i)].opened_ -
          std::min(segment_tree_[Right(i)].closed_, segment_tree_[Left(i)].opened_);
      segment_tree_[i].closed_ = segment_tree_[Left(i)].closed_ + segment_tree_[Right(i)].closed_ -
          std::min(segment_tree_[Right(i)].closed_, segment_tree_[Left(i)].opened_);
    }
  }
  // 0 - indexation
  uint32_t Left(uint32_t index) {
    return 2 * index + 1;
  }
  uint32_t Right(uint32_t index) {
    return 2 * index + 2;
  }
  Node Query(uint32_t left, uint32_t right, uint32_t node, uint32_t a, uint32_t b) {
    if (a >= left && b <= right) {
      return segment_tree_[node];
    }
    if (b < left || a > right) {
      Node node1;
      return node1;
    }
    Node first = Query(left, right, Left(node), a, (a + b) / 2);
    Node second = Query(left, right, Right(node), (a + b) / 2 + 1, b);
    Node combining;
    combining.ready_ = first.ready_ + second.ready_ + std::min(first.opened_, second.closed_);
    combining.opened_ = first.opened_ + second.opened_ - std::min(first.opened_, second.closed_);
    combining.closed_ = first.closed_ + second.closed_ - std::min(first.opened_, second.closed_);
    return combining;
  }
  size_t Size() const {
    return segment_tree_.size();
  }

 private:
  std::vector<Node> segment_tree_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  uint32_t size, left, right;
  std::string string;
  std::cin >> string >> size;
  SegmentTree segment_tree(string);
  for (size_t i = 0; i < size; ++i) {
    std::cin >> left >> right;
    left--;
    right--;
    if (segment_tree.Size() == 1) {
      std::cout << 2 * segment_tree.Query(left, right, 0, 0, 0).ready_ << "\n";
    } else {
      std::cout << 2 * segment_tree.Query(left, right, 0, 0, segment_tree.Size() / 2 - 1).ready_ << "\n";
    }
  }
  return 0;
}