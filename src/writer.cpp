#include "../include/writer.h"

Writer::Writer() : space(nullptr), filename(std::string{ }), out(std::ofstream{ }), print_time_interval(0) { }
