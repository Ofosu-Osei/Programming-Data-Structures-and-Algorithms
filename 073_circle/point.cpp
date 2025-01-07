#include "point.hpp"

#include <math.h>

Point::Point() : x(0), y(0) {
}

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) const {
  double d_x = pow((x - p.x), 2);
  double d_y = pow((y - p.y), 2);
  return sqrt(d_x + d_y);
}
