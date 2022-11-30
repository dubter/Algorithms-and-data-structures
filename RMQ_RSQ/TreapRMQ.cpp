/*
 Вы уже решали задачу RMQ, даже если есть обновления на отрезке. В этот раз границы решения этой задачи будут расширены. А именно, надо разработать структуру данных в виде массива, который умеет обрабатывать следующие запросы:

1) «? l r» — найти минимум на отрезке [l, r] в 1-индексации;
2) «+ i x» — добавить элемент x после i-го (в 1-индексации) элемента. Если i = 0, то вставка идет в начало списка.
Изначально структура пустая.
 */

#include <iostream>
#include <vector>

class Node {
 public:
  int64_t y;
  Node *left;
  Node *right;
  Node *parent;
  uint32_t size;
  int64_t value;
  int64_t result;
};

class Treap {
 public:
  Treap() {
    root_ = nullptr;
  }
  ~Treap() {
    Clear(root_);
  }
  int64_t Size(Node *root) {
    return root != nullptr ? root->size : 0;
  }
  int64_t Result(Node *root) {
    return root != nullptr ? root->result : INT64_MAX;
  }

  void FixNode(Node *&root) {
    if (root != nullptr) {
      root->result = std::min(std::min(Result(root->left), Result(root->right)), root->value);
      root->size = Size(root->left) + Size(root->right) + 1;
    }
  }

  Node *Merge(Node *root1, Node *root2) {
    if (root1 == nullptr) {
      return root2;
    }
    if (root2 == nullptr) {
      return root1;
    }
    if (root1->y < root2->y) {
      root1->right = Merge(root1->right, root2);
      if (root1->right != nullptr) {
        root1->right->parent = root1;
      }
      FixNode(root1);
      return root1;
    }
    root2->left = Merge(root1, root2->left);
    if (root2->left != nullptr) {
      root2->left->parent = root2;
    }
    FixNode(root2);
    return root2;
  }

  std::pair<Node *, Node *> Split(Node *&root, int64_t num) {
    std::pair<Node *, Node *> roots;
    if (root == nullptr) {
      return std::pair(nullptr, nullptr);
    }
    if (Size(root->left) < num) {
      roots = Split(root->right, num - 1 - Size(root->left));
      root->right = roots.first;
      if (roots.first != nullptr) {
        roots.first->parent = root;
      }
      if (roots.second != nullptr) {
        roots.second->parent = nullptr;
      }
      FixNode(root);
      return {root, roots.second};
    }
    roots = Split(root->left, num);
    root->left = roots.second;
    if (roots.second != nullptr) {
      roots.second->parent = root;
    }
    if (roots.first != nullptr) {
      roots.first->parent = nullptr;
    }
    FixNode(root);
    return {roots.first, root};
  }

  void Insert(int64_t index, int64_t value) {
    std::pair<Node *, Node *> roots = Split(root_, index);
    auto node = new Node{rand(), nullptr, nullptr, nullptr, 1, value, value};
    root_ = Merge(Merge(roots.first, node), roots.second);
  }

  void Clear(Node *&root) {
    if (root != nullptr) {
      Clear(root->left);
      Clear(root->right);
      delete root;
    }
  }

  void Rotate(int64_t left, int64_t right) {
    std::pair<Node *, Node *> left_cut = Split(root_, left);
    std::pair<Node *, Node *> necessary_tree = Split(left_cut.second, right - left + 1);
    root_ = Merge(Merge(necessary_tree.first, left_cut.first), necessary_tree.second);
  }

  int64_t Query(int64_t left, int64_t right) {
    std::pair<Node *, Node *> left_cut = Split(root_, left);
    std::pair<Node *, Node *> necessary_tree = Split(left_cut.second, right - left + 1);
    int64_t result = Result(necessary_tree.first);
    root_ = Merge(Merge(left_cut.first, necessary_tree.first), necessary_tree.second);
    return result;
  }

 private:
  Node *root_;
};

int main() {
  Treap treap;
  int64_t amount_of_queries, left, right;
  char symbol;
  std::cin >> amount_of_queries;
  for (int64_t i = 0; i < amount_of_queries; ++i) {
    std::cin >> symbol >> left >> right;
    if (symbol == '+') {
      treap.Insert(left, right);
    } else if (symbol == '?') {
      left--;
      right--;
      std::cout << treap.Query(left, right) << "\n";
    }
  }
  return 0;
}