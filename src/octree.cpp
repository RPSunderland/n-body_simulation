#include "../include/octree.h"

Octree::Octree(Body* body, Octant octant, double eps) : root(new Node(body, octant)), eps(eps) { }
Octree::~Octree() { delete_tree(root); }
void Octree::delete_tree(Node* node) {
	if (node != nullptr) {
		for (int i = 0; i < 8; ++i) {
			delete_tree(node->children[i]);
		}
		delete node;
	}
}

void Octree::insert(Body* body) {
	root = insert(root, root->octant, body);
}

Node* Octree::insert(Node* node, Octant octant, Body* body) {
	if (node == nullptr) {	//nullptr
		return new Node(body, octant);
	}
	node->center_of_mass = (node->center_of_mass * node->total_mass + body->position * body->mass) / (node->total_mass + body->mass);
	node->total_mass += body->mass;
	if (node->body == nullptr) { //internal node
		int index = node->get_child_index(body->position);
		switch (index) {
			case 0: octant = octant.SWD(); break;
			case 1: octant = octant.SED(); break;
			case 2: octant = octant.NWD(); break;
			case 3: octant = octant.NED(); break;
			case 4: octant = octant.SWU(); break;
			case 5: octant = octant.SEU(); break;
			case 6: octant = octant.NWU(); break;
			case 7: octant = octant.NEU(); break;
			default: break;
		}
		node->children[index] = insert(node->children[index], octant, body);
	} 	
	else { //external node	

		if (octant.length < eps) {
			Vector r = node->body->position - body->position;
			double d = r.norm();
			if (d < body->radius + node->body->radius) {	//collision
				if (body->radius < node->body->radius) { body->collided_body = node->body; return node; }
				node->body->collided_body = body;
				node->body = body;
				return node;
			}
		}

		int index_1 = node->get_child_index(body->position);
		int index_2 = node->get_child_index(node->body->position);
		Octant octant_1, octant_2;
		switch (index_1) {
			case 0: octant_1 = octant.SWD(); break;
			case 1: octant_1 = octant.SED(); break;
			case 2: octant_1 = octant.NWD(); break;
			case 3: octant_1 = octant.NED(); break;
			case 4: octant_1 = octant.SWU(); break;
			case 5: octant_1 = octant.SEU(); break;
			case 6: octant_1 = octant.NWU(); break;
			case 7: octant_1 = octant.NEU(); break;
			default: break;
		}
		switch (index_2) {
			case 0: octant_2 = octant.SWD(); break;
			case 1: octant_2 = octant.SED(); break;
			case 2: octant_2 = octant.NWD(); break;
			case 3: octant_2 = octant.NED(); break;
			case 4: octant_2 = octant.SWU(); break;
			case 5: octant_2 = octant.SEU(); break;
			case 6: octant_2 = octant.NWU(); break;
			case 7: octant_2 = octant.NEU(); break;
			default: break;
		}
		node->children[index_1] = insert(node->children[index_1], octant_1, body);
		node->children[index_2] = insert(node->children[index_2], octant_2, node->body);
		node->body = nullptr;
	}
	return node;
}

void Octree::update_acceleration(Body* body) {
	update_acceleration(root, body);
}

void Octree::update_acceleration(Node* node, Body* body) {
	if (body->collided_body != nullptr) return;
	if (node != nullptr) {
		Vector r;
		double d;
		double sq;
		if (node->body != nullptr) {
			if (body == node->body) return;
			r = node->body->position - body->position;
			d = r.norm();

			if (d < body->radius + node->body->radius) { //collision
				if (body->radius < node->body->radius) {
					body->collided_body = node->body;
					body->acceleration = { 0, 0, 0 };
					return;
				}
				node->body->collided_body = body;
				return;
			}

			sq = r.sq_norm();
			body->acceleration += (G * node->body->mass / sq) * (r / d);
			return;
		}
		r = node->center_of_mass - body->position;
		d = r.norm();
		double s = node->octant.length;
		if (s / d < 0.5) {
			sq = r.sq_norm();
			body->acceleration += (G * node->total_mass / r.sq_norm()) * (r / d);
			return;
		}
		for (int i = 0; i < 8; ++i) {
			update_acceleration(node->children[i], body);
		}
	}
}


void Octree::print() {
	print(root);
}

void Octree::print(Node* node) {
	if(node != nullptr) {
		if (node->body != nullptr) { std::cout << node->body->position.x << " " << node->body->position.y << " " << node->body->position.z << "\n"; return; }
		for (int i = 0; i < 8; ++i) {
			print(node->children[i]);
		}
	}
}