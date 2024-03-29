/*
Уже долгое время в Институте Мутантов, Фич Технологических и Иностранных языков разводят милых разноцветных зверюшек. Для удобства каждый цвет обозначен своим номером, всего цветов не более 109.

В один из прекрасных дней в питомнике случилось чудо: все зверюшки выстроились в ряд в порядке возрастания цветов. Пользуясь случаем, лаборанты решили посчитать, сколько зверюшек разных цветов живет в питомнике, и, по закону жанра, попросили вас написать программу, которая поможет им в решении этой нелегкой задачи.

Для решения этой задачи используйте std::vector и библиотеку algorithm.
 Формат ввода
В первой строке входного файла содержится единственное число N (0 ≤ N ≤ 105) — количество зверюшек в Институте.

В следующей строке находятся N упорядоченных по неубыванию неотрицательных целых чисел, не превосходящих 109 и разделенных пробелами — их цвета.

В третьей строке файла записано число M (1 ≤ M ≤ 100000) — количество запросов вашей программе, в следующей строке через пробел записаны M целых неотрицательных чисел (не превышающих 109+1).

Формат вывода
Выходной файл должен содержать M строчек. Для каждого запроса выведите число зверюшек заданного цвета в питомнике.
 */

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  size_t n, m;
  std::cin >> n;
  std::vector<size_t> colours;
  colours.reserve(n);
  size_t tmp;
  for (size_t i = 0; i < n; i++) {
    std::cin >> tmp;
    colours.push_back(tmp);
  }
  std::cin >> m;
  size_t count;
  for (size_t i = 0; i < m; i++) {
    std::cin >> tmp;
    auto start = std::lower_bound(colours.begin(), colours.end(), tmp);
    auto end = std::upper_bound(colours.begin(), colours.end(), tmp);
    count = end - start;
    std::cout << count << std::endl;
  }
  return 0;
}

