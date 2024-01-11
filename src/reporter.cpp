#include "../include/reporter.h"

Reporter::Reporter() : space(nullptr), gui_handler(std::make_unique<GUI_Handler>()), reader(nullptr), writer(nullptr), is_running(false), is_file_writing(false), is_file_reading(false) { }

void Reporter::random_reader_initialize() {
	reader = std::make_unique<RandomReader>();
}
void Reporter::txt_reader_initialize() {
	reader = std::make_unique<TxtReader>();
	is_file_reading = true;
}
void Reporter::txt_writer_initialize() {
	writer = std::make_unique<TxtWriter>();
	is_file_writing = true;
}

void Reporter::create_space() {
	space = std::make_shared<Space>();
	gui_handler->reporter = this;
	gui_handler->space = space;
	if(reader != nullptr) { reader->space = space; }
	if(writer != nullptr) { writer->space = space; }
}

void Reporter::read_data(const std::string& filename) {
	if (is_file_reading) {
		reader->filename = filename;
	}
	reader->read_data();
	if (is_file_writing) {
		writer->filename = "out_" + filename;
		writer->print_time_interval = reader->print_time_interval;
	}
}

void Reporter::run() {
	is_running = true;
	if (is_file_writing) {
		writer->out.open("data/" + writer->filename, std::ios_base::out);
		writer->write_initial();
	}
	gui_handler->initialize();
	gui_handler->run();
	if (is_file_writing) { writer->out.close(); }
}

		


