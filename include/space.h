#pragma once
#include "body.h"
#include "globals.h"
#include "octree.h"

class Space {
public:
	Space();
	Space(const std::string& name, std::size_t body_count, std::array<double, 3> size, std::size_t begin_time, std::size_t end_time, std::size_t dt, std::vector<Body> bodies);
	Space(const Space& other) = delete;
	Space(Space&& other) noexcept = delete;
	Space& operator=(const Space& other) = delete;
	Space& operator=(Space&& other) noexcept = delete;
	~Space() = default;

public:
	bool simulation_step();	
	void handle_collision(std::size_t i, Body* collided_body);
	void handle_escape(std::size_t i);
	std::size_t largest_body_index();

public:
	Octree octree;
	std::string name;
	std::array<double, 3> size;
	std::size_t begin_time; 
	std::size_t end_time; 
	std::size_t current_time;
	std::size_t body_count;
	std::size_t dt; 
	std::vector<Body> bodies; 
};


