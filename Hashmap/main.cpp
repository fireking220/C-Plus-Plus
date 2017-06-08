//Scott Patterson
//CS163
//Program 3
//Karla Fant
//This program will open a file and load it's contents into a table via a hashmap
//function, from there, the user can perform operations on the data such as
//removing a game, inserting a new game, display everything by platform, display everything,
//change the comment of a game, and retrieve a game

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
	char filepath[SZ] = "CS163_games.txt";
	char title[SZ] = "";
	char genre[SZ] = "";
	char game_type[SZ] = "";
	char platform[SZ] = "";
	int rating = 0;
	char comment[SZ] = "";
	int amt_of_games = 0;
	table g_table;
	game_data a_game;
	game_data my_games[SZ];
	ifstream in_file;

	cout << "Welcome to the game database!\n\n";

	do {
		cout << "A)Load game list\n"
		     << "B)Insert new game\n"
		     << "C)Remove game\n"
		     << "D)Edit previous comment\n"
		     << "E)Retrieve game information\n"
		     << "F)Display based on platform\n"
		     << "G)Display all\n"
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
				g_table.populate(in_file, a_game);
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
			title[0] = toupper(title[0]);
			cout << "Enter a genre: ";
			cin.get(genre, SZ, '\n');
			cin.ignore(SZ, '\n');
			cout << "Enter a game type: ";
			cin.get(game_type, SZ, '\n');
			cin.ignore(SZ, '\n');
			cout << "Enter a platform: ";
			cin.get(platform, SZ, '\n');
			cin.ignore(SZ, '\n');
			platform[0] = toupper(platform[0]);
			cout << "Enter a rating (0-5): ";
			cin >> rating;
			cin.ignore(SZ, '\n');
			cout << "Enter a comment: ";
			cin.get(comment, SZ, '\n');
			cin.ignore(SZ, '\n');
			
			a_game.create_game(title, genre, game_type, platform, rating, comment);
			g_table.insert(a_game);

			cout << "GAME ADDED!\n\n";
			break;

		case 'C': cout << "Checking games...\n\n";
			if(g_table.has_data())
			{
				cout << "Enter the title of the game to remove: ";
				cin.get(title, SZ, '\n');
				cin.ignore(SZ, '\n');
				title[0] = toupper(title[0]);
				cout << "Enter the platform of the game: ";
				cin.get(platform, SZ, '\n');
				cin.ignore(SZ, '\n');
				platform[0] = toupper(platform[0]);
				if(g_table.remove(title, platform))
				{
					cout << "GAME FOUND AND REMOVED!\n\n";
				}
				else
				{
					cout << "ERROR, GAME NOT FOUND!\n\n";
				}
			}
			else
			{
				cout << "ERROR: NO GAMES!\n\n";
			}
			break;

		case 'D': cout << "Checking games...\n";
			if(g_table.has_data())
			{
				cout << "Enter a title: ";
				cin.get(title, SZ, '\n');
				cin.ignore(SZ, '\n');
				title[0] = toupper(title[0]);
				cout << "Enter a platform: ";
				cin.get(platform, SZ, '\n');
				cin.ignore(SZ, '\n');
				platform[0] = toupper(platform[0]);
				cout << "Enter the new comment: ";
				cin.get(comment, SZ, '\n');
				cin.ignore(SZ, '\n');
				if(g_table.edit_comment(title, platform, comment, a_game))
				{
					cout << "Comment changed!\n\n";
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

		case 'E': cout << "Checking games...\n";
			if(g_table.has_data())
			{
				cout << "Enter a title: ";
				cin.get(title, SZ, '\n');
				cin.ignore(SZ, '\n');
				title[0] = toupper(title[0]);
				if(g_table.retrieve(title, my_games, amt_of_games))
				{
					cout << "Games found!\n\n";
					for(int i = 0; i < amt_of_games; ++i)
					{
						my_games[i].display();
					}
					amt_of_games = 0;
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

		case 'F': cout << "Checking games...\n";
			if(g_table.has_data())
			{
				cout << "Enter a platform: ";
				cin.get(platform, SZ, '\n');
				cin.ignore(SZ, '\n');
				platform[0] = toupper(platform[0]);
				g_table.display_all(platform);
				cout << "Displayed all games on the " << platform << "\n\n";
			}
			else
			{
				cout << "ERROR: NO GAMES!\n\n";
			}
			break;
		
		case 'G': cout << "Checking games...\n";
			if(g_table.has_data())
			{
				cout << "Displaying games...\n\n";
				g_table.display_all();
				cout << "Dislplayed all games!\n\n";
			}
			else
			{
				cout << "ERROR: NO GAMES!\n\n";
			}
			break;
		
		case 'Q': cout << "Quitting...\n";
			break;
		
		default: cout << "Invalid option, please enter a valid option\n\n";
			break;
		}
	}while(choice != 'Q');
}
