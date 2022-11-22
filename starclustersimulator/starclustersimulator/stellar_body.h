#pragma once
#include <string>

class stellar_body {
protected:
	std::string name;
	double mass;
	
	long int lifespan;
	long int current_age;
public:
	stellar_body(std::string name);
	stellar_body();
	virtual void age_body(int time);
};