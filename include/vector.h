#pragma once
#include <cmath>

class Vector {
public:
	Vector();
	Vector(double x, double y);
	double norm();
	inline double sq_norm();

	Vector& operator+=(const Vector& other);
	Vector& operator-=(const Vector& other);
	Vector& operator*=(double scalar);
	Vector& operator-();
	
	friend Vector operator+(Vector lhs, const Vector& rhs);
	friend Vector operator-(Vector lhs, const Vector& rhs);
	friend Vector operator*(Vector vector, double scalar);
	friend Vector operator*(double scalar, Vector vector);
	friend Vector operator/(Vector vector, double scalar);



	
//private:
	double x;
	double y;
};



