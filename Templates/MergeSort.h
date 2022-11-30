#pragma once

template <class T>
void Merge(T *begin, T *end) {
  auto *tmp = new T[end - begin + 1];
  int size = 0, i = 0;
  int middle = (end - begin) / 2;
  int j = middle + 1;
  while (i <= middle && j <= end - begin) {
    if (*(begin + i) < *(begin + j)) {
      tmp[size] = *(begin + i);
      i++;
    } else {
      tmp[size] = *(begin + j);
      j++;
    }
    size++;
  }
  while (i <= middle) {
    tmp[size] = *(begin + i);
    i++;
    size++;
  }
  while (j <= end - begin) {
    tmp[size] = *(begin + j);
    j++;
    size++;
  }
  for (int k = 0; k < size; k++) {
    *(begin + k) = tmp[k];
  }
  delete[] tmp;
}

template <class T>
void Sort(T *begin, T *end) {
  static bool x = true;
  if (x) {
    end--;
    x = false;
  }
  if (0 < end - begin) {
    Sort(begin, begin + (end - begin) / 2);
    Sort(begin + (end - begin) / 2 + 1, end);
    Merge(begin, end);
  }
}