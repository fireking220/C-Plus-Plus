//Scott Patterson
//CS163
//Program 4
//Karla Fant
//This program will open a file and load it's contents into a binary search tree, 
//from there, the user can perform operations on the tree such as
//removing a game, remove based on a keyword, return games with a rating of 5
//insert a new game, display everything alphabetically, display everything in a 
//range by two different characters, and retrieve a game

#include "table.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
	
const int SZ = 1000;

void game_menu(char choice);

int main()
{
	char choice = ' ';

	game_menu(choice);
	return 1;
}

//fuction to diplay our game menu
void game_menu(char choice)
{
	char filepath[SZ] = "";
	char title[SZ] = "";
	char genre[SZ] = "";
	char game_type[SZ] = "";
	char platform[SZ] = "";
	int rating  = 0;
	char comment[SZ] = "";
	int num_games = 0;
	char start = ' ';
	char end = ' ';
	table tree_table;
	game_data my_games[SZ];
	game_data a_game;
	ifstream in_file;

	cout << "Welcome to the game database!\n\n";

	do {
		cout << "A)Load game list --DONE--\n"
		     << "B)Insert a game --DONE--\n"
		     << "C)Remove a game --DONE--\n"
		     << "D)Remove based on key --DONE--\n"
		     << "E)Display top rated games --DONE--\n"
		     << "F)Retrieve game --DONE--\n"
		     << "G)Display all --DONE--\n"
		     << "H)Display within range --DONE--\n"
		     << "I)Display keys --DONE--\n"
		     << "Q)Quit\n\n"
		     << "Option: ";

		cin >> choice;
		choice = toupper(choice);
		cin.ignore(1000, '\n');
		cout << "\n\n";

		switch(choice)
		{

		case 'A': cout << "Enter a filepath to load: ";
			cin.get(filepath, SZ, '\n');
			cin.ignore(SZ, '\n'); 
			cout << "Opening game list...\n\n";
			in_file.open(filepath);

			if(in_file.is_open())
			{
				tree_table.populate(in_file, a_game);
				cout << "GAMES READ!\n\n";
				in_file.close();
			}
			else
			{	
				cout << "ERROR! GAME LIST COULD NOT BE OPENED!\n\n";
			}
			break;

		case 'B': cout << "Enter a title: ";
			cin.get(title, SZ, '\n');
			cin.ignore(SZ, '\n');
			cout << "Enter a genre: ";
			cin.get(genre, SZ, '\n');
			cin.ignore(SZ, '\n');
			cout << "Enter a game type: ";
			cin.get(game_type, SZ, '\n');
			cin.ignore(SZ, '\n');
			cout << "Enter a platform: ";
			cin.get(platform, SZ, '\n');
			cin.ignore(SZ, '\n');
			cout << "Enter a rating (0-5): ";
			cin >> rating;
			cin.ignore(SZ, '\n');
			cout << "Enter a comment/reccomendation: ";
			cin.get(comment, SZ, '\n');
			cin.ignore(SZ, '\n');
			a_game.create_game(title, genre, game_type, platform, rating, comment);
			tree_table.insert(a_game);
			cout << "Added game!\n\n";
			break;

		case 'C': cout << "Attempting to read games...\n\n";
			if(tree_table.has_data())
			{
				cout << "Enter the game's title to remove: ";
				cin.get(title, SZ, '\n');
				cin.ignore(SZ, '\n');
				if(tree_table.remove(title, a_game))
				{
					cout << "Game removed!\n\n";
				}
				else
				{
					cout << "ERROR, GAME NOT FOUND!\n\n";
				}
			}
			else
			{
				cout << "ERROR, NO GAMES!\n\n";
			}
			break;

		case 'D': cout << "Attemping to read games...\n\n";
			if(tree_table.has_data())
			{
				cout << "Enter the game's title to remove all entries: ";
				cin.get(title, SZ, '\n');
				cin.ignore(SZ, '\n');
				if(tree_table.remove_key(title, a_game, num_games))
				{
					cout << num_games << " games removed!\n\n";
					num_games = 0;
				}
				else
				{
					cout << "ERROR, GAMES NOT FOUND!\n\n";
				}
			}
			else
			{
				cout << "ERROR, NO GAMES!\n\n";
			}	
			break;

		case 'E': cout << "Attempting to read games...\n\n";
			if(tree_table.has_data())
			{
				tree_table.display_top(num_games);
				cout << "Displayed " << num_games << " games!\n\n";
			}
			else
			{
				cout << "ERROR, NO GAMES!\n\n";
			}
			num_games = 0;
			break;

		case 'F': cout << "Attempting to read games...\n\n";
			if(tree_table.has_data())
			{
				cout << "Enter the game title to find: ";
				cin.get(title, SZ, '\n');
				cin.ignore(SZ, '\n');
				if(tree_table.retrieve(title, my_games, num_games))
				{
					cout << "Games found!\n\n";
					for(int i = 0; i < num_games; ++i)
					{
						my_games[i].display();
					}
				}
				else
				{
					cout << "ERROR, GAME NOT FOUND!\n\n";
				}
			}
			else
			{
				cout << "ERROR, NO GAMES!\n\n";
			}		
			num_games = 0;
			break;
		
		case 'G': cout << "Attempting to display games...\n\n";
			if(tree_table.has_data())
			{
				tree_table.display_all();
				cout << "DISPLAYED GAMES!\n\n";
			}
			else
			{
				cout << "ERROR, NO GAMES!\n\n";
			} 
			break;
		
		case 'H': cout << "Attempting to read games...\n\n";
			if(tree_table.has_data())
			{
				cout << "Enter the start character: ";
				cin >> start;
				start = toupper(start);
				cin.ignore(SZ, '\n');
				cout << "Enter the end character: ";
				cin >> end;
				end = toupper(end);
				cin.ignore(SZ, '\n');
				cout << "\n";
				tree_table.display_range(start, end, num_games);
			}
			else
			{
				cout << "ERROR, NO GAMES!\n\n";
			}
			break;

		case 'I': cout << "Attempting to read games...\n\n";
			if(tree_table.has_data())
			{
				tree_table.display_key();
				cout << "\nDisplayed keys!\n\n";
			}
			else
			{
				cout << "ERROR, NO GAMES!\n\n";
			}
			break;
		
		case 'Q': cout << "Quitting...\n";
			break;
		
		default: cout << "Invalid option, please enter a valid option\n\n";
			break;
		}
	}while(choice != 'Q');
}
