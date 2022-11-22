#pragma once
#include <string>

class celestial_system {
	std::string system_name;
	double x;
	double y;
	double z;

public:
	virtual void age_stars(int time) = 0;
	celestial_system(std::string name, double x, double y, double z);
	std::string get_name();
};