#include "unary.h"
#include "protostar.h"

unary::unary(double mass, double x, double y, double z, std::string name) :celestial_system(name, x, y, z) {
	star = new protostar(name, mass);
}

void unary::age_stars(int time) {
	star->age_body(time);
}

stellar_body* unary::get_stars() {
	return star;
}

void unary::set_stars(stellar_body* new_star) {
	star = new_star;
}