#pragma once
#include "star.h"
#include <string>
#include "constants.h"

class main_sequence :public star {
public:
	main_sequence(std::string name, double mass);
};