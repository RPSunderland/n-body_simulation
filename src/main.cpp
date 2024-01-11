#include "../include/reporter.h"

int main(int argc, char* argv[]) {
    Reporter reporter;
    if (argc == 1) {
        reporter.random_reader_initialize();
    }
    else if (argc == 2) {
        reporter.txt_reader_initialize();
    }
    else if (argc == 3 && std::string(argv[2]) == "-s") {
        reporter.txt_reader_initialize();
        reporter.txt_writer_initialize();
    }
    else {
        std::cerr << "Invalid command line arguments.\n";
        return EXIT_FAILURE;
    }
    reporter.create_space();
    argc == 1 ? reporter.read_data("") : reporter.read_data(argv[1]);
    reporter.run();
    return EXIT_SUCCESS;
}









