//Scott Patterson
//CS163
//Program 3
//Karla Fant
//.cpp file for the table.h file, describes what the functions can be performed on the data.

#include "table.h"
#include <iostream>
#include <cstring>
#include <cstdlib>

const int SZ = 1000;

//table constructor
table::table(int sz)
{
	table_sz = sz;
	my_table = new game_node*[table_sz];
	num_items = 0;

	for(int i = 0; i < table_sz; ++i)
	{
		*(my_table + i) = NULL;
	}
}

//table destructor
table::~table()
{
	for(int i = 0; i < table_sz; ++i)
	{
		delete *(my_table + i);
	}
	delete[] my_table; 
}

//game_node constructor
game_node::game_node()
{
	game = new game_data();
	next = NULL;
}

//game_node destructor
game_node::~game_node()
{
	delete game;
	delete next;
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
		m_title = NULL;
	}

	if(m_genre)
	{
		delete[] m_genre;
		m_genre = NULL;
	}

	if(m_game_type)
	{
		delete[] m_game_type;
		m_game_type = NULL;	
	}

	if(m_platform)
	{
		delete[] m_platform;
		m_platform = NULL;
	}

	if(m_comment)
	{
		delete[] m_comment;
		m_comment = NULL;
	}
	m_rating = 0;
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
	
	title = new char[SZ];
	genre = new char[SZ];
	game_type = new char[SZ];
	platform = new char[SZ];
	c_rating = new char[SZ];
	comment = new char[SZ];

	if(num_items > 0)
	{
		delete[] *(my_table);
		num_items = 0;
	}

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
		
		//create our game
		a_game.create_game(title, genre, game_type, platform, rating, comment);
		insert(a_game);
		
		//read next game to set eof
		in_file.get(title, SZ, ':');
		in_file.ignore(SZ, ':');
	}
	
	cout << "Number of games added: " << num_items << "\n\n";
	delete[] title;
	delete[] genre;
	delete[] game_type;
	delete[] platform;
	delete[] c_rating;
	delete[] comment;
	return 1;
}

//insert a game into our table
void table::insert(game_data &a_game)
{
	int index = 0;
	game_node * temp_g_node = NULL;

	//format our data
	format(a_game.m_title);
	format(a_game.m_genre);
	format(a_game.m_game_type);
	format(a_game.m_platform);
	format(a_game.m_comment);

	index = hash(a_game.m_title);
	
	//using pointer arithmatic, we find the address to the poper array location
	temp_g_node = *(my_table + index);
	*(my_table + index) = new game_node();
	(*(my_table + index))->game->copy_game(a_game);
	(*(my_table + index))->next = temp_g_node;
	++num_items;
}
	
//checks to see if our table has data
int table::has_data()
{
	if(num_items > 0)
	{
		return 1;
	}
	return 0;
}
	
//wrapper for our remove_rec function
int table::remove(char * title, char * platform)
{
	int index = 0;

	format(title);
	format(platform);

	index = hash(title);
	
	if(remove_rec(*(my_table + index), title, platform))
	{
		--num_items;
		return 1;
	}
	return 0;
}

//removes a specific game node matching the data passed in recursivly and links up the linear linked list
int table::remove_rec(game_node * &head, char * title, char * platform)
{
	game_node * temp;

	//return 0 if no game at table index
	if(!head)
	{
		return 0;
	}

	//check only if the next game_node is NULL
	if(!head->next)
	{
		//compare the title and platform, the game to remove could be at the end of the list
		if(strcmp(head->game->m_title, title) == 0 && strcmp(head->game->m_platform, platform) == 0)
		{
			delete head;
			head = NULL;
			return 1;
		}
		return 0;
	}

	//compare title and platform
	if(strcmp(head->game->m_title, title) == 0 && strcmp(head->game->m_platform, platform) == 0)
	{
		//get next game_node and put it in a temp variable
		temp = head->next;
		//set next to NULL for the current head so we dont loop
		head->next = NULL;
		//delete current head
		delete head;
		//reconnect;
		head = temp;
		return 1;
	}
	return remove_rec(head->next, title, platform);
}		

//wrapper for our retrieve_rec function
int table::retrieve(char * title, game_data * my_games, int &amt_of_games)
{
	int index = 0;
	
	format(title);
	index = hash(title);
	
	if(retrieve_rec(*(my_table + index), title, my_games, amt_of_games))
	{
		return 1;
	}
	return 0;
}

//recursive function to get all of our games that match title and populate our my_games array
int table::retrieve_rec(game_node * &head, char * title, game_data * my_games, int &amt_of_games)
{
	if(!head)
	{
		return 1;
	}
	if(strcmp(head->game->m_title, title) == 0)
	{
		(*(my_games + amt_of_games)).copy_game(*(head->game));
		++amt_of_games;
	}
	return retrieve_rec(head->next, title, my_games, amt_of_games);
}
		
	
//wrapper for our display_rec recusve function, gets each game_node in our table
int table::display_all()
{
	for(int i = 0; i < table_sz; ++i)
	{
		display_rec(*(my_table + i));
	}
	return 1;
}

//wrapper for our display_platform_rec recursive function, gets each game_noce in our table
int table::display_all(char * platform)
{
	format(platform);

	for(int i = 0; i < table_sz; ++i)
	{
		display_platform_rec(*(my_table + i), platform);
	}
	return 1;
}

//displays the games in our game_node's linear linker list recursivly
int table::display_rec(game_node * head)
{
	if(!head)
	{
		return 0;
	}
	head->game->display();
	return display_rec(head->next);
}

//displays all games with the matching platform
int table::display_platform_rec(game_node * head, char * platform)
{
	if(!head)
	{
		return 0;
	}

	if(strcmp(head->game->m_platform, platform) == 0)
	{
		head->game->display();
	}
	return display_platform_rec(head->next, platform);
}

//wrapper for our edit_comment_rec function
int table::edit_comment(char * title, char * platform, char * comment, game_data &a_game)
{
	int index = 0;

	format(title);
	format(platform);
	format(comment);

	cout << title;
	index = hash(title);
	
	if(edit_comment_rec(*(my_table + index), title, platform, comment, a_game))
	{
		return 1;
	}
	return 0;
}

//recursive comment to find our game to change the comment, then populate the a_game variable with the new data
int table::edit_comment_rec(game_node * &head, char * title, char * platform, char * comment, game_data &a_game)
{
	if(!head)
	{
		return 0;
	}

	if(!head->next)
	{
		if(strcmp(head->game->m_title, title) == 0 && strcmp(head->game->m_platform, platform) == 0)
		{
			if(head->game->m_comment)
			{
				delete[] head->game->m_comment;
			}
			head->game->m_comment = new char[strlen(comment) + 1];
			strcpy(head->game->m_comment, comment);
			a_game.copy_game(*(head->game));
			return 1;
		}
		return 0;
	}

	if(strcmp(head->game->m_title, title) == 0 && strcmp(head->game->m_platform, platform) == 0)
	{
		if(head->game->m_comment)
		{
			delete[] head->game->m_comment;
		}
		head->game->m_comment = new char[strlen(comment) + 1];
		strcpy(head->game->m_comment, comment);
		a_game.copy_game(*(head->game));
		return 1;
	}

	return edit_comment_rec(head->next, title, platform, comment, a_game);
}
	
//gets the hash value to determine where we will place the game in our table
int table::hash(char * title)
{
	int size = strlen(title);
	int hash_title = 0;

	for(int i = 0; i < size; ++i)
	{
		hash_title += *(title + i);
	}
	
	hash_title = hash_title % table_sz;
	return hash_title;
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
