#pragma once
#include "space.h"
class Reader {
public:
	Reader();
	virtual ~Reader() = default;

public:
	virtual void read_data() = 0;

public:
	std::shared_ptr<Space> space;
	std::string filename;
	std::size_t print_time_interval;
};

