#pragma once


const double suggested_starting_cell_mass = 3;
const int cell_ly_size = 5;
const double percent_even_mass = 0.5;
const double percent_gravity_difference_transfer = 0.25;
const int max_random_percent = 30;
const int star_formation_chance = 5;
const int star_mass_min = 20;

enum class color {
	blue,
	deep_blue_white,
	blue_white,
	white,
	yellow,
	orange,
	red,
	brown,
	black,
};