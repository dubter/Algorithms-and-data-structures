/*
Напишите программу, которая определяет, сколько раз встречается заданное число x в данном массиве. Используйте последовательный контейнер и библиотеку алгоритмов для решения задачи. Старайтесь избегать циклов.

Формат ввода
В первой строке задается одно натуральное число N, не превосходящее 1,000,000 — размер массива.

Во второй строке вводятся N чисел — элементы массива (целые числа, не превосходящие по модулю 1,000).

В третьей строке содержится одно целое число x , не превосходящее по модулю 1,000,000.

Формат вывода
Вывести одно число — сколько раз встречается x в данном массиве.
 */

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  size_t n;
  std::cin >> n;
  std::vector<int32_t> numbers;
  numbers.reserve(n);
  int32_t tmp;
  for (size_t i = 0; i < n; i++) {
    std::cin >> tmp;
    numbers.push_back(tmp);
  }
  int64_t desired;
  std::cin >> desired;
  size_t count = std::count(numbers.begin(), numbers.end(), desired);
  std::cout << count << std::endl;
  return 0;
}
