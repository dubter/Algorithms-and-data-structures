#include <iostream>
#include <vector>

void BubbleSort(std::vector<int> &array) {
  for (size_t i = 0; i < array.size() - 1; i++) {
    for (size_t j = 0; j < array.size() - 1; j++) {
      if (array[j] > array[j + 1]) {
        std::swap(array[j], array[j + 1]);
      }
    }
  }
}

int main() {
  size_t number_elems;
  std::cin >> number_elems;
  std::vector<int> array(number_elems);
  for (size_t i = 0; i < number_elems; i++) {
    std::cin >> array[i];
  }
  BubbleSort(array);
  for (size_t i = 0; i < number_elems; i++) {
    std::cout << array[i] << " ";
  }
  return 0;
}