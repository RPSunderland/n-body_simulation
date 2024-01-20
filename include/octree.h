#pragma once
#include "node.h"
#include "octree_iterator.h"

class Octree {
public:
	Octree();
	Octree(Body* body, Octant octant, double eps);
	Octree(const Octree& other) = delete;
	Octree(Octree&& other) = delete;
	Octree& operator=(const Octree& other) = delete;
	Octree& operator=(Octree&& other) noexcept;
	~Octree();

public:
	Node* insert(Node* node, Octant octant, Body* body);
	void insert(Body* body);
	void update_acceleration(Body* body);
	void update_acceleration(Node* node, Body* body);
	void delete_tree(Node* node);
	std::shared_ptr<OctreeIterator> create_iterator();
	
public:
	Node* root;
	double eps;
	double theta;
};

