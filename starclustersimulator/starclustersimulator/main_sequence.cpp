#include "main_sequence.h"
#include <math.h>

main_sequence::main_sequence(std::string name, double mass) : star(name) {
	this->mass = mass;
	if (mass > 1) {
		radius = pow(mass, 0.5);
	}
	else {
		radius = pow(mass, 0.8);
	}
	luminosity = pow(mass, 3.5);
	lifespan = mass / luminosity * 10000000000;
	temperature = pow(luminosity / pow(radius, 2), 0.25) * 5778;
	if (temperature < 3700) {
		color = color::red;
	}
	else if (temperature < 5200) {
		color = color::orange;
	}
	else if (temperature < 6000) {
		color = color::yellow;
	}
	else if (temperature < 7500) {
		color = color::white;
	}
	else if (temperature < 10000) {
		color = color::blue_white;
	}
	else if(temperature < 30000) {
		color = color::deep_blue_white;
	}
	else if (temperature >= 30000) {
		color = color::blue;
	}
}