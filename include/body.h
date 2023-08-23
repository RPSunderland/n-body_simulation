#pragma once
#include "vector.h"

class Body {
public:
	Body();
	Body(const std::string& name, double mass, Vector position, Vector velocity, double radius);
	Body(const Body& other) = default;
	Body(Body&& other) noexcept = default;
	Body& operator=(const Body& other) = default;
	Body& operator=(Body&& other) noexcept = default;
	~Body() = default;

public:
	std::string name;
	double mass;
	Vector position; 
	Vector velocity; 
	double radius;
};
