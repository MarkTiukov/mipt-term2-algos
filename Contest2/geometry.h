#include <vector>
#include <cmath>
#include <iostream>

struct Point {
	double x = 0;
	double y = 0;

	Point(double x, double y) : x(x), y(y) {}
};

bool operator==(const Point &a, const Point &b) {
	return a.x == b.x && a.y == b.y;
}

bool operator!=(const Point &a, const Point &b) {
	return !(a == b);
}

class Line {
	std::vector<Point> points;
	double slope;
	double shift;

 public:

	Line(double slope, double shift) : slope(slope), shift(shift) {}

	Line(Point point, double slope) : Line(slope, point.y - slope * point.x) { this->points.push_back(point); }

	Line(Point p1, Point p2) {
		double tmp = (p2.y - p1.y) / (p2.x - p1.x);
		this->slope = tmp;
		this->shift = p1.y - p1.x * tmp;
	}

	static double length(const Point &p1, const Point &p2) {
		return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
	}

};

class Shape {
 public:
	virtual double perimeter() const = 0;
	virtual double area() const = 0;
//  virtual bool operator==(const Shape &another) = 0;
//  virtual bool isCongruentTo(const Shape &another) const = 0;
//    virtual bool isSimilarTo(const Shape &another) const = 0;
//    virtual bool containsPoint(Point point) const = 0;
//    virtual void rotate(Point center, double angle) = 0;
//    virtual void reflex(Point center) = 0;
//    virtual void reflex(Line axis) = 0;
//    virtual void scale(Point center, double coefficient) = 0;

};

class Polygon : public Shape {
	//TODO
	// isCongruentTo(const Shape& another) - равна ли эта фигура другой в геометрическом смысле;
	// isSimilarTo(const Shape& another) - подобна ли эта фигура другой;
	// containsPoint(Point point) - находится ли точка внутри фигуры.
	// rotate(Point center, double angle) - поворот на угол (в градусах, против часовой стрелки) относительно точки;
	// reflex(Point center) - симметрию относительно точки;
	// reflex(Line axis) - симметрию относительно прямой;
	// scale(Point center, double coefficient) - гомотетию с коэффициентом coefficient и центром center.
	// verticesCount() - количество вершин
	// std::vector<Point> getVertices - сами вершины без возможности изменения
	// isConvex() - выпуклый ли

	std::vector<Point> points;

 public:

	Polygon() {}

	/*template<Point &head, Point &...tail>
	Polygon() {
		this->points.push_back(head);
		Polygon(tail...);
	}*/

	template<class ... Points>
	Polygon(Points &&... points) : points{std::forward<Points>(points)...} {}

	Polygon(const std::vector<Point> &points) : points(points) {}

	double perimeter() const override;
	double area() const override;
	int verticesCount() const { return this->points.size(); }
	void print();
	bool isSimilarTo(const Polygon &another);

	bool operator==(const Polygon &another);

};

class Ellipse : public Shape {
	//TODO
	// Эллипс можно сконструировать из двух точек и double (два фокуса и сумма расстояний от эллипса до них);
	// perimeter() -периметр;
	// double area() - площадь;
	// operator==(const Shape& another) - совпадает ли эта фигура с другой;
	// isCongruentTo(const Shape& another) - равна ли эта фигура другой в геометрическом смысле;
	// isSimilarTo(const Shape& another) - подобна ли эта фигура другой;
	// containsPoint(Point point) - находится ли точка внутри фигуры.
	// rotate(Point center, double angle) - поворот на угол (в градусах, против часовой стрелки) относительно точки;
	// reflex(Point center) - симметрию относительно точки;
	// reflex(Line axis) - симметрию относительно прямой;
	// scale(Point center, double coefficient) - гомотетию с коэффициентом coefficient и центром center.
	// std::pair<Point,Point> focuses() - его фокусы
	// std::pair<Line, Line> directrices() - пару его директрис
	// double eccentricity() - его эксцентриситет
	// Point center() - его центр
};

class Circle : public Ellipse {
	//TODO
	// Круг можно задать точкой и числом (центр и радиус).
	// perimeter() -периметр;
	// double area() - площадь;
	// operator==(const Shape& another) - совпадает ли эта фигура с другой;
	// isCongruentTo(const Shape& another) - равна ли эта фигура другой в геометрическом смысле;
	// isSimilarTo(const Shape& another) - подобна ли эта фигура другой;
	// containsPoint(Point point) - находится ли точка внутри фигуры.
	// rotate(Point center, double angle) - поворот на угол (в градусах, против часовой стрелки) относительно точки;
	// reflex(Point center) - симметрию относительно точки;
	// reflex(Line axis) - симметрию относительно прямой;
	// scale(Point center, double coefficient) - гомотетию с коэффициентом coefficient и центром center.
	// double radius() - радиус.
};

class Rectangle : public Polygon {
	//TODO
	// Прямоугольник можно сконструировать по двум точкам (его противоположным вершинам) и числу (отношению смежных сторон), причем из двух таких прямоугольников выбирается тот, у которого более короткая сторона расположена по левую сторону от диагонали, если смотреть от первой заданной точки в направлении второй.
	// perimeter() -периметр;
	// double area() - площадь;
	// operator==(const Shape& another) - совпадает ли эта фигура с другой;
	// isCongruentTo(const Shape& another) - равна ли эта фигура другой в геометрическом смысле;
	// isSimilarTo(const Shape& another) - подобна ли эта фигура другой;
	// containsPoint(Point point) - находится ли точка внутри фигуры.
	// rotate(Point center, double angle) - поворот на угол (в градусах, против часовой стрелки) относительно точки;
	// reflex(Point center) - симметрию относительно точки;
	// reflex(Line axis) - симметрию относительно прямой;
	// scale(Point center, double coefficient) - гомотетию с коэффициентом coefficient и центром center.
	// Point center() - его центр
	// std::pair<Line, Line> diagonals() - пару его диагоналей.
};

class Square : public Rectangle {
	//TODO
	// Квадрат можно задать двумя точками - противоположными вершинами.
	// perimeter() -периметр;
	// double area() - площадь;
	// operator==(const Shape& another) - совпадает ли эта фигура с другой;
	// isCongruentTo(const Shape& another) - равна ли эта фигура другой в геометрическом смысле;
	// isSimilarTo(const Shape& another) - подобна ли эта фигура другой;
	// containsPoint(Point point) - находится ли точка внутри фигуры.
	// rotate(Point center, double angle) - поворот на угол (в градусах, против часовой стрелки) относительно точки;
	// reflex(Point center) - симметрию относительно точки;
	// reflex(Line axis) - симметрию относительно прямой;
	// scale(Point center, double coefficient) - гомотетию с коэффициентом coefficient и центром center.
	// Circle circumscribedCircle()
	// Circle inscribedCircle()
};

class Triangle : public Polygon {
	//TODO
	// perimeter() -периметр;
	// double area() - площадь;
	// operator==(const Shape& another) - совпадает ли эта фигура с другой;
	// isCongruentTo(const Shape& another) - равна ли эта фигура другой в геометрическом смысле;
	// isSimilarTo(const Shape& another) - подобна ли эта фигура другой;
	// containsPoint(Point point) - находится ли точка внутри фигуры.
	// rotate(Point center, double angle) - поворот на угол (в градусах, против часовой стрелки) относительно точки;
	// reflex(Point center) - симметрию относительно точки;
	// reflex(Line axis) - симметрию относительно прямой;
	// scale(Point center, double coefficient) - гомотетию с коэффициентом coefficient и центром center.
	// Circle circumscribedCircle()
	// Circle inscribedCircle()
	// Point centroid() - его центр масс,
	// Point orthocenter() - его ортоцентр,
	// Line EulerLine() - его прямую Эйлера,
	// Circle ninePointsCircle() - его окружность Эйлера.
};

double Polygon::perimeter() const {
	double result = 0.0;
	for (int i = 1; i < this->points.size(); ++i) {
		result += Line::length(this->points[i - 1], this->points[i]);
	}
	return result + Line::length(this->points[0], this->points[this->points.size() - 1]);
}
void Polygon::print() {
	for (Point p: this->points) {
		std::cout << "point " << p.x << " " << p.y << std::endl;
	}
}
double Polygon::area() const {
	double sum = 0.0;
	for (int i = 0; i < this->points.size(); ++i) {
		sum += (this->points[i].x * this->points[(i + 1) % this->points.size()].y
				- this->points[i].y * this->points[(i + 1) % this->points.size()].x);
	}
	return abs(sum) * 0.5;
}

bool Polygon::operator==(const Polygon &another) {
	bool result = false;
	if (this->points.size() == another.points.size()) {
		int length = this->points.size();
		int shift = 0;
		while (shift < length && this->points[shift] != another.points[0]) { // finds a shift in numeration
			++shift;
		}
		bool result1 = this->points[shift] == another.points[0];
		bool result2 = result1;
		for (int i = 0; i < length && (result1 || result2); ++i) {
			result1 = result1 && this->points[(shift + i) % length] == another.points[i]; // for one direction
			result2 = result2 && this->points[(length + shift - i) % length] == another.points[i]; // for another
		}
		result = result1 || result2;
	}
	return result;
}
