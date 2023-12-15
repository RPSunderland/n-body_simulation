#include "../include/vector.h"

Vector::Vector() : Vector(0, 0, 0) { }
Vector::Vector(double x, double y, double z) : x(x), y(y), z(z) { }

double Vector::norm() const{
	return sqrt(sq_norm());
}
double Vector::sq_norm() const {
	return std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2);
}

double Vector::max_norm() const {
	return std::max({ std::abs(x), std::abs(y), std::abs(z) });
}

Vector& Vector::operator+=(const Vector& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}	

Vector& Vector::operator-=(const Vector& other) {
	*this += other * (-1);
	return *this;
}

Vector& Vector::operator*=(double scalar) {
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

Vector& Vector::operator/=(double scalar) {
	*this *= (1 / scalar);
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


Vector operator*(Vector lhs, double rhs) {
	lhs *= rhs;
	return lhs;
}

Vector operator*(double lhs, Vector rhs) {
	rhs *= lhs;
	return rhs;
}

Vector operator/(Vector lhs, double rhs) {
	lhs /= rhs;
	return lhs;
}


