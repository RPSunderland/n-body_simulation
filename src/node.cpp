#include "../include/node.h"

Node::Node() : mass(-1), position(0, 0, 0), body(nullptr) { }
Node::Node(Body* body) : mass(body->mass), position(body->position), body(body) { }
bool Node::in(Octant octant) {
	if (position.x < octant.anchor.x || position.x > octant.anchor.x + octant.length) return false;
	if (position.y < octant.anchor.y || position.y > octant.anchor.y + octant.length) return false;
	if (position.z < octant.anchor.z || position.z > octant.anchor.z + octant.length) return false;
	return true;
}
Node merge(Node a, Node b) {
	Node c;
	c.mass = a.mass + b.mass;
	c.position = (a.position * a.mass + b.position * b.mass) / c.mass;
	return c;
}