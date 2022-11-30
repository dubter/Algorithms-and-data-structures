#pragma once
template <class T>
void KthElement(T *begin, T *kth, T *end) {
  static bool first_go = true;
  if (first_go) {
    end--;
    first_go = false;
  }
  if (0 < end - begin) {
    int partition_index = Partition(begin, end);
    if (partition_index < kth - begin) {
      KthElement(begin + partition_index + 1, kth, end);
    } else {
      KthElement(begin, kth, begin + partition_index);
    }
  }
}

template <class T>
int Partition(T *begin, T *end) {
  int i = 0;
  int j = end - begin;
  int pivot = (end - begin) / 2;
  T pivot_value = *(begin + pivot);
  while (!(j < i)) {
    while (*(begin + i) < pivot_value) {
      i++;
    }
    while (pivot_value < *(begin + j)) {
      j--;
    }
    if (!(i < j)) {
      break;
    }
    T tmp = *(begin + i);
    *(begin + i) = *(begin + j);
    *(begin + j) = tmp;
    i++;
    j--;
  }
  return j;
}