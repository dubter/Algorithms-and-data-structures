/*
 Вот так всегда: для кого-то балласт, а для кого-то сокровище.

Ромашковая долина наконец дождалась великого дня — робот Биби вернулся из космического путешествия во главе целой космической флотилии. По опыту Биби для космоса не существует трехмерной фигуры лучше куба, поэтому его космофлот выглядит как куб с длиной стороны N.

Для организации управления наш герой разделил исходный куб на
N^3 кубиков с ребром длины 1.

Биби хочет научиться быстро обрабатывать запросы следующих типов:

1) В каком-то секторе изменилось число космолетов;
2) Узнать количество космолетов в прямоугольном параллелепипеде.

 Формат ввода
Первая строка входного файла содержит натуральное число N. Координаты секторов~--- целые числа от 0 до
N-1. Далее следуют записи о происходивших событиях по одной в строке.

В начале строки записано число m. Если m равно:
1) 1, то за ним следуют 4 числа:
x,y,z,k
(0≤x,y,z≤N,−20000≤k≤20000)~--- координаты сектора и величина, на которую в нем изменилось количество космолетов;

2) 2, то за ним следуют 6 чисел:
x1, y1, z1, x2, y2, z2, которые означают, что нужно узнать, сколько космолетов в прямоугольном параллелепипеде с данными противолежащими вершинами и сторонами, параллельными осям координат.

3) то это означает, что Биби утомился, а значит можно закончить работу программы.
Количество записей во входном файле не превосходит 100500. Изначально в воздухе нет ни одного космолета.

Формат вывода
Для каждого запроса второго типа выведите на отдельной строке одно число~--- искомое количество космолетов.
 */

#include <cmath>
#include <iostream>
#include <vector>

class BinaryIndexedTree3D {
 public:
  explicit BinaryIndexedTree3D(size_t size) {
    bit_.resize(size);
    for (size_t i = 0; i < size; ++i) {
      bit_[i].resize(size);
      for (size_t j = 0; j < size; ++j) {
        bit_[i][j].resize(size);
      }
    }
  }
  void Update(int x, int y, int z, int value) {
    for (auto i = x; i < static_cast<int>(bit_.size()); i = i | (i + 1)) {
      for (auto j = y; j < static_cast<int>(bit_.size()); j = j | (j + 1)) {
        for (auto k = z; k < static_cast<int>(bit_.size()); k = k | (k + 1)) {
          bit_[i][j][k] += value;
        }
      }
    }
  }

  size_t Query(int x, int y, int z) const {
    size_t sum = 0;
    for (auto i = x; i >= 0; i = static_cast<int>(i & (i + 1)) - 1) {
      for (auto j = y; j >= 0; j = static_cast<int>(j & (j + 1)) - 1) {
        for (auto k = z; k >= 0; k = static_cast<int>(k & (k + 1)) - 1) {
          sum += bit_[i][j][k];
        }
      }
    }
    return sum;
  }

  size_t Query(int x2, int y2, int z2, int x1, int y1, int z1) const {
    if (x1 == 0 && y1 == 0 && z1 == 0) {
      return Query(x2, y2, z2);
    }
    if (x1 == 0 && y1 == 0) {
      return Query(x2, y2, z2) - Query(x2, y2, z1 - 1);
    }
    if (x1 == 0 && z1 == 0) {
      return Query(x2, y2, z2) - Query(x2, y1 - 1, z2);
    }
    if (y1 == 0 && z1 == 0) {
      return Query(x2, y2, z2) - Query(x1 - 1, y2, z2);
    }
    if (x1 == 0) {
      return Query(x2, y2, z2) - Query(x2, y1 - 1, z2) - Query(x2, y2, z1 - 1) + Query(x2, y1 - 1, z1 - 1);
    }
    if (y1 == 0) {
      return Query(x2, y2, z2) - Query(x1 - 1, y2, z2) - Query(x2, y2, z1 - 1) + Query(x1 - 1, y2, z1 - 1);
    }
    if (z1 == 0) {
      return Query(x2, y2, z2) - Query(x2, y1 - 1, z2) - Query(x1 - 1, y2, z2) + Query(x1 - 1, y1 - 1, z2);
    }
    return Query(x2, y2, z2) - Query(x2, y2, z1 - 1) - Query(x2, y1 - 1, z2) - Query(x1 - 1, y2, z2) +
        Query(x1 - 1, y1 - 1, z2) + Query(x1 - 1, y2, z1 - 1) + Query(x2, y1 - 1, z1 - 1) -
        Query(x1 - 1, y1 - 1, z1 - 1);
  }

 private:
  std::vector<std::vector<std::vector<int>>> bit_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t size;
  std::cin >> size;
  BinaryIndexedTree3D binary_indexed_tree_3_d(size);
  int mode;
  int x1, y1, z1, x2, y2, z2, value;
  while (std::cin >> mode) {
    if (mode == 2) {
      std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
      std::cout << binary_indexed_tree_3_d.Query(x2, y2, z2, x1, y1, z1) << "\n";
    } else if (mode == 1) {
      std::cin >> x1 >> y1 >> z1 >> value;
      binary_indexed_tree_3_d.Update(x1, y1, z1, value);
    } else if (mode == 3) {
      break;
    }
  }
  return 0;
}