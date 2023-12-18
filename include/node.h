#pragma once
#include "body.h"
#include "octant.h"

class Node {
public:
	Node();
	Node(Body* body);
	Node(const Node& other) = default;
	Node(Node&& other) noexcept = default;
	Node& operator=(const Node& other) = default;
	Node& operator=(Node && other) noexcept = default;
	~Node() = default;
public:
	//bool in(Octant octant);
public:
	double total_mass;
	Vector center_of_mass;
	std::shared_ptr<Body> body;
	std::shared_ptr<Node> children[8];
};

//Node merge(Node a, Node b);
