//Star Life Cycle Cluster Simulator
//Corban Larson

#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <time.h>
#include "constants.h"
#include "celestial_system.h"
#include "unary.h"
#include "stellar_body.h"
#include "protostar.h"
#include "main_sequence.h"

int get_cluster_diameter();
double get_initial_mass(int diameter);
int get_simulation_time();
void add_evem_cell_mass(int cluster_diameter_cells, double& cluster_mass, double*** interstellar_cloud);
void random_mass_distribution(int cluster_diameter_cells, double& cluster_mass, double*** interstellar_cloud);
void gravity(double*** interstellar_cloud, int x, int y, int z, int cluster_diameter_cells);
void generate_protostars(double*** interstellar_cloud, int x, int y, int z, std::vector<celestial_system*>& systems, std::string cluster_name, bool verbose = true);


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
	for (int x = 0; x < cluster_diameter_cells; x++) {
		interstellar_cloud[x] = new double* [cluster_diameter_cells];
		for (int y = 0; y < cluster_diameter_cells; y++) {
			interstellar_cloud[x][y] = new double[cluster_diameter_cells];
			for (int z = 0; z < cluster_diameter_cells; z++) {
				interstellar_cloud[x][y][z] = 0;
			}
		}
	}

	//initial mass
	
	add_evem_cell_mass(cluster_diameter_cells, cluster_mass, interstellar_cloud);

	random_mass_distribution(cluster_diameter_cells, cluster_mass, interstellar_cloud);
	
	std::vector<celestial_system*> systems;

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
						generate_protostars(interstellar_cloud, x, y, z, systems, cluster_name);
					}
				}
			}
			//age stars
			for (int i = 0; i < systems.size(); i++) {
				if (unary* un = dynamic_cast<unary*>(systems[i])) {
					systems[i]->age_stars(1000000);
					std::cout << systems[i]->get_stars()->get_age() << std::endl;
					if (systems[i]->get_stars()->get_age() >= systems[i]->get_stars()->get_lifespan()) {
						if (protostar* proto = dynamic_cast<protostar*>(systems[i]->get_stars())) {
							std::cout << "protostar " << systems[i]->get_stars()->get_mass() << std::endl;
							if (systems[i]->get_stars()->get_mass() > 0.08) {
								stellar_body* star = new main_sequence(systems[i]->get_stars()->get_name(), systems[i]->get_stars()->get_mass());
								systems[i]->set_stars(star);
								std::cout << "Main sequence" << std::endl;
							}
							else {
								//brown dwarf
								std::cout << "Brown Dwarf" << std::endl;
							}
						}
						else {
							std::cout << "not a proto" << std::endl;
						}
					}
					else {
						std::cout << "star still too young" << std::endl;
					}
				}
				else {
					std::cout << "not a unary system" << std::endl;
				}
				
			}
			//record state to csv

		}

		std::cout << "Continue Simulation? (y/n) ";
		std::string input;
		getline(std::cin, input);
		if (input != "y") {
			run_simulation = false;
		}
	}
	int size = systems.size();
	for (int i = 0; i < size; i++) {
		delete systems[i];
	}
	delete[] interstellar_cloud;
	return 0;
}
