/*
Вам дан словарь, состоящий из пар слов. Каждое слово является синонимом к парному ему слову. Все слова в словаре различны. Для каждого данного слова определите его синоним.

Для решения данной задачи используйте std::unordered_map

Формат ввода
Программа получает на вход количество пар синонимов N (0 ≤ N ≤ 105). Далее следует N строк, каждая строка содержит ровно два слова-синонима.

Затем идет число Q (1 ≤ Q ≤ 105) — количество запросов к словарю. Далее на каждой следующей из Q строк идет слово, к которому надо вывести синоним.

Формат вывода
Программа должна вывести синонимы к данным слову на отдельных строках.
 */

#include <iostream>
#include <string>
#include <unordered_map>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t n, m;
  std::cin >> n;
  std::string str1, str2;
  std::unordered_map<std::string, std::string> synonyms;
  for (size_t i = 0; i < n; i++) {
    std::cin >> str1;
    std::cin >> str2;
    synonyms.emplace(str1, str2);
    synonyms.emplace(str2, str1);
  }
  std::cin >> m;
  for (size_t i = 0; i < m; i++) {
    std::cin >> str1;
    std::cout << synonyms[str1] << "\n";
  }
  return 0;
}

