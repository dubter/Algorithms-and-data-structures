// Splay
// Реализуйте структуру данных, которая поддерживает множество S целых чисел, с котором разрешается производить следующие операции:
//     add(i) — добавить в множество S число i (если он там уже есть, то множество не меняется);
//     next(i) — вывести минимальный элемент множества, не меньший i. Если искомый элемент в структуре отсутствует, необходимо вывести -1.

// Формат ввода
// Исходно множество S пусто. Первая строка входного файла содержит n — количество операций (1≤ n≤ 300000). Следующие n строк содержат операции. Каждая операция имеет вид либо «+ i», либо «? i». Операция «? i» задает запрос next(i).
// Если операция «+ i» идет во входном файле в начале или после другой операции «+», то она задает операцию add(i). Если же она идет после запроса «?», и результат этого запроса был y, то выполняется операция add(i + y) mod 10^9.
// Во всех запросах и операциях добавления параметры лежат в интервале от 0 до 10^9.
// Формат вывода
// Для каждого запроса выведите одно число — ответ на запрос.


#include <iostream>
#include <vector>

struct Splay {
  int key;
  Splay* left;
  Splay* right;
  Splay* parent;
  Splay(int value) {
    key = value;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
  }
};

Splay* LeftRotation(Splay* node) { // zig
  Splay* new_node = node->right;
  node->right = new_node->left;
  if (new_node->left) {
    new_node->left->parent = node;
  }
  new_node->left = node;
  if (node->parent) {
    if (node == node->parent->left) {
      node->parent->left = new_node;
    } else {
      node->parent->right = new_node;
    }
  }
  new_node->parent = node->parent;
  node->parent = new_node;
  return new_node;
}

Splay* RightRotation(Splay* node) { // zag
  Splay* new_node = node->left;
  node->left = new_node->right;
  if (new_node->right) {
    new_node->right->parent = node;
  }
  new_node->right = node;
  if (node->parent) {
    if(node == node->parent->left)
      node->parent->left = new_node;
    else {
      node->parent->right = new_node;
    }
  }
  new_node->parent = node->parent;
  node->parent = new_node;
  return new_node;
}

Splay* SplayElement(Splay* node, Splay* root) {
  while (node->parent != nullptr) {
    if (node->parent == root) {
      if (node == root->left) {
        RightRotation(node->parent);
      } else {
        LeftRotation(node->parent);
      }
    } else {
      Splay* parent = node->parent;
      Splay* p_parent = parent->parent;
      if (node == parent->left && parent == p_parent->left) { // zig-zig
        RightRotation(p_parent);
        RightRotation(parent);
      } else if (node == parent->right && parent == p_parent->right) { // zag-zag
        LeftRotation(p_parent);
        LeftRotation(parent);
      } else if (node == parent->left && parent == p_parent->right) { // zig-zag
        RightRotation(parent);
        LeftRotation(p_parent);
      } else { // zag-zig
        LeftRotation(parent);
        RightRotation(p_parent);
      }
    }
  }
  return node;
}

Splay* Find(Splay* root, int search) {
  Splay* copy_root = root;
  while (true) {
    if (copy_root->key < search) {
      if (copy_root->right == nullptr) {
        break;
      }
      copy_root = copy_root->right;
    } else if (copy_root->key > search) {
      if (copy_root->left == nullptr) {
        break;
      }
      copy_root = copy_root->left;
    } else {
      break;
    }
  }
  return copy_root;
}

Splay* Insert(Splay* root, int value) {
  if (root == nullptr) {
    root = new Splay(value);
    return root;
  }
  Splay *find_node = Find(root, value);
  if (find_node->key != value) {
    auto new_node = new Splay(value);
    if (value > find_node->key) {
      new_node->parent = find_node;
      find_node->right = new_node;
    } else {
      new_node->parent = find_node;
      find_node->left = new_node;
    }
    return SplayElement(new_node, root);
  } else {
    return SplayElement(find_node, root);
  }
}

int FindNext(Splay* root, int search) {
  Splay* copy_root = root;
  int min_greater_search = 1000000001;
  while (copy_root != nullptr) {
    if (copy_root->key < search) {
      copy_root = copy_root->right;
    } else if (copy_root->key > search) {
      min_greater_search = std::min(copy_root->key, min_greater_search);
      copy_root = copy_root->left;
    } else {
      min_greater_search = copy_root->key;
      break;
    }
  }
  return min_greater_search;
}

int Next(Splay* root, int key) {
  int next_min = FindNext(root, key);
  if (next_min == 1000000001) {
    return -1;
  }
  return next_min;
}

int main () {
  Splay* tree(nullptr);
  char prev_task = ' ';
  int prev_next_return;
  int num;
  std::cin >> num;
  for (int i = 0; i < num; ++i) {
    int digit;
    char task;
    std::cin >> task >> digit;
    if (task == '?') {
      prev_next_return = Next(tree, digit);
      std::cout << prev_next_return << "\n";
      prev_task = task;
    } else {
      if (prev_task == '?') {
        tree = Insert(tree, (digit + prev_next_return) % 1000000000);
      } else {
        tree = Insert(tree, digit);
      }
      prev_task = task;
    }
  }
  return 0;
}