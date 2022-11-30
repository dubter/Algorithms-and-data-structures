/*
 Реализуйте структуру данных, которая поддерживает множество S целых чисел, с которым разрешается производить следующие операции:

1) add(i) — добавить в множество S число i (если оно там уже есть, то множество не меняется);
2) sum(l, r) — вывести сумму всех элементов x из S, которые удовлетворяют неравенствуl ≤ x ≤ r.
 */

#include <iostream>
#include <vector>

class Node {
 public:
  int64_t x;
  int64_t y;
  Node *left;
  Node *right;
  Node *parent;
  uint32_t size;
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
  int64_t Result(Node *root) {
    return root != nullptr ? root->result : 0;
  }

  void FixNode(Node *&root) {
    if (root != nullptr) {
      root->result = Result(root->left) + root->x + Result(root->right);
      uint32_t size = 1;
      if (root->left != nullptr) {
        size += root->left->size;
      }
      if (root->right != nullptr) {
        size += root->right->size;
      }
      root->size = size;
    }
  }

  Node *Merge(Node *root1, Node *&root2) {
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
    if (root->x < num) {
      roots = Split(root->right, num);
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

  void Insert(int64_t num, int64_t y) {
    std::pair<Node *, Node *> roots = Split(root_, num);
    auto node = new Node{num, y, nullptr, nullptr, nullptr, 1, num};
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

  bool Search(Node *root, int64_t num) {
    if (root == nullptr) {
      return false;
    }
    if (root->x == num) {
      return true;
    }
    if (root->x > num) {
      return Search(root->left, num);
    }
    return Search(root->right, num);
  }

  int64_t Query(int64_t left, int64_t right) {
    std::pair<Node *, Node *> left_cut = Split(root_, left);
    std::pair<Node *, Node *> necessary_tree = Split(left_cut.second, right + 1);
    int64_t result = Result(necessary_tree.first);
    root_ = Merge(Merge(left_cut.first, necessary_tree.first), necessary_tree.second);
    return result;
  }
  Node *GetRoot() {
    return root_;
  }

 private:
  Node *root_;
};

void Handler(Treap &treap, const char &symbol, const int64_t &num) {
  int64_t right;
  if (symbol == '+') {
    if (!treap.Search(treap.GetRoot(), num)) {
      treap.Insert(num, rand());
    }
  } else if (symbol == '?') {
    std::cin >> right;
    std::cout << treap.Query(num, right) << "\n";
  }
}

int main() {
  Treap treap;
  char symbol;
  int64_t num, n;
  std::cin >> n;
  for (int64_t i = 0; i < n; ++i) {
    std::cin >> symbol >> num;
    Handler(treap, symbol, num);
  }
  return 0;
}