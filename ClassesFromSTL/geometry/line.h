#pragma once
#include "segment.h"

namespace geometry {
class Line : public IShape {
 public:
  Line(const Point &point1, const Point &point2);
  Line &Move(const Vector &vector) override;
  bool CrossesSegment(const geometry::Segment &segment) const override;
  Line *Clone() const override;
  std::string ToString() const override;
  bool ContainsPoint(const geometry::Point &point) const override;

 private:
  Point point1_;
  Point point2_;
};
}  // namespace geometry
