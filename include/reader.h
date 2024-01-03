#pragma once
#include "space.h"
class Reader {
public:
	Reader();
	virtual ~Reader() = default;
public:
	virtual void read_data(std::size_t& print_time_interval) = 0;
public:
	std::shared_ptr<Space> space;
	std::string filename;
};

