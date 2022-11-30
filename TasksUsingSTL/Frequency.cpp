/*
Дан текст. Выведите все слова, встречающиеся в тексте, по одному на каждую строку. Слова должны быть отсортированы по убыванию их количества появления в тексте, а при одинаковой частоте появления в лексикографическом порядке.

Input format
Вводится текст — последовательность строк через пробел или перенос строки.

Output format
Выведите ответ на задачу.
 */

#include <algorithm>
#include <exception>
#include <iostream>
#include <map>
#include <string>
#include <vector>

bool Comparator(const std::pair<std::string, size_t> &first, const std::pair<std::string, size_t> &second) {
  return first.second > second.second || (first.second == second.second && first.first < second.first);
}

int main() {
  std::map<std::string, size_t> words;
  std::string string;
  while (std::cin >> string && string != "kek") {
    words[string] += 1;
  }
  std::vector<std::pair<std::string, size_t>> frequency;
  frequency.reserve(words.size());
  for (auto &it : words) {
    std::pair<std::string, size_t> pair(it.first, it.second);
    frequency.emplace_back(pair);
  }
  std::sort(frequency.begin(), frequency.end(), Comparator);
  for (auto &item : frequency) {
    std::cout << item.first << "\n";
  }
  return 0;
}
