/*
 * Person.h
 *
 *  Created on: May 3, 2021
 *      Author: hangbui
 */


#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Contact
{
public:
	string contact;
	string time;
	string location;

	Contact(string contact, string time, string location)
	{
		this->contact = contact;
		this->time = time;
		this->location = location;
	}

	string toString()
	{
		return contact + "@" + time + "@" + location;
	}
	void addContact(string name, Contact* contact);
};
