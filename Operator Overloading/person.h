/*Scott Patterson
CS202
Program 3
person.h*/

#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class name
{
	public:
	name();
	name(name & a_name);
	~name();

	protected:
	char * f_name;
	char * l_name;
};

class person: public name
{
	public:
	person();
	person(person & a_person);
	~person();
	//method to create a person and populate it with data
	void create(char * a_f_name, char * a_l_name, class contact & a_contact);
	char * get_f_name();
	char * get_l_name();
	contact * get_contact();
	//operator overloads
	bool operator==(char * l_name);
	friend bool operator==(char * l_name, person &a_person);
	bool operator<(char * l_name);
	friend bool operator<(char * l_name, person & a_person);
	bool operator<=(char * l_name);
	friend bool operator<=(char * l_name, person & a_person);
	bool operator>(char * l_name);
	friend bool operator>(char * l_name, person & a_person);
	bool operator>=(char * l_name);
	friend bool operator>=(char * l_name, person & a_person);
	friend ostream& operator<<(ostream &os, person &my_person);

	protected:
	class contact * my_contact;
};

class contact
{
	public:
	contact();
	contact(contact & a_contact);
	~contact();
	char * get_contact1();
	char * get_contact2();
	char * get_contact3();
	//method to create a contact and populate it with data
	void create(char * a_contact1, char * a_contact2, char * a_contact3);

	protected:
	char * contact1;
	char * contact2;
	char * contact3;
};
