#include "white_dwarf.h"
#include <string>
#include <math.h>

white_dwarf::white_dwarf(std::string name, double masss) : star(name) {
	this->mass = mass;
	radius = pow(mass, (-1 / 3.0));
	lifespan = 10000000000;
	luminosity = pow(mass, 3.5);
	temperature = pow(luminosity / pow(radius, 2), 0.25) * 5778;
	star_color = color::white;
}