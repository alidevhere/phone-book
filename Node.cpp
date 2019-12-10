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

Node::Node(string n, string no, string nn, string mail, string adr, string rel):prev(NULL),next(NULL)
{
	pName = n;
	nName = nn;
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

void Node::writeToFile(ofstream &out)
{
	out << this->getName()<<endl;
	out << this->getPhoneNo() << endl;
	out << this->getmail() << endl;
	out << this->getadress() << endl;
	out << this->getrelation() << endl;
	out << this->getNickName() << endl;
}

bool Node::isSame(Node * ptr)
{
	if (this->getName() == ptr->getName() && this->getPhoneNo() == ptr->getPhoneNo() &&
		this->getadress() == ptr->getadress() && this->getNickName() == ptr->getNickName() &&
		this->getmail() == ptr->getmail() && this->getrelation() == this->getrelation())
	{
		return true;
	}
	else {
		return false;
	}
}

Node *& Node::copy()
{
	Node *ptr = new Node(this->getName(), this->getPhoneNo(), this->getNickName(), this->getmail(),
		this->getadress(), this->getrelation());
	return ptr;

}


void Node::shareDetails(string s)
{
	ofstream out;
	out.open(s);
	if(this->getName()!="0") out << this->getName() << endl;
	if (this->getPhoneNo() != "0")out << this->getPhoneNo() << endl;
	if (this->getrelation() != "0")out << this->getrelation();
	if (this->getadress() != "0")out << this->getadress() << endl;
	if (this->getmail() != "0")out << this->getmail();
	out.close();

}


