#pragma once
#include "vector.h"

class Octant {
public:
	Octant();
	Octant(Vector anchor, double length);
	Octant(const Octant& other) = default;
	Octant(Octant && other) noexcept = default;
	Octant& operator=(const Octant & other) = default;
	Octant& operator=(Octant && other) noexcept = default;
	~Octant() = default;

public:
	bool contains(Vector vector);
	Octant SWD();
	Octant SED();
	Octant NWD();
	Octant NED();
	Octant SWU();
	Octant SEU();
	Octant NWU();
	Octant NEU();

public:
	Vector anchor;
	double length;
};

