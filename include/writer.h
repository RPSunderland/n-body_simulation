#pragma once
#include "space.h"
class Writer {
public:
	Writer();
	virtual ~Writer() = default;

public:
	virtual void write_initial() = 0;
	virtual void write_space() = 0;
	virtual void write_body(const Body& body) = 0;

public:
	std::shared_ptr<Space> space;
	std::string filename;
	std::ofstream out;
	std::size_t print_time_interval;
};
