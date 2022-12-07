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
		star_color = color::red;
	}
	else if (temperature < 5200) {
		star_color = color::orange;
	}
	else if (temperature < 6000) {
		star_color = color::yellow;
	}
	else if (temperature < 7500) {
		star_color = color::white;
	}
	else if (temperature < 10000) {
		star_color = color::blue_white;
	}
	else if(temperature < 30000) {
		star_color = color::deep_blue_white;
	}
	else if (temperature >= 30000) {
		star_color = color::blue;
	}
}