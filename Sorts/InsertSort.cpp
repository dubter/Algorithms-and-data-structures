#include <iostream>
#include <vector>

void InsertSort(std::vector<int> &array) {
  int j;
  for (int i = 1; i < array.size(); i++) {
    j = i - 1;
    while (j >= 0 && array[j] > array[j + 1]) {
      std::swap(array[j], array[j + 1]);
      j--;
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
  InsertSort(array);
  for (size_t i = 0; i < number_elems; i++) {
    std::cout << array[i] << " ";
  }
  return 0;
}