/*
Юный программист Саша написал свою первую тестирующую систему. Он так обрадовался тому, что она скомпилировалась, что решил пригласить школьных друзей на свой собственный контест.

Но в конце тура выяснилось, что система не умеет сортировать команды в таблице результатов. Помогите Саше реализовать эту сортировку.

Команды упорядочиваются по правилам ACM:

1) по количеству решённых задач в порядке убывания;
2) при равенстве количества решённых задач – по штрафному времени в порядке возрастания;
3) при прочих равных — по номеру команды в порядке возрастания.
Используйте в этой задаче std::vector, std::sort и собственный компаратор.
 Формат ввода
Первая строка содержит натуральное число n (1 ≤ n ≤ 105) — количество команд, участвующих в контесте.

В i-й из следующих n строк записано количество решенных задач S (0 ≤ S ≤ 100) и штрафное время T (0 ≤ T ≤ 105) команды с номером i.

Формат вывода
В выходной файл выведите n чисел — номера команд в отсортированном порядке.
 */

#include <algorithm>
#include <iostream>
#include <vector>

class Team {
 public:
  size_t num_;
  size_t amount_of_tasks_;
  size_t penalty_time_;
};

bool Comparator(const Team &first_team, const Team &second_team) {
  return first_team.amount_of_tasks_ > second_team.amount_of_tasks_ ||
      (first_team.amount_of_tasks_ == second_team.amount_of_tasks_ &&
          (first_team.penalty_time_ < second_team.penalty_time_ ||
              (first_team.penalty_time_ == second_team.penalty_time_ && first_team.num_ < second_team.num_)));
}

int main() {
  size_t size;
  std::vector<Team> teams;
  std::cin >> size;
  teams.reserve(size);
  size_t tmp1;
  size_t tmp2;
  size_t num;
  for (size_t i = 0; i < size; i++) {
    num = i + 1;
    std::cin >> tmp1;
    std::cin >> tmp2;
    teams.push_back({num, tmp1, tmp2});
  }
  std::sort(teams.begin(), teams.end(), Comparator);
  for (size_t i = 0; i < size; i++) {
    std::cout << teams[i].num_ << std::endl;
  }
  return 0;
}

