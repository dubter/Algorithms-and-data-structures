#include "../ray.h"
#include "../vector.h"

geometry::Ray::Ray(const Point &point, const Vector &vector) : point1_(point) {
  Point point1(point1_.GetX() + vector.GetX(), point1_.GetY() + vector.GetY());
  point2_ = point1;
}

geometry::Ray::Ray(const Point &point1, const Point &point2) : point1_(point1), point2_(point2) {
}

geometry::Ray &geometry::Ray::Move(const Vector &vector) {
  point1_.Move(vector);
  point2_.Move(vector);
  return *this;
}

const geometry::Vector geometry::Ray::GetVector() const {
  return point2_ - point1_;
}

bool geometry::Ray::CrossesSegment(const geometry::Segment &segment) const {
  Vector tmp(0, 0);
  if (segment.GetPoint1() == segment.GetPoint2() && GetVector() == tmp) {
    return point1_.ContainsPoint(segment.GetPoint1());
  }
  if (segment.GetPoint1() == segment.GetPoint2()) {
    return ContainsPoint(segment.GetPoint1());
  }
  if (GetVector() == tmp) {
    return point1_.CrossesSegment(segment);
  }
  Line line(point1_, point2_);
  Vector po = point1_ - segment.GetPoint1();
  Vector pq = segment.GetPoint2() - segment.GetPoint1();
  int64_t a = po.VectorProduct(pq);
  int64_t b = GetVector().VectorProduct(pq);
  return ContainsPoint(segment.GetPoint1()) || ContainsPoint(segment.GetPoint2()) || segment.ContainsPoint(point1_) ||
         ((a * b < 0) && line.CrossesSegment(segment));
}

geometry::Ray *geometry::Ray::Clone() const {
  return new Ray(point1_, point2_);
}

std::string geometry::Ray::ToString() const {
  return "Ray(" + point1_.ToString() + ", " + "Vector(" + std::to_string(GetVector().GetX()) + ", " +
         std::to_string(GetVector().GetY()) + "))";
}

bool geometry::Ray::ContainsPoint(const geometry::Point &point) const {
  Vector vector = point - point1_;
  Vector tmp(0, 0);
  if (GetVector() != tmp) {
    return vector.Parallel(GetVector()) && vector.ScalarProduct(GetVector()) >= 0;
  }
  return point1_.ContainsPoint(point);
}
