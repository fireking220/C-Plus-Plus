//Scott Patterson
//CS163
//Program 3
//Karla Fant
//Table class for declaring functions to help build our table and operate on our table

#include <fstream>

using namespace std;

//struct for defining what data a game holds
struct game_data
{
	game_data();
	~game_data();
	void create_game(char * title, char * genre, char * game_type, char * platform, int rating, char * comment);
	void copy_game(game_data &a_game);
	void display();
	char * m_title;
	char * m_genre;
	char * m_game_type;
	char * m_platform;
	int m_rating;
	char * m_comment;
};

//struct for each of my game nodes for a linear linked list
struct game_node
{
	game_node();
	~game_node();
	void game_node_del_list(game_node * &next);
	game_data * game;
	game_node * next;
};

//class that defines our table
class table
{
	public:
	table(int sz = 101);
	~table();
	int populate(ifstream &in_file, game_data &a_game);
	int has_data();
	void insert(game_data &a_game);
	int remove(char * title, char * platform);
	int retrieve(char * title, game_data * my_games, int &amt_of_games);
	int edit_comment(char * title, char * platform, char * comment, game_data &a_game);
	int display_all();
	int display_all(char * platform);

	private:
	int hash(char * title);
	void format(char * temp);
	int remove_rec(game_node * &head, char * title, char * platform);
	int retrieve_rec(game_node * &head, char * title, game_data * my_games, int &amt_of_games);
	int edit_comment_rec(game_node * &head, char * title, char * platform, char * comment, game_data &a_game);
	int display_rec(game_node * head);
	int display_platform_rec(game_node * head, char * platform);
	int num_items;
	int table_sz;
	game_node ** my_table; //dynamically allocated array of head pointers
	
};
