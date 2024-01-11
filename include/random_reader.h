#pragma once
#include <random>
#include "reader.h"

class RandomReader : public Reader {
public:
	using Reader::Reader;
	RandomReader() = default;
	RandomReader(const RandomReader& other) = delete;
	RandomReader(RandomReader&& other) noexcept = delete;
	RandomReader& operator=(const RandomReader& other) = delete;
	RandomReader& operator=(RandomReader&& other) noexcept = delete;
	~RandomReader() = default;

public:
	void read_data();
};


