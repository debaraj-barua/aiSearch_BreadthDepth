/*
 * Daniel Vázquez
 * Aritifiacial Intelligence for Robots
 * MAS SS 2016
 * Assignment 3
 *
 * environment.hpp
 * */

#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Environment {
public:

	Environment();
	void run();
	bool load_map(int map_index);
	void initialize_map();
	void print_map();

private:
	string map_names[3];
	string map_dir;
	string start_sym;
	int map_number_of_goals;      //stores the number of dirts in the current map
	pair<int, int> initial_position; //stores the initial position of the robot in the selected map
								  //where initial_position.first = row
								  //      initial_position.second = col
	vector<vector<string> > map;  //stores the selected map. It can be handled like a
								  //double dimensional array e.g. map[0][0] or
								  //map[initla_position.first][initial_position.second]
};

#endif
