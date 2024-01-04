#include "../include/reporter.h"

int main(int argc, char* argv[]) {
    Reporter reporter;
    reporter.create_space();
    if (argc == 2) {
        reporter.is_file_writing = true;
        reporter.read_file_data(argv[1]);
    }
    else { reporter.read_random_data(); }
	reporter.run(); //reporter will start simulation and make writer to write data to file in specific time interval

    

	return 0;
}



//no input file -> no save to file
 //input file -> save to file by default, you can change it in second command




//reporter.stop(); //reporter will stop simulation






