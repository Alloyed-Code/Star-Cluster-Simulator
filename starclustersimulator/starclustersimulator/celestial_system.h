#pragma once
#include <string>
#include "stellar_body.h"

class celestial_system {
	std::string system_name;
	double x;
	double y;
	double z;

public:
	virtual void age_stars(int time) = 0;
	celestial_system(std::string name, double x, double y, double z);
	std::string get_name();
	virtual stellar_body* get_stars() = 0;
};