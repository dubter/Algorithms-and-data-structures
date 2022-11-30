#include <iostream>
#include <vector>

void SelectionSortOptimized(std::vector<int> &array) {
  size_t min;
  for (size_t i = 0; i < array.size() - 1; i++) {
    min = i;
    for (size_t j = i + 1; j < array.size(); j++) {
      if (array[j] < array[min]) {
        min = j;
      }
    }
    std::swap(array[min], array[i]);
  }
}

int main() {
  size_t number_elems;
  std::cin >> number_elems;
  std::vector<int> array(number_elems);
  for (size_t i = 0; i < number_elems; i++) {
    std::cin >> array[i];
  }
  SelectionSortOptimized(array);
  for (size_t i = 0; i < number_elems; i++) {
    std::cout << array[i] << " ";
  }
  return 0;
}