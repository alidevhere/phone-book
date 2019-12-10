#include "List.h"
#include <ctime>


HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // used for goto
COORD CursorPosition; // used for goto
HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
list <Node*>results;
list <Node *>::iterator resultsIter;
List favorites;

List::List()
{
	head = current = tail = NULL;
	count = 0;
}

List::List(Node * ptr)
{
	head= current = ptr;
	count = 1;
	tail = NULL;
		
}

void List::print()
{
	Node *rptr = head;
	
	while (rptr)
	{
		
		cout << rptr->getName() << endl;
		cout << rptr->getPhoneNo() << endl;
		rptr = rptr->next;
	}
}

void List::insert(Node *& ptr)
{
	//first node in list
	//frontNode 
	//last node
	//middle
	

	
	if (!head)//first node in list
	{
		ptr->next = ptr->prev = NULL;
		current=head = ptr;
		tail = NULL;
		count = 1;

	}
	else
	{
		if (ptr->getNameLetter() <= head->getNameLetter())//make new node the front node
		{
			ptr->next = head;
			ptr->prev = NULL;
			head->prev = ptr;
			current=head = ptr;
		}
		else
		{
			setTail();

			if (tail&&(ptr->getNameLetter() >= tail->getNameLetter()))//insert at last 
			{
				tail->next = ptr;
				ptr->next = NULL;
				ptr->prev = tail;
			}
			else
			{
				Node *rptr = head;
				while (rptr)
				{
					if (ptr->getNameLetter() >= rptr->getNameLetter()&&(ptr->getNameLetter()<=rptr->next->getNameLetter() ))
					{
						ptr->next = rptr->next;
						rptr->next = ptr;
						ptr->prev = rptr;
						ptr->next->prev = ptr;
						break;
					}
					rptr = rptr->next;
				}



			}


		}
		count++;
	}
	

}

void List::printMainMenuOptions()
{

	gotoXY(18, 5); cout << setw(30) << left << "Contact Names" << "   " << "Phone Numbers";
	gotoXY(18, 7); cout << "=>";

	gotoXY(95, 5); cout << "* Add New Contatct";
	gotoXY(95, 6); cout << "* Favorites";
	gotoXY(95, 7); cout << "* Search";
	gotoXY(95, 8); cout << "* Exit";
}

void List::addNew()
{
Node *ptr = new Node();

gotoXY(13, 5); cout << "=>";
gotoXY(15, 17); cout << "( SAVE )";
gotoXY(45, 17); cout << "( BACK )";

bool running = true;
int x = 5, y = 13;



int menu_item = 0;
while (running)
{	//		down=Y increase
	//towrds right =X increases

 // the >nul bit causes it the print no message
	system("pause>nul");
	if (GetAsyncKeyState(VK_DOWN) && x != 17) //down button pressed:17
	{
		gotoXY(y, x); cout << "  ";
		x = x + 2;
		gotoXY(y, x); cout << "=>";
		menu_item++;

		continue;

	}

	if (GetAsyncKeyState(VK_RIGHT))
	{

		gotoXY(y, x); cout << "  ";
		//gotoXY(13, 17); cout << "  ";
		y = 43; x = 17;
		gotoXY(y, x); cout << "=>";
		menu_item = 7;
		continue;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		gotoXY(y, x); cout << "  ";
		x = 17; y = 13;

		gotoXY(y, x); cout << "=>";
		menu_item = 6;
		continue;
	}


	if (GetAsyncKeyState(VK_UP) && (x != 5) && y != 43) //up button pressed
	{
		gotoXY(y, x); cout << "  ";
		x = x - 2;
		gotoXY(y, x); cout << "=>";
		menu_item--;
		continue;
	}

	if (GetAsyncKeyState(VK_RETURN)<0)
	{
		//changes being made in copy
		string n;
		switch (menu_item) {


		case 0: {
			gotoXY(33, 5); cout << "                   ";

			gotoXY(33, 5); getline(cin, n);

			ptr->setName(n);
			break;
		}


		case 1: {
			gotoXY(33, 7); cout << "                   ";

			gotoXY(33, 7); getline(cin, n);
			ptr->setPhone(n);
			break;
		}

		case 2: {
			gotoXY(33, 9); cout << "                   ";

			gotoXY(33, 9); getline(cin, n);
			ptr->setnickName(n);
			break;
		}

		case 3: {
			gotoXY(33, 11); cout << "                   ";

			gotoXY(33, 11); getline(cin, n);
			ptr->setMail(n);
			break;
		}

		case 4: {
			gotoXY(33, 13); cout << "                   ";

			gotoXY(33, 13); getline(cin, n);
			ptr->setAdress(n);
			break;
		}


		case 5: {
			gotoXY(33, 15); cout << "                   ";

			gotoXY(33, 15); getline(cin, n);
			ptr->setRelation(n);
			break;
		}
		case 6: {

			if ((ptr->getName() != "0") && (ptr->getPhoneNo() != "0"))
			{
				if (!isFound(ptr->getName()))
				{

					insert(ptr);
					ofstream out;
					out.open("contacts.txt");
					saveContactsToFile(out);
					gotoXY(40, 20); cout << "Contact saved successfully !!";
					Sleep(1000);
					clearMenu();
					clearContacts();
					printMainMenuOptions();
					contact();
				}
				else {
					gotoXY(15, 20); cout << "This name already exists please change the name";
					Sleep(2000);
					gotoXY(15, 20); cout << "                                                ";
				}
			}
			else
			{
				gotoXY(35, 20); cout << "Please fill at Least name and phone number";
				Sleep(2000);
				gotoXY(35, 20); cout << "                                          ";
			}
			break;

		}
		case 7: {
			clearContacts();
			printMainMenuOptions();
			contact();

			break;
		}

		}




	}
}

	
}

void List::search(string s)
{
	bool flag = true;
	int x = 7, y = 18;
	gotoXY(18, 5); cout << setw(30) << left << "Contact Names" << "   " << "Phone Numbers";
	Node *rptr = head;
	
	results.clear();
	for (int i = 1; i <= count; i++)
	{ 
		
		
		if (substring(rptr->getName(), s.length()) == s)
		{
			gotoXY(y, x); cout << setw(30) << left << rptr->getName() << "    " << rptr->getPhoneNo();
			results.push_back(rptr);
			x++;
			flag = false;
		}
		
			rptr = rptr->next;
	}

	

	if (flag)
	{
		gotoXY(25, 8); cout << setw(30) << "No Contatcs Found";
		Sleep(1000);
		clearMenu();
		clearContacts();
		printContacts();
		printMainMenuOptions();
		gotoXY(18, 7); cout << "  ";
		Menu();
	}

}

void List::searchControls()//after searching contats control is trnasfered to this function
{
	gotoXY(16, 7); cout << "=>";
	gotoXY(87, 10); cout << "BACK";
	int x=7, y=16;

	bool running = true;
	unsigned int menu_item = 1;
	while (running)
	{	

		system("pause>nul");
		if (GetAsyncKeyState(VK_DOWN) && x != (results.size()+6)&& y != 85)
		{
			gotoXY(y, x); cout << "  ";
			x++;
			gotoXY(y, x); cout << "=>";
			menu_item++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && x != 7&& y!=85) //up button pressed
		{
			gotoXY(y, x); cout << "  ";
			x--;
			gotoXY(y, x); cout << "=>";
			menu_item--;
			continue;
		}

		if (GetAsyncKeyState(VK_LEFT))
		{

			gotoXY(y, x); cout << "  ";
			y = 16; x = 7;
			gotoXY(16, 7); cout << "=>";
			menu_item = 1;
			continue;
		}

		if (GetAsyncKeyState(VK_RIGHT))
		{
			
			gotoXY(y, x); cout << "  ";
			y = 85, x = 10;
			gotoXY(85, 10); cout << "=>";
			menu_item = 0;
			continue;
		}



		if (GetAsyncKeyState(VK_RETURN)<0)
		{
			switch (menu_item)
			{

			case 0:
			{
				clearMenu();
				clearContacts();
				printContacts();
				printMainMenuOptions();
				gotoXY(18, 7); cout << "  ";
				Menu();
				break;
	
			}
			
			default :
			{
				list <Node*>::iterator it;
				int n = 0;
				for (resultsIter = results.begin(); resultsIter != results.end(); resultsIter++)
				{
					n++;
					if (n == menu_item)
					{
						clearContacts();
						printContactDetails(*resultsIter);
						printDetails(*resultsIter);
	
					}
				}
				
				break;
			
			}

			

		
			}

			
		}
	}

}

void List::clearContacts()
{
	
	for (int x = 4; x < 30; x++)
	{
		for (int y = 2; y <80 ; y=y+2)
		{
			gotoXY(y, x); cout << "  ";
		}
	}

}


void List::clearMenu()
{

	for (int x = 5; x < 25; x++)
	{

		for (int y = 82; y < 118; y = y+6)
		{
			gotoXY(y, x); cout << "      ";
		}
	}

}

void List::UpdateContact(Node *&rptr)
{
	//making copy

	Node *ptr = rptr->copy();
		/**
		new Node();
	ptr->setName(rptr->getName());
	ptr->setAdress(rptr->getadress());
	ptr->setMail(rptr->getmail());
	ptr->setnickName(rptr->getNickName());
	ptr->setPhone(rptr->getPhoneNo());
	ptr->setRelation(rptr->getrelation());
	*/


	gotoXY(13, 5); cout << "=>";
	gotoXY(15, 17); cout << "( SAVE )";
	gotoXY(45, 17); cout << "( BACK )";

	bool running = true;
	int x=5, y=13;
	


	int menu_item = 0;
	while (running)
	{	//		down=Y increase
		//towrds right =X increases

	 // the >nul bit causes it the print no message
		system("pause>nul");
		if (GetAsyncKeyState(VK_DOWN) && x != 17) 
		{
			gotoXY(y, x); cout << "  ";
			x=x+2;
			gotoXY(y, x); cout << "=>";
			menu_item++;

			continue;

		}

		if (GetAsyncKeyState(VK_RIGHT))
		{

			gotoXY(y, x); cout << "  ";
			y = 43; x = 17;
			gotoXY(y, x); cout << "=>";
			menu_item = 7;
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			gotoXY(y, x); cout << "  ";
			x = 17; y = 13;
		
			gotoXY(y, x); cout << "=>";
			menu_item = 6;
		}


		if (GetAsyncKeyState(VK_UP) &&( x != 5)&&  y!=43) //up button pressed
		{
			gotoXY(y, x); cout << "  ";
			x = x - 2;
			gotoXY(y, x); cout << "=>";
			menu_item--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN)<0)
		{
			//changes being made in copy
			string n;
			switch (menu_item) {


			case 0: {
				gotoXY(33, 5); cout << "                   ";
				
				gotoXY(33, 5); getline(cin, n);
			
				ptr->setName(n);
				break;
			}


			case 1: {
				gotoXY(33, 7); cout << "                   ";
				
				gotoXY(33, 7); getline(cin, n);
				ptr->setPhone(n);
				break;
			}

			case 2: {
				gotoXY(33, 9); cout << "                   ";
			
				gotoXY(33, 9); getline(cin, n);
				ptr->setnickName(n);
				break;
			}

			case 3: {
				gotoXY(33, 11); cout << "                   ";
			
				gotoXY(33, 11); getline(cin, n);
				ptr->setMail(n);
				break;
			}

			case 4: {
				gotoXY(33, 13); cout << "                   ";
			
				gotoXY(33, 13); getline(cin, n);
				ptr->setAdress(n);
				break;
			}


			case 5: {
				gotoXY(33, 15); cout << "                   ";
			
				gotoXY(33, 15); getline(cin, n);
				ptr->setRelation(n);
				break;
			}
			case 6: {
			
				if (( ptr->getName()!="0" )&& (ptr->getPhoneNo()!="0") )
				{
					if (!rptr->isSame(ptr))
					{	
						if (favorites.isFound(rptr->getName()))//if this contact also exists in favorites list 
						{										//then also update it their
							Node *fvr=favorites.isFoundAt(rptr->getName());
							favorites.deleteContact(fvr);
							Node *f=ptr->copy();
							favorites.insert(f);
							ofstream favOut;
							favOut.open("favorites.txt");
							favorites.saveContactsToFile(favOut);
							favOut.close();
						}
						
					deleteContact(rptr);
					insert(ptr);
					ofstream out;
					out.open("contacts.txt");
					saveContactsToFile(out);
					gotoXY(40, 20); cout << "Contact saved successfully !!";
					Sleep(1000);
					clearMenu();
					clearContacts();
					printMainMenuOptions();
					contact();
					}else 
					{
						gotoXY(13, 20); cout << "same data credentials as previous :not updated";
						Sleep(2000);
						gotoXY(13, 20);cout<< "                                                                ";
					}
				}
				else
				{
					gotoXY(35, 20); cout << "Please fill at Least name and phone number";
					Sleep(2000);
					gotoXY(35, 20); cout << "                                          ";
				}
				break;

			}
			case 7: {
				clearContacts();
				printMainMenuOptions();
				contact();

				break;
			}

			}

			


		}
	}


}

void List::deleteContact(Node *&ptr)
{
	if (ptr->next&&ptr->prev) //middle node
	{
		ptr->prev->next = ptr->next;
		ptr->next->prev = ptr->prev;
		
	}
	else
	{
		if (ptr->next == NULL)//last node
		{
			if (count==1)//last and only node :after its deletion list will be empty
			{
				current=tail=head = NULL;
				count = 0;
				
			}
			else
			{
				ptr->prev->next = NULL;
				ptr->prev = ptr->next = NULL;
			}



		}
		else
		{
			if (ptr->prev == NULL)//first node
			{
				head = ptr->next;
				ptr->next->prev = NULL;
				ptr->next = ptr->prev = NULL;
			}
		}


	}

	delete ptr;
	count--;

}

void List:: printContactDetails(Node *rptr)
{
	gotoXY(15, 5); cout << setw(20) << left << "Phonetic Name    " << rptr->getName();//each length 0f 18
	gotoXY(15, 7); cout << setw(20) << left << "Contatc Number   " << rptr->getPhoneNo();
	gotoXY(15, 9); cout << setw(20) << left << "Nick Name        " << rptr->getNickName();
	gotoXY(15, 11); cout << setw(20) << left << "E-mail Address   " << rptr->getmail();
	gotoXY(15, 13); cout << setw(20) << left << "House Address    " << rptr->getadress();
	gotoXY(15, 15); cout << setw(20) << left << "Relationship     " << rptr->getrelation();

}

void List::removeFromFav()
{


	clearMenu();
	gotoXY(95, 5); cout << "* Back";
	gotoXY(16, 7); cout << "=>";
	int x = 7, y = 16;
	int menu_item = 1;
	bool running = true;
	while (running)
	{
		system("pause>nul");

		if (GetAsyncKeyState(VK_DOWN) && x != (favorites.count + 6) && x != 5 && y != 93)
		{
			gotoXY(y, x); cout << "  ";
			x++;
			gotoXY(y, x); cout << "=>";
			menu_item++;
			continue;

		}



		if (GetAsyncKeyState(VK_UP) && x != 7 && x != 5 && y != 93)
		{
			gotoXY(y, x); cout << "  ";
			x--;
			gotoXY(y, x); cout << "=>";
			menu_item--;
			continue;
		}

		if (GetAsyncKeyState(VK_LEFT))
		{

			gotoXY(y, x); cout << "  ";
			y = 16; x = 7;
			gotoXY(16, 7); cout << "=>";
			menu_item = 1;

		}
		if (GetAsyncKeyState(VK_RIGHT))
		{

			gotoXY(y, x); cout << "  ";
			x = 5; y = 93;
			gotoXY(y, x); cout << "=>";
			menu_item = 0;

		}

		if (GetAsyncKeyState(VK_RETURN)<0)
		{
			switch (menu_item)
			{
			case 0://back option in removing from favorites
			{
				clearMenu();
				clearContacts();
				printFavorites();
				
			break;
			}
			default:
			{
				
				Node *rptr=favorites.head;
				for (int i=1;i<=favorites.count;i++)
				{
					if (i == menu_item) { break; }
					rptr = rptr->next;
				}
				
				favorites.deleteContact(rptr);
				gotoXY(85, 20); cout << "Contact removed from favorites";
				ofstream out("favorites.txt");
				favorites.saveContactsToFile(out);
				Sleep(3000);
				clearMenu();
				clearContacts();
				printFavorites();
				break;

			}


			}

		}

	}

}


void List::printDetails(Node *rptr)
{
	
	printContactDetails(rptr);

	//add controls for this menu
	clearMenu();

	gotoXY(95, 5); cout << setw(20) << left << "* Update";
	gotoXY(95, 6); cout << setw(20) << left << "* Delete";
	gotoXY(95, 7); cout << setw(20) << left << "* Add to Favorites";//to remove favorites go to favorites
	gotoXY(95, 8); cout << setw(20) << left << "* Share";
	gotoXY(95, 9); cout << setw(20) << left << "* Back";

	bool running = true;
	int x = 5, y = 93;
	gotoXY(y, x); cout << "=>";
	

	
	int menu_item = 0;
	while (running)
	{	
		system("pause>nul");
		if (GetAsyncKeyState(VK_DOWN) && x != 9) 
		{
			gotoXY(y, x); cout << "  ";
			x++;
			gotoXY(y, x); cout << "=>";
			menu_item++;

			continue;

		}

		if (GetAsyncKeyState(VK_UP) && x != 5) //up button pressed
		{
			gotoXY(y, x); cout << "  ";
			x--;
			gotoXY(y, x); cout << "=>";
			menu_item--;
			continue;
		}
		
		if (GetAsyncKeyState(VK_RETURN)<0)
		{
			switch (menu_item) {

			case 0: {//update
				
					gotoXY(93, 5); cout << "  ";
					UpdateContact(rptr);
				break;
					}


			case 1: {

				deleteContact(rptr);
				ofstream out;
				out.open("contacts.txt");
				saveContactsToFile(out);
				gotoXY(85, 20); cout << "Contact Deleted Successfully...";
				Sleep(1000);
				gotoXY(85, 20); cout << "                                ";
				clearContacts();
				clearMenu();
				printMainMenuOptions();

				contact();
				break;
			}

			case 2: {//add to favorite
				if (!favorites.isFound(rptr->getName()))
				{
					Node *fav = new Node(rptr->getName(), rptr->getPhoneNo(),
						rptr->getNickName(), rptr->getmail(),
						rptr->getadress(), rptr->getrelation());
					favorites.insert(fav);
					ofstream out;
					out.open("favorites.txt");
					favorites.saveContactsToFile(out);
					gotoXY(85, 20); cout << "Contact Added to favorites";
					Sleep(1000);
					gotoXY(85, 20); cout << "                                ";
					clearContacts();
					clearMenu();
					printMainMenuOptions();
					contact();
				}
				else
				{
					gotoXY(30, 20); cout << "Contact is already added to favorites";
					Sleep(2000);
					gotoXY(30, 20); cout << "                                     ";
					clearContacts();
					clearMenu();
					printMainMenuOptions();
					contact();
				}
				break;
			}

			case 3: {// share
				
				gotoXY(15, 20); cout << "Details of this contact are saved in file 'share.txt'";
					gotoXY(15, 21);cout<<"you can share it with anyone ";
				rptr->shareDetails("share.txt");
				Sleep(3000);
				clearContacts();
				clearMenu();
				printMainMenuOptions();
				contact();
				
				break;
			}
			case 4: {

				clearMenu();
			clearContacts();
			//display headings
			gotoXY(18, 5); cout << setw(30) << left << "Contact Names" << "   " << "Phone Numbers";
			gotoXY(18, 7); cout << "=>";
			gotoXY(85, 20); cout << "                               ";
			printMainMenuOptions();
				contact();

				break;
			}

			}
		}





	}
}

//main menu options at right
void List::Menu()
{

	bool running = true;
	int x = 5, y = 93;

	gotoXY(y, x); cout << "=>";
	int menu_item = 0;
	while (running)
	{	//		down=Y increase
		//towrds right =X increases

	 // the >nul bit causes it the print no message
		system("pause>nul");
		if (GetAsyncKeyState(VK_DOWN) && x != 8) //down button pressed:17
		{
			gotoXY(y, x); cout << "  ";
			x++;
			gotoXY(y, x); cout << "=>";
			menu_item++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && x != 5) //up button pressed
		{
			gotoXY(y, x); cout << "  ";
			x--;
			gotoXY(y, x); cout << "=>";
			menu_item--;
			continue;
		}

		if (GetAsyncKeyState(VK_LEFT))
		{

			gotoXY(y, x); cout << "  ";
			gotoXY(18, 7); cout << "=>";
			contact();
			continue;//extra
		}

		if (GetAsyncKeyState(VK_RETURN)<0)
		{
			switch (menu_item) {//for exit make running=false

			case 0: {//add new contact
				clearContacts();
				gotoXY(15, 5); cout << setw(20) << left << "Phonetic Name    ";//each length 0f 18
				gotoXY(15, 7); cout << setw(20) << left << "Contatc Number   ";
				gotoXY(15, 9); cout << setw(20) << left << "Nick Name        ";
				gotoXY(15, 11); cout << setw(20) << left << "E-mail Address   ";
				gotoXY(15, 13); cout << setw(20) << left << "House Address    " ;
				gotoXY(15, 15); cout << setw(20) << left << "Relationship     " ;
				gotoXY(y, x); cout << "  ";
				addNew();

				break;
			}


			case 1: {//favorites
				
				clearContacts();
				printFavorites();
				break;
			}

			case 2: {//search
				string s;
				clearContacts();
				clearMenu();
				gotoXY(85, 5); cout << "Search :  ";
				getline(cin, s);
				search(s);
					searchControls();//make functio that records searched results
					//now control should be transfered to search controls
				break;
			}

			case 3: 
				exit(0);
				break;
			
			default:
			
				cout << "choose an option";
				Sleep(2000);

			}
		}



	}

}




void List::printContacts()
{
	if (count > 0)
	{
		Node *rptr = head;
		int XL = 7;
		for (int i = 0; i < count; i++)
		{
			gotoXY(20, XL);  cout << setw(30) << left << rptr->getName() << "       " << rptr->getPhoneNo();
			rptr = rptr->next;
			XL++;
		}
	}
	else
	{
		gotoXY(20, 7);  cout << "No contacts to display !!!";
	}
}

void List::saveContactsToFile(ofstream &out)//out.open(s, ios::app);
{
	out << this->count<<endl;
	Node *rptr = this->head;
	for (int i = 0; i < count; i++)
	{
		rptr->writeToFile(out);
		rptr = rptr->next;
	}

	out.close();

}

void List::loadContacts(string s)
{
	string buff,t;
	int count;
	ifstream in;
	in.open(s,ios::in);
	if (in.is_open())
	{
		getline(in, buff);
		count = stoi(buff);
	
		this->count = count;
		for (int i = 0; i < count; i++)
		{
			Node *ptr = new Node();

			getline(in, buff);
			ptr->setName(buff);
			


			getline(in, buff);
			ptr->setPhone(buff);
			

			getline(in, buff);
			ptr->setMail(buff);
			
			getline(in, buff);
			ptr->setAdress(buff);
			

			getline(in, buff);
			ptr->setRelation(buff);
			

			getline(in, buff);
			ptr->setnickName(buff);
			

			this->insert(ptr);

		}



		in.close();
	}
	else
	{

		cout << "ERRORR    could not load file 'contacts.txt'";
		system("pause");
	}
}



void List::printFavorites()
{
	gotoXY(18, 5); cout << setw(30) << left << "Contact Names" << "   " << "Phone Numbers";


	if(favorites.count>0)
	{
	Node *rptr = favorites.head;
	for (int i = 7; i < (favorites.count + 7); i++)
	{
		gotoXY(18, i); cout << setw(30) << left << rptr->getName() << "    " << rptr->getPhoneNo();
		rptr = rptr->next;
	}
	clearMenu();
	gotoXY(93, 5); cout << "=>";
	gotoXY(95, 5); cout << setw(20) << left << "* Remove";
	gotoXY(95, 6); cout << setw(20) << left << "* Back";

	int x = 5, y = 93;
	int menu_item = 0;
	bool running = true;
	while (running)
	{

		system("pause>nul");

		if (GetAsyncKeyState(VK_UP) && x != 5) //up button pressed
		{
			gotoXY(y, x); cout << "  ";
			x--;
			gotoXY(y, x); cout << "=>";
			menu_item--;
			continue;
		}
		if (GetAsyncKeyState(VK_DOWN) && x != 6)
		{
			gotoXY(y, x); cout << "  ";
			x++;
			gotoXY(y, x); cout << "=>";
			menu_item++;
			continue;

		}
		if (GetAsyncKeyState(VK_RETURN)<0)
		{

			switch (menu_item)
			{
			case 0://remove 
			{
				gotoXY(93, 5); cout << "  ";
				removeFromFav();
				break;
			}
			case 1:
			{
				clearMenu();
				clearContacts();

				printContacts();
				printMainMenuOptions();
				contact();
				break;
			}


			}

		}

	}

	}
	else {
		gotoXY(18, 10); cout << "No Favorite contacts to display";
		Sleep(2000);
		clearMenu();
		clearContacts();
		printMainMenuOptions();
		contact();
	}
}






void List::loadFav()
{
	favorites.loadContacts("favorites.txt");
}



void List::contact()
{

	int menu_item = 0, run, x = 7;
	bool running = true;
	int maxCursorValue = count+(x-1);

	printContacts();


	while (running)
	{	//		down=Y increase
		//towrds right =X increases

	 // the >nul bit causes it the print no message
	//	system("pause");
		system("pause>nul");
		if (GetAsyncKeyState(VK_DOWN) && x!= maxCursorValue)	// !=count) 
		{
			gotoXY(18, x); cout << "  ";
			x++;
			gotoXY(18, x); cout << "=>";
			menu_item++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && x != 7) //up button pressed
		{
			gotoXY(18, x); cout << "  ";
			x--;
			gotoXY(18, x); cout << "=>";
			menu_item--;
			continue;
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			gotoXY(18, x); cout << "  ";
			Menu();

		}

		if (GetAsyncKeyState(VK_RETURN)<0) { // Enter key pressed

			clearContacts();
			Node *rptr = head;
			for (int i = 0; i < menu_item; i++)
			{
				rptr = rptr->next;
			}
	printDetails(rptr);

		}

	}





}

void List::setTail()
{
	Node *rptr = head;
	while (rptr)
	{
		this->tail = rptr;
		rptr=rptr->next;
	}


}

string List::substring(string s,int n)
{
	string sub;
	for (int i = 0; i < n; i++)
	{
		sub = sub + s[i];
	}

	return sub;

}

bool List::isFound(string s)
{
	Node *rptr = this->head;
	while (rptr)
	{
		if (s == rptr->getName())
		{
			return true;
		}
		rptr = rptr->next;
	}
	return false;
}

Node *& List::isFoundAt(string s)
{
	Node *rptr = this->head;
	while (rptr)
	{
		if (s == rptr->getName())
		{
			return rptr;
		}
		rptr = rptr->next;
	}
	
}

void List::gotoXY(int x, int y)
{

	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);

}

void List::start()
{
	gotoXY(98, 2); cout << "MAIN MENU";
	gotoXY(36, 2);
	cout << "PHONE BOOK";

	gotoXY(80, 3); cout << "========================================";
	gotoXY(0, 3); cout << "========================================================================================";

	for (int i = 0; i < 30; i++)
	{
		gotoXY(80, i); cout << "||";
		gotoXY(0, i); cout << "||";

	}

	gotoXY(18, 5); cout << setw(30) << left << "Contact Names" << "   " << "Phone Numbers";
	gotoXY(18, 7); cout << "=>";

	gotoXY(95, 5); cout << "* Add New Contatct";
	gotoXY(95, 6); cout << "* Favorites";
	gotoXY(95, 7); cout << "* Search";
	gotoXY(95, 8); cout << "* Exit";


}
