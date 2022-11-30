#include "../line.h"
#include "../vector.h"

geometry::Line::Line(const Point &point1, const Point &point2) : point1_(point1), point2_(point2) {
}

geometry::Line &geometry::Line::Move(const Vector &vector) {
  point1_.Move(vector);
  point2_.Move(vector);
  return *this;
}

bool geometry::Line::CrossesSegment(const geometry::Segment &segment) const {
  int64_t a = point2_.GetY() - point1_.GetY();
  int64_t b = point1_.GetX() - point2_.GetX();
  int64_t c = -point1_.GetX() * point2_.GetY() + point1_.GetY() * point2_.GetX();
  if (a < 0) {
    a *= -1;
    b *= -1;
    c *= -1;
  }
  int64_t x1 = segment.GetPoint1().GetX();
  int64_t y1 = segment.GetPoint1().GetY();
  int64_t x2 = segment.GetPoint2().GetX();
  int64_t y2 = segment.GetPoint2().GetY();
  bool first_point_higher = (a * x1 + b * y1 + c >= 0) && (a * x2 + b * y2 + c <= 0);
  bool second_point_higher = (a * x1 + b * y1 + c <= 0) && (a * x2 + b * y2 + c >= 0);
  return first_point_higher || second_point_higher;
}

geometry::Line *geometry::Line::Clone() const {
  return new Line(point1_, point2_);
}

std::string geometry::Line::ToString() const {
  int64_t a = point2_.GetY() - point1_.GetY();
  int64_t b = point1_.GetX() - point2_.GetX();
  int64_t c = -point1_.GetX() * point2_.GetY() + point1_.GetY() * point2_.GetX();
  return "Line(" + std::to_string(a) + ", " + std::to_string(b) + ", " + std::to_string(c) + ")";
}

bool geometry::Line::ContainsPoint(const geometry::Point &point) const {
  int64_t a = point2_.GetY() - point1_.GetY();
  int64_t b = point1_.GetX() - point2_.GetX();
  int64_t c = -point1_.GetX() * point2_.GetY() + point1_.GetY() * point2_.GetX();
  return point.GetX() * a + point.GetY() * b + c == 0;
}