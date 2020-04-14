#include <iostream>
#include "geometry.h"
#include <vector>
#include <cmath>
#include <iomanip>

int main() {
  Polygon polygon = Polygon(Point(0, 0), Point(3, 5), Point(8, -7));
  Point point = Point(6, 10);
  std::cout << polygon.containsPoint(point) << std::endl;
}

