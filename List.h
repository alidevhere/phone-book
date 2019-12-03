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
	void printDetails(int n);
	void clearMenu();

	void UpdateContact(Node *&ptr);
	void deleteContact(Node *&ptr);
	void printContactDetails(Node * rptr);
	void addToFavorite(List &fav,Node *&ptr);
	void printMainMenuOptions();
	void addNew();
	void search(string s);
	void searchControls();
	void printContacts();


	void Menu();
	void contact();
	void gotoXY(int, int);
	

	~List();
};

