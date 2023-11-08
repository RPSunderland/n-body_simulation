#include "body.h"
#include "globals.h"

class Space {
public:
	Space(const std::string& name, int body_count, std::array<double, 3> size, double begin_time, double end_time, double dt, std::vector<Body> bodies);	//jeden jedyny konstruktor jawny
	Space(const Space& other) = delete;
	Space(Space&& other) noexcept = delete;
	Space& operator=(const Space& other) = delete;
	Space& operator=(Space&& other) noexcept = delete;
	~Space() = default;

	bool compute_simulation_step();	//oblicza krok symulacji o czas dt
	void handle_colision(int i, int j);	//obluga kolizje dwoch obiektow
	void handle_escape(int i); //obsluga ucieczki obiektu

public:
	const std::string name;
	const std::array<double, 3> size; //rozmiar przestrzeni
	const double begin_time; //start symulacji
	const double end_time; //zakonczenie symulacji
	double actual_time; //obecny czas
	int body_count; //ilosc cial
	const double dt; //krok czasowy
	std::vector<Body> bodies; //ciala
};


//-maybe some static variables 