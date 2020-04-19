#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>

const double PI = 3.14159265358;

struct Point {
  double x = 0;
  double y = 0;

  Point() {}
  Point(double x, double y) : x(x), y(y) {}
};

bool operator==(const Point &a, const Point &b) {
  return a.x == b.x && a.y == b.y;
}

bool operator!=(const Point &a, const Point &b) {
  return !(a == b);
}

Point operator-(const Point &a, const Point &b) {
  return Point(a.x - b.x, a.y - b.y);
}

bool operator<(const Point &a, const double &number) {
  return a.x < number && a.y < number;
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

  const std::vector<Point> &getPoints() const {
	return points;
  }
  double getSlope() const {
	return slope;
  }
  double getShift() const {
	return shift;
  }

  static double length(const Point &p1, const Point &p2) {
	return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
  }

};

class Shape {
 public:
  virtual double perimeter() const = 0;
  virtual double area() const = 0;
  virtual bool operator==(const Shape &another) = 0;
  virtual bool isCongruentTo(const Shape &another) const = 0;
  virtual bool isSimilarTo(const Shape &another) const = 0;
  virtual bool containsPoint(const Point &point) const = 0;
  virtual void rotate(const Point &center, const double &angle) = 0;
  virtual void reflex(const Point &center) = 0;
  virtual void reflex(const Line &axis) = 0;
  virtual void scale(const Point &center, const double &coefficient) = 0;

};

double dot(const Point &a, const Point &b) { // dot production of vector a and vector b
  return a.x * b.x + a.y * b.y;
}

double cross(const Point &a, const Point &b) {
  return a.x * b.y - a.y * b.x;
}

double module(const Point &a) { // length of vector a
  return std::sqrt(dot(a, a));
}

double cos(const Point &a, const Point &b) { // cos between vector a and vector b
  return dot(a, b) / (module(a) * module(b));
}

double sin(const Point &a, const Point &b) { // sin between vector a and vector b
  return cross(a, b) / (module(a) * module(b));
}

int getSign(const double &number) {
  if (number > 0)
	return 1;
  if (number == 0)
	return 0;
  return -1;
}

double toRad(double angle) {
  return PI * angle / 180.0;
}

void rotatePoint(const Point &center, const double &curCos, const double &curSin, Point &point) {
  double shiftX = point.x - center.x;
  double shiftY = point.y - center.y;
  point.x = curCos * shiftX - curSin * shiftY + center.x;
  point.y = curSin * shiftX + curCos * shiftY + center.y;
}

void rotatePoint(const Point &center, const double &angle, Point &point) {
  double ang = toRad(angle);
  double curCos = cos(ang);
  double curSin = sin(ang);
  rotatePoint(center, curCos, curSin, point);
}

class Polygon : public Shape {
 protected:
  std::vector<Point> points;
  std::vector<Point> vectors; // stores sides as vectors: v[i] = p[i + 1] - p[i]

 public:

  Polygon() {}

  template<class ...Points>
  Polygon(Points &... points) : points{std::forward<Points>(points)...} { makeVectors(); }
  Polygon(const std::vector<Point> &points) : points(points) { makeVectors(); }

  void makeVectors();
  const std::vector<Point> &getPoints() const;

  double perimeter() const override;
  double area() const override;
  int verticesCount() const { return this->points.size(); }
  bool isCongruentTo(const Shape &another) const override;
  bool isSimilarTo(const Shape &another) const override;
  bool containsPoint(const Point &point) const override;

  bool isConvex() const;
  bool operator==(const Shape &another) override;
  void print() const;
  void print(int precision) const;
  size_t size() const { return this->points.size(); }
  void rotate(const Point &center, const double &angle) override;
  void reflex(const Point &center) override;
  void reflex(const Line &axis) override;
  void scale(const Point &center, const double &coefficient) override;

};

class Rectangle : public Polygon {
 protected:

  double bigger;
  double smaller;

 public:

  Rectangle(Point a, Point b, double ratio);

  Rectangle(Point a, Point b, Point c, Point d) : Polygon(a, b, c, d) {
	double one = module(this->vectors[0]);
	double two = module(this->vectors[1]);
	this->bigger = std::max(one, two);
	this->smaller = std::min(one, two);
  }

  Point center() const;
  std::pair<Line, Line> diagonals() const;

};

class Square : public Rectangle {
  //TODO
  // Circle circumscribedCircle()
  // Circle inscribedCircle()

 public:

  Square(Point a, Point b, Point c, Point d) : Rectangle(a, b, c, d) {}
  Square(Point a, Point b) : Rectangle(a, b, 1) {}

  double area() { return this->smaller * this->bigger; }
  bool isSimilarTo(const Square &square) { return true; }
};

class Triangle : public Polygon {
  //TODO
  // Circle circumscribedCircle()
  // Circle inscribedCircle()
  // Point orthocenter() - его ортоцентр,
  // Line EulerLine() - его прямую Эйлера,
  // Circle ninePointsCircle() - его окружность Эйлера.
 private:
  double sideOne, sideTwo, sideThree;

 public:

  Triangle(Point a, Point b, Point c) : Polygon(a, b, c) {
	this->sideOne = module(this->vectors[0]);
	this->sideTwo = module(this->vectors[1]);
	this->sideThree = module(this->vectors[2]);
  }

  double perimeter() const override { return sideOne + sideTwo + sideThree; }

  Point centroid() const;

};

class Ellipse : public Shape {
  //TODO
  // std::pair<Line, Line> directrices() - пару его директрис
 private:
  Point f1, f2;
  double a, b, c;

 public:

  Ellipse(const Point &f_1, const Point &f_2, double a) : f1(f_1), f2(f_2), a(a / 2) {
	this->c = Line::length(f1, f2) / 2;
	this->b = std::sqrt(this->a * this->a - this->c * this->c);
  }

  std::pair<Point, Point> focuses() { return std::make_pair(f1, f2); }

  double perimeter() const override {
	return PI * (3 * (this->a + this->b) - std::sqrt((3 * this->a + this->b) * (this->a + 3 * this->b)));
  }

  double area() const override { return PI * this->a * this->b; }

  bool operator==(const Shape &another) override {
	try {
	  const Ellipse &another2 = dynamic_cast<const Ellipse &>(another);
	  return this->a == another2.a
		  && (this->f1 == another2.f1 && this->f2 == another2.f2 || this->f1 == another2.f2 && this->f2 == another2.f1);
	} catch (...) {
	  return false;
	}
  }

  bool isCongruentTo(const Shape &another) const override {
	try {
	  const Ellipse &another2 = dynamic_cast<const Ellipse &>(another2);
	  return this->c == another2.c && this->a == another2.a;
	} catch (...) {
	  return false;
	}
  }

  bool isSimilarTo(const Shape &another) const override {
	try {
	  const Ellipse &another2 = dynamic_cast<const Ellipse &>(another2);
	  return (this->c / another2.c - this->a / another2.a) < 1e-9;
	} catch (...) {
	  return false;
	}
  }

  bool containsPoint(const Point &point) const override {
	return Line::length(point, this->f1) + Line::length(point, this->f2) <= 2 * this->a;
  }

  void rotate(const Point &center, const double &angle) override {
	rotatePoint(center, angle, this->f1);
	rotatePoint(center, angle, this->f2);
  }

  void reflex(const Point &center) override {
	this->f1 = Point(2 * center.x - this->f1.x, 2 * center.y - this->f1.y);
	this->f2 = Point(2 * center.x - this->f2.x, 2 * center.y - this->f2.y);
  }

  void reflex(const Line &axis) override {
	double denominator = 1 + axis.getSlope() * axis.getSlope();
	double slope = axis.getSlope();
	double shift = axis.getShift();
	double currentX = this->f1.x;
	double currentY = this->f1.y;
	this->f1.x = 2 * (currentX - slope * (shift - currentY)) / denominator - currentX;
	this->f1.y = (slope * (2 * currentX + slope * currentY) + 2 * shift - currentY) / denominator;
	currentX = this->f2.x;
	currentY = this->f2.y;
	this->f2.x = 2 * (currentX - slope * (shift - currentY)) / denominator - currentX;
	this->f2.y = (slope * (2 * currentX + slope * currentY) + 2 * shift - currentY) / denominator;
  }

  void scale(const Point &center, const double &coefficient) override {
	this->f1.x = coefficient * (this->f1.x - center.x) + center.x;
	this->f1.y = coefficient * (this->f1.y - center.y) + center.y;
	this->f2.x = coefficient * (this->f2.x - center.x) + center.x;
	this->f2.y = coefficient * (this->f2.y - center.y) + center.y;
  }

  double eccentricity() const { return this->c / this->a; }

  Point center() const { return Point((this->f1.x + this->f2.x) / 2, (this->f1.y + this->f2.y) / 2); }

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

double Polygon::perimeter() const {
  double result = 0.0;
  for (size_t i = 1; i < this->points.size(); ++i) {
	result += Line::length(this->points[i - 1], this->points[i]);
  }
  return result + Line::length(this->points[0], this->points[this->points.size() - 1]);
}

void Polygon::print() const {
  for (Point p: this->points) {
	std::cout << std::setprecision(9) << "point " << p.x << " " << p.y << std::endl;
  }
}

void Polygon::print(int precision) const {
  for (Point p: this->points) {
	std::cout << std::setprecision(precision) << "point " << p.x << " " << p.y << std::endl;
  }
}

double Polygon::area() const {
  double sum = 0.0;
  for (size_t i = 0; i < this->points.size(); ++i) {
	sum += (this->points[i].x * this->points[(i + 1) % this->points.size()].y
		- this->points[i].y * this->points[(i + 1) % this->points.size()].x);
  }
  return abs(sum) * 0.5;
}

bool Polygon::operator==(const Shape &another) {
  try {
	const Polygon &copyAnother = dynamic_cast<const Polygon &>(another);
	bool result = false;
	if (this->points.size() == copyAnother.points.size()) {
	  size_t length = this->points.size();
	  int shift = 0;
	  while (shift < length && this->points[shift] != copyAnother.points[0]) { // finds a shift in numeration
		++shift;
	  }
	  bool result1 = (this->points[shift] - copyAnother.points[0] < 1e-9);
	  bool result2 = result1;
	  for (size_t i = 0; i < length && (result1 || result2); ++i) {
		result1 = result1 && this->points[(shift + i) % length] == copyAnother.points[i]; // for one direction
		result2 = result2 && this->points[(length + shift - i) % length] == copyAnother.points[i]; // for another
	  }
	  result = result1 || result2;
	}
	return result;
  } catch (...) {
	return false;
  }
}

void Polygon::makeVectors() {
  for (size_t i = 0; i < this->size(); ++i) {
	this->vectors.push_back(this->points[(i + 1) % this->size()] - this->points[i]);
  }
}

bool Polygon::isSimilarTo(const Shape &another) const {
  try {
	const Polygon &copyAnother = dynamic_cast<const Polygon &>(another);
	bool result = false;
	if (this->points.size() == copyAnother.points.size()) {
	  int length = this->points.size();
	  for (int shift = 0; shift < length; ++shift) {
		bool
			result1 = cos(this->vectors[shift], this->vectors[(shift + 1) % length])
			== cos(copyAnother.vectors[0], copyAnother.vectors[1]);
		bool result2 = result1;
		for (int i = 0; i < length && (result1 || result2); ++i) {
		  result1 = result1 &&
			  cos(this->vectors[(shift + i) % length], this->vectors[(shift + i + 1) % length]) ==
				  cos(copyAnother.vectors[i], copyAnother.vectors[(i + 1) % length]); // for one direction
		  result2 = result2 &&
			  cos(this->vectors[(length + shift - i) % length], this->vectors[(length + shift - i + 1) % length])
				  ==
					  cos(copyAnother.vectors[i], copyAnother.vectors[(i + 1) % length]); // for another
		}
		result = result || result1 || result2;
	  }
	}
	return result;
  } catch (...) {
	return false;
  }
}
const std::vector<Point> &Polygon::getPoints() const {
  return points;
}

bool Polygon::isCongruentTo(const Shape &another) const {
  try {
	const Polygon &copyAnother = dynamic_cast<const Polygon &>(another);
	bool result = false;
	if (this->isSimilarTo(copyAnother)) {
	  if (this->points.size() == copyAnother.points.size()) {
		size_t length = this->points.size();
		for (size_t shift = 0; shift < length; ++shift) {
		  bool result1;
		  result1 = module(this->vectors[shift]) == module(copyAnother.vectors[0]);
		  bool result2 = result1;
		  for (size_t i = 0; i < length && (result1 || result2); ++i) {
			result1 = result1 &&
				module(this->vectors[(shift + i) % length]) == module(copyAnother.vectors[i]); // for one direction
			result2 = result2 &&
				module(this->vectors[(length + shift - i) % length]) == module(copyAnother.vectors[i]); // for another
		  }
		  result = result || result1 || result2;
		}
	  }
	}
	return result;
  } catch (...) {
	return false;
  }
}

bool Polygon::containsPoint(const Point &point) const {
  bool result = true;
  int sign = getSign(cross(this->vectors[0], Point(point.x - this->points[0].x, point.y - this->points[0].y)));
  if (sign == 0)
	sign = getSign(cross(this->vectors[1], Point(point.x - this->points[1].x, point.y - this->points[1].y)));
  if (sign == 0)
	sign = getSign(cross(this->vectors[2], Point(point.x - this->points[2].x, point.y - this->points[2].y)));
  for (size_t i = 0; i < this->size() && result; ++i) {
	int currentSign = getSign(cross(this->vectors[i], Point(point.x - this->points[i].x, point.y - this->points[i].y)));
	result = result && (sign == currentSign || currentSign == 0);
  }
  return result;
}

bool Polygon::isConvex() const {
  bool result = true;
  int sign = getSign(cross(this->vectors[0], this->vectors[1]));
  if (sign == 0)
	sign = getSign(cross(this->vectors[1], this->vectors[2]));
  for (size_t i = 0; i < this->size() && result; ++i) {
	int currentSign = getSign(cross(this->vectors[i], this->vectors[(i + 1) % this->size()]));
	result = result && (sign == currentSign || currentSign == 0);
  }
  return result;
}

void Polygon::rotate(const Point &center, const double &angle) {
  for (size_t i = 0; i < this->size(); ++i) {
	rotatePoint(center, angle, this->points[i]);
  }
  this->vectors = std::vector<Point>();
  this->makeVectors();
}

void Polygon::reflex(const Point &center) {
  for (size_t i = 0; i < this->size(); ++i) {
	this->points[i] = Point(2 * center.x - this->points[i].x, 2 * center.y - this->points[i].y);
  }
  this->vectors = std::vector<Point>();
  this->makeVectors();
}

void Polygon::reflex(const Line &axis) {
  double denominator = 1 + axis.getSlope() * axis.getSlope();
  double slope = axis.getSlope();
  double shift = axis.getShift();
  for (size_t i = 0; i < this->size(); ++i) {
	double currentX = this->points[i].x;
	double currentY = this->points[i].y;
	this->points[i].x = 2 * (currentX - slope * (shift - currentY)) / denominator - currentX;
	this->points[i].y = (slope * (2 * currentX + slope * currentY) + 2 * shift - currentY) / denominator;
  }
  this->vectors = std::vector<Point>();
  this->makeVectors();
}

void Polygon::scale(const Point &center, const double &coefficient) {
  for (size_t i = 0; i < this->size(); ++i) {
	this->points[i].x = coefficient * (this->points[i].x - center.x) + center.x;
	this->points[i].y = coefficient * (this->points[i].y - center.y) + center.y;
  }
  this->vectors = std::vector<Point>();
  this->makeVectors();
}

Rectangle::Rectangle(Point a, Point b, double ratio) {
  this->points.push_back(a);
  double sideA = Line::length(a, b) / std::sqrt(std::pow(ratio, 2) + 1);
  double sideB = ratio * sideA;
  this->bigger = std::max(sideA, sideB);
  this->smaller = std::min(sideA, sideB);
  this->points.push_back(Point(a.x + 0, a.y + this->smaller));
  this->points.push_back(Point(a.x + this->bigger, a.y + this->smaller));
  this->points.push_back(Point(a.x + this->bigger, a.y + 0));
  this->print();
  //TODO make a different method
  Point realDiagonal = Point(b.x - a.x, b.y - a.y);
  Point fakeDiagonal = Point(this->points[2].x - a.x, this->points[2].y - a.y);
  std::cout << module(fakeDiagonal) << "         " << module(realDiagonal) << std::endl;
  double curCos = cos(realDiagonal, fakeDiagonal);
  double curSin = sin(fakeDiagonal, realDiagonal);
  std::cout << curCos << "---------------" << curSin << std::endl;
  for (size_t i = 1; i < 4; ++i) {
	rotatePoint(a, curCos, curSin, this->points[i]);
  }
}

Point Rectangle::center() const {
  return Point((this->points[0].x + this->points[2].x) / 2, (this->points[0].y + this->points[2].y) / 2);
}

std::pair<Line, Line> Rectangle::diagonals() const {
  return std::make_pair(Line(this->points[0], this->points[2]), Line(this->points[1], this->points[3]));
}

Point Triangle::centroid() const {
  return Point((this->points[0].x + this->points[1].x + this->points[2].x) / 3,
			   (this->points[1].y + this->points[2].y + this->points[2].y) / 3);
}
