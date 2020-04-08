#include <iostream>
#include "geometry.h"
#include <vector>
#include <cmath>
#include <iomanip>

int main() {
	std::vector<Point> points;
	int n = 0;
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		double a, b;
		std::cin >> a >> b;
		points.push_back(Point(a, b));
	}
	Polygon polygon = Polygon(points);
	polygon.print();
	std::cout << std::setprecision(15) << polygon.area() << std::endl;
	return 0;
}

