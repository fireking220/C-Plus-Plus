/*Scott Patterson
CS202
Program 3
This program will build a binary search tree where each node has a linear linked
list of people with contacts. In this program we will overload different operators
including =,+,+=,==,!=,<,<=,>,>=,<<, and >>*/

#include <iostream>
#include "BST.h"
using namespace std;

const int SZ = 100;

int main()
{
	char choice = ' ';
	char f_name[SZ];
	char l_name[SZ];
	char contact1[SZ];
	char contact2[SZ];
	char contact3[SZ];
	person a_person;
	contact a_contact;
	BST a_BST;

	do
	{
		cout << "Emergency Broadcast System!\n"
		     << "a)Add person to system\n"
		     << "b)Display all contacts\n"
		     << "q)Quit\n";
		cin >> choice;
		choice = toupper(choice);
		cin.ignore(100, '\n');

		switch(choice)
		{
			case 'A': cout << "Enter the person's first name: ";
			cin.get(f_name, SZ, '\n');
			cin.ignore(SZ, '\n');
			cout << "\nEnter the person's last name: ";
			cin.get(l_name, SZ, '\n');
			cin.ignore(SZ, '\n');
			cout << "\nEnter the first contact: ";
			cin.get(contact1, SZ, '\n');
			cin.ignore(SZ, '\n');
			cout << "\nEnter the second contact: ";
			cin.get(contact2, SZ, '\n');
			cin.ignore(SZ, '\n');
			cout << "\nEnter the third contact: ";
			cin.get(contact3, SZ, '\n');
			cin.ignore(SZ, '\n');
			a_contact.create(contact1, contact2, contact3); //creates contact
			a_person.create(f_name, l_name, a_contact); //creates person
			cout << "Adding contact...";
			a_BST += a_person; //operator overload adds the person to our BST and returns the same BST by reference
			break;
		
			case 'B': cout << "Displaying entire emergency contact list...\n";
			if(a_BST != NULL)
			{
				cout << "ERROR, NO EMERGENCY CONTACTS\n\n";
			}
			else
			{
				a_BST.display_all();
			}
			break;

			case 'Q': cout << "Quitting...\n\n";
			break;

			default: cout << "Please enter a valid choice...\n\n";
			break;
		}	
	}while(choice != 'Q');
}
