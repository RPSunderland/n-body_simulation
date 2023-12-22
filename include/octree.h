#pragma once
#include "node.h"

class Octree {
public:
	Octree() = delete;
	Octree(Body* body, Octant octant, double eps);
	Octree(const Octree& other) = delete;
	Octree(Octree&& other) noexcept = default;
	Octree& operator=(const Octree & other) = delete;
	Octree& operator=(Octree&& other) noexcept = default;
	~Octree();
public:
	Node* insert(Node* node, Octant octant, Body* body);
	void insert(Body* body);
	void update_acceleration(Body* body);
	void update_acceleration(Node* node, Body* body);
	void delete_tree(Node* node);
	void print();	//x
	void print(Node* node);	//x
public:
	Node* root;
	double eps;
};

