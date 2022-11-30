#pragma once
#include "segment.h"

namespace geometry {
class Circle : public IShape {
 private:
  Point center_;
  size_t radius_;

 public:
  Circle(const Point &center, const size_t &radius);
  Circle &Move(const Vector &vector) override;
  bool CrossesSegment(const geometry::Segment &segment) const override;
  Circle *Clone() const override;
  std::string ToString() const override;
  bool ContainsPoint(const geometry::Point &center) const override;
};
}  // namespace geometry
