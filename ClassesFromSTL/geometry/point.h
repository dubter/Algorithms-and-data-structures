#pragma once
#include "ishape.h"

namespace geometry {
class Point : public IShape {
 public:
  int64_t GetX() const;
  int64_t GetY() const;
  Point(const Point &point);
  Point();
  Point &operator=(const Point &point);
  Point(const int64_t &x, const int64_t &y);
  const Vector operator-(const Point &point) const;
  Point &Move(const Vector &vector) override;
  bool CrossesSegment(const geometry::Segment &segment) const override;
  Point *Clone() const override;
  std::string ToString() const override;
  bool ContainsPoint(const geometry::Point &point) const override;
  bool operator==(const Point &point) const;

 private:
  int64_t x_;
  int64_t y_;
};
}  // namespace geometry
