#include "../polygon.h"
#include "../vector.h"

geometry::Polygon::Polygon(const std::vector<Point> &polygon) : polygon_(polygon) {
}

geometry::Polygon &geometry::Polygon::Move(const geometry::Vector &vector) {
  for (size_t i = 0; i < polygon_.size(); i++) {
    polygon_[i].Move(vector);
  }
  return *this;
}

bool geometry::Polygon::CrossesSegment(const geometry::Segment &segment) const {
  bool result = false;
  for (size_t i = 0; i < polygon_.size() - 1; i++) {
    Segment segment1(polygon_[i], polygon_[i + 1]);
    if (segment1.CrossesSegment(segment)) {
      result = true;
      break;
    }
  }
  Segment segment1(polygon_[polygon_.size() - 1], polygon_[0]);
  if (segment1.CrossesSegment(segment)) {
    result = true;
  }
  return result;
}

geometry::Polygon *geometry::Polygon::Clone() const {
  return new Polygon(polygon_);
}

std::string geometry::Polygon::ToString() const {
  std::string string = "Polygon(";
  for (size_t i = 0; i < polygon_.size(); i++) {
    string += polygon_[i].ToString();
    if (i != polygon_.size() - 1) {
      string += ", ";
    }
  }
  return string + ")";
}

bool geometry::Polygon::ContainsPoint(const geometry::Point &point) const {
  bool contains_point = true;
  size_t count = 0;
  for (size_t i = 0; i < polygon_.size() - 1; i++) {
    Segment segment1(polygon_[i], polygon_[i + 1]);
    if (point.CrossesSegment(segment1)) {
      contains_point = false;
      count = 1;
    }
  }
  Segment segment1(polygon_[polygon_.size() - 1], polygon_[0]);
  if (point.CrossesSegment(segment1)) {
    contains_point = false;
    count = 1;
  }
  if (contains_point) {
    Vector vector(1, 0);
    Ray ray(point, vector);
    for (size_t i = 0; i < polygon_.size() - 1; i++) {
      if (polygon_[i] == polygon_[i + 1]) {
        continue;
      }
      Segment segment(polygon_[i], polygon_[i + 1]);
      if (ray.CrossesSegment(segment)) {
        if (ray.ContainsPoint(polygon_[i])) {
          if (polygon_[i].GetY() > polygon_[i + 1].GetY()) {
            count++;
          }
        } else if (ray.ContainsPoint(polygon_[i + 1])) {
          if (polygon_[i].GetY() < polygon_[i + 1].GetY()) {
            count++;
          }
        } else {
          count++;
        }
      }
    }
    if (!(polygon_[polygon_.size() - 1] == polygon_[0])) {
      Segment segment(polygon_[polygon_.size() - 1], polygon_[0]);
      if (ray.CrossesSegment(segment)) {
        if (ray.ContainsPoint(polygon_[0])) {
          if (polygon_[0].GetY() > polygon_[polygon_.size() - 1].GetY()) {
            count++;
          }
        } else if (ray.ContainsPoint(polygon_[polygon_.size() - 1])) {
          if (polygon_[0].GetY() < polygon_[polygon_.size() - 1].GetY()) {
            count++;
          }
        } else {
          count++;
        }
      }
    }
  }
  return count % 2 != 0;
}