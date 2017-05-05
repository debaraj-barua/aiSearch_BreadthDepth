/*
 * Daniel Vázquez
 * Aritifiacial Intelligence for Robots
 * MAS SS 2016
 * Assignment 3
 *
 * environment.cpp
 * */

#include "environment.hpp"
#include "agent.hpp"

Environment::Environment() :
		map_dir("./maps/"), map(map_rows, vector < string > (map_cols, "")), start_sym(
				"s"), map_number_of_goals(0), initial_position(2, 0) {
	map_names[0] = "map1.txt";
	map_names[1] = "map2.txt";
	map_names[2] = "map3.txt";
}

void Environment::run() {
	int map_number = 0;
	int op = 0;

	do {
		do {
			cout << "Select a map :" << endl;
			cout << "(1) Map1 (2) Map2 (3) Map3" << endl;
			cin >> map_number;
			if (map_number < 1 || map_number > 3)
				cout << "Wrong option, please select again" << endl;
		} while (map_number < 1 || map_number > 3);

		if (load_map(map_number - 1)) {
			int search_option;

			do {
				cout << "Please select : " << endl;
				cout << "(1) Breadth-first  (2)Depth-fisrt " << endl;
				cin >> search_option;
				if (search_option < 1 || search_option > 2)
					cout << "Wrong option, please select again" << endl;
			} while (search_option < 1 || search_option > 2);

			//create and run agent
			Agent anAgent(map, initial_position, map_number_of_goals,
					search_option);
			anAgent.run();

			do {
				cout << "Search again ?: " << endl;
				cout << "(1) Yes  (2) No " << endl;
				cin >> op;
				if (op < 1 || op > 2)
					cout << "Wrong option, please select again" << endl;
			} while (op < 1 || op > 2);
		} else {
			cout << "The selected map could not be loaded." << endl;
		}
	} while (op == 1);

}

//loads the selected map
bool Environment::load_map(int map_index) {

	initialize_map();

	string line;
	ifstream aMap((map_dir + map_names[map_index]).c_str());

	int row = 0;

	if (aMap.is_open()) {
		while (getline(aMap, line)) {
			for (int col = 0; col < line.length(); col++) {
				map[row][col] = line[col];

				//Store the initial possition of the robot
				if (line[col] == 's') {
					initial_position.first = row;
					initial_position.second = col;
					cout << "Initial position of the robot: "
							<< initial_position.first << ", "
							<< initial_position.second << endl;
				} else if (line[col] == '*') { //count the number of dirts in the given map
					map_number_of_goals++;
				}
			}
			row++;
		}

		cout << "The selected map has been loaded" << endl;
		cout << "Number of dirts in the map: " << map_number_of_goals << endl;
		aMap.close();
		print_map();

		return true;
	}

	return false;
}

//Initializes the array to ""
void Environment::initialize_map() {
	map_number_of_goals = 0;

	for (int row = 0; row < map_rows; row++) {
		for (int col = 0; col < map_cols; col++) {
			map[row][col] = "";
		}
	}
}

//print map
void Environment::print_map() {
	for (int row = 0; row < map_rows; row++) {
		for (int col = 0; col < map_cols; col++) {
			cout << map[row][col];
		}

		cout << endl;
	}
}
