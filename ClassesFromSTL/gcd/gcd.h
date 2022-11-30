#pragma once

template<typename T>
T Gcd(T x, T y) {
  if (x == 0) {
    return y;
  }
  return Gcd(y % x, x);
}