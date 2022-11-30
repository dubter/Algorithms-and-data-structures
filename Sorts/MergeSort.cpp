#include <iostream>
#include <vector>

void Merge(std::vector<int> &array, size_t left, size_t right) {
  size_t i = left;
  size_t middle = (left + right) / 2;
  size_t j = middle + 1;
  std::vector<int> buffer(right - left + 1);
  size_t count = 0;
  while (i <= middle && j <= right) {
    if (array[i] < array[j]) {
      buffer[count] = array[i];
      i++;
    } else {
      buffer[count] = array[j];
      j++;
    }
    count++;
  }

  while (i <= middle) {
    buffer[count] = array[i];
    i++;
    count++;
  }
  while (j <= right) {
    buffer[count] = array[j];
    j++;
    count++;
  }
  for (size_t k = 0; k < count; k++) {
    array[left + k] = buffer[k];
  }
}

void MergeSort(std::vector<int> &array, size_t left, size_t right) {
  if (left < right) {
    MergeSort(array, left, (left + right) / 2);
    MergeSort(array, (left + right) / 2 + 1, right);
    Merge(array, left, right);
  }
}

int main() {
  size_t number_elems = 0;
  std::cin >> number_elems;
  std::vector<int> array(number_elems);
  for (size_t i = 0; i < number_elems; i++) {
    std::cin >> array[i];
  }
  MergeSort(array, 0, number_elems - 1);
  for (int i = 0; i < number_elems; i++) {
    std::cout << array[i] << " ";
  }
  return 0;
}