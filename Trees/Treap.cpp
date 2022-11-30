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
};

class Treap {
 public:
  Treap() {
    root_ = nullptr;
  }
  ~Treap() {
    Clear(root_);
  }
  void FixNode(Node *&root) {
    if (root != nullptr) {
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

  std::pair<Node *, Node *> Split(Node *root, int64_t num) {
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
    auto node = new Node{num, y, nullptr, nullptr, nullptr, 1};
    root_ = Merge(Merge(roots.first, node), roots.second);
  }

  void Erase(int64_t num) {
    std::pair<Node *, Node *> roots1 = Split(root_, num);
    std::pair<Node *, Node *> roots2 = Split(roots1.second, num + 1);
    delete roots2.first;
    root_ = Merge(roots1.first, roots2.second);
  }

  void Clear(Node *&root) {
    if (root != nullptr) {
      Clear(root->left);
      Clear(root->right);
      delete root;
    }
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

  Node *SearchMin(Node *root, int64_t num, Node *result) {
    if (root == nullptr) {
      return result;
    }
    if (root->x <= num) {
      return SearchMin(root->right, num, result);
    }
    result = root;
    return SearchMin(root->left, num, result);
  }

  Node *SearchMax(Node *root, int64_t num, Node *result) {
    if (root == nullptr) {
      return result;
    }
    if (root->x >= num) {
      return SearchMax(root->left, num, result);
    }
    result = root;
    return SearchMax(root->right, num, result);
  }

  Node *Kth(Node *root, uint32_t k) {
    if (root == nullptr) {
      return nullptr;
    }
    if (root->left == nullptr && k == 0) {
      return root;
    }
    if (root->left == nullptr) {
      return Kth(root->right, k - 1);
    }
    if (root->left->size < k) {
      return Kth(root->right, k - root->left->size - 1);
    }
    if (root->left->size > k) {
      return Kth(root->left, k);
    }
    return root;
  }
  Node *GetRoot() {
    return root_;
  }

 private:
  Node *root_;
};

void Handler(Treap &treap, const std::string &string, const int64_t &num) {
  if (string == "insert") {
    if (!treap.Search(treap.GetRoot(), num)) {
      treap.Insert(num, rand());
    }
  } else if (string == "exists") {
    if (treap.Search(treap.GetRoot(), num)) {
      std::cout << "true"
                << "\n";
    } else {
      std::cout << "false"
                << "\n";
    }
  } else if (string == "delete") {
    treap.Erase(num);
  } else if (string == "next") {
    Node *node = treap.SearchMin(treap.GetRoot(), num, nullptr);
    if (node == nullptr) {
      std::cout << "none\n";
    } else {
      std::cout << node->x << "\n";
    }
  } else if (string == "prev") {
    Node *node = treap.SearchMax(treap.GetRoot(), num, nullptr);
    if (node == nullptr) {
      std::cout << "none\n";
    } else {
      std::cout << node->x << "\n";
    }
  } else if (string == "kth") {
    Node *node = treap.Kth(treap.GetRoot(), num);
    if (node == nullptr) {
      std::cout << "none\n";
    } else {
      std::cout << node->x << "\n";
    }
  } else {
    return;
  }
}

int main() {
  Treap treap;
  std::string string;
  int64_t num;
  while (std::cin >> string >> num) {
    Handler(treap, string, num);
  }
  return 0;
}