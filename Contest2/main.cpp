#include <iostream>
#include "geometry.h"
#include <vector>
#include <cmath>
#include <iomanip>

int main() {
  Rectangle rect(Point(1, 0), Point(6, 0), 0.75);
  rect.print(15);
  std::cout << "//////////////////" << std::endl;
}

