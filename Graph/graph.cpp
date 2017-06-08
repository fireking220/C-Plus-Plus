//Scott Patterson
//12/2/2016
//CS163
//Karla Fant
//.cpp file for definining what our graph can do.

#include "graph.h"
#include <iostream>
#include <cstring>

using namespace std;

//graph constructor
graph::graph(int size)
{
	graph_size = size;
	num_vertex = 0;
	adjacency_list = new vertex[size];
}

//graph destructor
graph::~graph()
{
	delete[] adjacency_list;
}

//vertex constructor
vertex::vertex()
{
	visit = false;
	num_edges = 0;
	m_goal = NULL;
	head = NULL;
}

//vertex destructor
vertex::~vertex()
{
	if(m_goal)
	{
		delete[] m_goal;
	}
	if(head)
	{
		delete head;
	}
}

//edge constructor
edge::edge()
{
	adjacent = NULL;
	next = NULL;
}

//edge destructor
edge::~edge()
{
	adjacent = NULL;
	if(next)
	{
		delete next;
	}
}

//inserts a vertex containing our goal into our adjacency list
int graph::insert_vertex(char * goal)
{
	vertex * cur;
	bool done = false;
	int i = 0;

	cur = adjacency_list;

	while(i < graph_size && !done)
	{
		if(!(*cur).m_goal)
		{
			(*cur).m_goal = new char[strlen(goal) + 1];
			strcpy((*cur).m_goal, goal);
			++num_vertex;
			done = true;
		}
		++cur;
		++i;
	}

	if(done)
	{
		return 1;
	}
	return 0;
}

//inserts an edge to a vertex
int graph::insert_edge(char * cur_vertex, char * to_attach)
{
	//finds the array location of our goal and sub goal
	int connect1 = find_location(cur_vertex);
	int connect2 = find_location(to_attach);
	edge * temp;

	if(connect1 < 0 || connect2 < 0)
	{
		return 0;
	}

	//add to our edge list
	temp = (*(adjacency_list + connect1)).head;
	(*(adjacency_list + connect1)).head = new edge();
	(*(adjacency_list + connect1)).head->next = temp;
	(*(adjacency_list + connect1)).head->adjacent = adjacency_list + connect2;
	++(*(adjacency_list + connect1)).num_edges;

	return 1;
}

//finds the location of the specified key
int graph::find_location(char * key)
{
	vertex * cur;
	cur = adjacency_list;

	for(int i = 0; i < graph_size; ++i)
	{
		if((*(cur + i)).m_goal)
		{
			if(strcmp(key, (*(cur + i)).m_goal) == 0)
			{
				return i;
			}
		}
	}

	return -1;
}

//displays all the goals
int graph::display_all()
{
	vertex * cur;
	bool done = false;
	int i = 0;

	cur = adjacency_list;

	while(i < graph_size && !done)
	{
		if(!(*cur).m_goal)
		{
			done = true;
		}
		else
		{
			(*cur).display();
			++cur;
			++i;
		}
	}
	
	if(done && i == 0)
	{
		return 0;
	}
	return 1;
}

//wrapper to display all the sub goals attached to a goal
int graph::display_all_goal(char * key)
{
	int cur_goal = find_location(key);

	if(cur_goal < 0)
	{
		return 0;
	}

	display_all_goal_rec((*(adjacency_list + cur_goal)).head);
	return 1;
}

//recursive function to display all subgoals attached to a specific goal
void graph::display_all_goal_rec(edge * &head)
{
	if(!head)
	{
		return;
	}
	
	display_all_goal_rec(head->next);
	head->adjacent->display();     
}

//wrapper for our recursive/iterative depth first function
int graph::depth_first(char * key)
{
	int start = find_location(key);

	if(start < 0)
	{
		return 0;
	}
	
	//reset all visit flags to false
	for(int i = 0; i < num_vertex; ++i)
	{
		(*(adjacency_list + i)).visit = false;
	}
	depth_first_rec(key);
	return 1;
}
	
//displays all goals connected to each other in a depth first fashion
void graph::depth_first_rec(char * key)
{
	edge * cur;
	int start = find_location(key);
	
	//display the contents of our vertex
	(*(adjacency_list + start)).display();
	//set cur to the start of our edge list
	cur = (*(adjacency_list + start)).head;
	//set the visit flag to true so we don't visit this vertex again
	(*(adjacency_list + start)).visit = true;

	while(cur != NULL)
	{
		if(!cur->adjacent->visit)
		{
			//go to the next vertex in our edge list and display
			depth_first_rec(cur->adjacent->m_goal);
		}
		cur = cur->next;
	}
}

//displays our goal
void vertex::display()
{
	cout << "Goal: " << m_goal << "\n";
}
