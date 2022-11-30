#include <iostream>
#include <vector>

int BinarySearch(const std::vector<int> &sequence, int left, int right, int key) {
  while (right > 1 + left) {
    int middle = left + (right - left) / 2;
    if (sequence[middle] >= key) {
      right = middle;
    } else {
      left = middle;
    }
  }
  return right;
}

int FastLIS(std::vector<int> &sequence) {
  std::vector<int> buffer(sequence.size());
  buffer[0] = sequence[0];
  int size = 1;
  for (int i = 1; i < sequence.size(); i++) {
    if (sequence[i] < buffer[0]) {
      buffer[0] = sequence[i];
    } else if (sequence[i] > buffer[size - 1]) {
      buffer[size] = sequence[i];
      size++;
    } else {
      buffer[BinarySearch(buffer, -1, size - 1, sequence[i])] = sequence[i];
    }
  }
  return size;
}

int main() {
  int amount_numbers;
  std::cin >> amount_numbers;
  std::vector<int> sequence(amount_numbers);
  for (int i = 0; i < amount_numbers; i++) {
    std::cin >> sequence[i];
  }
  std::cout << FastLIS(sequence);
  return 0;
}