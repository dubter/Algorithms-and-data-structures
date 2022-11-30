#include <iostream>
#include <vector>

void FindSequence(std::vector<std::vector<int>> &lcs, size_t i, size_t j, std::vector<int> &firstSequence, std::vector<int> &secondSequence) {
  if ((i == 0) || (j == 0)) {
    return;
  }
  if (firstSequence[i] == secondSequence[j]) {
    FindSequence(lcs, i - 1, j - 1, firstSequence, secondSequence);
    std::cout << firstSequence[i] << " ";
  } else if (lcs[i - 1][j] > lcs[i][j - 1]) {
    FindSequence(lcs, i - 1, j, firstSequence, secondSequence);
  } else {
    FindSequence(lcs, i, j - 1, firstSequence, secondSequence);
  }
}

void PrintLCS(std::vector<int> &firstSequence, std::vector<int> &secondSequence) {
  std::vector<std::vector<int>> lcs(firstSequence.size());
  for (int i = 0; i < firstSequence.size(); i++) {
    lcs[i].resize(secondSequence.size());
  }
  for (int i = 0; i < firstSequence.size(); i++) {
    lcs[i][0] = 0;
  }
  for (int j = 0; j < secondSequence.size(); j++) {
    lcs[0][j] = 0;
  }
  for (int i = 1; i < firstSequence.size(); i++) {
    for (int j = 1; j < secondSequence.size(); j++) {
      if (firstSequence[i] == secondSequence[j]) {
        lcs[i][j] = lcs[i - 1][j - 1] + 1;
      } else {
        lcs[i][j] = std::max(lcs[i - 1][j], lcs[i][j - 1]);
      }
    }
  }
  FindSequence(lcs, firstSequence.size() - 1, secondSequence.size() - 1, firstSequence, secondSequence);
}

int main() {
  int amount1 = 0, amount2 = 0;
  std::cin >> amount1;
  std::vector<int> firstSequence(amount1 + 1);
  for (int i = 1; i <= amount1; i++) {
    std::cin >> firstSequence[i];
  }
  std::cin >> amount2;
  std::vector<int> secondSequence(amount2 + 1);
  for (int i = 1; i <= amount2; i++) {
    std::cin >> secondSequence[i];
  }
  PrintLCS(firstSequence, secondSequence);
  return 0;
}