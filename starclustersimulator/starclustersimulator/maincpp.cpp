//Star Life Cycle Cluster Simulator
//Corban Larson

#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <time.h>

const int suggested_starting_cell_mass = 3;
const int cell_ly_size = 25;
const double percent_even_mass = 0.5;

int get_cluster_diameter();
double get_initial_mass(int diameter);
int get_simulation_time();

int main() {

	std::cout << "Star Life Cycle in a Star Cluster Simmulator" << std::endl << std::endl;
	srand(time(0));

	int cluster_diameter = get_cluster_diameter();
	int cluster_diameter_cells = cluster_diameter / cell_ly_size;
	double cluster_mass = get_initial_mass(cluster_diameter_cells);

	double*** interstellar_cloud = new double** [cluster_diameter_cells];
	for (int i = 0; i < cluster_diameter_cells; i++) {
		interstellar_cloud[i] = new double* [cluster_diameter_cells];
		for (int j = 0; j < cluster_diameter_cells; j++) {
			interstellar_cloud[i][j] = new double[cluster_diameter_cells];
			for (int a = 0; a < cluster_diameter_cells; a++) {
				interstellar_cloud[i][j][a] = 0;
			}
		}
	}

	//initial mass
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

	while (cluster_mass > 0) {
		int x = rand() % (cluster_diameter_cells);
		int y = rand() % (cluster_diameter_cells);
		int z = rand() % (cluster_diameter_cells);

		double mass_percent = rand() % (91) + 10;
		mass_percent = mass_percent / 100;
		double mass = mass_percent * cluster_mass;

		interstellar_cloud[x][y][z] += mass;
		cluster_mass -= mass;
		//std::cout << x << "," << y << "," << z << " " << interstellar_cloud[x][y][z] << std::endl;
	}

	//start of simulation
	int simulation_time = get_simulation_time();

	delete[] interstellar_cloud;
	return 0;
}

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