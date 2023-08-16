#include "../include/space.h"
#include <iostream>



//deafult units: s, m, kg
int main() {
	//simulation properties
	std::pair<double, double> space_size = std::make_pair<double, double>(1000, 1000); //1000m x 1000m
	double space_begin_time = 0;
	double space_end_time = 86400 * 365 * 1;	//
	double space_dt = 1;
	double space_eps = 0.01;
	int n; //amount of bodies

	//input for space
	//std::cout << "enter amount of bodies: ";
	std::cin >> n;
	std::vector<Body> space_bodies;

	//input for bodies
	std::string body_name;
	double body_mass;
	Vector body_position;
	Vector body_veliocity;
	for (int i = 0; i < n; ++i) {
		//std::cout << "enter name, mass, position and veliocity: ";
		std::cin >> body_name;
		std::cin >> body_mass;
		std::cin >> body_position.x >> body_position.y;
		std::cin >> body_veliocity.x >> body_veliocity.y;
		space_bodies.emplace_back(body_name, body_mass, body_position, body_veliocity);
		//space.bodies.emplace_back(body_name, body_mass, body_position, body_veliocity);
	}

	Space space(n, space_size, space_begin_time, space_end_time, space_dt, space_eps, space_bodies);	//create space		//space.bodies != space_bodies
	


	//run simulation	
	space.run();








	

	return 0;
}