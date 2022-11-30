#include <iostream>
#include <vector>

size_t Partition(std::vector<int> &array, size_t left, size_t right) {
  size_t pivot_idx = (left + right) / 2;
  int pivot_value = array[pivot_idx];
  size_t i = left, j = right;
  while (i <= j) {
    while (array[i] < pivot_value) {
      i++;
    }
    while (array[j] > pivot_value) {
      j--;
    }
    if (i >= j) {
      break;
    }
    int t = array[i];
    array[i] = array[j];
    array[j] = t;
    i++;
    j--;
  }
  return j;
}

void QuickSort(std::vector<int> &array, size_t left, size_t right) {
  if (left < right) {
    size_t pivot_idx = Partition(array, left, right);
    QuickSort(array, left, pivot_idx);
    QuickSort(array, pivot_idx + 1, right);
  }
}

int main() {
  size_t number_elems = 0;
  std::cin >> number_elems;
  std::vector<int> array(number_elems);
  for (size_t i = 0; i < number_elems; i++) {
    std::cin >> array[i];
  }
  QuickSort(array, 0, number_elems - 1);
  for (int i = 0; i < number_elems; i++) {
    std::cout << array[i] << " ";
  }
  return 0;
}