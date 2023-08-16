#include "body.h"
#include "globals.h"
#include "units.h"
#include <vector>

struct Space {
	Space(int n, std::pair<double, double> size, double begin_time, double end_time, double dt, double eps, std::vector<Body> bodies);
	int n;
	std::pair<double, double> size;
	double begin_time;
	double end_time;
	double actual_time;
	double dt;	
	double eps;
	std::vector<Body> bodies;
	

	void compute_simulation_step();
	void run();
	void print_data() const;
};


//-maybe some static variables 