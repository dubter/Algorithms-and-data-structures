#include <iostream>
#include <vector>

void BubbleSortOptimized(std::vector<int> &array) {
  bool sorted = false;
  size_t i = 0;
  while (!sorted) {
    sorted = true;
    for (size_t j = 0; j < array.size() - i - 1; j++) {
      if (array[j] > array[j + 1]) {
        std::swap(array[j], array[j + 1]);
        sorted = false;
      }
    }
    i++;
  }
}

int main() {
  size_t number_elems;
  std::cin >> number_elems;
  std::vector<int> array(number_elems);
  for (size_t i = 0; i < number_elems; i++) {
    std::cin >> array[i];
  }
  BubbleSortOptimized(array);
  for (size_t i = 0; i < number_elems; i++) {
    std::cout << array[i] << " ";
  }
  return 0;
}