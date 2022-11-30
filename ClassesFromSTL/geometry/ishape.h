#pragma once
#include <string>

namespace geometry {
class Point;
class Segment;
class Vector;
class IShape {
 public:
  virtual IShape &Move(const Vector &vector) = 0;
  virtual bool ContainsPoint(const geometry::Point &point) const = 0;
  virtual bool CrossesSegment(const geometry::Segment &segment) const = 0;
  virtual IShape *Clone() const = 0;
  virtual std::string ToString() const = 0;
  virtual ~IShape() = default;
};
}  // namespace geometry
