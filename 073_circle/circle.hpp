#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "point.hpp"

class Circle {
 private:
  Point center;         // Center of the circle
  const double radius;  // Radius of the circle (constant)

 public:
  // Constructor that takes a Point and a radius and uses an initializer list
  Circle(const Point & c, double r);

  // Method to move the circle by dx and dy
  void move(double dx, double dy);

  // Method to compute the intersection area between this circle and another circle
  double intersectionArea(const Circle & otherCircle) const;
};

#endif  // CIRCLE_HPP
