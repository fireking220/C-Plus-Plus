//Scott Patterson
//12/2/2016
//CS163
//Karla Fant
//This program will construct a graph data type that will link to other vertexes through
//it's own linear linked list, we will have the option to add a vertex, add a link to a vertex,
//find all the tasks needed to complete a specific goal, display all connected verticies for a specific
//goal

#include "graph.h"
#include <iostream>
#include <cstring>

using namespace std;

const int SZ = 1000;

void planner_menu();

int main()
{	
	cout << "Welcome to the planner!\n\n";
	planner_menu();
	return 1;
}

void planner_menu()
{
	char choice = ' ';
	char goal[SZ] = "";
	char sub_goal[SZ] = "";
	graph goals;

	do{
		cout << "A) Insert new goal\n"
		     << "B) Connect goal to sub goals\n"
		     << "C) Display goal and sub goals\n"
		     << "D) Display all main goals\n"
		     << "E) Display all goals (depth first)\n"
		     << "Q) Quit\n\n"
		     << "Choice: ";
		cin >> choice;
		choice = toupper(choice);
		cin.ignore(SZ, '\n');
		
		switch(choice)
		{
			case 'A': cout << "Enter a new goal!\n";
				cin.get(goal, SZ, '\n');
				cin.ignore(SZ, '\n');
				if(goals.insert_vertex(goal))
				{
					cout << "GOAL ADDED!\n\n";
				}
				else
				{
					cout << "TOO MANY GOALS!\n\n";
				}
				break;
			
			case 'B': cout << "Enter goal!\n";
				cin.get(goal, SZ, '\n');
				cin.ignore(SZ, '\n');
				cout << "Enter sub goal!\n";
				cin.get(sub_goal, SZ, '\n');
				cin.ignore(SZ, '\n');
				if(goals.insert_edge(goal, sub_goal))
				{
					cout << "SUB GOAL ADDED!\n\n";
				}
				else
				{
					cout << "GOAL OR SUB GOAL NOT FOUND!\n\n";
				}
				break;
			
			case 'C': cout << "Enter goal to display everything we need to do!\n";
				cin.get(goal, SZ, '\n');
				cin.ignore(SZ, '\n');
				if(goals.display_all_goal(goal))
				{
					cout << "DISPLAYED ALL SUB GOALS OF GOAL!\n\n";
				}
				else
				{
					cout << "NO SUB GOALS OR GOAL NOT FOUND!\n\n";
				}
				break;

			case 'D': cout << "Displaying all goals...\n\n";
				if(goals.display_all())
				{
					cout << "GOALS DISPLAYED!\n\n";
				}
				else
				{
					cout << "NO GOALS TO DISPLAY!\n\n";
				}
				break;
			
			case 'E': cout << "Displaying depth first...\n\n";
				cin.get(goal, SZ, '\n');
				cin.ignore(SZ, '\n');
				if(goals.depth_first(goal))
				{
					cout << "DISPLAYED DEPTH FIRST!\n\n";
				}
				else
				{
					cout << "NO GOALS!\n\n";
				}
				break;

			case 'Q': cout << "Quitting...\n";
				break;
			
			default: cout << "Enter valid option\n\n";
				break;
		}
	}while(choice != 'Q');
}
