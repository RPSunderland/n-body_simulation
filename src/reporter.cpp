#include "../include/reporter.h"

Reporter::Reporter() : space(nullptr), filename(std::string()), time_interval(0) { }

void Reporter::load_data(const std::string& filename) {
	std::ifstream in;
	this->filename = filename;
	in.open("data/" + filename, std::ios_base::in);

	if (!in.is_open()) {
		std::cerr << "Failed to open data file\n";
		return;
	}

	std::string space_name;
	std::array<double, 3> space_size; //7.5e+12 
	double space_begin_time = 0; //?
	double space_end_time;
	double space_dt;
	int space_body_count;
	std::vector<Body> space_bodies;

	std::string body_name;
	double body_mass;
	Vector body_position;
	Vector body_velocity;
	double body_radius;
	

	std::regex name_regex(R"(SPACE_NAME:\s*(.+))");
	std::regex size_regex(R"(SPACE_SIZE:\s*\((\d+(?:\.\d+)?(?:e[+-]?\d+)?),\s*(\d+(?:\.\d+)?(?:e[+-]?\d+)?),\s*(\d+(?:\.\d+)?(?:e[+-]?\d+)?)\))");
	std::regex duration_regex(R"(SPACE_DURATION:\s*(\d+))");
	std::regex dt_regex(R"(SPACE_DT:\s*(\d+))");
	std::regex print_interval_regex(R"(PRINT_TIME_INTERVAL:\s*(\d+))");
	std::regex body_count_regex(R"(BODY_COUNT:\s*(\d+))");
	std::regex body_regex(R"(\s*BODY_NAME:\s*(.+?),\s*BODY_MASS:\s*(-?\d+(?:\.\d+)?(?:e[+-]?\d+)?),\s*BODY_RADIUS:\s*(-?\d+(?:\.\d+)?(?:e[+-]?\d+)?),\s*BODY_POSITION:\s*\((-?\d+(?:\.\d+)?(?:e[+-]?\d+)?),\s*(-?\d+(?:\.\d+)?(?:e[+-]?\d+)?),\s*(-?\d+(?:\.\d+)?(?:e[+-]?\d+)?)\),\s*BODY_VELOCITY:\s*\((-?\d+(?:\.\d+)?(?:e[+-]?\d+)?),\s*(-?\d+(?:\.\d+)?(?:e[+-]?\d+)?),\s*(-?\d+(?:\.\d+)?(?:e[+-]?\d+)?)\))");

	std::string line;

	std::smatch match;
	std::getline(in, line);
	std::regex_match(line, match, name_regex);
	space_name = match.str(1);
	
	std::getline(in, line);
	std::regex_match(line, match, size_regex);
	space_size = { std::stod(match.str(1)), std::stod(match.str(2)), std::stod(match.str(3)) };
	
	std::getline(in, line);
	std::regex_match(line, match, duration_regex);
	space_end_time = std::stod(match.str(1));

	std::getline(in, line);
	std::regex_match(line, match, dt_regex);
	space_dt = std::stod(match.str(1));

	std::getline(in, line);
	std::regex_match(line, match, print_interval_regex);
	time_interval = std::stod(match.str(1));

	std::getline(in, line);
	std::regex_match(line, match, body_count_regex);
	space_body_count = std::stod(match.str(1));

	for (int i = 0; i < space_body_count; ++i) {
		std::getline(in, line);
		std::regex_match(line, match, body_regex);
		Body body = { match.str(1),
						 std::stod(match.str(2)), std::stod(match.str(3)),
						 {std::stod(match.str(4)), std::stod(match.str(5)), std::stod(match.str(6))},
						 {std::stod(match.str(7)), std::stod(match.str(8)), std::stod(match.str(9))},
		};
		space_bodies.push_back(body);
	}

	space = std::make_unique<Space>("space", space_body_count, space_size, space_begin_time, space_end_time, space_dt, space_bodies);
	
	in.close();
}

void Reporter::run_simulation() {
	std::ofstream out;
	out.open("data/out_" + filename , std::ios_base::out);
	out << "SIMULATION DATA:\n";;
	out << "	space_name: " << space->name << "\n";
	out << "	space_size: (" << space->size[0] << ", " << space->size[1] << ", " << space->size[2] << ")\n";
	out << "	space_duration: " << (space->end_time - space->begin_time) << "\n";
	out << "	space_dt: " << space->dt << "\n";
	out << "	print_time_interval: " << time_interval << "\n";
	out << "	space body_count: " << space->body_count << "\n";
	out << "SIMULATION START\n";
	do {
		print_space(out);
	} while (compute_part_simulation(time_interval));
	out.close();
}

bool Reporter::compute_part_simulation(double time_interval) {
	double i = 0;
	while (i <= time_interval && space->compute_simulation_step()) {
		i += space->dt;
	}
	if (space->actual_time <= space->end_time) return true;
	return false;
}

void Reporter::print_space(std::ofstream& out) const {
	int day = static_cast<int>(space->actual_time / 86400);
	int year = day / 365;
	out << "	TIME: " << day << " DAYS,	" << year << " YEARS\n";
	for (const auto& body : space->bodies) {
		print_body(body, out);
	}
	out << "\n";
	//print space to ifstream in suitable format
}

void Reporter::print_body(const Body& body, std::ofstream& out) const {
	out << "	NAME: " << body.name
		<< ",	mass: " << body.mass
		<< ",	radius: " << body.radius
		<< ",	position: (" << body.position.x << ", " << body.position.y << ", " << body.position.z << ")"
		<< ",	velocity: (" << body.velocity.x << ", " << body.velocity.y << ", " << body.velocity.z << ")\n";
}
