#include "../include/txt_writer.h"

void TxtWriter::write_initial(std::size_t print_time_interval, std::ofstream& out) {
	out << "SPACE_NAME: " << space->name << "\n";
	out << "SPACE_SIZE: (" << space->size[0] << ", " << space->size[1] << ", " << space->size[2] << ")\n";
	out << "SPACE_DURATION: " << (space->end_time - space->begin_time) << "\n";
	out << "SPACE_DT: " << space->dt << "\n";
	out << "PRINT_TIME_INTERVAL: " << print_time_interval << "\n";
	out << "BODY_COUNT: " << space->body_count << "\n";	
}

void TxtWriter::write_space(std::ofstream& out) {
	std::size_t day = seconds_to_days(space->current_time);
	std::size_t month = seconds_to_months(space->current_time);
	std::size_t year = seconds_to_years(space->current_time);
	out << "	SPACE_CURRENT_TIME: " << space->current_time << " (" << day << ", " << month << ", " << year << ")\n";
	for (const auto& body : space->bodies) {
		write_body(body, out);
	}
}

void TxtWriter::write_body(const Body& body, std::ofstream& out) const {
	out << "		BODY_NAME: " << body.name
		<< ",	BODY_MASS: " << body.mass
		<< ",	BODY_RADIUS: " << body.radius
		<< ",	BODY_POSITION: (" << body.position.x << ", " << body.position.y << ", " << body.position.z << ")"
		<< ",	BODY_VELOCITY: (" << body.velocity.x << ", " << body.velocity.y << ", " << body.velocity.z << ")\n";
}