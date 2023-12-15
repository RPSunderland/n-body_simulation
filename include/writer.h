#pragma once
#include "space.h"
class Writer {
public:
	Writer();
	Writer(const Writer& other) = delete;
	Writer(Writer&& other) noexcept = delete;
	Writer& operator=(const Writer& other) = delete;
	Writer& operator=(Writer&& other) noexcept = delete;
	~Writer() = default;

public:
	std::size_t seconds_to_days(std::size_t seconds); 
	std::size_t seconds_to_months(std::size_t seconds); 
	std::size_t seconds_to_years(std::size_t seconds);

	void write_initial(std::size_t print_time_interval, std::ofstream& out);
	void write_space(std::ofstream& out);
	void write_body(const Body& body, std::ofstream& out) const;

public:
	std::shared_ptr<Space> space;
	std::string filename;
};

