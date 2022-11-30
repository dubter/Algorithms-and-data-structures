/*
Формат ввода
В первой строке вводится одно натуральное число
N — количество скульптур, выставленных в ряд.
Во второй строке вводятся N чисел — количество голосов у скульптур в ряду.
В третьей строке вводится одно натуральное число K — количество запросов Копатыча.
В следующих K строках вводится по два числа — номера левого и правого концов композиции (считается, что скульптуры нумеруются с единицы).

Формат вывода
Для каждого запроса выведите сумму чисел соответствующей композиции скульптур. Числа выводите в одну строку через пробел.
 */

#include <iostream>
#include <vector>

int main() {
  size_t n, k, vote, sum = 0;
  std::vector<size_t> sculptures;
  std::cin >> n;
  for (size_t i = 0; i < n; ++i) {
    std::cin >> vote;
    sum += vote;
    sculptures.emplace_back(sum);
  }
  std::cin >> k;
  size_t left, right;
  for (size_t i = 0; i < k; ++i) {
    std::cin >> left >> right;
    if (left == 1) {
      std::cout << sculptures[right - 1] << " ";
    } else {
      std::cout << sculptures[right - 1] - sculptures[left - 2] << " ";
    }
  }
  return 0;
}