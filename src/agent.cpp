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

	//this_thread::sleep_for(chrono::milliseconds(10));

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

	std::set<pair<int, int>> explored;

	if(explored.insert(make_pair(initial_pos.first, initial_pos.second)).second)
	{
		cout<<"Updated explored\n";
		while (nodes_queue.size() > 0) {

				current_node = nodes_queue.front();

				nodes_queue.pop();
				number_of_stored_nodes--;
				int row = current_node.first;
				int col = current_node.second;
				cout<<"`````````````````````````````````````````````````````````````\n";
				cout <<"\n Current Position::("<<row<<";"<<col<<")\n";
				cout <<"\n Status in Current Position::"<< map[row][col]<<"\n";
				number_of_visited_nodes++;
				cout<<"`````````````````````````````````````````````````````````````\n";
				if  (map[row][col]=="*")
				{
					//goal_positions.push(current_node);
					cout<<"=============================================================\n";
					cout<<"found one~\n";
					goal_positions.push_back(std::make_pair(row, col));
					cout<<"=============================================================\n";
					if (goal_positions.size()>=number_of_goals)
						return ;

				}
				else if (map[row][col]=="=" or map[row][col]=="|")
				{
					cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
					cout<<"Obstacle\n";
					cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
				}
				else
				{

				}

				nodes_queue.push(make_pair(row+1, col));
				number_of_stored_nodes++;
				nodes_queue.push(make_pair(row-1, col));
				number_of_stored_nodes++;
				nodes_queue.push(make_pair(row, col+1));
				number_of_stored_nodes++;
				nodes_queue.push(make_pair(row, col-1));
				number_of_stored_nodes++;
	}
	}
	else
	{
		cout<<"Already explored";
	}
	//explored.push(make_pair(initial_pos.first, initial_pos.second));



		//TODO
		/*Note: If the current node contains a dirt you can
		 * store the position in the goal_positions vector 
		 * by calling the push method e.g goal_positions.push(current_node)
		 */

		//print_map();



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

	while (nodes_stack.size() > 0) {

		current_node = nodes_stack.top();
		nodes_stack.pop();

		//TODO
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

