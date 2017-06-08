//Scott Patterson
//CS163
//Program 4
//Karla Fant
//Table class for declaring functions to help build our tree and operate on our tree

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

//struct for each of my game nodes for our tree
struct game_node
{
	game_node();
	~game_node();
	game_data * game;
	game_node * left;
	game_node * right;
};

//class that defines our table
class table
{
	public:
	table();
	~table();
	int has_data();
	int populate(ifstream &in_file, game_data &a_game);
	int insert(game_data &a_game);
	int remove(char * title, game_data &a_game);
	int remove_key(char * title, game_data &a_game, int &num_games);
	int retrieve(char * title, game_data * my_games, int &num_items);
	int display_range(char start, char end, int &num_games);
	int display_top(int &num_games);
	int display_key();
	int display_all();

	private:
	void format(char * temp);
	int insert_rec(game_node * &root, game_data &a_game);
	int remove_rec(game_node * &root, char * title, game_data &a_game);
	int remove_key_rec(game_node * &root, char * title, game_data &a_game, int &num_games);
	int retrieve_rec(game_node * &root, char * title, game_data * my_games, int &num_items);
	void in_order_succesor(game_node * &root, game_data &a_game);
	void display_range_rec(game_node * &root, char start, char end, int &num_games);
	void display_key_rec(game_node * &root);
	void display_top_rec(game_node * &root, int &num_games);
	void display_all_rec(game_node * &root);
	void delete_all(game_node * &root);
	int num_of_items;
	game_node * root;
};
