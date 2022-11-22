#include "celestial_system.h"

celestial_system::celestial_system(std::string name, double x, double y, double z) {
	this->system_name = name;
	this->x = x;
	this->y = y;
	this->z = z;
}

std::string celestial_system::get_name() {
	return system_name;
}