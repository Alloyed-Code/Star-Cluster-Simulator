#include <iostream>
#include <string>
#include "constants.h"
#include "celestial_system.h"
#include <vector>
#include "celestial_system.h"
#include "unary.h"
#include "protostar.h"
#include "main_sequence.h"
#include "brown_dwarf.h"
#include "supergiant.h"
#include "red_giant.h"
#include "white_dwarf.h"
#include "black_hole.h"
#include "neutron_star.h"

void explosion(double*** interstellar_cloud, double sys_x, double sys_y, double sys_z, double mass, int cluster_diameter_cells);

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
	if (interstellar_cloud[x][y][z] > cloud_mass_min) {
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

void evolve_stars(double*** interstellar_cloud, std::vector<celestial_system*>& systems, int cluster_diameter_cells, bool verbose = true) {
	for (int i = 0; i < systems.size(); i++) {
		if (unary* un = dynamic_cast<unary*>(systems[i])) {
			systems[i]->age_stars(1000000);
			//std::cout << systems[i]->get_stars()->get_age() << std::endl;
			if (systems[i]->get_stars()->get_age() >= systems[i]->get_stars()->get_lifespan()) {
				if (protostar* proto = dynamic_cast<protostar*>(systems[i]->get_stars())) {
					//protostar
					if (systems[i]->get_stars()->get_mass() > 0.08) {
						//to main sequence
						stellar_body* star = new main_sequence(systems[i]->get_stars()->get_name(), systems[i]->get_stars()->get_mass());
						systems[i]->set_stars(star);
						if (verbose) {
							std::cout << "The protostar " << systems[i]->get_stars()->get_name() << " has evolved into a main sequence star!" << std::endl;
						}
					}
					else {
						//to brown dwarf
						stellar_body* star = new brown_dwarf(systems[i]->get_stars()->get_name(), systems[i]->get_stars()->get_mass());
						systems[i]->set_stars(star);
						if (verbose) {
							std::cout << "The protostar " << systems[i]->get_stars()->get_name() << " has evolved into a brown dwarf!" << std::endl;
						}
					}
				}
				else if (main_sequence* main_star = dynamic_cast<main_sequence*>(systems[i]->get_stars())) {
					//main sequence
					if (systems[i]->get_stars()->get_mass() > 8) {
						//to supergiant
						stellar_body* star = new supergiant(systems[i]->get_stars()->get_name(), systems[i]->get_stars()->get_mass());
						systems[i]->set_stars(star);
						if (verbose) {
							std::cout << "The main sequence star " << systems[i]->get_stars()->get_name() << " has evolved into a supergiant!" << std::endl;
						}
					}
					else {
						//to red giant
						stellar_body* star = new red_giant(systems[i]->get_stars()->get_name(), systems[i]->get_stars()->get_mass());
						systems[i]->set_stars(star);
						if (verbose) {
							std::cout << "The main sequence star " << systems[i]->get_stars()->get_name() << " has evolved into a red giant!" << std::endl;
						}
					}
				}
				else if (red_giant* giant = dynamic_cast<red_giant*>(systems[i]->get_stars())) {
					//red giant
					//to white dwarf
					//planetary nebula
					explosion(interstellar_cloud, systems[i]->get_x(), systems[i]->get_y(), systems[i]->get_z(), systems[i]->get_stars()->get_mass() / 2, cluster_diameter_cells);
					stellar_body* star = new white_dwarf(systems[i]->get_stars()->get_name(), systems[i]->get_stars()->get_mass() / 2);
					systems[i]->set_stars(star);
					if (verbose) {
						std::cout << "The red giant " << systems[i]->get_stars()->get_name() << " has evolved into a planetary nebula and white dwarf!" << std::endl;
					}

				}
				else if (supergiant* giant = dynamic_cast<supergiant*>(systems[i]->get_stars())) {
					//supergiant
					if (systems[i]->get_stars()->get_mass() > 25) {
						//to black hole
						//supernova
						explosion(interstellar_cloud, systems[i]->get_x(), systems[i]->get_y(), systems[i]->get_z(), systems[i]->get_stars()->get_mass() * (4.0/5), cluster_diameter_cells);
						stellar_body* body = new black_hole(systems[i]->get_stars()->get_name(), systems[i]->get_stars()->get_mass() / 5);
						systems[i]->set_stars(body);
						if (verbose) {
							std::cout << "The supergiant " << systems[i]->get_stars()->get_name() << " has exploded in a supernova and left a black hole!" << std::endl;
						}
					}
					else {
						//to neutron star
						//supernova
						explosion(interstellar_cloud, systems[i]->get_x(), systems[i]->get_y(), systems[i]->get_z(), systems[i]->get_stars()->get_mass() * (4.0/5), cluster_diameter_cells);
						stellar_body* star = new neutron_star(systems[i]->get_stars()->get_name(), systems[i]->get_stars()->get_mass() / 5);
						systems[i]->set_stars(star);
						if (verbose) {
							std::cout << "The supergiant " << systems[i]->get_stars()->get_name() << " has exploded in a supernova and left a neutron star!" << std::endl;
						}
					}
				}
			}
			else {
				//std::cout << "star still too young" << std::endl;
			}
		}
		else {
			std::cout << "not a unary system" << std::endl;
		}

	}
}

void explosion(double*** interstellar_cloud, double sys_x, double sys_y, double sys_z, double mass, int cluster_diameter_cells) {
	int cell_x = int(sys_x) / cell_ly_size;
	int cell_y = int(sys_y) / cell_ly_size;
	int cell_z = int(sys_z) / cell_ly_size;
	double per_mass = mass / 27;
	for (int x_rel = -1; x_rel < 2; x_rel++) {
		if ((x_rel + cell_x) >= 0 && (x_rel + cell_x) < cluster_diameter_cells) { //check if inside array
			for (int y_rel = -1; y_rel < 2; y_rel++) {
				if ((y_rel + cell_y) >= 0 && (y_rel + cell_y) < cluster_diameter_cells) {
					for (int z_rel = -1; z_rel < 2; z_rel++) {
						if ((z_rel + cell_z) >= 0 && (z_rel + cell_z) < cluster_diameter_cells) {
							if (x_rel != 0 || y_rel != 0 || z_rel != 0) {
								interstellar_cloud[cell_x + x_rel][cell_y + y_rel][cell_z + z_rel] += per_mass;
							}
						}
						else { //outside array
							interstellar_cloud[cell_x][cell_y][cell_z] += per_mass;
						}
					}
				}
				else { //outside array
					interstellar_cloud[cell_x][cell_y][cell_z] += per_mass;
				}
			}
		}
		else { //outside array
			interstellar_cloud[cell_x][cell_y][cell_z] += per_mass;
		}
	}
}

std::string color_string(color color) {
	switch (color) {
	case color::blue:
		return "blue";
	case color::deep_blue_white:
		return "deep blue white";
	case color::blue_white:
		return "blue white";
	case color::white:
		return "white";
	case color::yellow:
		return "yellow";
	case color::orange:
		return "orange";
	case color::red:
		return "red";
	case color::brown:
		return "brown";
	case color::black:
		return "black";
	default:
		return "invisible";
	}
}