#include <iostream>
#include "geometry.h"
#include <vector>
#include <cmath>
#include <iomanip>

int main() {
  Polygon polygon = Polygon(Point(0, 0), Point(1, 0), Point(0, 1));
  double angle = 90;
  Point center(1, 1);
  std::cout << polygon.area() << std::endl;
  polygon.rotate(center, angle);
  polygon.print();
  std::cout << polygon.area() << std::endl;

}

