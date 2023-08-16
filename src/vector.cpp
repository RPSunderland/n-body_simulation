#include "../include/vector.h"

Vector::Vector() : Vector(0, 0) { }
Vector::Vector(double x, double y) : x(x), y(y) { }

double Vector::norm() {
	return sqrt(sq_norm());
}
double Vector::sq_norm() {
	return std::pow(x, 2) + std::pow(y, 2);
}

Vector& Vector::operator+=(const Vector& other) {
	x += other.x;
	y += other.y;
	return *this;
}	

Vector& Vector::operator-=(const Vector& other) {
	*this += other * (-1);
	return *this;
}

Vector& Vector::operator*=(double scalar) {
	x *= scalar;
	y *= scalar;
	return *this;
}

Vector& Vector::operator-() {
	(*this) *= -1;
	return *this;
}


Vector operator+(Vector lhs, const Vector& rhs) {
	lhs += rhs;
	return lhs;
}

Vector operator-(Vector lhs, const Vector& rhs) {
	lhs -= rhs;
	return lhs;
}


Vector operator*(Vector vector, double scalar) {
	vector *= scalar;
	return vector;
}

Vector operator*(double scalar, Vector vector) {
	vector *= scalar;
	return vector;
}

Vector operator/(Vector vector, double scalar) {
	vector *= (1 / scalar);
	return vector;
}
