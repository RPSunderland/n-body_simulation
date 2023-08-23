#include "../include/reporter.h"


int main(int argc, char* argv[]) {
	Reporter reporter;
	reporter.load_data(argv[1]);	//GUI
	reporter.run_simulation();	//GUI
	//reporter.stop_simulation(); //GUI
	//reporter.save_data(); //GUI

	return 0;
}