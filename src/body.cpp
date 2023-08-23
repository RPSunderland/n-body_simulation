#include "../include/body.h"

Body::Body() : Body(std::string(), 0, Vector(), Vector(), 0) { }
Body::Body(const std::string& name, double mass, Vector position, Vector velocity, double radius) : name(name), mass(mass), position(position), velocity(velocity), radius(radius) { }




