#include "../circle.h"
#include "../vector.h"
#include "cmath"

geometry::Circle::Circle(const Point &center, const size_t &radius) : center_(center), radius_(radius) {
}

geometry::Circle &geometry::Circle::Move(const Vector &vector) {
  center_.Move(vector);
  return *this;
}

bool geometry::Circle::CrossesSegment(const geometry::Segment &segment) const {
  Vector vector1 = center_ - segment.GetPoint1();
  Vector vector2 = segment.GetPoint2() - segment.GetPoint1();
  Vector vector3 = segment.GetPoint2() - center_;
  bool first_point_belong_to_circle =
      std::pow(radius_, 2) == std::pow(segment.GetPoint1().GetX() - center_.GetX(), 2) +
                                  std::pow(segment.GetPoint1().GetY() - center_.GetY(), 2);
  bool second_point_belong_to_circle =
      std::pow(radius_, 2) == std::pow(segment.GetPoint2().GetX() - center_.GetX(), 2) +
                                  std::pow(segment.GetPoint2().GetY() - center_.GetY(), 2);
  size_t distance;
  if (vector1.ScalarProduct(vector2) >= 0 && vector2.ScalarProduct(vector3) >= 0) {
    distance = vector1.VectorProduct(vector2);
    return first_point_belong_to_circle || second_point_belong_to_circle ||
           (distance * distance <= radius_ * radius_ * vector2.Distance() &&
            !(ContainsPoint(segment.GetPoint1()) && ContainsPoint(segment.GetPoint2())));
  }
  if (vector1.ScalarProduct(vector2) < 0) {
    distance = vector1.Distance();
  } else {
    distance = vector3.Distance();
  }
  return first_point_belong_to_circle || second_point_belong_to_circle ||
         (distance <= radius_ * radius_ && !(ContainsPoint(segment.GetPoint1()) && ContainsPoint(segment.GetPoint2())));
}

geometry::Circle *geometry::Circle::Clone() const {
  return new Circle(center_, radius_);
}

std::string geometry::Circle::ToString() const {
  return "Circle(" + center_.ToString() + ", " + std::to_string(radius_) + ")";
}

bool geometry::Circle::ContainsPoint(const geometry::Point &point) const {
  return std::pow(radius_, 2) >=
         std::pow(point.GetX() - center_.GetX(), 2) + std::pow(point.GetY() - center_.GetY(), 2);
}