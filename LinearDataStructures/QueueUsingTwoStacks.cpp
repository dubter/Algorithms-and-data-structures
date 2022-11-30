//В этом коде поле pend используется в качестве верхнего элемента стэка push_stack, а pbeg в качестве верхнего элемента стэка pop_stack.
//Логичнее сделать только одно поле в структуре Stack, отвечающее за верхний элемент.

#include <iostream>

struct Node {
  Node *next;
  Node *prev;
  int64_t elem;
  int64_t curr_min;
};

struct Stack {
  Node *pbeg;
  Node *pend;
  int size;
};

int64_t Min(int64_t first, int64_t second) {
  return (first < second ? first : second);
}

void Enqueue(Stack *&push_stack, int64_t elem) {
  Node *pv = new Node;
  pv->elem = elem;
  pv->next = nullptr;
  if ((push_stack->pend != nullptr) && (push_stack->size != 0)) {
    push_stack->pend->next = pv;
    pv->prev = push_stack->pend;
    pv->prev = push_stack->pend;
    pv->curr_min = Min(elem, push_stack->pend->curr_min);
    push_stack->pend = pv;
  } else {
    pv->prev = nullptr;
    pv->curr_min = elem;
    push_stack->pbeg = push_stack->pend = pv;
  }
  push_stack->size++;
}

void Dequeue(Stack *&push_stack, Stack *&pop_stack) {
  if (pop_stack->size == 0) {
    int len = push_stack->size;
    pop_stack->pbeg = push_stack->pbeg;
    pop_stack->pend = push_stack->pend;
    push_stack->pbeg = push_stack->pend = nullptr;
    Node *pv = pop_stack->pend;
    pv->curr_min = pv->elem;
    pv = pv->prev;
    for (int i = 0; i < len - 1; ++i) {
      pv->curr_min = Min(pv->next->curr_min, pv->elem);
      pv = pv->prev;
    }
    pop_stack->size = push_stack->size;
    push_stack->size = 0;
  }
  Node *del = pop_stack->pbeg;
  if (pop_stack->pbeg != nullptr && pop_stack->pbeg->next != nullptr) {
    pop_stack->pbeg = pop_stack->pbeg->next;
    pop_stack->pbeg->prev = nullptr;
    del->next = nullptr;
  } else {
    pop_stack->pbeg = pop_stack->pend = nullptr;
  }
  pop_stack->size--;
  delete del;
}

int64_t Front(Stack *&stack) {
  return stack->pbeg->elem;
}

int Size(Stack *&stack) {
  return stack->size;
}

void Clear(Stack *&push_stack, Stack *&pop_stack) {
  while (push_stack->size != 0) {
    Dequeue(push_stack, pop_stack);
  }
  while (pop_stack->size != 0) {
    Dequeue(push_stack, pop_stack);
  }
}

int main() {
  auto *push_stack = new Stack({nullptr, nullptr, 0});
  auto *pop_stack = new Stack({nullptr, nullptr, 0});
  std::string instruction;
  int64_t M;
  std::cin >> M;
  for (int i = 0; i < M; i++) {
    std::cin >> instruction;
    if (instruction == "enqueue") {
      int64_t elem;
      std::cin >> elem;
      Enqueue(push_stack, elem);
      std::cout << "ok" << std::endl;
    } else if (instruction == "dequeue") {
      if (pop_stack->size != 0) {
        std::cout << pop_stack->pbeg->elem << std::endl;
        Dequeue(push_stack, pop_stack);
      } else if (push_stack->size != 0) {
        std::cout << push_stack->pbeg->elem << std::endl;
        Dequeue(push_stack, pop_stack);
      } else {
        std::cout << "error" << std::endl;
      }
    } else if (instruction == "front") {
      if (pop_stack->size != 0) {
        std::cout << Front(pop_stack) << std::endl;
      } else if (push_stack->size != 0) {
        std::cout << Front(push_stack) << std::endl;
      } else {
        std::cout << "error" << std::endl;
      }
    } else if (instruction == "size") {
      std::cout << Size(pop_stack) + Size(push_stack) << std::endl;
    } else if (instruction == "clear") {
      Clear(push_stack, pop_stack);
      std::cout << "ok" << std::endl;
    } else if (instruction == "min") {
      if (pop_stack->size != 0 && push_stack->size != 0) {
        std::cout << Min(push_stack->pend->curr_min, pop_stack->pbeg->curr_min) << std::endl;
      } else if (pop_stack->size != 0) {
        std::cout << pop_stack->pbeg->curr_min << std::endl;
      } else if (push_stack->size != 0) {
        std::cout << push_stack->pend->curr_min << std::endl;
      } else {
        std::cout << "error" << std::endl;
      }
    }
  }
  Clear(push_stack, pop_stack);
  delete push_stack;
  delete pop_stack;
  return 0;
}