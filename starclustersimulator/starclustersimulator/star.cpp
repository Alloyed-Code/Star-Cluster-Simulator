#include "star.h"
#include <string>

star::star(std::string name) : stellar_body(name) {

}

double star::get_radius() {
	return radius;
}

color star::get_color() {
	return star_color;
}