#pragma once
#include <string>
#include "constants.h"

class stellar_body {
protected:
	std::string name;
	double mass;
	
	long long int lifespan;
	long long int current_age;
public:
	stellar_body(std::string name);
	stellar_body();
	virtual void age_body(int time);
	long long int get_lifespan();
	long long int get_age();
	std::string get_name();
	double get_mass();
	virtual double get_radius();
	virtual color get_color();
};