/*Scott Patterson
CS202
Program 3
BST.h*/

#include "person.h"


class BST
{
	public:
	BST();
	~BST();
	void display_all();
	//overloaded operators
	BST & operator+=(person & a_person);
	bool operator!=(class BST_node * isNull);

	protected:
	//function to delete all of our BST nodes recursivly
	void delete_rec(class BST_node * &head);
	void add(BST_node * &head, person & a_person);
	void display_all_rec(BST_node * & head);
	class BST_node * head;
};

//ostream& operator<<(ostream &os, BST & my_BST);

class LLL_node
{
	public:
	LLL_node(person & a_person);
	~LLL_node();
	LLL_node * &get_next();
	person * get_person();

	protected:
	LLL_node * next;
	person * my_person;
};

class LLL
{
	public:
	LLL(person & a_person);
	~LLL();
	void add_to_LLL(LLL_node * &head, person & a_person);
	
	protected:
	void display_LLL_rec(LLL_node * & head);
	LLL_node * head;
};

class BST_node: public LLL
{
	public:
	//method to copy a person into a BST_node
	BST_node(person & a_person);
	BST_node(BST_node & a_node);
	~BST_node();
	LLL_node * &get_LLL_head();
	void display_LLL();
	//methods to get our left and right pointers
	BST_node * & get_left();
	BST_node * & get_right();
	char * get_l_name();

	protected:
	BST_node * left;
	BST_node * right;
	//last name to compare to at every node
	char * l_name;
};
