#include "protostar.h"
#include "constants.h"
#include "star.h"

protostar::protostar(std::string name, double mass) : star(name) {
	this->mass = mass;
	luminosity = 1000;
	temperature = 2500;
	lifespan = 10000000;
	current_age = 0;
	radius = 70;
	color = color::white;
}