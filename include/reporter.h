#pragma once
#include "space.h"
#include "txt_reader.h"
#include "txt_writer.h"

class Reporter {
public:
	Reporter();
	Reporter(const Reporter& other) = delete;
	Reporter(Reporter&& other) noexcept = delete;
	Reporter& operator=(const Reporter& other) = delete;
	Reporter& operator=(Reporter&& other) noexcept = delete;
	~Reporter() = default;

public:
	void create_space();
	void read_file_data(const std::string& filename);
	void run();
	void stop(); 

private:
	std::shared_ptr<Space> space;	
	std::unique_ptr<Reader> reader;
	std::unique_ptr<Writer> writer;
	std::size_t print_time_interval;
	bool is_running;	
	bool is_file_writing; 
};




//std::size_t show_time_interval = dt?;	- interval for frequency of showing the simulation on gui screen
//void speed_up();	- decrease show_time
//void slow_down(); - increase show_time
//void change_dt(), change_end_time, - danger, change physics 
//std::shared_ptr<Space> orginal_space - it would be space with initial conditisions (for restart or sth)

//gui need to care about scale from real size to screen size (also time need to be scaled)





