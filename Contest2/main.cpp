#include <iostream>
#include "geometry.h"
//#include "test.h"
#include <vector>
#include <cmath>
#include <iomanip>

int main() {
  Triangle p(Point(2, 2), Point(-1, -2), Point(-2, 2));
  Line line = p.EulerLine();
  std::cout << line.getSlope() << " " << line.getShift();
}

