#pragma once
#include "stellar_body.h"
#include "constants.h"

class star : public stellar_body {
protected:
	double luminosity;
	double temperature;
	double radius;
	color color;
public:
	star(std::string name);
};