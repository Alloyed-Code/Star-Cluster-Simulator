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

double celestial_system::get_x() {
	return x;
}
double celestial_system::get_y() {
	return y;
}
double celestial_system::get_z() {
	return z;
}