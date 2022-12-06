#pragma once
#include "star.h"
#include <string>

class white_dwarf : public star {
public:
	white_dwarf(std::string name, double masss);
};