#include "../vector.h"

geometry::Vector::Vector(const int64_t &x1, const int64_t &y1, const int64_t &x2, const int64_t &y2)
    : x_(x2 - x1), y_(y2 - y1) {
}

geometry::Vector::Vector(const int64_t &x, const int64_t &y) : x_(x), y_(y) {
}

geometry::Vector::Vector(const geometry::Vector &vector) : x_(vector.x_), y_(vector.y_) {
}

geometry::Vector::Vector() : x_(0), y_(0) {
}

geometry::Vector &geometry::Vector::operator=(const geometry::Vector &vector) {
  if (this != &vector) {
    x_ = vector.x_;
    y_ = vector.y_;
  }
  return *this;
}

const geometry::Vector geometry::Vector::operator+(const geometry::Vector &vector) const {
  int64_t x = vector.x_ + x_;
  int64_t y = vector.y_ + y_;
  return {x, y};
}

const geometry::Vector geometry::Vector::operator-(const geometry::Vector &vector) const {
  int64_t x = x_ - vector.x_;
  int64_t y = y_ - vector.y_;
  return {x, y};
}

const geometry::Vector geometry::Vector::operator+() const {
  return {x_, y_};
}

const geometry::Vector geometry::Vector::operator-() const {
  return {-x_, -y_};
}

geometry::Vector &geometry::Vector::operator+=(const geometry::Vector &vector) {
  x_ += vector.x_;
  y_ += vector.y_;
  return *this;
}

geometry::Vector &geometry::Vector::operator-=(const geometry::Vector &vector) {
  x_ -= vector.x_;
  y_ -= vector.y_;
  return *this;
}

geometry::Vector &geometry::Vector::operator*=(const int64_t &num) {
  x_ *= num;
  y_ *= num;
  return *this;
}

const geometry::Vector geometry::Vector::operator/(const int64_t &num) const {
  int64_t x = x_ / num;
  int64_t y = y_ / num;
  return {x, y};
}

geometry::Vector &geometry::Vector::operator/=(const int64_t &num) {
  x_ /= num;
  y_ /= num;
  return *this;
}

bool geometry::Vector::operator==(const geometry::Vector &vector) const {
  return x_ == vector.x_ && y_ == vector.y_;
}

bool geometry::Vector::operator!=(const geometry::Vector &vector) const {
  return !(*this == vector);
}

const geometry::Vector geometry::operator*(const geometry::Vector &vector, const int64_t &num) {
  int64_t x = vector.x_ * num;
  int64_t y = vector.y_ * num;
  return {x, y};
}

const geometry::Vector geometry::operator*(const int64_t &num, const geometry::Vector &vector) {
  int64_t x = vector.x_ * num;
  int64_t y = vector.y_ * num;
  return {x, y};
}

int64_t geometry::Vector::GetX() const {
  return x_;
}

int64_t geometry::Vector::GetY() const {
  return y_;
}

bool geometry::Vector::Parallel(const geometry::Vector &vector2) const {
  return VectorProduct(vector2) == 0;
}

int64_t geometry::Vector::VectorProduct(const Vector &vector) const {
  return x_ * vector.y_ - vector.x_ * y_;
}

int64_t geometry::Vector::ScalarProduct(const Vector &vector) const {
  return x_ * vector.x_ + vector.y_ * y_;
}

size_t geometry::Vector::Distance() const {
  return x_ * x_ + y_ * y_;
}
