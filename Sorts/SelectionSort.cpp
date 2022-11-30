#include <iostream>
#include <vector>

void SelectionSort(std::vector<int> &array) {
  for (size_t i = 0; i < array.size() - 1; i++) {
    for (size_t j = i + 1; j < array.size(); j++) {
      if (array[i] > array[j]) {
        std::swap(array[j], array[i]);
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
  SelectionSort(array);
  for (size_t i = 0; i < number_elems; i++) {
    std::cout << array[i] << " ";
  }
  return 0;
}