#include <iostream>

struct Node {
  Node* pnext;
  Node* pprev;
  int data;
};

struct Deque {
  Node* pbeg;
  Node* pend;
  size_t size;
};

void push_back(Deque& deque, int key) {
  Node* tmp = new Node;
  tmp->data = key;
  tmp->pnext = nullptr;
  if ((deque.pend != nullptr) && (deque.size != 0)) {
    deque.pend->pnext = tmp;
    tmp->pprev = deque.pend;
    deque.pend = tmp;
  } else {
    tmp->pprev = nullptr;
    deque.pbeg = deque.pend = tmp;
  }
  deque.size++;
}

void push_front(Deque& deque, int key) {
  Node* tmp = new Node;
  tmp->data = key;
  tmp->pprev = nullptr;
  if ((deque.pbeg != nullptr) && (deque.size != 0)) {
    deque.pbeg->pprev = tmp;
    tmp->pnext = deque.pbeg;
    deque.pbeg = tmp;
  } else {
    tmp->pnext = nullptr;
    deque.pbeg = deque.pend = tmp;
  }
  deque.size++;
}

void pop_front(Deque& deque) {
  if (deque.pbeg != nullptr) {
    Node* tmp = deque.pbeg;
    deque.pbeg = deque.pbeg->pnext;
    delete tmp;
    deque.size--;
  }
}

void pop_back(Deque& deque) {
  if (deque.pend != nullptr) {
    Node* tmp = deque.pend;
    deque.pend = deque.pend->pprev;
    delete tmp;
    deque.size--;
  }
}

int front(Deque& deque) {
  return deque.pbeg->data;
}

int back(Deque& deque) {
  return deque.pend->data;
}

size_t Size(Deque& deque) {
  return deque.size;
}

void clear(Deque& deque) {
  while (deque.size != 0) {
    pop_front(deque);
  }
}

void Output(const std::string &str, Deque* deque) {
  if (str == "pop_front") {
    if (deque->size == 0) {
      std::cout << "error\n";
    } else {
      std::cout << front(*deque) << '\n';
      pop_front(*deque);
    }
  } else if (str == "pop_back") {
    if (deque->size != 0) {
      std::cout << back(*deque) << '\n';
      pop_back(*deque);
    } else {
      std::cout << "error\n";
    }
  } else if (str == "size") {
    std::cout << Size(*deque) << '\n';
  } else if (str == "clear") {
    clear(*deque);
    std::cout << "ok\n";
  } else if (str == "front") {
    if (deque->size != 0) {
      std::cout << front(*deque) << "\n";
    } else {
      std::cout << "error\n";
    }
  } else if (str == "back") {
    if (deque->size != 0) {
      std::cout << back(*deque) << "\n";
    } else {
      std::cout << "error\n";
    }
  } else if (str == "exit") {
    std::cout << "bye";
    exit(0);
  }
}

int main() {
  auto *deque = new Deque;
  deque->pbeg = nullptr;
  deque->pend = nullptr;
  deque->size = 0;
  std::string str;
  long m = 0;
  std::cin >> m;
  for (int i = 0; i < m; i++) {
    std::cin >> str;
    if (str == "push_back") {
      int n;
      std::cin >> n;
      push_back(*deque, n);
      std::cout << "ok\n";
    } else if (str == "push_front") {
      int n;
      std::cin >> n;
      push_front(*deque, n);
      std::cout << "ok\n";
    } else {
      Output(str, deque);
    }
  }
  clear(*deque);
  delete deque;
  return 0;
}