#include "supergiant.h"
#include <string>

supergiant::supergiant(std::string name, double mass) : star(name) {
	this->mass = mass;
	radius = 500;
	lifespan = 30000000;
	luminosity = 1000000;
	temperature = 10000;
	star_color = color::blue_white;
}