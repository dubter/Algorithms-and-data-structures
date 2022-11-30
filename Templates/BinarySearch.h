#pragma once

template <class T>
bool BinarySearch(const T *begin, const T *end, const T &target) {
  int left = 0;
  int right = end - begin - 1;
  while (right >= left) {
    int middle = (right + left) / 2;
    if (target < *(begin + middle)) {
      right = middle - 1;
    } else if (*(begin + middle) < target) {
      left = middle + 1;
    } else {
      return true;
    }
  }
  return false;
}