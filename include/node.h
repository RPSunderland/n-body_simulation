#pragma once
#include "body.h"
#include "octant.h"

class Node {
public:
	Node() = delete;
	Node(Body* body, Octant octant);
	Node(const Node& other) = default;
	Node(Node&& other) noexcept = default;
	Node& operator=(const Node& other) = default;
	Node& operator=(Node && other) noexcept = default;
	~Node() = default;
public:
	int get_child_index(Vector vector);
public:
	double total_mass;	
	Vector center_of_mass;	
	Octant octant;	
	Body* body;	
	Node* children[8]; 
};


