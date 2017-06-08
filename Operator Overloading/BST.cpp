/*Scott Patterson
CS202
Program 3
BST.cpp*/

#include "BST.h"

//constructor for a BST
BST::BST(): head(NULL)
{
}

//Destructor for a BST
BST::~BST()
{
	if(head)
	{
		delete_rec(head);
	}
	head = NULL;
}

//function to display all nodes in our BST
void BST::display_all()
{
	display_all_rec(head);
}

//operator overload for += to add a person to our BST
BST & BST::operator+=(person & a_person)
{
	if(!(this->head))
	{
		this->head = new BST_node(a_person);
	}
	else
	{
		this->add(this->head, a_person);
	}
	return *this;
}

//operator overload to check if we have contacts in our BST by checking if the root is NULL
bool BST::operator!=(BST_node * isNull)
{
	if(head == isNull)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//function to delete every node in our BST
void BST::delete_rec(BST_node * &head)
{
	if(!head)
	{
		return;
	}
	//go to the left
	delete_rec(head->get_left());
	//go to the right
	delete_rec(head->get_right());
	//if leaf, delete
	delete head;
}

//function to add to our BST
void BST::add(BST_node * &head, person & a_person)
{
	if(!head)
	{
		head = new BST_node(a_person);
		return;
	}
	if(a_person == head->get_l_name()) //if we have a match, add the person to the BST's LLL sorted by f_name
	{
		cout << "MATCH!";
		head->add_to_LLL(head->get_LLL_head(), a_person);
		return;
	}
	//go left if less than BST's l_name
	if(a_person < head->get_l_name())
	{
		return add(head->get_left(), a_person);
	}
	if(a_person >= head->get_l_name())
	{
		return add(head->get_right(), a_person);
	}
}

//function to display all nodes recusively
void BST::display_all_rec(BST_node * & head)
{
	if(!head)
	{
		return;
	}
	display_all_rec(head->get_left());
	head->display_LLL();
	display_all_rec(head->get_right());
}

//Constructor for a LLL_node
LLL_node::LLL_node(person & a_person): next(NULL)
{
	my_person = new person(a_person);
}

//Destructor for a LLL_node
LLL_node::~LLL_node()
{
	if(next)
	{
		delete next;
	}
	if(my_person)
	{
		delete my_person;
	}
}

//recursive function to add to the end of our linear linked list, sorting it at the same time
void LLL::add_to_LLL(LLL_node * &head, person &a_person)
{
	LLL_node * temp = NULL;

	if(!head)
	{
		head = new LLL_node(a_person);
		return;
	}
	if(strcmp(a_person.get_f_name(), head->get_person()->get_f_name()) < 0)
	{
		temp = head;
		head = new LLL_node(a_person);
		head->get_next() = temp;
		return;
	}
	add_to_LLL(head->get_next(), a_person);
}

void LLL::display_LLL_rec(LLL_node * & head)
{
	if(!head)
	{
		return;
	}
	cout << *(head->get_person());
	return display_LLL_rec(head->get_next());
}

//function to get our next pointer by reference
LLL_node * & LLL_node::get_next()
{
	return next;
}

//function to get my person
person * LLL_node::get_person()
{
	return my_person;
}

//Constructor for a LLL
LLL::LLL(person & a_person)
{
	head = new LLL_node(a_person);
}

//destructor for a LLL
LLL::~LLL()
{
	if(head)
	{
		delete head;
	}
}

//function to get our head for our LLL
LLL_node * & BST_node::get_LLL_head()
{
	return head;
}

//function to display our LLL
void BST_node::display_LLL()
{
	display_LLL_rec(get_LLL_head());
}

//Constructor for a BST_node
BST_node::BST_node(person & a_person): LLL(a_person), left(NULL), right(NULL)
{
	l_name = new char[strlen(a_person.get_l_name()) + 1];
	strcpy(l_name, a_person.get_l_name());
}

//Copy contructor for a BST_node
BST_node::BST_node(BST_node & a_BST_node): LLL(*(a_BST_node.head->get_person()))
{
	left = NULL;
	right = NULL;
	l_name = new char[strlen(a_BST_node.l_name) + 1];
	strcpy(l_name, a_BST_node.l_name); //possible overload here!
}

//Destructor for a BST_node
BST_node::~BST_node()
{
	if(l_name)
	{
		delete[] l_name;
	}
}

//function to get our left pointer
BST_node * & BST_node::get_left()
{
	return left;
}

//function to get our right pointer
BST_node * & BST_node::get_right()
{
	return right;
}

char * BST_node::get_l_name()
{
	return l_name;
}
