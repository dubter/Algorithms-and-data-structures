/*
Формат ввода
В первой строке дано натуральное число
N — длина шеренги. Во второй строке через пробел перечислена подозрительность у каждого из смешариков (учтите, что она может быть отрицательной).

Формат вывода
В одну строку через пробел выведите границы группировки (в 1-индексации), а также ее подозрительность.
 */

#include <cmath>
#include <iostream>

int main() {
  size_t n, left = 0;
  int64_t vote, sum = 0, max_sum = 0;
  size_t max_sum_left, max_sum_right;
  std::cin >> n;
  for (size_t i = 0; i < n; ++i) {
    std::cin >> vote;
    sum += vote;
    if (max_sum < sum || i == 0) {
      max_sum = sum;
      max_sum_left = left + 1;
      max_sum_right = i + 1;
    }
    if (sum < 0) {
      sum = 0;
      left = i + 1;
    }
  }
  std::cout << max_sum_left << " " << max_sum_right << " " << max_sum;
  return 0;
}