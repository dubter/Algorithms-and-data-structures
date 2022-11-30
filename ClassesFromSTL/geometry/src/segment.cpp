#include "../segment.h"
#include "../vector.h"

geometry::Segment::Segment(const geometry::Point &point1, const geometry::Point &point2)
    : point1_(point1), point2_(point2) {
}

geometry::Segment::Segment(const geometry::Segment &segment) : point1_(segment.point1_), point2_(segment.point2_) {
}

const geometry::Point &geometry::Segment::GetPoint1() const {
  return point1_;
}

const geometry::Point &geometry::Segment::GetPoint2() const {
  return point2_;
}

geometry::Segment &geometry::Segment::Move(const geometry::Vector &vector) {
  point1_.Move(vector);
  point2_.Move(vector);
  return *this;
}

bool geometry::Segment::ContainsPoint(const geometry::Point &point) const {
  return point.CrossesSegment(*this);
}

bool geometry::Segment::CrossesSegment(const geometry::Segment &segment) const {
  if (segment.GetPoint1() == segment.GetPoint2() && point1_ == point2_) {
    return segment.GetPoint1().ContainsPoint(point1_);
  }
  if (segment.GetPoint1() == segment.GetPoint2()) {
    return segment.GetPoint1().CrossesSegment(*this);
  }
  if (point1_ == point2_) {
    return point1_.CrossesSegment(segment);
  }
  int64_t x = (segment.point2_.GetX() - segment.point1_.GetX()) * (point1_.GetY() - segment.point1_.GetY()) -
              (segment.point2_.GetY() - segment.point1_.GetY()) * (point1_.GetX() - segment.point1_.GetX());
  int64_t y = (point2_.GetX() - point1_.GetX()) * (point1_.GetY() - segment.point1_.GetY()) -
              (point2_.GetY() - point1_.GetY()) * (point1_.GetX() - segment.point1_.GetX());
  int64_t distance = (segment.point2_.GetY() - segment.point1_.GetY()) * (point2_.GetX() - point1_.GetX()) -
                     (segment.point2_.GetX() - segment.point1_.GetX()) * (point2_.GetY() - point1_.GetY());
  bool first_point_higher =
      std::max(std::min(point1_.GetX(), point2_.GetX()), std::min(segment.point1_.GetX(), segment.point2_.GetX())) >
      std::min(std::max(point1_.GetX(), point2_.GetX()), std::max(segment.point1_.GetX(), segment.point2_.GetX()));
  bool second_point_higher =
      std::max(std::min(point1_.GetY(), point2_.GetY()), std::min(segment.point1_.GetY(), segment.point2_.GetY())) >
      std::min(std::max(point1_.GetY(), point2_.GetY()), std::max(segment.point1_.GetY(), segment.point2_.GetY()));
  if (first_point_higher || second_point_higher) {
    return false;
  }
  if (distance == 0) {
    return x == 0;
  }
  if (distance < 0) {
    x = -x;
    y = -y;
    distance = -distance;
  }
  return x >= 0 && x <= distance && y >= 0 && y <= distance;
}

geometry::Segment *geometry::Segment::Clone() const {
  return new Segment(point1_, point2_);
}
std::string geometry::Segment::ToString() const {
  std::string string = "Segment(" + point1_.ToString() + ", " + point2_.ToString() + ")";
  return string;
}

geometry::Segment &geometry::Segment::operator=(const Segment &segment) {
  if (this != &segment) {
    point1_ = segment.point1_;
    point2_ = segment.point2_;
  }
  return *this;
}