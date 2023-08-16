#pragma once
#include <utility>
#include <string>
#include <iostream>
#include "vector.h"
class Body {
public:
	Body();
	Body(const std::string& name, double mass, Vector position, Vector veliocity);
	void print_data() const;
//private:
	const std::string name;
	double mass;
	Vector position; //(x, y)
	Vector veliocity; //(v_x, v_y)
};

