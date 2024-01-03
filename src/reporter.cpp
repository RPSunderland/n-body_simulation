#include "../include/reporter.h"


Reporter::Reporter() : space(nullptr), reader(std::make_unique<TxtReader>()), writer(std::make_unique<TxtWriter>()), print_time_interval(0), is_running(false), is_file_writing(true) { }

void Reporter::create_space() {
	space = std::make_shared<Space>();
	reader->space = space;
	writer->space = space;
}

void Reporter::read_file_data(const std::string& filename) {
	reader->filename = filename;
	writer->filename = "out_" + filename;
	reader->read_data(print_time_interval);
}

void Reporter::run() {
	is_running = true;
	std::ofstream out;
	if (is_file_writing) {
		out.open("data/" + writer->filename, std::ios_base::out);
		writer->write_initial(print_time_interval, out);
	}
	
	while (space->simulation_step() && is_running) {
		if (space->current_time % print_time_interval < space->dt && is_file_writing) {
			writer->write_space(out);
		}
	}
	if (is_file_writing) out.close();
}

void Reporter::stop() {
	is_running = false;
}


//if(space->current_time % show_time_interval == 0 && is_gui_open) {
//	writer->write_to_gui()
//}
		


