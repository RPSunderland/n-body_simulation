#pragma once
#include "space.h"

class Reporter {
public:
	Reporter() = default;
	void load_data(const std::string& filename);
	void run_simulation();
	bool compute_part_simulation(double time_interval);	
	void print_body(const Body& body, std::ofstream& out) const;
	void print_space(std::ofstream& out) const;	

private:
	std::unique_ptr<Space> space;
	std::string filename;
};




