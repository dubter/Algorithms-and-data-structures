#include <iostream>
#include <vector>

void QuickSortOptimized(int left, int right, std::vector<int> &array) {
  if (left >= right) {
    return;
  }
  int pivot_value = array[right];
  int i = left, j = right - 1;
  int p = left - 1;
  int q = right;
  while (i <= j) {
    while (array[i] < pivot_value) {
      i++;
    }
    while (j >= 0 && array[j] > pivot_value) {
      j--;
    }
    if (i >= j) {
      break;
    }
    std::swap(array[j], array[i]);
    if (array[i] == pivot_value) {
      ++p;
      std::swap(array[i], array[p]);
    }
    if (array[j] == pivot_value) {
      --q;
      std::swap(array[j], array[q]);
    }
    j--;
    i++;
  }
  std::swap(array[i], array[right]);
  j = i - 1;
  i++;
  for (int k = left; k <= p; k++, j--) {
    std::swap(array[k], array[j]);
  }
  for (int k = right - 1; k >= q; k--, i++) {
    std::swap(array[k], array[i]);
  }
  QuickSortOptimized(left, j, array);
  QuickSortOptimized(i, right, array);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int number_elems = 0;
  std::cin >> number_elems;
  std::vector<int> array(number_elems);
  for (int i = 0; i < number_elems; i++) {
    std::cin >> array[i];
  }
  QuickSortOptimized(0, number_elems - 1, array);
  for (int i = 0; i < number_elems; i++) {
    std::cout << array[i] << " ";
  }
  return 0;
}
