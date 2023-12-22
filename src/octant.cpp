#include "../include/octant.h"

Octant::Octant() : Octant({ 0, 0, 0 }, 0) { }
Octant::Octant(Vector anchor, double length) : anchor(anchor), length(length) { }
bool Octant::contains(Vector vector) {
	if (vector.x < anchor.x || vector.x > anchor.x + length) return false;
	if (vector.y < anchor.y || vector.y > anchor.y + length) return false;
	if (vector.z < anchor.z || vector.z > anchor.z + length) return false;
	return true;
}
Octant Octant::SWD() {
	Octant swd_octant;
	swd_octant.anchor = anchor;
	swd_octant.length = length / 2;
	return swd_octant;
}
Octant Octant::SED() {
	Octant sed_octant;
	sed_octant.anchor = { anchor.x + length / 2, anchor.y, anchor.z };
	sed_octant.length = length / 2;
	return sed_octant;
}
Octant Octant::NWD() {
	Octant nwd_octant;
	nwd_octant.anchor = { anchor.x, anchor.y + length / 2, anchor.z };
	nwd_octant.length = length / 2;
	return nwd_octant;
}
Octant Octant::NED() {
	Octant ned_octant;
	ned_octant.anchor = { anchor.x + length / 2, anchor.y + length / 2, anchor.z };
	ned_octant.length = length / 2;
	return ned_octant;
}
Octant Octant::SWU() {
	Octant swu_octant;
	swu_octant.anchor = { anchor.x, anchor.y, anchor.z + length / 2 };
	swu_octant.length = length / 2;
	return swu_octant;
}
Octant Octant::SEU() {
	Octant seu_octant;
	seu_octant.anchor = { anchor.x + length / 2, anchor.y, anchor.z + length / 2 };
	seu_octant.length = length / 2;
	return seu_octant;
}
Octant Octant::NWU() {
	Octant nwu_octant;
	nwu_octant.anchor = { anchor.x, anchor.y + length / 2, anchor.z + length / 2 };
	nwu_octant.length = length / 2;
	return nwu_octant;
}
Octant Octant::NEU() {
	Octant neu_octant;
	neu_octant.anchor = { anchor.x + length / 2, anchor.y + length / 2, anchor.z + length / 2};
	neu_octant.length = length / 2;
	return neu_octant;
}

