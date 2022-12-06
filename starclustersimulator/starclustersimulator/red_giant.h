#pragma once
#include "star.h"
#include <string>

class red_giant : public star {
public:
	red_giant(std::string name, double mass);
};