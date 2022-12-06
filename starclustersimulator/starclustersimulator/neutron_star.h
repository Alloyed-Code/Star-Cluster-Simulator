#pragma once
#include "star.h"
#include <string>

class neutron_star : public star {
public:
	neutron_star(std::string name, double mass);
};