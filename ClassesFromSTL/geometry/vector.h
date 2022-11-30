#pragma once
#include <iostream>

namespace geometry {
class Vector {
 public:
  int64_t GetX() const;
  int64_t GetY() const;
  Vector();
  Vector(const Vector &vector);
  Vector(const int64_t &x1, const int64_t &x2, const int64_t &y1, const int64_t &y2);
  Vector(const int64_t &x, const int64_t &y);
  ~Vector() = default;
  Vector &operator=(const Vector &vector);
  const Vector operator+(const Vector &vector) const;
  const Vector operator-(const Vector &vector) const;
  const Vector operator+() const;
  const Vector operator-() const;
  Vector &operator+=(const Vector &vector);
  Vector &operator-=(const Vector &vector);
  Vector &operator*=(const int64_t &num);
  Vector &operator/=(const int64_t &num);
  const Vector operator/(const int64_t &num) const;
  bool operator==(const Vector &vector) const;
  bool operator!=(const Vector &vector) const;
  bool Parallel(const Vector &vector2) const;
  int64_t VectorProduct(const Vector &vector) const;
  int64_t ScalarProduct(const Vector &vector) const;
  size_t Distance() const;
  friend const Vector operator*(const Vector &vector, const int64_t &num);
  friend const Vector operator*(const int64_t &num, const Vector &vector);

 private:
  int64_t x_;
  int64_t y_;
};

const Vector operator*(const Vector &vector, const int64_t &num);
const Vector operator*(const int64_t &num, const Vector &vector);
}  // namespace geometry