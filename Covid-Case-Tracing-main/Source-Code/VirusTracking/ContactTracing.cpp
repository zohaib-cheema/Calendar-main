//============================================================================
// Name        : ContactTracing.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include "Contact.h"
#include <cstring>

using namespace std;

map<string, vector<Contact*>*> tracer;

void addContact(string name, Contact* contact)
{
	int count = 0;
	map<string, vector<Contact*>*>  :: iterator itr;
	
	for(itr = tracer.begin(); itr != tracer.end(); ++itr)
	{
		if(itr->first == name)
		{
			itr->second->push_back(contact);
			count++;
			break;
		}
	}
	
	if(count == 0)
	{
		vector<Contact*>* newContact = new vector<Contact*>;
		newContact->push_back(contact);
		tracer.insert(std::pair<string, vector<Contact*>*>(name, newContact));
	}
}

void inputContact()
{
	ifstream fin;
	fin.open("contacts.csv", ios::in);
	
//	if(!fin.is_open()) throw std::runtime_error("Could not open file");
	
	vector<string> row;
	string line, word;
	
	while(!fin.eof())
	{
		row.clear();
		getline(fin, line);
		stringstream s(line);
		
		while(getline(s, word, ','))
		{
			row.push_back(word);
		}
		
		string name = row[0];
		Contact* contact = new Contact(row[1], row[2], row[3]);
		Contact* otherContact = new Contact(name, row[2], row[3]);
		addContact(name, contact);
		addContact(row[1], otherContact);
	}
}

void editContact(string name, Contact* contact)
{

}

//string convertToString(char* a, int size)
//{
//	int i;
//	string s = "";
//	for(i = 0; i<size; i++)
//	{
//		s = s + a[i];
//	}
//	return s;
//}

void printReport(string name) //
{
	bool present = false;
	map<string, vector<Contact*>*>  :: iterator itr;
	
	for(itr = tracer.begin(); itr != tracer.end(); ++itr)
	{
		if(itr->first == name)
		{
			cout << "----------------------------" << endl;
			cout << "*** REPORT ***" << endl;
			cout << "Name: " << name << endl;
			cout << "Contacts: " << endl;
			vector<Contact*> :: iterator it;
			int i=1;
			for (it = itr->second->begin(); it != itr->second->end(); ++it)
			{
				cout << i << ". " << it[0]->contact << " - " << it[0]->location << " " << it[0]->time << endl;
				i++;
			}
			cout << "----------------------------" << endl;
			present = true;
			break;
		}
	}
	
	if(!present)
	{
		cout << "Name not found" << endl;
	}
}

int main()
{
	string name;
	string contact;
	string location;
	string time;
	char cont;
	int choice;

	fstream fout;
	fout.open("contacts.csv", ios::out | ios::app);
	ifstream read("contacts.csv");
	
	if(read.peek() == EOF)
	{
		fout << "Name" << "," << "Contact" << "," << "Location" << "," << "Time" << "\n";
	}
	
	cout << "----------- WELCOME TO SUPERTRACE!!! -----------" << endl;

do
{
	tracer.clear();
	cout << "1. Add entry" << endl;
	cout << "2. Remove entry" << endl;
	cout << "3. Edit entry" << endl;
	cout << "4. Print report" << endl;
	cout << "5. Reset database" << endl;
	cin >> choice;


	switch(choice)
	{
			
	case 1:
		{
			cout << "Enter name: ";
			cin >> name;
			cout << "Enter name of contact: ";
			cin >> contact;
			cout << "Enter location of contact: ";
			cin >> location;
			cout << "Enter time of contact: ";
			cin >> time;

			fout << name << ',' << contact << ',' << location << ',' << time << "\n";

			fout.close();

//			Contact* newContact = new Contact(contact, time, location);
//			Contact* otherContact = new Contact(name, time, location);
//			addContact(name, newContact);
//			addContact(contact, otherContact);

			break;
		}
			
	case 2:
		{
			cout << "Remove entry" << endl;
			break;
		}
			
	case 3:
		{
			cout << "Edit entry" << endl;
			break;
		}
			
	case 4:
		{
			inputContact();
			cout << "Enter name: ";
			cin >> name;
			printReport(name);
			break;
		}
			
	case 5:
		{
			remove("contacts.csv");
			cout << "Database deleted." << endl;
			break;
		}
			
	}
	
	cout << "Do you want to continue? (y or n) ";
	cin >> cont;
	cout << "\n";
	
}

//while(cont == 'y');

cout << "The program has ended.";
	
return 0;
}
