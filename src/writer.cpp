#include "../include/writer.h"

Writer::Writer() : space(nullptr), filename(std::string{ }) {}

std::size_t seconds_to_days(std::size_t seconds) { 
	std::size_t days = seconds / 86400;
	days %= 365;
	return days;
}
std::size_t seconds_to_months(std::size_t seconds) {
	std::size_t days = seconds_to_days(seconds);
	std::size_t months = days / 30;
	months %= 12 + 1;
	return months;
}
std::size_t seconds_to_years(std::size_t seconds) {
	return (seconds / 31536000);
}