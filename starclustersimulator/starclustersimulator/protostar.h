#pragma once
#include "stellar_body.h"
#include "constants.h"
#include "star.h"
#include <string>

class protostar : public star {
private:
public:
	protostar(std::string name, double mass);
};