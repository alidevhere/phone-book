#pragma once
#include"Node.h"
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include<iomanip>
#include<list>




class List
{
private:
	void setTail();
	string substring(string s, int n);
	bool isFound(string s,Node *head);//modify it second argument
	Node *& isFoundAt(string s);
public:
	
	int count;

	Node *head;
	Node *current;
	Node *tail;
	
	List();
	List(Node *ptr);
	void print();
	void insert(Node *&ptr);
	
	
	
	
	void clearContacts();
	void printDetails(Node *rptr);
	void clearMenu();

	void UpdateContact(Node *&ptr);
	void deleteContact(Node *&ptr);
	void printContactDetails(Node * rptr);
	void removeFromFav();
	void printMainMenuOptions();
	void addNew();
	void search(string s);
	void searchControls();
	void printContacts();

	void saveContactsToFile(ofstream &out);
	void loadContacts(string s);
	void printFavorites();
	void loadFav();
	void Menu();
	void contact();
	void gotoXY(int, int);
	
};

