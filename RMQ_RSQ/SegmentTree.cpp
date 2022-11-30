/*
 Если ты не можешь бросить старый зонтик, то как мы можем бросить тебя — старого друга? Ты ведь тоже часть нашей биографии.

Наконец-то к популярному среди старшего поколения явлению потянулась и перспективная молодежь. Крош изучает тренды Шар-Тока и пытается найти лучших кандидатов для совместного видео. Чтобы видео залетело в тренды, нашему другу нужно знать, сколько именно смешариков в конкретном творческом объединении имеет максимальное число подписчиков.

Если вы вдруг забыли, то напомним, что все выборы в Шарараме примечательны тем, что любой подотрезок ряда является творческим объединением.

 Формат ввода
В первой строке вводится одно натуральное число N ~--- количество смешариков в ряду.

Во второй строке вводятся N чисел ~--- количество подписчиков у смешарика.

В третьей строке вводится одно натуральное число K ~--- количество запросов Кроша.

В следующих K строках вводится по два числа ~--- номера левого и правого смешарика, границ творческого объединения (в 1-индексации).

Формат вывода
Для каждого запроса выведите в отдельной строке через пробел максимальное количество подписчиков у смешарика в указанном объединении и количество смешариков с числом подписчиков, равным максимальному.
 */

#include <iostream>
#include <vector>

class SegmentTree {
 public:
  explicit SegmentTree(const std::vector<uint32_t> &initial_nums) {
    size_t size = 1;
    while (size < initial_nums.size()) {
      size *= 2;
    }
    segment_tree_.resize(2 * size - 1);
    for (uint32_t i = 0; i < initial_nums.size(); ++i) {
      segment_tree_[i + size - 1] = std::pair(initial_nums[i], 1);
    }
    for (uint32_t i = initial_nums.size(); i < size; ++i) {
      segment_tree_[i + size - 1] = std::pair(0, 0);
    }
    for (int32_t i = size - 2; i >= 0; --i) {
      segment_tree_[i].first = std::max(segment_tree_[Left(i)].first, segment_tree_[Right(i)].first);
      if (segment_tree_[Left(i)].first == segment_tree_[Right(i)].first) {
        segment_tree_[i].second = segment_tree_[Left(i)].second + segment_tree_[Right(i)].second;
      } else {
        if (segment_tree_[i].first == segment_tree_[Left(i)].first) {
          segment_tree_[i].second = segment_tree_[Left(i)].second;
        } else {
          segment_tree_[i].second = segment_tree_[Right(i)].second;
        }
      }
    }
  }

  // 0 - indexation
  uint32_t Parent(uint32_t index) const {
    return (index - 1) / 2;
  }
  uint32_t Left(uint32_t index) const {
    return 2 * index + 1;
  }
  uint32_t Right(uint32_t index) const {
    return 2 * index + 2;
  }

  std::pair<uint32_t, uint32_t> Query(uint32_t left, uint32_t right) const {
    left += segment_tree_.size() / 2;
    right += segment_tree_.size() / 2;
    uint32_t copy_left = left;
    uint32_t copy_right = right;
    uint32_t max = 0;
    uint32_t count = 0;
    while (left < right) {
      if (left == Right(Parent(left))) {
        max = std::max(max, segment_tree_[left].first);
      }
      left = Parent(left + 1);
      if (right == Left(Parent(right))) {
        max = std::max(max, segment_tree_[right].first);
      }
      right = Parent(right - 1);
    }
    if (left == right) {
      max = std::max(max, segment_tree_[left].first);
    }
    left = copy_left;
    right = copy_right;
    while (left < right) {
      if (left == Right(Parent(left)) && max == segment_tree_[left].first) {
        count += segment_tree_[left].second;
      }
      left = Parent(left + 1);
      if (right == Left(Parent(right)) && max == segment_tree_[right].first) {
        count += segment_tree_[right].second;
      }
      right = Parent(right - 1);
    }
    if (left == right && max == segment_tree_[left].first) {
      count += segment_tree_[left].second;
    }
    std::pair<uint32_t, uint32_t> result(max, count);
    return result;
  }

 private:
  std::vector<std::pair<uint32_t, uint32_t>> segment_tree_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  uint32_t size, q, left, right;
  uint32_t tmp;
  std::cin >> size;
  std::vector<uint32_t> initial_nums;
  initial_nums.resize(size);
  for (size_t i = 0; i < size; ++i) {
    std::cin >> tmp;
    initial_nums[i] = tmp;
  }
  SegmentTree segment_tree(initial_nums);
  std::cin >> q;
  for (uint32_t i = 0; i < q; ++i) {
    std::cin >> left >> right;
    left--;
    right--;
    std::pair<uint32_t, uint32_t> pair = segment_tree.Query(left, right);
    std::cout << pair.first << " " << pair.second << "\n";
  }
  return 0;
}
