#include "Service.hpp"

string Service::getTime() {
	time_t result = time(NULL);
	string time_now = "[" + to_string(localtime(&result)->tm_hour) + ":" + to_string(localtime(&result)->tm_min) + ":" +
			to_string(localtime(&result)->tm_sec) + "]";
	return time_now;
}

