#pragma once
#include "space.h"

class Reader {
public:
	Reader();
	Reader(const Reader& other) = delete;
	Reader(Reader&& other) noexcept = delete;
	Reader& operator=(const Reader& other) = delete;
	Reader& operator=(Reader&& other) noexcept = delete;
	~Reader() = default;

public:
	void read_file_data(std::size_t& print_time_interval); 

public:
	std::shared_ptr<Space> space;
	std::string filename;
};

