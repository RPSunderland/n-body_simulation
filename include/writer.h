#pragma once
#include "space.h"
class Writer {
public:
	Writer();
	virtual ~Writer() = default;
public:
	virtual void write_initial(std::size_t print_time_interval, std::ofstream& out) = 0;
	virtual void write_space(std::ofstream& out) = 0;
	virtual void write_body(const Body& body, std::ofstream& out) const = 0;
public:
	std::shared_ptr<Space> space;
	std::string filename;
};

std::size_t seconds_to_days(std::size_t seconds);	
std::size_t seconds_to_months(std::size_t seconds);
std::size_t seconds_to_years(std::size_t seconds);