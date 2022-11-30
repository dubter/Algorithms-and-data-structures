#include <iostream>

struct Node {
  int key;
  Node* left;
  Node* right;
  Node* parent;
};

struct BinTree {
  Node* root;
};

Node* min(Node* node) {
  if (node->left == nullptr) {
    return node;
  }
  return min(node->left);
}

void Insert(BinTree* tree, Node*& node) {
  Node* y = nullptr;
  Node* x = tree->root;
  while (x != nullptr) {
    y = x;
    if (node->key < x->key) {
      x = x->left;
    } else if (node->key == x->key) {
      delete node;
      return;
    } else {
      x = x->right;
    }
  }
  node->parent = y;
  if (y == nullptr) {
    tree->root = node;
  } else if (node->key < y->key) {
    y->left = node;
  } else {
    y->right = node;
  }
}

void Transplant(BinTree* tree, Node* first, Node* second) {
  if (first->parent == nullptr) {
    tree->root = second;
  } else if (first == first->parent->left) {
    first->parent->left = second;
  } else {
    first->parent->right = second;
  }
  if (second != nullptr) {
    second->parent = first->parent;
  }
}

void Erase(BinTree* tree, Node* node) {
  if (node->left == nullptr) {
    Transplant(tree, node, node->right);
  } else if (node->right == nullptr) {
    Transplant(tree, node, node->left);
  } else {
    Node* y = min(node->right);
    if (y->parent != node) {
      Transplant(tree, y, y->right);
      y->right = node->right;
      y->right->parent = y;
    }
    Transplant(tree, node, y);
    y->left = node->left;
    y->left->parent = y;
  }
  delete node;
}

void InOrderWalk(Node* node, int* count) {
  if (node != nullptr) {
    (*count)++;
    InOrderWalk(node->left, count);
    (*count)++;
    InOrderWalk(node->right, count);
  } else {
    (*count)--;
  }
}

int getSize(BinTree* tree) {
  int count = 1;
  int* indicate = &count;
  InOrderWalk(tree->root, indicate);
  return count;
}

int HeightTree(Node* root) {
  int left, right;
  int height = 0;
  if (root != nullptr) {
    left = HeightTree(root->left);
    right = HeightTree(root->right);
    height = std::max(left, right) + 1;
  }
  return height;
}

void Clear(Node*& root) {
  if (root != nullptr) {
    Clear(root->left);
    Clear(root->right);
    delete root;
  }
}

int main() {
  auto tree = new BinTree;
  tree->root = nullptr;
  int key = 0;
  std::cin >> key;
  while (key != 0) {
    Node* node = new Node;
    node->left = nullptr;
    node->right = nullptr;
    node->key = key;
    Insert(tree, node);
    std::cin >> key;
  }
  std::cout << getSize(tree);
  Clear(tree->root);
  delete tree;
  return 0;
}