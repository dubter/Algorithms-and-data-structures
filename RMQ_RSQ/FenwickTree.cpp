/*
 Я тебя породить, я тебе и говорить «до свидания»! Auf Wiedersehen!

Пин готовится к технологической выставке, продумывая лучшую расстановку экспонатов. По мнению пингвина, расстановка будет наилучшей, если все его механизмы будут расположены вдоль одной прямой.

Теперь Пин ищет, а как лучше распределить устройства вдоль стенда, чтобы произвести впечатление на комиссию. Он попросил вас, как лучшего программиста Ромашковой долины, написать программу, которая сможет отвечать на два типа запросов:

1) "s l r" — узнать суммарную технологическую сложность устройств, расположенных на отрезке [l,r] в 1-индексации;

2)"u i v" — переставить приборы так, чтобы в позиции с индексом i технологическая сложность стала v. Считайте, что он просто заменяет технологическую сложность на позиции
i на сложность v. Не задумывайтесь, как Пин это делает, - его гениальность нам не постижима.

Формат ввода
В первой строке вводится одно натуральное число N — длина стенда.

Во второй строке вводятся N чисел — изначальная расстановка экспонатов.

В третьей строке вводится одно натуральное число M — количество запросов.

Каждая из следующих M строк представляет собой описание запроса в формате выше.

Формат вывода
Для каждого запроса s выведите результат. Все числа выводите в одну строку через пробел.


 */

#include <cmath>
#include <iostream>
#include <vector>

class BinaryIndexedTree {
 public:
  explicit BinaryIndexedTree(const std::vector<int64_t> &number_releases) : number_releases_(number_releases) {
    size_t sum = 0;
    prefix_sum_.reserve(number_releases_.size());
    bit_.reserve(number_releases_.size());
    for (size_t i = 0; i < number_releases_.size(); ++i) {
      sum += number_releases_[i];
      prefix_sum_.emplace_back(sum);
    }
    int64_t j;
    for (size_t i = 0; i < number_releases_.size(); ++i) {
      j = static_cast<int64_t>((i & (i + 1))) - 1;
      if (j < 0) {
        bit_.emplace_back(prefix_sum_[i]);
      } else {
        bit_.emplace_back(prefix_sum_[i] - prefix_sum_[j]);
      }
    }
  }
  void Update(int64_t index, int64_t value) {
    index -= 1;
    value -= number_releases_[index];
    for (auto i = index; i < static_cast<int64_t>(bit_.size()); i = i | (i + 1)) {
      bit_[i] += value;
    }
    number_releases_[index] += value;
  }

  size_t Query(int64_t index) const {
    size_t sum = 0;
    for (auto i = index; i >= 0; i = static_cast<int64_t>(i & (i + 1)) - 1) {
      sum += bit_[i];
    }
    return sum;
  }

  size_t Query(size_t left, size_t right) const {
    left--;
    right--;
    if (left == 0) {
      return Query(right);
    }
    return Query(right) - Query(left - 1);
  }

 private:
  std::vector<int64_t> prefix_sum_;
  std::vector<int64_t> bit_;
  std::vector<int64_t> number_releases_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t n, q;
  size_t tmp, left, right, index, value;
  std::vector<int64_t> number_releases;
  std::cin >> n;
  number_releases.reserve(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> tmp;
    number_releases.emplace_back(tmp);
  }
  BinaryIndexedTree binary_indexed_tree(number_releases);
  std::cin >> q;
  char mode;
  for (size_t i = 0; i < q; ++i) {
    std::cin >> mode;
    if (mode == 's') {
      std::cin >> left >> right;
      std::cout << binary_indexed_tree.Query(left, right) << " ";
    } else {
      std::cin >> index >> value;
      binary_indexed_tree.Update(index, value);
    }
  }
  return 0;
}