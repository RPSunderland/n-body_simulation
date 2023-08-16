#include "../include/space.h"


Space::Space(int n, std::pair<double, double> size, double begin_time, double end_time, double dt, double eps, std::vector<Body> bodies) : n(n), size(size), begin_time(begin_time), end_time(end_time),
				actual_time(begin_time), dt(dt), eps(eps), bodies(std::move(bodies)) { };

void Space::run() {
	int count = 0;//
	while (actual_time <= end_time) {
		if(count % 86400 == 0) print_data();//
		compute_simulation_step();
		actual_time += dt;
		++count;
	}
}

void Space::compute_simulation_step() {	//naive (first update veliocity, then posiotions)
	for (int i = 0; i < n; ++i) {
		Vector acceleration;
		for (int j = 0; j < n; ++j) {
			if (i == j) continue;
			Vector r = bodies[j].position - bodies[i].position;
			double acc_scalar = G * bodies[j].mass / r.sq_norm();
			acceleration += (G * bodies[j].mass / r.sq_norm()) * (r / r.norm());
		}
		bodies[i].veliocity += acceleration * dt;
	}

	for (int i = 0; i < n; ++i) {
		bodies[i].position += bodies[i].veliocity * dt;
	}
}

void Space::print_data() const {
	std::cout << "TIME: " << actual_time / 86400 << " DAY\n";
	for (auto& body : bodies) {
		body.print_data();
	}
}


