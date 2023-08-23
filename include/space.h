#include "body.h"
#include "globals.h"

class Space {
public:
	Space(int body_count, std::array<double, 3> size, double begin_time, double end_time, double dt, double eps, std::vector<Body> bodies);
	Space(const Space& other) = delete;
	Space(Space&& other) noexcept = delete;
	Space& operator=(const Space& other) = delete;
	Space& operator=(Space&& other) noexcept = delete;
	~Space() = default;

	void compute_simulation_step();
	void handle_colision(int i, int j);
	void handle_escape(int i);

public:
	int body_count;
	const std::array<double, 3> size;
	const double begin_time;
	const double end_time;
	double actual_time;
	const double dt;
	const double eps;
	std::vector<Body> bodies;
};


//-maybe some static variables 