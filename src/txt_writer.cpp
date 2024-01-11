#include "../include/txt_writer.h"

void TxtWriter::write_initial() {
	out << "SPACE_NAME: " << space->name << "\n";
	out << "SPACE_SIZE: (" << space->size[0] << ", " << space->size[1] << ", " << space->size[2] << ")\n";
	out << "SPACE_DURATION: " << (space->end_time - space->begin_time) << "\n";
	out << "SPACE_DT: " << space->dt << "\n";
	out << "PRINT_TIME_INTERVAL: " << print_time_interval << "\n";
	out << "BODY_COUNT: " << space->body_count << "\n";	
}

void TxtWriter::write_space() {
	out << "	SPACE_CURRENT_TIME: " << space->current_time << "\n";
	for (const auto& body : space->bodies) {
		write_body(body);
	}
}

void TxtWriter::write_body(const Body& body) {
	out << "		BODY_NAME: " << body.name
		<< ",	BODY_MASS: " << body.mass
		<< ",	BODY_RADIUS: " << body.radius
		<< ",	BODY_POSITION: (" << body.position.x << ", " << body.position.y << ", " << body.position.z << ")"
		<< ",	BODY_VELOCITY: (" << body.velocity.x << ", " << body.velocity.y << ", " << body.velocity.z << ")\n";
}