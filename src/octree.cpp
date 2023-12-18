#include "../include/octree.h"
#include "../include//space.h"

Octree::Octree() { }
Octree::Octree(Octant octant) : node(Node{ }), octant(octant), SWD(nullptr), SED(nullptr), NWD(nullptr), NED(nullptr), SWU(nullptr), SEU(nullptr), NWU(nullptr), NEU(nullptr) { }
void Octree::insert(Node node) {

	if (this->node.mass == -1) {	//empty node
		this->node = node;
		return;
	}
	if (is_leaf()) {	//external node
		SWD = std::make_unique<Octree>(octant.SWD());
		SED = std::make_unique<Octree>(octant.SED());
		NWD = std::make_unique<Octree>(octant.NWD());
		NED = std::make_unique<Octree>(octant.NED());
		SWU = std::make_unique<Octree>(octant.SWU());
		SEU = std::make_unique<Octree>(octant.SEU());
		NWU = std::make_unique<Octree>(octant.NWU());
		NEU = std::make_unique<Octree>(octant.NEU());

		if (node.in(octant.SWD())) { SWD->insert(node); }
		else if (node.in(octant.SED())) { SED->insert(node); }
		else if (node.in(octant.NWD())) { NWD->insert(node); }
		else if (node.in(octant.NED())) { NED->insert(node); }
		else if (node.in(octant.SWU())) { SWU->insert(node); }
		else if (node.in(octant.SEU())) { SEU->insert(node); }
		else if (node.in(octant.NWU())) { NWU->insert(node); }
		else if (node.in(octant.NEU())) { NEU->insert(node); }

		if (this->node.in(octant.SWD())) { SWD->insert(this->node); }
		else if (this->node.in(octant.SED())) { SED->insert(this->node); }
		else if (this->node.in(octant.NWD())) { NWD->insert(this->node); }
		else if (this->node.in(octant.NED())) { NED->insert(this->node); }
		else if (this->node.in(octant.SWU())) { SWU->insert(this->node); }
		else if (this->node.in(octant.SEU())) { SEU->insert(this->node); }
		else if (this->node.in(octant.NWU())) { NWU->insert(this->node); }
		else if (this->node.in(octant.NEU())) { NEU->insert(this->node); }

		this->node = merge(this->node, node);
		return;
	}
	this->node = merge(this->node, node);	//internal node
	if (node.in(octant.SWD())) { SWD->insert(node); return; }
	if (node.in(octant.SED())) { SED->insert(node); return; }
	if (node.in(octant.NWD())) { NWD->insert(node); return; }
	if (node.in(octant.NED())) { NED->insert(node); return; }
	if (node.in(octant.SWU())) { SWU->insert(node); return; }
	if (node.in(octant.SEU())) { SEU->insert(node); return; }
	if (node.in(octant.NWU())) { NWU->insert(node); return; }
	if (node.in(octant.NEU())) { NEU->insert(node); return; }
	std::cerr << "not insert\n";
}

void Octree::update_acceleration(Body* body) { 
	if (node.body != nullptr && body != node.body) {	//calculate force
		Vector r = body->position - node.body->position;
		if (r.norm() < body->radius + node.body->radius) { std::cout << "boom\n"; } //handle_colision, TO_DO!!!
		body->acceleration += (G * node.body->mass / r.sq_norm()) * (r / r.norm());
		return;
	}
	double s = octant.length;
	Vector r = body->position - node.position;
	double d = r.norm();
	if (s / d < 0.5) {
		body->acceleration += (G * node.mass / r.sq_norm()) * (r / d);
		return;
	}
	if (SWD != nullptr) SWD->update_acceleration(body);
	if (SED != nullptr) SED->update_acceleration(body);
	if (NWD != nullptr) NWD->update_acceleration(body);
	if (NED != nullptr) NED->update_acceleration(body);
	if (SWU != nullptr) SWU->update_acceleration(body);
	if (SEU != nullptr) SEU->update_acceleration(body);
	if (NWU != nullptr) NWU->update_acceleration(body);
	if (NEU != nullptr) NEU->update_acceleration(body);
}

bool Octree::is_leaf() {
	if (SWD == nullptr && SED == nullptr && NWD == nullptr && NED == nullptr && SWU == nullptr && SEU == nullptr && NWU == nullptr && NEU == nullptr) return true;
	return false;
}

void Octree::print() {
	if (node.body != nullptr) {
		std::cout << node.body->position.x << " " << node.body->position.y << " " << node.body->position.z << "\n";
	}
	if (SWD != nullptr) SWD->print();
	if (SED != nullptr) SED->print();
	if (NWD != nullptr) NWD->print();
	if (NED != nullptr) NED->print();
	if (SWU != nullptr) SWU->print();
	if (SEU != nullptr) SEU->print();
	if (NWU != nullptr) NWU->print();
	if (NEU != nullptr) NEU->print();
}