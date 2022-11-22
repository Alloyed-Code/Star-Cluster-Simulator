#pragma once
#include "celestial_system.h"
#include "stellar_body.h"

class unary : public celestial_system {
private:
	stellar_body star;

public:
	void age_stars(int time) override;
	unary(double mass, double x, double y, double z, std::string name);
};