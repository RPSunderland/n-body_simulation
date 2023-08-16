#include "../include/body.h"

Body::Body() = default;
Body::Body(const std::string& name, double mass, Vector position, Vector veliocity) : name(name), mass(mass), position(position), veliocity(veliocity) { }
void Body::print_data() const {
	std::cout << name << " #### " << "(" << position.x << ", " << position.y << ")" << " #### " << "(" << veliocity.x << ", " << veliocity.y << ")\n";
}
