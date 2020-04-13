#include <iostream>
#include "geometry.h"
#include <vector>
#include <cmath>
#include <iomanip>

int main() {
	/*std::vector<Point> points;
	int n = 0;
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		double a, b;
		std::cin >> a >> b;
		points.push_back(Point(a, b));
	}
	Polygon polygon = Polygon(points);
	polygon.print();
	std::cout << std::setprecision(15) << polygon.area() << std::endl;*/
	Polygon p1 = Polygon(Point(0, 0), Point(1, 0), Point(0, 1));
	Polygon p2 = Polygon(Point(1, 0), Point(0, 0), Point(0, 1));
	std::cout << (p1 == p2) << std::endl;
}

