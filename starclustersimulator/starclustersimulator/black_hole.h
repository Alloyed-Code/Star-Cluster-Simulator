#pragma once
#include "stellar_body.h"
#include <string>
#include "constants.h"

class black_hole : public stellar_body {
private:
	double s_radius;
	color black_hole_color;
public:
	black_hole(std::string name, double mass);
	double get_radius() override;
	color get_color() override;
};