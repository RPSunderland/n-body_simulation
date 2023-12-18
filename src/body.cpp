#include "../include/body.h"

Body::Body() : Body(std::string(), 0, 0, Vector(), Vector()) { }
Body::Body(const std::string& name, double mass, double radius, Vector position, Vector velocity) : name(name), mass(mass), radius(radius), position(position), velocity(velocity), acceleration(0, 0, 0) { }




