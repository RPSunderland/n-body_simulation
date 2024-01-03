#pragma once
#include "reader.h"

class TxtReader : public Reader {
public:
	using Reader::Reader;
	TxtReader() = default;
	TxtReader(const TxtReader& other) = delete;
	TxtReader(TxtReader&& other) noexcept = delete;
	TxtReader& operator=(const TxtReader& other) = delete;
	TxtReader& operator=(TxtReader&& other) noexcept = delete;
	~TxtReader() = default;
public:
	void read_data(std::size_t& print_time_interval);
};
