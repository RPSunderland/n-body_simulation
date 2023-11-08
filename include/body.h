#pragma once
#include "vector.h"

class Body {	
public:
	Body();
	Body(const std::string& name, double mass, double radius, Vector position, Vector velocity);
	Body(const Body& other) = default;
	Body(Body&& other) noexcept = default;
	Body& operator=(const Body& other) = default;
	Body& operator=(Body&& other) noexcept = default;
	~Body() = default;

public:
	std::string name;
	double mass;
	double radius;
	Vector position; 
	Vector velocity; 
};
