#pragma once
#include "line.h"

namespace geometry {
class Ray : public IShape {
 public:
  const Vector GetVector() const;
  Ray(const Point &point, const Vector &vector);
  Ray(const Point &point1, const Point &point2);
  Ray &Move(const Vector &vector) override;
  bool CrossesSegment(const geometry::Segment &segment) const override;
  Ray *Clone() const override;
  std::string ToString() const override;
  bool ContainsPoint(const geometry::Point &point) const override;

 private:
  Point point1_;
  Point point2_;
};
}  // namespace geometry
