#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Node
{
private:
			//phoneticName;
	string pName;
	string nName;		//nickName;
	string phnNo;		//phoneNo;
	string mail	;		//e-mail
	string adrs;		//address
	string relation;
	
public:
	

//data pointers
	Node *next;
	Node *prev;
	//constructors
	Node();
	Node(string n, string no);
	Node(string n, string no, string phn, string mail, string adr, string rel);
	
	//getters
	string getName();
	string getPhoneNo();
	string getmail();
	string getadress();
	string getNickName();
	string getrelation();
	//setters
	void setName(string);
	void setPhone(string);
	void setMail(string);
	void setAdress(string);
	void setnickName(string);
	void setRelation(string);
	//opertaor overloading

	
	// functions
	char getNameLetter();
	void writeToFile(ofstream &out);
	


	void shareDetails(string s);
	

};

