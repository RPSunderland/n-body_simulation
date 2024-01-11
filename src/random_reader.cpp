#include "../include/random_reader.h"
void RandomReader::read_data() {
	std::string space_name = "random_space";
	double size = 5000;
	std::size_t dt = 1;
	std::size_t body_count = 100;
	std::size_t end_time = UINT64_MAX;
	double x_min = -500;
	double x_max = 500;
	double v_min = 0;
	double v_max = 0;
	double r_min = 1;
	double r_max = 1;
	double m_min = 5;
	double m_max = 5;

	std::mt19937 re(123);
	std::uniform_real_distribution<double> unif_x(x_min, x_max);
	std::uniform_real_distribution<double> unif_v(v_min, v_max);
	std::uniform_real_distribution<double> unif_r(r_min, r_max);
	std::uniform_real_distribution<double> unif_m(m_min, m_max);

	space->name = space->name;
	space->size = { size, size, size };
	space->end_time = end_time;
	space->dt = dt;
	space->body_count = body_count;

	for (std::size_t i = 0; i < body_count; ++i) {
		Body body;
		body.name = std::string("P") + std::to_string(i + 1);
		body.mass = unif_m(re);
		body.radius = unif_r(re);
		body.position.x = unif_x(re);
		body.position.y = unif_x(re);
		body.position.z = 0;
		body.velocity.x = unif_v(re);
		body.velocity.y = unif_v(re);
		body.velocity.z = 0;
		body.set_graphic_position();
		space->bodies.push_back(body);
	}

}