#include "Node.h"



Node::Node():prev(NULL),next(NULL)
{
	 pName="0";
	 nName= "0";
	 phnNo= "0";
	 mail = "0";
	 adrs = "0";
	 relation = "0";
}

Node::Node(string n, string no):prev(NULL),next(NULL)
{
	pName = n;
	nName = "0";
	phnNo = no;
	mail = "0";
	adrs = "0";
	relation = "0";
}

Node::Node(string n, string no, string phn, string mail, string adr, string rel):prev(NULL),next(NULL)
{
	pName = n;
	nName = phn;
	phnNo = no;
	this->mail = mail;
	this->adrs =adr;
	relation = rel;
}

string Node::getName()
{
	return pName;
}

string Node::getPhoneNo()
{
	return phnNo;
}

string Node::getmail()
{
	return mail;
}

string Node::getadress()
{
	return adrs;
}

string Node::getNickName()
{
	return nName;
}

string Node::getrelation()
{
	return relation;
}

void Node::setName(string n)
{
	pName = n;
}

void Node::setPhone(string n)
{
	phnNo = n;
}

void Node::setMail(string n)
{
	mail = n;
}

void Node::setAdress(string n)
{
	adrs = n;
}

void Node::setnickName(string n)
{
	nName = n;
}

void Node::setRelation(string n)
{
	relation = n;
}

char Node::getNameLetter()
{
	return pName[0];
}


