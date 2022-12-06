#pragma once
#include "stellar_body.h"
#include <string>

class black_hole : public stellar_body {
private:
	double s_radius;
public:
	black_hole(std::string name, double mass);
	double get_radius();
};