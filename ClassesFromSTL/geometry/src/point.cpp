#include "../point.h"
#include "../segment.h"
#include "../vector.h"

geometry::Point::Point(const int64_t &x, const int64_t &y) : x_(x), y_(y) {
}

geometry::Point::Point() : x_(0), y_(0) {
}

geometry::Point::Point(const geometry::Point &point) : x_(point.x_), y_(point.y_) {
}

std::string geometry::Point::ToString() const {
  std::string string = "Point(" + std::to_string(x_) + ", " + std::to_string(y_) + ")";
  return string;
}

geometry::Point *geometry::Point::Clone() const {
  return new Point(x_, y_);
}

bool geometry::Point::CrossesSegment(const geometry::Segment &segment) const {
  Vector vector1 = *this - segment.GetPoint1();
  Vector vector2 = *this - segment.GetPoint2();
  if (vector1 == vector2) {
    Point point(segment.GetPoint1().GetX(), segment.GetPoint1().GetY());
    return ContainsPoint(point);
  }
  return vector1.Parallel(vector2) && vector1.ScalarProduct(vector2) <= 0;
}

bool geometry::Point::ContainsPoint(const geometry::Point &point) const {
  return x_ == point.x_ && y_ == point.y_;
}

geometry::Point &geometry::Point::Move(const geometry::Vector &vector) {
  x_ += vector.GetX();
  y_ += vector.GetY();
  return *this;
}

int64_t geometry::Point::GetX() const {
  return x_;
}

int64_t geometry::Point::GetY() const {
  return y_;
}

geometry::Point &geometry::Point::operator=(const geometry::Point &point) {
  if (this != &point) {
    x_ = point.GetX();
    y_ = point.GetY();
  }
  return *this;
}

bool geometry::Point::operator==(const Point &point) const {
  return point.y_ == y_ && point.x_ == x_;
}

const geometry::Vector geometry::Point::operator-(const Point &point) const {
  int64_t x = x_ - point.x_;
  int64_t y = y_ - point.y_;
  return {x, y};
}