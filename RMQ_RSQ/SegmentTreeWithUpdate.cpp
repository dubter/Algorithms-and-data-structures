/*
 Ёлки-иголки, да что же это такое тут происходит?

После ударного дачного сезона Копатыч расставил свои ульи в ряд, чтобы определить лучшую пчелиную семью (подотрезок ряда).

Качество пчелиной семьи Копатыч определяет по наибольшему количеству собранного меда в одном улье. Периодически Копатыч собирает дополнительный мед из того или иного улья.

Необходимо помочь Копатычу определить качество каждой пчелиной семьи и разобраться в его отношениях со сбором меда.

Формат ввода
В первой строке вводится одно натуральное число N (1≤N≤100000) — количество ульев в ряду.

Во второй строке вводятся N чисел от 0 до 100000 — количество собранного меда с каждого улья в начальный момент.

В третьей строке вводится одно натуральное число M
(1≤M≤30000) — количество запросов Копатыча.

Каждая из следующих M строк представляет собой описание запроса.
 Сначала вводится одна буква, кодирующая вид запроса (m — найти наибольшее число собранного меда в семье,
a — увеличить число собранного меда у пчелиной семьи).
Следом за m вводятся два числа — левая и правая граница ряда.

Следом за a вводятся три числа — левый и правый концы ряда и число
add, на которое нужно увеличить количество собранного меда у каждого улья данной пчелиной семьи
(0≤add≤100000).

Формат вывода
Выведите в одну строку через пробел ответы на каждый запрос m.
 */

#include <iostream>
#include <vector>

class SegmentTree {
 public:
  explicit SegmentTree(const std::vector<uint32_t> &numbers) {
    segment_tree_.reserve(numbers.size());
    for (uint32_t i = 0; i < numbers.size(); ++i) {
      segment_tree_.emplace_back(std::pair(numbers[i], 0));
    }
    uint32_t size = 1;
    while (size < numbers.size()) {
      size *= 2;
    }
    segment_tree_.resize(2 * size - 1);
    for (uint32_t i = 0; i < numbers.size(); ++i) {
      segment_tree_[i + size - 1] = segment_tree_[i];
      segment_tree_[i].first = 0;
    }
    for (uint32_t i = numbers.size(); i < size; ++i) {
      segment_tree_[i + size - 1].first = 0;
    }
    for (int32_t i = size - 2; i >= 0; --i) {
      segment_tree_[i] = std::max(segment_tree_[Left(i)], segment_tree_[Right(i)]);
    }
  }
  // 0 - indexation
  uint32_t Left(uint32_t index) {
    return 2 * index + 1;
  }
  uint32_t Right(uint32_t index) {
    return 2 * index + 2;
  }

  void Push(uint32_t node) {
    segment_tree_[node].first += segment_tree_[node].second;
    segment_tree_[Left(node)].second += segment_tree_[node].second;
    segment_tree_[Right(node)].second += segment_tree_[node].second;
    segment_tree_[node].second = 0;
  }

  void Update(uint32_t left, uint32_t right, uint32_t node, uint32_t a, uint32_t b, uint32_t change) {
    if (a >= left && b <= right) {
      segment_tree_[node].second += change;
      return;
    }
    if (b < left || a > right) {
      return;
    }
    Push(node);
    Update(left, right, Left(node), a, (a + b) / 2, change);
    Update(left, right, Right(node), (a + b) / 2 + 1, b, change);
    segment_tree_[node].first = std::max(segment_tree_[Left(node)].first + segment_tree_[Left(node)].second,
                                         segment_tree_[Right(node)].first + segment_tree_[Right(node)].second);
  }

  uint32_t Query(uint32_t left, uint32_t right, uint32_t node, uint32_t a, uint32_t b) {
    if (a >= left && b <= right) {
      return segment_tree_[node].first + segment_tree_[node].second;
    }
    if (b < left || a > right) {
      return 0;
    }
    Push(node);
    return std::max(Query(left, right, Left(node), a, (a + b) / 2),
                    Query(left, right, Right(node), (a + b) / 2 + 1, b));
  }
  size_t Size() const {
    return segment_tree_.size();
  }

 private:
  std::vector<std::pair<uint32_t, uint32_t>> segment_tree_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  uint32_t n, q, left, right, change;
  char symbol;
  std::cin >> n;
  std::vector<uint32_t> numbers;
  uint32_t tmp;
  numbers.reserve(n);
  for (uint32_t i = 0; i < n; ++i) {
    std::cin >> tmp;
    numbers.emplace_back(tmp);
  }
  SegmentTree segment_tree(numbers);
  std::cin >> q;
  for (uint32_t i = 0; i < q; ++i) {
    std::cin >> symbol >> left >> right;
    left--;
    right--;
    if (symbol == 'm') {
      std::cout << segment_tree.Query(left, right, 0, 0, segment_tree.Size() / 2 - 1) << "\n";
    } else {
      std::cin >> change;
      segment_tree.Update(left, right, 0, 0, segment_tree.Size() / 2 - 1, change);
    }
  }
  return 0;
}