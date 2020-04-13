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
	Polygon p1 = Polygon(Point(3, 3), Point(7, 7), Point(17, 1), Point(13, -6));
	Polygon p2 = Polygon(Point(7, 7), Point(3, 3), Point(13, -6), Point(17, 1));
	std::cout << p1.isSimilarTo(p2) << std::endl;
	Point A(0, 0), B(1, 1), C(2, 1), D(3, 0), E(-1, 0);
	Polygon a(A, B, C, D, E), b(B, C, D, E, A);
	std::cout << a.isSimilarTo(b) << std::endl;
	p1 = Polygon(Point(0, 0), Point(1, 0), Point(0, 1));
	p2 = Polygon(Point(0, 0), Point(2, 0), Point(0, 2));
	std::cout << p1.isSimilarTo(p2) << std::endl;

}

