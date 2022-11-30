#pragma once

template <class T>
void Swap(T &x, T &y) {
  T tmp = x;
  x = y;
  y = tmp;
}

int Parent(int i) {
  return (i - 1) / 2;
}

int LeftChield(int i) {
  return 2 * i + 1;
}

int RightChield(int i) {
  return 2 * i + 2;
}

template <class T>
void SiftUp(T *begin, int idx) {
  int parent = Parent(idx);
  if ((idx > 0) && (*(begin + parent) < *(begin + idx))) {
    Swap(*(begin + parent), *(begin + idx));
    SiftUp(begin, parent);
  }
}

template <class T>
void SiftDown(T *begin, int idx, int count) {
  int left = LeftChield(idx);
  int right = RightChield(idx);
  int largest = idx;
  if ((left < count) && (*(begin + largest) < *(begin + left))) {
    largest = left;
  }
  if ((right < count) && (*(begin + largest) < *(begin + right))) {
    largest = right;
  }
  if (largest != idx) {
    Swap(*(begin + largest), *(begin + idx));
    SiftDown(begin, largest, count);
  }
}

template <class T>
void PopHeap(T *begin, T *end) {
  end--;
  Swap(*begin, *end);
  int idx = 0;
  int count = end - begin;
  SiftDown(begin, idx, count);
}

template <class T>
void PushHeap(T *begin, T *end) {
  end--;
  SiftUp(begin, end - begin);
}