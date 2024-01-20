#include "../include/space.h"

Space::Space() : Space(std::string{ }, 0, { 0., 0., 0. }, 0, 0, 0, std::vector<Body>{ }) { };
Space::Space(const std::string& name, std::size_t body_count, std::array<double, 3> size, std::size_t begin_time, std::size_t end_time, std::size_t dt, std::vector<Body> bodies) : octree(), name(name), body_count(body_count), size(size), begin_time(begin_time), end_time(end_time),
				current_time(begin_time), dt(dt), bodies(std::move(bodies)), save_positions(false), body_positions() { };

bool Space::simulation_step() {	
	
	if (current_time >= end_time) return false;
	if (body_count == 0) return true;
	Octant octant({ -size[0], -size[0],-size[0] }, 2 * size[0]);	
	octree = Octree(&bodies[0], octant, bodies[largest_body_index()].radius * 5);
	if (body_count > 1000) { octree.theta = body_count / 1000. * 0.5;  }
	for (std::size_t i = 1; i < body_count; ++i) {
		octree.insert(&bodies[i]);	
	}

	for (int i = 0; i < body_count; ++i) {
		if (bodies[i].collided_body != nullptr && bodies[i].collided_body->name != std::string{ }) { handle_collision(i, bodies[i].collided_body); --i; continue; }
		octree.update_acceleration(&bodies[i]);
		bodies[i].velocity += bodies[i].acceleration * static_cast<double>(dt);
	}
	
	

	for (int i = 0; i < body_count; ++i) {
		if (bodies[i].collided_body != nullptr && bodies[i].collided_body->name != std::string{ }) { handle_collision(i, bodies[i].collided_body); --i; continue; }
		bodies[i].position += bodies[i].velocity * static_cast<double>(dt);
		if (bodies[i].position.max_norm() > size[0]) { handle_escape(i); --i; continue; }
		bodies[i].acceleration = { 0, 0, 0 };
	}

	
	if (save_positions && body_positions.size() == 0) {
		for (int i = 0; i < body_count; ++i) {
			body_positions.push_back(std::vector<Vector>{ });
		}
	}
	if (save_positions) {
		for (int i = 0; i < body_count; ++i) {
			body_positions[i].push_back(bodies[i].position);
		}
	}
	

	current_time += dt;

	

	return true;
}


void Space::handle_collision(std::size_t i, Body* collided_body) {
	collided_body->velocity = (bodies[i].mass * bodies[i].velocity + collided_body->mass * collided_body->velocity) / (collided_body->mass + bodies[i].mass);
	collided_body->mass += bodies[i].mass;
	collided_body->radius = std::pow(std::pow(bodies[i].radius, 3) + std::pow(collided_body->radius, 3), 1.0 / 3);
	collided_body->setRadius(static_cast<float>(collided_body->radius));
	bodies.erase(bodies.begin() + i);
	--body_count;
}

void Space::handle_escape(std::size_t i) { 
	bodies.erase(bodies.begin() + i);
	--body_count;
}

std::size_t Space::largest_body_index() {
	std::size_t max_index = 0;
	for (std::size_t i = 0; i < body_count; ++i) {
		if (bodies[i].radius > bodies[max_index].radius) { max_index = i; }
	}
	return max_index;
}