#include "../include/body.h"

Body::Body() : Body(std::string(), 0, 0, Vector(), Vector()) { }
Body::Body(const std::string& name, double mass, double radius, Vector position, Vector velocity) : sf::CircleShape(radius), name(name), mass(mass), radius(radius), position(position), velocity(velocity), acceleration(0, 0, 0), collided_body(nullptr) { 
	set_graphic_position();
}

void Body::set_graphic_position() {
	sf::Vector2f graphic_position = to_graphic_coords(position);
	setPosition(graphic_position);
	setFillColor(sf::Color::White);
	setRadius(radius);
}

void Body::move() {
	sf::Vector2f graphic_velocity = sf::Vector2f(static_cast<float>(velocity.x), static_cast<float>(-velocity.y));
	sf::CircleShape::move(graphic_velocity.x, graphic_velocity.y);
}




