#include <iostream>
#include <vector>

long long CountCombinations(std::vector<int> &array) {
  array[1] = 0;
  array[2] = 1;
  for (int i = 3; i < array.size(); i++) {
    array[i] = array[i - 1] + array[i - 2];
  }
  return array[array.size() - 1];
}

int main() {
  int num = 0;
  std::cin >> num;
  std::vector<int> array(num + 1);
  std::cout << CountCombinations(array);
  return 0;
}