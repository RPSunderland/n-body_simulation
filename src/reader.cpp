#include "../include/reader.h"

Reader::Reader() : space(nullptr), filename(std::string{ }) { }

void Reader::read_file_data(std::size_t& print_time_interval) {
	std::ifstream in;
	in.open("data/" + filename, std::ios_base::in);

	if (!in.is_open()) {
		std::cerr << "Failed to open data file\n";
		return;
	}
	in >> space->name;
	in >> space->size[0] >> space->size[1] >> space->size[2];
	in >> space->end_time; 
	in >> space->dt;
	in >> print_time_interval;
	in >> space->body_count;
	for (std::size_t i = 0; i < space->body_count; ++i) {
		Body body;
		in >> body.name;
		in >> body.mass;
		in >> body.radius;
		in >> body.position.x >> body.position.y >> body.position.z;
		in >> body.velocity.x >> body.velocity.y >> body.velocity.z;
		space->bodies.push_back(body);
	}
	in.close();
}