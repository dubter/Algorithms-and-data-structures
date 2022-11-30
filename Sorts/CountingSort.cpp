#include <iostream>
#include <vector>

void CountingSort(std::vector<int> &array, const size_t max_elem) {
  std::vector<size_t> counting(max_elem, 0);
  for (int i : array) {
    counting[i]++;
  }
  size_t counter = 0;
  for (int i = 0; i < max_elem; i++) {
    for (int j = 0; j < counting[i]; j++) {
      array[counter] = i;
      counter++;
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
  CountingSort(array, 100);
  for (size_t i = 0; i < number_elems; i++) {
    std::cout << array[i] << " ";
  }
  return 0;
}