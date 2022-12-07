#include "red_giant.h"
#include <string>

red_giant::red_giant(std::string name, double mass) : star(name) {
	this->mass = mass;
	radius = 100;
	lifespan = 1000000000;
	luminosity = 3000;
	temperature = 2500;
	star_color = color::red;
}