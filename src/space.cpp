#include "../include/space.h"

Space::Space(int body_count, std::array<double, 3> size, double begin_time, double end_time, double dt, double eps, std::vector<Body> bodies) : body_count(body_count), size(size), begin_time(begin_time), end_time(end_time),
				actual_time(begin_time), dt(dt), eps(eps), bodies(std::move(bodies)) { };

void Space::compute_simulation_step() {	//naive (first update velocity, then posiotions)
	
	for (int i = 0; i < body_count; ++i) {
		Vector acceleration;
		for (int j = 0; j < body_count; ++j) {
			if (i == j) continue;
			Vector r = bodies[j].position - bodies[i].position;

			if (r.norm() < bodies[i].radius + bodies[j].radius) {
				handle_colision(i, j);	//i will be always before j!!
				--j;
				continue;
			}
			acceleration += (G * bodies[j].mass / r.sq_norm()) * (r / r.norm());
		}
		bodies[i].velocity += acceleration * dt;
	}

	for (int i = 0; i < body_count; ++i) {
		bodies[i].position += bodies[i].velocity * dt;
		if (bodies[i].position.max_norm() > size[0]) {
			handle_escape(i);
			--i;
		}
	}
}

void Space::handle_colision(int i, int j) {
	std::string new_name = bodies[i].radius < bodies[j].radius ? bodies[j].name : bodies[i].name;
	double new_mass = bodies[i].mass + bodies[j].mass;
	double new_radius = std::pow(std::pow(bodies[i].radius, 3) + std::pow(bodies[j].radius, 3), 1.0 / 3);
	Vector new_velocity = (bodies[i].mass * bodies[i].velocity + bodies[j].mass * bodies[j].velocity) / new_mass;
	bodies.erase(bodies.begin() + j);	
	--body_count;
	bodies[i].mass = new_mass;
	bodies[i].radius = new_radius;
	bodies[i].velocity = new_velocity;
	
}

void Space::handle_escape(int i) { 
	bodies.erase(bodies.begin() + i);
	--body_count;
}
