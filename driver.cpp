#include"List.h"

int  main()
{
	
	

	//fav.loadContacts("contacts.txt");
	//cout<<fav.count;
	//system("pause");
	
	/**
	Node *ptr1 = new Node("ali","023456789");
	List lis;
	
	lis.insert(ptr1);
	ptr1 = new Node("raza", "123456789");
	
	lis.insert(ptr1);
	ptr1 = new Node("arbaz", "030456789056");
	
	lis.insert(ptr1);
	lis.saveContactsToFile("contacts.txt");
	
	system("pause");
	/**

	//writing to file
	ofstream of;
	of.	open("node.bin", ios::app | ios::binary);
	of.seekp()
	ptr1->writeToFile(of);
	
	
	//reading from file

	system("pause");


	ifstream in;
	in.open("node.bin", ios::in | ios::binary);

	
	Node *ptr2 = new Node();
	Node *ptr3 = new Node();

	//cout << sizeof(ptr1->getName());
	//

	ptr2->readFromFile(in);
	cout << ptr2->getName() << "  " << ptr2->getPhoneNo();
	
	in.seekg(176, ios::cur);
	ptr3->readFromFile(in);
	cout << ptr3->getName() << "  " << ptr3->getPhoneNo();
	system("pause");

	
	*/


	//88888888888888888888888888888888888888888888888888888888888888888888

	system("color a");
	List lis;
	lis.loadContacts("contacts.txt");
	//system("pause");

	//cout<<lis.head->getName();
	//cout<<"phn is"<<lis.head->getPhoneNo();

	//system("pause");

	lis.gotoXY(98, 2); cout << "MAIN MENU";
	lis.gotoXY(36, 2);
	cout << "PHONE BOOK";
	
	lis.gotoXY(80, 3); cout << "========================================";
	lis.gotoXY(0, 3); cout << "========================================================================================";

	for (int i = 0; i < 30; i++)
	{
		lis.gotoXY(80, i); cout << "||";
		lis.gotoXY(0, i); cout << "||";

	}

	lis.gotoXY(18, 5); cout << setw(30) << left << "Contact Names" << "   " << "Phone Numbers";
	lis.gotoXY(18, 7); cout << "=>";

	lis.gotoXY(95, 5); cout << "* Add New Contatct";
	lis.gotoXY(95, 6); cout << "* Favorites";
	lis.gotoXY(95, 7); cout << "* Search";
	lis.gotoXY(95, 8); cout << "* Exit";
	lis.loadFav();
	lis.contact();
	


	system("pause");
	return 0;
}