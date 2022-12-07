#pragma once
#include "stellar_body.h"
#include "constants.h"

class star : public stellar_body {
protected:
	double luminosity;
	double temperature;
	double radius;
	color star_color;
public:
	star(std::string name);
	double get_radius() override;
	color get_color() override;
};