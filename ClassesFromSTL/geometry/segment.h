#pragma once
#include "point.h"

namespace geometry {
class Segment : public IShape {
 public:
  Segment &Move(const Vector &vector) override;
  bool ContainsPoint(const geometry::Point &point) const override;
  bool CrossesSegment(const Segment &segment) const override;
  Segment *Clone() const override;
  std::string ToString() const override;
  const geometry::Point &GetPoint2() const;
  const geometry::Point &GetPoint1() const;
  Segment(const geometry::Point &point1, const geometry::Point &point2);
  Segment(const geometry::Segment &segment);
  Segment &operator=(const Segment &segment);

 private:
  Point point1_;
  Point point2_;
};
}  // namespace geometry