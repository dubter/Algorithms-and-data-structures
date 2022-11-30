#include <iostream>
#include <vector>

void FindSequence(std::vector<int> &numbers, std::vector<int> &sequence, int i, int idxOfMax) {
  if (i < 0) {
    return;
  }
  if ((sequence[idxOfMax] - sequence[i - 1] == 1) && (numbers[idxOfMax] > numbers[i - 1])) {
    FindSequence(numbers, sequence, i - 1, i - 1);
    if (i > 0) {
      std::cout << numbers[i - 1] << " ";
    }
  } else {
    FindSequence(numbers, sequence, i - 1, idxOfMax);
  }
}

void PrintLIS(std::vector<int> &numbers) {
  int max, imax = 0;
  std::vector<int> sequence(numbers.size());
  sequence[0] = 1;
  for (int i = 1; i < numbers.size(); i++) {
    max = 0;
    for (int j = 0; j < i; j++) {
      if ((max < sequence[j]) && (numbers[j] < numbers[i])) {
        max = sequence[j];
      }
    }
    if (max != 0) {
      sequence[i] = max + 1;
    } else {
      sequence[i] = 1;
    }
  }
  max = 0;
  for (int i = 0; i < numbers.size(); i++) {
    if (max < sequence[i]) {
      max = sequence[i];
      imax = i;
    }
  }
  FindSequence(numbers, sequence, imax, imax);
  std::cout << numbers[imax];
}

int main() {
  int amount_numbers = 0;
  std::cin >> amount_numbers;
  std::vector<int> numbers(amount_numbers);
  for (int i = 0; i < amount_numbers; i++) {
    std::cin >> numbers[i];
  }
  PrintLIS(numbers);
  return 0;
}