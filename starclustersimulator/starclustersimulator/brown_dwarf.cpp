#include "brown_dwarf.h"
#include <string>

brown_dwarf::brown_dwarf(std::string name, double mass) : star(name) {
	this->mass = mass;
	radius = .1;
	lifespan = 10000000;
	luminosity = 0;
	temperature =  1000;
	color = color::brown;
}