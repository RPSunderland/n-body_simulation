#include "../include/node.h"

Node::Node(Body* body, Octant octant) : total_mass(body->mass), center_of_mass(body->position), octant(octant), body(body) {
	std::fill(std::begin(children), std::end(children), nullptr);
}

int Node::get_child_index(Vector vector) {
	int index = 0;
	if (vector.x > octant.anchor.x + octant.length / 2) {
		index |= 1;
	}
	if (vector.y > octant.anchor.y + octant.length / 2) {
		index |= 2;
	}
	if (vector.z > octant.anchor.z + octant.length / 2) {
		index |= 4;
	}
	return index;
}