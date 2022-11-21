#pragma once
#include <string>

class system {
	std::string system_name;
	double x;
	double y;
	double z;

public:
	virtual void age_stars() = 0;
	system(std::string name, double x, double y, double z);
};