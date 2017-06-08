//Scott Patterson
//CS163
//Program 4
//Karla Fant
//.cpp file for the table.h file, describes what the functions can be performed on the tree.

#include "table.h"
#include <iostream>
#include <cstring>
#include <cstdlib>

const int SZ = 1000;

//table constructor
table::table()
{
	root = NULL;
	num_of_items = 0;
}

table::~table()
{
	delete_all(root);
	num_of_items = 0;
}

//game_node constructor
game_node::game_node()
{
	game = new game_data();
	left = NULL;
	right = NULL;
}

//game_node destructor
game_node::~game_node()
{
	delete game;
	left = NULL;
	right = NULL;
}

//game_data constructor
game_data::game_data()
{
	m_title = NULL;
	m_genre = NULL;
	m_game_type = NULL;
	m_platform = NULL;
	m_rating = 0;
	m_comment = NULL;
}

//game_data destructor
game_data::~game_data()
{
	if(m_title)
	{
		delete[] m_title;
	}
	m_title = NULL;
	if(m_genre)
	{
		delete[] m_genre;
	}
	m_genre = NULL;
	if(m_game_type)
	{
		delete[] m_game_type;
	}
	m_game_type = NULL;
	if(m_platform)
	{
		delete[] m_platform;
	}
	m_platform = NULL;
	m_rating = 0;
	if(m_comment)
	{
		delete[] m_comment;
	}
	m_comment = NULL;
}

//populates our table with data
int table::populate(ifstream &in_file, game_data &a_game)
{
	char * title;
	char * genre;
	char * game_type;
	char * platform;
	char * c_rating;
	int rating = 0;
	char * comment;
	int file_num = 0;
	
	title = new char[SZ];
	genre = new char[SZ];
	game_type = new char[SZ];
	platform = new char[SZ];
	c_rating = new char[SZ];
	comment = new char[SZ];

	//attempting to read before we check eof
	in_file.get(title, SZ, ':');
	in_file.ignore(SZ, ':');
	
	//loop until eof, grabbing the different sections of each game
	while(!in_file.eof())
	{
		in_file.get(genre, SZ, ':');
		in_file.ignore(SZ, ':');
		
		in_file.get(game_type, SZ, ':');
		in_file.ignore(SZ, ':');

		in_file.get(platform, SZ, ':');
		in_file.ignore(SZ, ':');

		in_file.get(c_rating, SZ, ':');
		in_file.ignore(SZ, ':');
		rating = atoi(c_rating);

		in_file.get(comment, SZ, ':');
		in_file.ignore(SZ, '\n');
		
		//format our data
		format(title);
		format(genre);
		format(game_type);
		format(platform);
		format(comment);

		//create our game
		a_game.create_game(title, genre, game_type, platform, rating, comment);
		insert(a_game);
		++file_num;

		//read next game to set eof
		in_file.get(title, SZ, ':');
		in_file.ignore(SZ, ':');
	}
	
	cout << file_num << " Items added!\n\n";

	delete[] title;
	delete[] genre;
	delete[] game_type;
	delete[] platform;
	delete[] c_rating;
	delete[] comment;
	return 1;
}

//wrapper to insert a game into our table
int table::insert(game_data &a_game)
{
	format(a_game.m_title);
	format(a_game.m_genre);
	format(a_game.m_game_type);
	format(a_game.m_platform);
	format(a_game.m_comment);

	//if no root exists, create a new one
	if(!root)
	{
		root = new game_node();
		root->game->copy_game(a_game);
		++num_of_items;
		return 1;
	}
	return insert_rec(root, a_game);
}

//recursive function to insert the game at the end of the correct path in the tree
int table::insert_rec(game_node * &root, game_data &a_game)
{
	//if root is null, insert at root
	if(!root)
	{
		root = new game_node();
		root->game->copy_game(a_game);
		++num_of_items;
		return 1;
	}
	else if(strcmp(a_game.m_title, root->game->m_title) < 0)
	{
		//go to the left
		return insert_rec(root->left, a_game);
	}
	else
	{
		//go to the right
		return insert_rec(root->right, a_game);
	}
}

//wrapper to remove 1 item
int table::remove(char * title, game_data &a_game)
{
	format(title);

	if(!root)
	{
		return 0;
	}
	return remove_rec(root, title, a_game);
}

//recursive function to remove 1 item
int table::remove_rec(game_node * &root, char * title, game_data &a_game)
{
	game_node * child;

	if(!root)
	{
		return 0;
	}
	if(strcmp(title, root->game->m_title) == 0)
	{
		//if matching root is at a leaf
		if(!root->left && !root->right)
		{
			delete root;
			root = NULL;
			--num_of_items;
			return 1;
		}
		//else if matching root is in the middle of a path that leads to
		//the left and not the right
		else if(root->left && !root->right)
		{
			child = root->left;
			delete root;
			root = child;
			--num_of_items;
			return 1;
		}
		//else if matching root is in the middle of a path that leads to
		//the right and not the left
		else if(!root->left && root->right)
		{
			child = root->right;
			delete root;
			root = child;
			--num_of_items;
			return 1;
		}
		else
		{
			//find the in order sucessor
			in_order_succesor(root->right, a_game);
			root->game->copy_game(a_game);
			--num_of_items;
			return 1;
		}
	}
	//determine what path to go down
	if(strcmp(title, root->game->m_title) < 0)
	{
		return remove_rec(root->left, title, a_game);
	}
	else
	{
		return remove_rec(root->right, title, a_game);
	}
}
	
int table::remove_key(char * title, game_data &a_game, int &num_games)
{
	format(title);
	
	if(!root)
	{
		return 0;
	}
	return remove_key_rec(root, title, a_game, num_games);
}

int table::remove_key_rec(game_node * &root, char * title, game_data &a_game, int &num_games)
{
	game_node * child;
	bool found = false;

	if(!root)
	{
		if(num_games == 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	if(strcmp(title, root->game->m_title) == 0)
	{
		//if matching root is at a leaf
		if(!root->left && !root->right)
		{
			delete root;
			root = NULL;
			--num_of_items;
			++num_games;
			return 1;
		}
		//else if matching root is in the middle of a path that leads to
		//the left and not the right
		else if(root->left && !root->right)
		{
			child = root->left;	
			delete root;
			root = child;
			--num_of_items;
			++num_games;
			found = true;
		}
		//else if matching root is in the middle of a path that leads to
		//the right and not the left
		else if(!root->left && root->right)
		{
			child = root->right;
			delete root;
			root = child;
			--num_of_items;
			++num_games;
			found = true;
		}
		else
		{
			//find the in order sucessor
			in_order_succesor(root->right, a_game);
			root->game->copy_game(a_game);
			--num_of_items;
			++num_games;
			found = true;
		}
	}
	//determine what path to go down
	if(strcmp(title, root->game->m_title) < 0)
	{
		return remove_key_rec(root->left, title, a_game, num_games);
	}
	else
	{
		if(found)
		{
			return remove_key_rec(root, title, a_game, num_games);
		}
		else
		{
			return remove_key_rec(root->right, title, a_game, num_games);
		}
	}
}	

//recursive function to find the in order succesor
void table::in_order_succesor(game_node * &root, game_data &a_game)
{
	game_node * child;

	if(!root->left)
	{
		child = root->right;
		a_game.copy_game(*(root->game));
		delete root;
		root = child;
		return;;
	}
	in_order_succesor(root->left, a_game);
}
	
//wrapper to retrieve a game
int table::retrieve(char * title, game_data * my_games, int &num_items)
{
	format(title);

	if(!root)
	{
		return 0;
	}
	return retrieve_rec(root, title, my_games, num_items);
}

//recursive function to find our game and then populate our a_game object with
//the game
int table::retrieve_rec(game_node * &root, char * title, game_data * my_games, int &num_items)
{
	//if not found, return 0
	if(!root)
	{
		if(num_items == 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}

	//if found, populate a_game with the game found
	if(strcmp(title, root->game->m_title) == 0)
	{
		my_games[num_items].copy_game(*(root->game));
		++num_items;
	}

	if(strcmp(title, root->game->m_title) < 0)
	{
		return retrieve_rec(root->left, title, my_games, num_items);
	}
	else
	{
		return retrieve_rec(root->right, title, my_games, num_items);
	}
}

//wrapper to display all games with a rating of 5
int table::display_top(int &num_games)
{
	if(!root)
	{
		return 0;
	}
	display_top_rec(root, num_games);
	return 1;
}
	
//display all games in our tree recursivly by traversing all the way to the left
//and then returning up the stack, displaying all the games with a rating of 5
void table::display_top_rec(game_node * &root, int &num_games)
{
	if(!root)
	{
		return;
	}
	display_top_rec(root->left, num_games);
	if(root->game->m_rating == 5)
	{
		root->game->display();
		++num_games;
	}
	display_top_rec(root->right, num_games);
}

//wrapper to display all data between two characters
int table::display_range(char start, char end, int &num_games)
{
	if(!root)
	{
		return 0;
	}
	display_range_rec(root, start, end, num_games);
	return 1;
}

//recursive function to display all game between two characters
void table::display_range_rec(game_node * &root, char start, char end, int &num_games)
{
	if(!root)
	{
		return;
	}
	display_range_rec(root->left, start, end, num_games);
	if(root->game->m_title[0] >= start && root->game->m_title[0] <= end)
	{
		root->game->display();
	}
	display_range_rec(root->right, start, end, num_games);
}

//wrapper to display all games in our tree
int table::display_all()
{
	if(!root)
	{
		return 0;
	}
	display_all_rec(root);
	cout << num_of_items << " Items\n\n";
	return 1;
}
	
//display all of the games in our tree recusivly by traversing all the way to the left
//and then returning up the stack, going right as much as possible
void table::display_all_rec(game_node * &root)
{
	if(!root)
	{
		return;
	}
	display_all_rec(root->left);
	root->game->display();
	display_all_rec(root->right);
}

//wrapper to display all keywords
int table::display_key()
{
	if(!root)
	{
		return 0;
	}
	display_key_rec(root);
	return 1;
}

//recursive function that will display all game titles as "keys"
void table::display_key_rec(game_node * &root)
{
	if(!root)
	{
		return;
	}
	display_key_rec(root->left);
	//if at a leaf, display title
	if(!root->left && !root->right)
	{
		cout << root->game->m_title << "\n";
	}
	else if(root->right)
	{
		//if the game title to the right of our current root doesn't match
		//our current root's game title, display the current root's game 
		//title, this is so we dont display the same key twice in case
		//there is multiple of the same game on different platforms
		if(strcmp(root->game->m_title, root->right->game->m_title) != 0)
		{
			cout << root->game->m_title << "\n";
		}
	}
	display_key_rec(root->right);
}

//check to see if we have data;	
int table::has_data()
{
	if(!root)
	{
		return 0;
	}
	return 1;
}

//formats a string
void table::format(char * temp)
{
	int temp_size = 0;

	temp_size = strlen(temp);

	for(int i = 0; i < temp_size; ++i)
	{
		if(i == 0 && (*(temp + i) != ' '))
		{
			(*(temp + i)) = toupper((*(temp + i)));
		}
	
		if((*(temp + i)) == ' ' && (*(temp + i + 1) != ' '))
		{
			(*(temp + i + 1)) = toupper((*(temp + i + 1)));
		}
	}
}

//recursive function to delete entire tree
void table::delete_all(game_node * &root)
{
	if(!root)
	{
		return;
	}
	
	delete_all(root->left);
	delete_all(root->right);
	delete root;
}

//Create a game object, checking to see if each member is already populated, deleting it if it is, and then repopulating it with
//data passed in
void game_data::create_game(char * title, char * genre, char * game_type, char * platform, int rating, char * comment)
{
	//check to see if title/genre/game_type/platform/comment aready has data
	if(m_title)
	{
		delete[] m_title;
	}
	m_title = new char[strlen(title) + 1];
	strcpy(m_title, title);

	if(m_genre)
	{
		delete[] m_genre;
	}
	m_genre =  new char[strlen(genre) + 1];
	strcpy(m_genre, genre);

	if(m_game_type)
	{
		delete[] m_game_type;
	}
	m_game_type = new char[strlen(game_type) + 1];
	strcpy(m_game_type, game_type);
	
	if(m_platform)
	{
		delete[] m_platform;
	}
	m_platform = new char[strlen(platform) + 1];
	strcpy(m_platform, platform);
	
	m_rating = rating;

	if(m_comment)
	{
		delete[] m_comment;
	}
	m_comment = new char[strlen(comment) + 1];
	strcpy(m_comment, comment);
}

//function to copy game data from another game_data object
void game_data::copy_game(game_data &a_game)
{	
	if(m_title)
	{
		delete[] m_title;
	}
	m_title = new char[strlen(a_game.m_title) + 1];
	strcpy(m_title, a_game.m_title);
	
	if(m_genre)
	{
		delete[] m_genre;
	}
	m_genre = new char[strlen(a_game.m_genre) + 1];
	strcpy(m_genre, a_game.m_genre);

	if(m_game_type)
	{
		delete[] m_game_type;
	}
	m_game_type = new char[strlen(a_game.m_game_type) + 1];
	strcpy(m_game_type, a_game.m_game_type);

	if(m_platform)
	{
		delete[] m_platform;
	}
	m_platform = new char[strlen(a_game.m_platform) + 1];
	strcpy(m_platform, a_game.m_platform);

	m_rating = a_game.m_rating;

	if(m_comment)
	{
		delete[] m_comment;
	}
	m_comment = new char[strlen(a_game.m_comment) + 1];
	strcpy(m_comment, a_game.m_comment);
}
	
//displays our game object
void game_data::display()
{
	cout << "Title: " << m_title << "\n"
	     << "Genre: " << m_genre << "\n"
	     << "Game type: " << m_game_type << "\n"
	     << "Platform: " << m_platform << "\n"
	     << "Rating (0-5): " << m_rating << "\n"
	     << "Comment: " << m_comment << "\n\n";
}
