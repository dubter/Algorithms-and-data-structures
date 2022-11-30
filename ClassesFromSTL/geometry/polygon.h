#pragma once
#include "ray.h"
#include <vector>

namespace geometry {
class Polygon : public IShape {
 public:
  explicit Polygon(const std::vector<Point> &polygon);
  Polygon &Move(const Vector &vector) override;
  bool CrossesSegment(const geometry::Segment &segment) const override;
  Polygon *Clone() const override;
  std::string ToString() const override;
  bool ContainsPoint(const geometry::Point &point) const override;

 private:
  std::vector<Point> polygon_;
};
}  // namespace geometry
