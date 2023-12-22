#include "../include/octree.h" //
#include "../include/reporter.h"

int main(int argc, char* argv[]) {
	Reporter reporter; //create reporter (singleton?)
	reporter.create_space(); //reporter create default empty space
	reporter.read_file_data(argv[1]); //reporter will make reader to read data to space
	reporter.run(); //reporter will start simulation and make writer to write data to file in specific time interval

	

	return 0;
}







//reporter.stop(); //reporter will stop simulation