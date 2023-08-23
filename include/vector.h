#pragma once
#include "includes.h"

class Vector {
public:
	Vector();
	Vector(double x, double y, double z);
	Vector(const Vector& other) = default;
	Vector(Vector&& other) noexcept = default;
	Vector& operator=(const Vector& other) = default;
	Vector& operator=(Vector&& other) noexcept = default;
	~Vector() = default;

	double norm() const;
	double sq_norm() const;
	double max_norm() const;

	Vector& operator+=(const Vector& other);
	Vector& operator-=(const Vector& other);
	Vector& operator*=(double scalar);
	Vector& operator/=(double scalar);
	Vector& operator-();
	
	friend Vector operator+(Vector lhs, const Vector& rhs);
	friend Vector operator-(Vector lhs, const Vector& rhs);
	friend Vector operator*(Vector lhs, double rhs);
	friend Vector operator*(double lhs, Vector rhs);
	friend Vector operator/(Vector lhs, double rhs);

public:
	double x;
	double y;
	double z;
};


