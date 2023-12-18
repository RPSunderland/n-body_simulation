#pragma once
#include "node.h"

class Octree {
public:
	Octree();
	Octree(Octant octant);
	Octree(const Octree& other) = delete;
	Octree(Octree&& other) noexcept = default;
	Octree& operator=(const Octree & other) = delete;
	Octree& operator=(Octree&& other) noexcept = default;
	~Octree() = default;
public:
	void insert(Node node);
	void update_acceleration(Body* body);
	void handle_collision(Node* n1, Node* n2);
	bool is_leaf();
	void print();
public:
	Node node;
	Octant octant; 
	std::unique_ptr<Octree> SWD;
	std::unique_ptr<Octree> SED;
	std::unique_ptr<Octree> NWD;
	std::unique_ptr<Octree> NED;
	std::unique_ptr<Octree> SWU;
	std::unique_ptr<Octree> SEU;
	std::unique_ptr<Octree> NWU;
	std::unique_ptr<Octree> NEU;
};

