#pragma once
#include "system.h"
#include "stellar_body.h"

class unary : public system {
private:
	stellar_body star;

public:
	void age_stars() override;
	unary(double mass, double x, double y, double z, std::string name) :system(name, x, y, z);
};