#include <iostream>

struct Node {
  char val;
  Node* prev;
};

void push(Node*& head, char data) {
  Node* node = new Node;
  node->val = data;
  node->prev = head;
  head = node;
}

void pop(Node*& head) {
  if (head != nullptr) {
    Node* tmp = head;
    head = head->prev;
    delete tmp;
  }
}

char GetBackVal(Node* head) {
  if (head != nullptr) {
    return head->val;
  }
  return 0;
}

int GetSize(Node* head) {
  int stack_size = 0;
  for (; head != nullptr; stack_size++) {
    head = head->prev;
  }
  return stack_size;
}

void Clear(Node*& head) {
  if (head == nullptr) {
    return;
  }
  while (head != nullptr) {
    pop(head);
  }
}

int main() {
  Node* stack = nullptr;
  bool firstEntrance = true;
  char symbol;
  while (std::cin >> symbol) {
    if (!firstEntrance) {
      if ((GetBackVal(stack) == '(') && (symbol == ')')) {
        pop(stack);
      } else if ((GetBackVal(stack) == '{') && (symbol == '}')) {
        pop(stack);
      } else if ((GetBackVal(stack) == '[') && (symbol == ']')) {
        pop(stack);
      } else {
        push(stack, symbol);
      }
    } else {
      firstEntrance = false;
      push(stack, symbol);
    }
  }
  if (GetSize(stack) == 0) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  Clear(stack);
  return 0;
}