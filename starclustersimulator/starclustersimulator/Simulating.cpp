#include <iostream>
#include <string>
#include "constants.h"
#include "celestial_system.h"
#include <vector>
#include "celestial_system.h"
#include "unary.h"

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

void gravity(double*** interstellar_cloud, int x, int y, int z, int cluster_diameter_cells) {
	if (interstellar_cloud[x][y][z] > 0) {
		int heaviest_mass_index_x = -1;
		int heaviest_mass_index_y = -1;
		int heaviest_mass_index_z = -1;
		for (int x_rel = -1; x_rel < 2; x_rel++) {
			if ((x_rel + x) >= 0 && (x_rel + x) < cluster_diameter_cells) { //check if inside array
				for (int y_rel = -1; y_rel < 2; y_rel++) {
					if ((y_rel + y) >= 0 && (y_rel + y) < cluster_diameter_cells) {
						for (int z_rel = -1; z_rel < 2; z_rel++) {
							if ((z_rel + z) >= 0 && (z_rel + z) < cluster_diameter_cells) {
								if (x_rel != 0 || y_rel != 0 || z_rel != 0) {
									if (heaviest_mass_index_x < 0 || heaviest_mass_index_y < 0 || heaviest_mass_index_z < 0) { //if there is no heavier yet
										if (interstellar_cloud[x][y][z] < interstellar_cloud[x + x_rel][y + y_rel][z + z_rel]) {
											heaviest_mass_index_x = x + x_rel;
											heaviest_mass_index_y = y + y_rel;
											heaviest_mass_index_z = z + z_rel;
										}
									}
									else {
										if (interstellar_cloud[heaviest_mass_index_x][heaviest_mass_index_y][heaviest_mass_index_z] < interstellar_cloud[x + x_rel][y + y_rel][z + z_rel]) { //if new is heavier than current heaviest
											heaviest_mass_index_x = x + x_rel;
											heaviest_mass_index_y = y + y_rel;
											heaviest_mass_index_z = z + z_rel;
										}
									}
								}
							}
						}
					}
				}
			}
		}

		if (heaviest_mass_index_x > -1 && heaviest_mass_index_y > -1 && heaviest_mass_index_z > -1) {
			//std::cout << heaviest_mass_index_x << "," << heaviest_mass_index_y << "," << heaviest_mass_index_z << " " << interstellar_cloud[heaviest_mass_index_x][heaviest_mass_index_y][heaviest_mass_index_z] << " Compared to " << interstellar_cloud[x][y][z] << std::endl;
			double mass_dif = interstellar_cloud[heaviest_mass_index_x][heaviest_mass_index_y][heaviest_mass_index_z] - interstellar_cloud[x][y][z];
			//std::cout << mass_dif << std::endl;
			if (mass_dif * percent_gravity_difference_transfer > interstellar_cloud[x][y][z]) {
				interstellar_cloud[heaviest_mass_index_x][heaviest_mass_index_y][heaviest_mass_index_z] += interstellar_cloud[x][y][z];
				interstellar_cloud[x][y][z] = 0;
			}
			else {
				interstellar_cloud[heaviest_mass_index_x][heaviest_mass_index_y][heaviest_mass_index_z] += mass_dif * percent_gravity_difference_transfer;
				interstellar_cloud[x][y][z] -= mass_dif * percent_gravity_difference_transfer;
			}
			//std::cout << interstellar_cloud[x][y][z] << " and " << interstellar_cloud[heaviest_mass_index_x][heaviest_mass_index_y][heaviest_mass_index_z] << std::endl;
		}
		else {
			//std::cout << "Current is heaviest " << interstellar_cloud[x][y][z] << std::endl;
		}
	}
}

void generate_protostars(double*** interstellar_cloud, int x, int y, int z, std::vector<celestial_system*>& systems, std::string cluster_name, bool verbose = true) {
	if (interstellar_cloud[x][y][z] > 0) {
		int random_percent = rand() % (100) + 1;
		if (random_percent + interstellar_cloud[x][y][z] > (100 - star_formation_chance)) {
			double mass_used = interstellar_cloud[x][y][z] * ((rand() % (100 - star_mass_min + 1) + star_mass_min) / 100.0);
			double system_x = x * cell_ly_size + cell_ly_size * (double(rand() % (100) + 1) / 100);
			double system_y = y * cell_ly_size + cell_ly_size * (double(rand() % (100) + 1) / 100);
			double system_z = z * cell_ly_size + cell_ly_size * (double(rand() % (100) + 1) / 100);
			//form star
			systems.push_back(new unary(mass_used, system_x, system_y, system_z, cluster_name + "-" + std::to_string(systems.size() + 1)));
			interstellar_cloud[x][y][z] -= mass_used;
			if (verbose) {
				std::cout << "A protostar named " << systems[systems.size() - 1]->get_name() << " has formed at " << system_x << "," << system_y << "," << system_z << std::endl;
			}
		}
	}
}