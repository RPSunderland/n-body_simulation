#include "../include/reporter.h"

void Reporter::load_data(const std::string& filename) {
	std::ifstream in;
	this->filename = filename;
	in.open("data/" + filename, std::ios_base::in);

	if (!in.is_open()) {
		std::cerr << "Failed to open data file\n";
		return;
	}

	//maybe in data filee
	std::array<double, 3> space_size = { 7.5e+12, 7.5e+12, 7.5e+12 }; //size of solar_system
	double space_begin_time = 0;
	double space_end_time = 86400 * 365 * 1;	//10 years
	double space_dt = 1;
	double space_eps = 0.01;	//(to perform safier calculations)
	int body_count;
	std::vector<Body> space_bodies;

	in >> body_count;
	std::string body_name;
	double body_mass;
	Vector body_position;
	Vector body_velocity;
	double radius;
	for (int i = 0; i < body_count; ++i) {
		in >> body_name;
		in >> body_mass;
		in >> body_position.x >> body_position.y >> body_position.z;
		in >> body_velocity.x >> body_velocity.y >> body_velocity.z;
		in >> radius;
		space_bodies.emplace_back(body_name, body_mass, body_position, body_velocity, radius);
		
	}
	space = std::make_unique<Space>(body_count, space_size, space_begin_time, space_end_time, space_dt, space_eps, space_bodies);
	
	in.close();
}

void Reporter::run_simulation() {
	double time_interval = 86400; //1 day
	std::ofstream out;
	out.open("data/out_" + filename , std::ios_base::out);
	out << "SIMULATION DATA:\n";;
	out << "	space_begin_time:  " << space->begin_time << "\n";
	out << "	space_end_time: " << space->end_time << "\n";
	out << "	space_dt: " << space->dt << "\n";
	out << "	space body_count: " << space->body_count << "\n";
	out << "SIMULATION START\n";
	do {
		print_space(out);
	} while (compute_part_simulation(time_interval));
	out.close();
}

bool Reporter::compute_part_simulation(double time_interval) {
	double i = 0;
	while (i <= time_interval && space->actual_time < space->end_time) {
		space -> compute_simulation_step();
		i += space->dt;
		space->actual_time += space->dt;
	}
	if (space->actual_time < space->end_time) return true;
	return false;
}


void Reporter::print_space(std::ofstream& out) const {
	int day = static_cast<int>(space->actual_time / 86400);
	int year = day / 365;
	out << "	TIME: " << day << " DAYS,	" << year << " YEARS\n";
	for (const auto& body : space->bodies) {
		print_body(body, out);
	}
	//print space to ifstream in suitable format
}

void Reporter::print_body(const Body& body, std::ofstream& out) const {
	out << "	NAME: " << body.name << ",	POSITION: (" << body.position.x << ", " << body.position.y << ", " << body.position.z << "),	" <<
		"velocity: (" << body.velocity.x << ", " << body.velocity.y << ", " << body.velocity.z << "),	" << "radius: " << body.radius << "\n";
		
}
