//Star Life Cycle Cluster Simulator
//Corban Larson

#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <time.h>
#include "constants.h"

int get_cluster_diameter();
double get_initial_mass(int diameter);
int get_simulation_time();
void add_evem_cell_mass(int cluster_diameter_cells, double& cluster_mass, double*** interstellar_cloud);
void random_mass_distribution(int cluster_diameter_cells, double& cluster_mass, double*** interstellar_cloud);
void gravity(double*** interstellar_cloud, int x, int y, int z, int cluster_diameter_cells);


int main() {

	std::cout << "Star Life Cycle in a Star Cluster Simmulator" << std::endl << std::endl;
	srand(time(0));

	std::cout << "What is this star cluster's name? ";
	std::string cluster_name;
	getline(std::cin, cluster_name);

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
	
	add_evem_cell_mass(cluster_diameter_cells, cluster_mass, interstellar_cloud);

	random_mass_distribution(cluster_diameter_cells, cluster_mass, interstellar_cloud);

	//start of simulation
	bool run_simulation = true;
	while (run_simulation) {
		int simulation_time = get_simulation_time();
		for (int i = 0; i < simulation_time; i++) {
			//move gas
			for (int x = 0; x < cluster_diameter_cells; x++) {
				for (int y = 0; y < cluster_diameter_cells; y++) {
					for (int z = 0; z < cluster_diameter_cells; z++) {
						gravity(interstellar_cloud, x, y, z, cluster_diameter_cells);
					}
				}
			}
			//check for star generation
			for (int x = 0; x < cluster_diameter_cells; x++) {
				for (int y = 0; y < cluster_diameter_cells; y++) {
					for (int z = 0; z < cluster_diameter_cells; z++) {
						int random_percent = rand() % (100) + 1;
						if (random_percent + interstellar_cloud[x][y][z] > (100 - star_formation_chance)) {
							//form star
						}
					}
				}
			}
			//age stars
			//record state to csv

		}

		std::cout << "Continue Simulation? (y/n) ";
		std::string input;
		getline(std::cin, input);
		if (input != "y") {
			run_simulation = false;
		}
	}
	delete[] interstellar_cloud;
	return 0;
}
