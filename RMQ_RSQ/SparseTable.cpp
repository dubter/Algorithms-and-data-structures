/*
Очень трудно жить, думая о каждой ошибке, которую ты совершил, поэтому всё плохое забываешь, а помнишь только хорошее — очень удобно, но от себя не уйдёшь.

Для новой серии научно-популярного шоу смешарикам необходимо найти в творческой команде самого сообразительного смешарика, принявшего участие в наименьшем количестве выпусков. Командой может быть любая шеренга смешариков. Вам нужно помочь нашим героям для каждой команды, которую они попросят, найти самого редкого гостя на экране.

Формат ввода
В первой строке вводятся два числа n, q - число смешариков и число запросов. В следующей строке
n чисел - количество выпусков с каждым из смешариков. В следующих q строках запросы 1≤l≤r≤n

Формат вывода
Выведите ответы на q запросов
 */

#include <cmath>
#include <iostream>
#include <vector>

class SparseTable {
 public:
  explicit SparseTable(const std::vector<size_t> &number_releases) : number_releases_(number_releases) {
    size_t tmp_size;
    size_t log = log2(number_releases.size());
    st_.reserve(log);
    st_.emplace_back(number_releases);
    for (size_t k = 1; k <= log; ++k) {
      st_.emplace_back();
      tmp_size = number_releases_.size() - pow(2, k);
      st_[k].reserve(tmp_size + 1);
      for (size_t i = 0; i <= tmp_size; ++i) {
        st_[k].emplace_back(std::min(st_[k - 1][i], st_[k - 1][i + pow(2, k - 1)]));
      }
    }
  }
  size_t Query(size_t left, size_t right) {
    size_t log;
    left -= 1;
    right -= 1;
    log = log2(right - left + 1);
    return std::min(st_[log][left], st_[log][right - pow(2, log) + 1]);
  }

 private:
  std::vector<std::vector<size_t>> st_;
  std::vector<size_t> number_releases_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t n, q;
  size_t tmp, left, right;
  std::vector<size_t> number_releases;
  std::cin >> n >> q;
  number_releases.reserve(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> tmp;
    number_releases.emplace_back(tmp);
  }
  SparseTable sparse_table(number_releases);
  for (size_t i = 0; i < q; ++i) {
    std::cin >> left >> right;
    std::cout << sparse_table.Query(left, right) << "\n";
  }
  return 0;
}