#include "../include/reporter.h"



int main(int argc, char* argv[]) {
	Reporter reporter; //stworzenie reportera (singleton?)
	reporter.load_data(argv[1]); //za³adowanie danych z symulacji do reportera
	reporter.run_simulation(); //reporter odpala symulacje (automatyczny rejestr do pliku - mozna wylaczyc jesli bedzie tryb graficzny)
	
	
	return 0;
}







