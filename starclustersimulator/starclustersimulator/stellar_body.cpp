#include "stellar_body.h"

stellar_body::stellar_body(std::string name) {
	this->name = name;
	current_age = 0;
}
stellar_body::stellar_body() {
	stellar_body("temp");
}
void stellar_body::age_body(int time) {
	current_age += time;
}

long long int stellar_body::get_lifespan() {
	return lifespan;
}
long long int stellar_body::get_age() {
	return current_age;
}

std::string stellar_body::get_name() {
	return name;
}

double stellar_body::get_mass() {
	return mass;
}

double stellar_body::get_radius() {
	return -1;
}

color stellar_body::get_color() {
	return color::black;
}