#include <iostream>
#include <string>

int get_simulation_time() {
	std::cout << "How many millions of years should the simulation run for? ";
	std::string years;
	std::getline(std::cin, years);

	for (char i : years) {
		if (i > '9' || i < '0') {
			std::cout << "Invalid integer!" << std::endl;
			return get_simulation_time();
		}
	}
	int number = stoi(years);

	return number;

}