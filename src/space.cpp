#include "../include/space.h"

Space::Space(const std::string& name, std::size_t body_count, std::array<double, 3> size, std::size_t begin_time, std::size_t end_time, std::size_t dt, std::vector<Body> bodies) : name(name), body_count(body_count), size(size), begin_time(begin_time), end_time(end_time),
				current_time(begin_time), dt(dt), bodies(std::move(bodies)) { };

bool Space::simulation_step() {	
	if (current_time >= end_time) return false;
	if (body_count == 0) return true;
	Octant octant({ -size[0], -size[0],-size[0] }, 2 * size[0]);
	Octree octree(&bodies[0], octant, bodies[0].radius * 10);	//max radius?
	for (std::size_t i = 1; i < body_count; ++i) {
		octree.insert(&bodies[i]);	//handle collisions
	}

	for (int i = 0; i < body_count; ++i) {
		if (bodies[i].collided_body != nullptr) { handle_collision(i, bodies[i].collided_body); --i; continue; }
		octree.update_acceleration(&bodies[i]);
		bodies[i].velocity += bodies[i].acceleration * static_cast<double>(dt);
	}
	
	for (int i = 0; i < body_count; ++i) { //potential bug if b1 <- b2 <- b3 and b2 is erased
		if (bodies[i].collided_body != nullptr) { handle_collision(i, bodies[i].collided_body); --i; continue; }
		bodies[i].position += bodies[i].velocity * static_cast<double>(dt);
		if (bodies[i].position.max_norm() > size[0]) { handle_escape(i); --i; continue; }
		bodies[i].acceleration = { 0, 0, 0 };
	}

	current_time += dt;

	return true;
}


void Space::handle_collision(std::size_t i, Body* collided_body) {
	std::cout << "boom\n";
	collided_body->velocity = (bodies[i].mass * bodies[i].velocity + collided_body->mass * collided_body->velocity) / (collided_body->mass + bodies[i].mass);
	collided_body->mass += bodies[i].mass;
	collided_body->radius = std::pow(std::pow(bodies[i].radius, 3) + std::pow(collided_body->radius, 3), 1.0 / 3);
	bodies.erase(bodies.begin() + i);
	--body_count;
}

void Space::handle_escape(std::size_t i) { 
	std::cout << "elo \n";
	bodies.erase(bodies.begin() + i);
	--body_count;
}




//naive
	//for (std::size_t i = 0; i < body_count; ++i) {
	//	bodies[i].acceleration = Vector(0, 0, 0);
	//	Vector acceleration;
	//	for (std::size_t j = 0; j < body_count; ++j) {
	//		if (i == j) continue;
	//		Vector r = bodies[j].position - bodies[i].position;		
	//		bodies[i].acceleration += (G * bodies[j].mass / r.sq_norm()) * (r / r.norm());
	//	}
	//	bodies[i].velocity += bodies[i].acceleration * static_cast<double>(dt);
	//}
