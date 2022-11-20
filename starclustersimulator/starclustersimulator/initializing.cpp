#include <iostream>
#include <string>
#include "constants.h"


int get_cluster_diameter() {
	std::cout << "How big is the star cluster? (in light years, divisible by " << cell_ly_size << ") ";
	std::string diameter;
	std::getline(std::cin, diameter);

	for (char i : diameter) {
		if (i > '9' || i < '0') {
			std::cout << "Invalid integer!" << std::endl;
			return get_cluster_diameter();
		}
	}
	int number = stoi(diameter);
	if (number % cell_ly_size > 0) {
		std::cout << "Number must be divisible by " << cell_ly_size << "!" << std::endl;
		return get_cluster_diameter();
	}
	return number;
}

double get_initial_mass(int diameter) {
	int cell_count = diameter * diameter * diameter;
	std::cout << "How many solar masses are there in this star cluster? (suggested amount is " << cell_count * suggested_starting_cell_mass << ") ";
	std::string mass;
	std::getline(std::cin, mass);

	for (char i : mass) {
		if ((i > '9' || i < '0') && i != '.') {
			std::cout << "Invalid float!" << std::endl;
			return get_initial_mass(diameter);
		}
	}

	double number = stod(mass);
	return number;
}

void add_evem_cell_mass(int cluster_diameter_cells, double& cluster_mass, double*** interstellar_cloud) {
	int num_cells = cluster_diameter_cells * cluster_diameter_cells * cluster_diameter_cells;
	double initial_mass_per_cell = (cluster_mass * percent_even_mass) / num_cells;

	for (int x = 0; x < cluster_diameter_cells; x++) {
		for (int y = 0; y < cluster_diameter_cells; y++) {
			for (int z = 0; z < cluster_diameter_cells; z++) {
				interstellar_cloud[x][y][z] += initial_mass_per_cell;
				cluster_mass -= initial_mass_per_cell;
			}
		}
	}
}

void random_mass_distribution(int cluster_diameter_cells, double& cluster_mass, double*** interstellar_cloud) {
	while (cluster_mass > 0) {
		int x = rand() % (cluster_diameter_cells);
		int y = rand() % (cluster_diameter_cells);
		int z = rand() % (cluster_diameter_cells);

		double mass;
		if (cluster_mass > 1) {
			double mass_percent = double(rand() % (max_random_percent + 1)) + 10;
			mass_percent = mass_percent / 100;
			mass = mass_percent * cluster_mass;
			
		}
		else {
			mass = 1;
		}
		interstellar_cloud[x][y][z] += mass;
		cluster_mass -= mass;
		//std::cout << x << "," << y << "," << z << " " << interstellar_cloud[x][y][z] << std::endl;
	}
}