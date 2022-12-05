#pragma once

template <typename T>
T Gcd(T x, T y) {
  T tmp;
  while (x != y && y != 0) {
    x %= y;
    tmp = x;
    x = y;
    y = tmp;
  }
  return x;
}