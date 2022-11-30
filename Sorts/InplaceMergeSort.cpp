#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

void InplaceMergeSort(std::vector<int>::iterator first_beg, std::vector<int>::iterator first_end, std::vector<int>::iterator second_beg, std::vector<int>::iterator second_end) {
  int first_size = static_cast<int>(std::distance(first_beg, first_end));
  int second_size = static_cast<int>(second_end - second_beg);
  if (first_size == 0 || second_size == 0) {
    return;
  }
  if (first_size == 1 && second_size == 1) {
    if (*first_beg > *second_beg) {
      std::swap(*first_beg, *second_beg);
    }
    return;
  }
  auto B1_beg = first_beg;
  std::vector<int>::iterator B1_end;
  std::vector<int>::iterator B2_beg;
  auto B2_end = first_end;
  auto B3_beg = second_beg;
  std::vector<int>::iterator B3_end;
  std::vector<int>::iterator B4_beg;
  auto B4_end = second_end;
  if (first_size >= second_size) {
    B1_end = first_beg + first_size / 2;
    B2_beg = B1_end;
    auto sep = std::lower_bound(second_beg, second_end, *B2_beg);
    B3_end = sep;
    B4_beg = sep;
  }
  else {
    B3_end = second_beg + second_size / 2;
    B4_beg = B3_end;
    auto sep = std::upper_bound(first_beg, first_end, *B4_beg);
    B1_end = sep;
    B2_beg = sep;
  }
  std::rotate(B2_beg, B3_beg, B3_end);
  auto B3_size = std::distance(B3_beg, B3_end);
  InplaceMergeSort(B1_beg, B1_end, B2_beg, B2_beg + B3_size);
  InplaceMergeSort(B2_beg + B3_size, B3_end, B4_beg, B4_end);
}

void MergeSort(std::vector<int> &array, std::vector<int>::iterator beg, std::vector<int>::iterator end) {
  if (std::distance(beg, end) <= 1) {
    return;
  }
  size_t mid = std::distance(beg, end) / 2;
  auto middle = beg;
  for (size_t i = 0; i < mid; i++) {
    if (middle != end) {
      ++middle;
    }
  }
  MergeSort(array, beg, middle);
  MergeSort(array, middle, end);
  InplaceMergeSort(beg, middle, middle, end);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t number_elems;
  std::cin >> number_elems;
  std::vector<int> array(number_elems);
  for (size_t i = 0; i < number_elems; ++i) {
    std::cin >> array[i];
  }
  MergeSort(array, array.begin(), array.end());
  for (size_t i = 0; i < number_elems; ++i) {
    std::cout << array[i] << " ";
  }
  return 0;
}