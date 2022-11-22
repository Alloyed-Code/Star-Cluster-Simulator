#include "stellar_body.h"

stellar_body::stellar_body(std::string name) {
	this->name = name;
}
stellar_body::stellar_body() {
	stellar_body("temp");
}
void stellar_body::age_body(int time) {
	current_age += time;
}