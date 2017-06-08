/*Scott Patterson
CS202
Program 3
person.cpp*/

#include "person.h"

//Contructor for a name
name::name(): f_name(NULL), l_name(NULL)
{
}

//Copy constructor for a name
name::name(name & a_name)
{
	f_name = new char[strlen(a_name.f_name) + 1];
	strcpy(f_name, a_name.f_name);
	l_name = new char[strlen(a_name.l_name) + 1];
	strcpy(l_name, a_name.l_name);
}

//Destructor for a name
name::~name()
{
	if(f_name)
	{
		delete[] f_name;
	}
	if(l_name)
	{
		delete[] l_name;
	}
}

//Constructor for a person
person::person(): my_contact(NULL)
{
}

//Copy constructor for a person
person::person(person & a_person)
{
	f_name = new char[strlen(a_person.get_f_name()) + 1];
	strcpy(f_name, a_person.get_f_name());
	l_name = new char[strlen(a_person.get_l_name()) + 1];
	strcpy(l_name, a_person.get_l_name());
	my_contact = new contact(*(a_person.get_contact()));
}

//Destructor for a person
person::~person()
{
	if(my_contact)
	{
		delete my_contact;
	}
}

//function to create a person using information
void person::create(char * a_f_name, char * a_l_name, contact & a_contact)
{
	if(f_name)
	{
		delete[] f_name;
	}
	f_name = new char[strlen(a_f_name) + 1];
	strcpy(f_name, a_f_name);

	if(l_name)
	{
		delete[] l_name;
	}
	l_name = new char [strlen(a_l_name) + 1];
	strcpy(l_name, a_l_name);

	if(my_contact)
	{
		delete my_contact;
	}
	my_contact = new contact(a_contact);
}

//function to get our first name
char * person::get_f_name()
{
	return f_name;
}

//function to get our last name
char * person::get_l_name()
{
	return l_name;
}

//function to get our contact
contact * person::get_contact()
{
	return my_contact;
}

//operator overload for == to compare a person to a name
bool person::operator==(char * l_name)
{
	if(strcmp(this->get_l_name(), l_name) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Overloaded friend operator for ==
bool operator==(char * l_name, person &a_person)
{
	if(strcmp(a_person.get_l_name(), l_name) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//operator overload for < to compare a person to a name to determine what side of the BST to go down
bool person::operator<(char * l_name)
{
	if(strcmp((this->get_l_name()), l_name) < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//overloaded friend operator for <
bool operator<(char * l_name, person & a_person)
{
	if(strcmp(l_name, a_person.get_l_name()) < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//operator overload for <= to compare a person to a name
bool person::operator<=(char * l_name)
{
	if(strcmp((this->get_l_name()), l_name) <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//overloaded friend operator for <=
bool operator<=(char * l_name, person & a_person)
{
	if(strcmp(l_name, a_person.get_l_name()) <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//operator overload for > to compare a person to a name to determine which side of the BST to go down
bool person::operator>(char * l_name)
{
	if(strcmp((this->get_l_name()), l_name) > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//overloaded friend operator for >
bool operator>(char * l_name, person & a_person)
{
	if(strcmp(l_name, a_person.get_l_name()) > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//operator overload for >= to compare a person to a name
bool person::operator>=(char * l_name)
{
	if(strcmp((this->get_l_name()), l_name) >= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//overloaded friend operator for >=
bool operator>=(char * l_name, person & a_person)
{
	if(strcmp(l_name, a_person.get_l_name()) >= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//overloaded friend operator for << for displaying a person
ostream& operator<<(ostream &os, person &my_person)
{
	os << "\nFirst name: " << my_person.get_f_name()
	   << "\nLast Name: " << my_person.get_l_name()
	   << "\nContact 1: " << my_person.get_contact()->get_contact1()
	   << "\nContact 2: " << my_person.get_contact()->get_contact2()
	   << "\nContact 3: " << my_person.get_contact()->get_contact3();
	return os;
}

//overloaded operator for << to display all the contents of a person
//Constructor for a contact
contact::contact(): contact1(NULL), contact2(NULL), contact3(NULL)
{
}

//Copy constructor for a contact
contact::contact(contact & a_contact)
{
	contact1 = new char[strlen(a_contact.contact1) + 1];
	strcpy(contact1, a_contact.contact1);
	contact2 = new char[strlen(a_contact.contact2) + 1];
	strcpy(contact2, a_contact.contact2);
	contact3 = new char[strlen(a_contact.contact3) + 1];
	strcpy(contact3, a_contact.contact3);
}

//Destructor for a contact
contact::~contact()
{
	if(contact1)
	{
		delete[] contact1;
	}
	if(contact2)
	{
		delete[] contact2;
	}
	if(contact3)
	{
		delete[] contact3;
	}
}

char * contact::get_contact1()
{
	return contact1;
}

char * contact::get_contact2()
{
	return contact2;
}

char * contact::get_contact3()
{
	return contact3;
}

//function to create a contact from information
void contact::create(char * a_contact1, char * a_contact2, char * a_contact3)
{
	if(contact1)
	{
		delete[] contact1;
	}
	contact1 = new char[strlen(a_contact1) + 1];
	strcpy(contact1, a_contact1);

	if(contact2)
	{
		delete[] contact2;
	}
	contact2 = new char[strlen(a_contact2) + 1];
	strcpy(contact2, a_contact2);

	if(contact3)
	{
		delete[] contact3;
	}
	contact3 = new char[strlen(a_contact3) + 1];
	strcpy(contact3, a_contact3);
}
