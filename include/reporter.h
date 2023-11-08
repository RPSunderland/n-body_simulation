#pragma once
#include "space.h"
#include "reader.h"
#include "writer.h"

class Reporter {
public:
	Reporter();	//jeden jedyny konstruktor domyslny
	Reporter(const Reporter& other) = delete;
	Reporter(Reporter&& other) noexcept = delete;
	Reporter& operator=(const Reporter& other) = delete;
	Reporter& operator=(Reporter&& other) noexcept = delete;
	~Reporter() = default;

	void load_data(const std::string& filename); //odczyt danych z pliku zakonczony stworzeniem przestrzeni o zadanych wlasnosciach
	void run_simulation();	//zapis danych do pliki, wywoluje metode compute_part_simulation co time_interval i zapisuje dane
	bool compute_part_simulation(double time_interval);	//wywoluje krok symulacji przestrzeni! przez time_interval czasu
	void print_body(const Body& body, std::ofstream& out) const; //szablon do printowania cia³a -> writer
	void print_space(std::ofstream& out) const;	 //szbalon do printowania przesztrzeni -> write

private:
	std::unique_ptr<Space> space;	//wskaznik na symulowana przestrzen
	std::unique_ptr<Reader> reader;
	std::unique_ptr<Writer> writer;
	std::string filename;	//output 
	double time_interval;	//zmienna okreslajaca krok czasowy kolejnych wpisów
	
};




