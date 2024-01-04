#pragma once
#include "writer.h"
class TxtWriter : public Writer {
public:
	using Writer::Writer;
	TxtWriter() = default;
	TxtWriter(const TxtWriter& other) = delete;
	TxtWriter(TxtWriter&& other) noexcept = delete;
	TxtWriter& operator=(const TxtWriter& other) = delete;
	TxtWriter& operator=(TxtWriter&& other) noexcept = delete;
	~TxtWriter() = default;

public:
	void write_initial(std::size_t print_time_interval, std::ofstream& out);
	void write_space(std::ofstream& out);
	void write_body(const Body& body, std::ofstream& out) const;
};
