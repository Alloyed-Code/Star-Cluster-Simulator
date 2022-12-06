#include "black_hole.h"
#include <string>

black_hole::black_hole(std::string name, double mass) {
	this->name = name;
	this->mass = mass;
	s_radius = (mass * 2.95) / 695700.0;
}

double black_hole::get_radius() {
	return s_radius;
}