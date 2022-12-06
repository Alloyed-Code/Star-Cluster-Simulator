#pragma once
#include "star.h"
#include "constants.h"
#include <string>

class brown_dwarf : public star {
public:
	brown_dwarf(std::string name, double mass);
};