#include "../include/txt_reader.h"
void TxtReader::read_data() {
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
		body.set_graphic_position();
		space->bodies.push_back(body);
	}
	in.close();
}