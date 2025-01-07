#include "circle.hpp"
#define PI 3.1415926535

#include <cmath>  // for M_PI and sqrt

// Constructor implementation using an initializer list
Circle::Circle(const Point & c, double r) : center(c), radius(r) {
}

// Move method - moves the center of the circle by dx, dy
void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

// Method to calculate the intersection area of two circles
double Circle::intersectionArea(const Circle & otherCircle) const {
  double d = center.distanceFrom(otherCircle.center);

  double R1 = this->radius;
  double R2 = otherCircle.radius;
  double ans;
  if (d > R1 + R2) {
    ans = 0;
  }
  else if (d <= (R1 - R2) and R1 >= R2) {
    ans = PI * R2 * R2;
  }
  else if (d <= (R2 - R1) and R2 >= R1) {
    ans = PI * R1 * R1;
  }
  else {
    double alpha = acos(((R1 * R1) + (d * d) - (R2 * R2)) / (2 * R1 * d)) * 2;
    double beta = acos(((R2 * R2) + (d * d) - (R1 * R1)) / (2 * R2 * d)) * 2;

    double a1 = (0.5 * beta * R2 * R2) - (0.5 * R2 * R2 * sin(beta));
    double a2 = (0.5 * alpha * R1 * R1) - (0.5 * R1 * R1 * sin(alpha));
    ans = a1 + a2;
  }
  return ans;
}
