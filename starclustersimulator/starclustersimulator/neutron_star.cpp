#include "neutron_star.h"
#include <string>

neutron_star::neutron_star(std::string name, double mass) : star(name) {
	this->mass = mass;
	radius = 0.000014;
	lifespan = 10000000000;
	luminosity = pow(mass, 3.5);
	temperature = 1000000;
	color = color::blue;
}