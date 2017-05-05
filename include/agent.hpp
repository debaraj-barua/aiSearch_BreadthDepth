/*
 * Daniel Vázquez
 * Aritifiacial Intelligence for Robots
 * MAS SS 16
 * Assignment 3
 *
 * agent.hpp
 * */

#ifndef AGENT_HPP
#define AGENT_HPP

#include <vector>
#include <utility>
#include <string>

#define map_rows 25
#define map_cols 141

using namespace std;

class Agent {
public:
	Agent(vector<vector<string> >, const pair<int, int>, int, int);
	~Agent();

	void run();
private:

	vector<vector<string> > map;      //stores the selected map. It can be handled like a
								      //double dimensional array e.g. map[0][0] or
								      //map[initla_position.first][initial_position.second]
	const pair<int, int> initial_pos; //stores the initial position of the robot in the selected map
								      //where initial_pos.first = row
								      //      initial_position.second = col
	int number_of_goals;              //stores the number of dirts in the current map
	int search_option;
	vector<pair<int, int> > goal_positions; //This vector should be used to store the position of
											//the dirts once they are found. It stores each position
											//as a pair. To add new pairs to the vector use the std::make_pair() method:
											//e.g. goal_positions.push(std::make_pair(current_row, current_col))

	int number_of_stored_nodes; //The are some metrics you could used to evaluate the performance of your implementation.
	int number_of_visited_nodes;

	void print_map();
	void bfs();
	void dfs();

	void print_evaluation_metrics(string);
	void print_goal_positions();

};

#endif
