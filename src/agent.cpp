/*
 * Daniel Vázquez
 * Aritifiacial Intelligence for Robots
 * MAS SS 2016
 * Assignment 3
 *
 * agent.cpp
 * */

#include "agent.hpp"
#include <stdlib.h>
#include <iostream>
#include <stack>
#include <queue>
#include <set>
#include <chrono>
#include <thread>

using namespace std;

Agent::Agent(vector<vector<string> > map, const pair<int, int> initial_pos,
		int number_of_goals, int search_option) :
		map(map), initial_pos(initial_pos), number_of_goals(number_of_goals), search_option(
				search_option), number_of_stored_nodes(0), number_of_visited_nodes(
				0) {

}

Agent::~Agent() {

}

void Agent::run() {

	if (search_option == 1) {
		cout << "Running BFS " << endl;
		cout << "Number of goals " << number_of_goals << endl;
		bfs();
	} else {
		cout << "Running DFS " << endl;
		cout << "Number of goals " << number_of_goals << endl;
		dfs();
	}

}

void Agent::print_map() {
	system("clear");

	for (int row = 0; row < map_rows; row++) {
		for (int col = 0; col < map_cols; col++) {
			cout << map[row][col];
		}
		cout << endl;
	}

	this_thread::sleep_for(chrono::milliseconds(10));

}

void Agent::bfs() {
	//queue stores a pair in the form (row, col)
	queue<pair<int, int> > nodes_queue;
	pair<int, int> current_node;

	//Note: Elements stored in a pair can be accessed by calling the .first and .second attributes. E.g:
	//int row = current_node.first
	//int col = current_node.second

	//Add the initial node to the queue
	//Note: To add a new pair to the queue you can use the std::make_pair method e.g:

	nodes_queue.push(make_pair(initial_pos.first, initial_pos.second));
	number_of_stored_nodes++;
    int max_rows = map.size();
    int max_cols = map[0].size();

	while (nodes_queue.size() > 0) {
			current_node = nodes_queue.front();

			nodes_queue.pop();
			number_of_stored_nodes--;
			int row = current_node.first;
			int col = current_node.second;
			number_of_visited_nodes++;

			if ((map[row][col]=="=") or (map[row][col]=="|") or (map[row][col]=="-"))
			{
				continue;
			}
			else
			{
				if  (map[row][col]=="*")
				{
					goal_positions.push_back(std::make_pair(row, col));

					if (goal_positions.size()>=number_of_goals)
					{
						map[row][col]="-";
						print_evaluation_metrics("queue");
						return ;
					}

				}
				map[row][col]="-";

				if (((row+1)<max_rows and (row+1)>0) and ((map[row+1][col]!="=") and (map[row+1][col]!="|") and (map[row+1][col]!="-")))
				{

					nodes_queue.push(make_pair(row+1, col));
					number_of_stored_nodes++;
				}
				if (((row-1)<max_rows and (row-1)>0)and ((map[row-1][col]!="=") and (map[row-1][col]!="|") and (map[row-1][col]!="-")))
				{
					nodes_queue.push(make_pair(row-1, col));
					number_of_stored_nodes++;
				}

				if (((col+1)<max_cols and (col+1)>0)and ((map[row][col+1]!="=") and (map[row][col+1]!="|") and (map[row][col+1]!="-")))
				{
					nodes_queue.push(make_pair(row, col+1));
					number_of_stored_nodes++;
				}
				if (((col-1)<max_cols and (col-1)>0)and ((map[row][col-1]!="=") and (map[row][col-1]!="|") and (map[row][col-1]!="-")))
				{
					nodes_queue.push(make_pair(row, col-1));
					number_of_stored_nodes++;
				}
			}
			print_map();
		}
		//TO DO
		/*Note: If the current node contains a dirt you can
		 * store the position in the goal_positions vector 
		 * by calling the push method e.g goal_positions.push(current_node)
		 */





	print_evaluation_metrics("queue");
}

void Agent::dfs() {
	//the stack stores a pair in the form (row, col)
	stack<pair<int, int> > nodes_stack;
	pair<int, int> current_node;

	//Note: Elements stored in a pair can be accessed by calling the .first and .second attributes. E.g:
	//int row = current_node.first
	//int col = current_node.second

	//Add the initial node to the stack
	//Note: To add a new pair to the stack you can use the std::make_pair method e.g:

	nodes_stack.push(make_pair(initial_pos.first, initial_pos.second));
	number_of_stored_nodes++;
    int max_rows = map.size();
    int max_cols = map[0].size();

	while (nodes_stack.size() > 0) {

		current_node = nodes_stack.top();
		nodes_stack.pop();
		number_of_stored_nodes--;
		int row = current_node.first;
		int col = current_node.second;
		number_of_visited_nodes++;

		if ((map[row][col]=="=") or (map[row][col]=="|") or (map[row][col]=="-"))
		{
			continue;
		}
		else
		{
			if  (map[row][col]=="*")
			{
				goal_positions.push_back(std::make_pair(row, col));

				if (goal_positions.size()>=number_of_goals)
				{
					map[row][col]="-";
					print_evaluation_metrics("stack");
					return ;
				}

			}
			map[row][col]="-";

			if (((row+1)<max_rows and (row+1)>0) and ((map[row+1][col]!="=") and (map[row+1][col]!="|") and (map[row+1][col]!="-")))
			{

				nodes_stack.push(make_pair(row+1, col));
				number_of_stored_nodes++;
			}

			if (((row-1)<max_rows and (row-1)>0)and ((map[row-1][col]!="=") and (map[row-1][col]!="|") and (map[row-1][col]!="-")))
			{
				nodes_stack.push(make_pair(row-1, col));
				number_of_stored_nodes++;
			}

			if (((col+1)<max_cols and (col+1)>0)and ((map[row][col+1]!="=") and (map[row][col+1]!="|") and (map[row][col+1]!="-")))
			{
				nodes_stack.push(make_pair(row, col+1));
				number_of_stored_nodes++;
			}

			if (((col-1)<max_cols and (col-1)>0)and ((map[row][col-1]!="=") and (map[row][col-1]!="|") and (map[row][col-1]!="-")))
			{
				nodes_stack.push(make_pair(row, col-1));
				number_of_stored_nodes++;
			}




		}

			//TO DO
			/*Note: If the current node contains a dirt you can
			 * store the position in the goal_positions vector
			 * by calling the push method e.g goal_positions.push(current_node)
			 */

		print_map();

		}

	print_evaluation_metrics("stack");

}

void Agent::print_evaluation_metrics(string data_structure_name) {
	print_map();
	cout << "All the possible nodes have been explored " << endl;
	cout << "Found " << goal_positions.size() << " of " << number_of_goals
			<< endl;
	cout << "Maximum size of the " << data_structure_name << " : "
			<< number_of_stored_nodes << endl;
	cout << "Number of stored nodes: " << number_of_stored_nodes << endl;
	cout << "Total of visited nodes: " << number_of_visited_nodes << endl;
	print_goal_positions();
}

void Agent::print_goal_positions() {
	cout << "Goals: " << endl;
	for (int i = 0; i < goal_positions.size(); i++) {
		cout << i + 1 << ": (" << goal_positions[i].first << ", "
				<< goal_positions[i].second << ")" << endl;
	}
}

