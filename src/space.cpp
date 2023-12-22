#include "../include/space.h"

Space::Space(const std::string& name, std::size_t body_count, std::array<double, 3> size, std::size_t begin_time, std::size_t end_time, std::size_t dt, std::vector<Body> bodies) : name(name), body_count(body_count), size(size), begin_time(begin_time), end_time(end_time),
				current_time(begin_time), dt(dt), bodies(std::move(bodies)) { };

bool Space::simulation_step() {	
	if (current_time >= end_time) return false;

	//naive
	//for (std::size_t i = 0; i < body_count; ++i) {
	//	bodies[i].acceleration = Vector(0, 0, 0);
	//	Vector acceleration;
	//	for (std::size_t j = 0; j < body_count; ++j) {
	//		if (i == j) continue;
	//		Vector r = bodies[j].position - bodies[i].position;
	//		//if (r.norm() < bodies[i].radius + bodies[j].radius) {
	//		//	//handle_colision(i, j);	
	//		//	//std::cout << "boom \n";
	//		//	--j;	
	//		//	continue;
	//		//}
	//		bodies[i].acceleration += (G * bodies[j].mass / r.sq_norm()) * (r / r.norm());
	//	}
	//	bodies[i].velocity += bodies[i].acceleration * static_cast<double>(dt);
	//}
	

	//create tree (if there are bodies!!!)
	//insert all bodies to the tree
	//call tree.update_acceleration
	//iterate over bodies if there is null (collison) delete it and update bodie_count

	if (body_count == 0) return true;
	Octant octant({ -size[0], -size[0],-size[0] }, 2 * size[0]);
	Octree octree(&bodies[0], octant, bodies[0].radius * 10);	//max radus?
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






//void Space::handle_colision(std::size_t i, std::size_t j) {
//	std::string new_name = bodies[i].radius < bodies[j].radius ? bodies[j].name : bodies[i].name;
//	double new_mass = bodies[i].mass + bodies[j].mass;
//	double new_radius = std::pow(std::pow(bodies[i].radius, 3) + std::pow(bodies[j].radius, 3), 1.0 / 3);
//	Vector new_velocity = (bodies[i].mass * bodies[i].velocity + bodies[j].mass * bodies[j].velocity) / new_mass;
//	bodies.erase(bodies.begin() + j);	
//	--body_count;
//	bodies[i].mass = new_mass;
//	bodies[i].radius = new_radius;
//	bodies[i].velocity = new_velocity;
//	
//}

