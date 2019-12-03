#include "List.h"
#include <ctime>


HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // used for goto
COORD CursorPosition; // used for goto
HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
list <Node*>results;
list <Node *>::iterator resultsIter;

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
	gotoXY(95, 8); cout << "* More Options";
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
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		gotoXY(y, x); cout << "  ";
		x = 17; y = 13;

		gotoXY(y, x); cout << "=>";
		menu_item = 6;
	}


	if (GetAsyncKeyState(VK_UP) && (x != 5) && y != 43) //up button pressed
	{
		gotoXY(y, x); cout << "  ";
		x = x - 2;
		gotoXY(y, x); cout << "=>";
		menu_item--;
		continue;
	}

	if (GetAsyncKeyState(VK_RETURN))
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

				
				insert(ptr);
				gotoXY(40, 20); cout << "Contact saved successfully !!";
				Sleep(1000);
				clearMenu();
				clearContacts();
				printMainMenuOptions();
				contact();
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
	int menu_item = 1;
	while (running)
	{	//		down=Y increase
		//towrds right =X increases

	 // the >nul bit causes it the print no message
		system("pause>nul");
		if (GetAsyncKeyState(VK_DOWN) && x != (results.size()+6)) 
		{
			gotoXY(y, x); cout << "  ";
			x++;
			gotoXY(y, x); cout << "=>";
			menu_item++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && x != 7) //up button pressed
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



		if (GetAsyncKeyState(VK_RETURN))
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
				gotoXY(70, 15); cout << "MEnU item is" << menu_item;
				list <Node*>::iterator it;
				int n = 0;
				for (resultsIter = results.begin(); resultsIter != results.end(); resultsIter++)
				{
					n++;
					if (n == menu_item)
					{
						gotoXY(70, 10); cout << (*resultsIter)->getName() << endl;//
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

	//gotoXY(80, 5); 

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

	Node *ptr = new Node();
	ptr->setName(rptr->getName());
	ptr->setAdress(rptr->getadress());
	ptr->setMail(rptr->getmail());
	ptr->setnickName(rptr->getNickName());
	ptr->setPhone(rptr->getPhoneNo());
	ptr->setRelation(rptr->getrelation());



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
		if (GetAsyncKeyState(VK_DOWN) && x != 17) //down button pressed:17
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
			//gotoXY(13, 17); cout << "  ";
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

		if (GetAsyncKeyState(VK_RETURN))
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

					deleteContact(rptr);
					insert(ptr);
					gotoXY(40, 20); cout << "Contact saved successfully !!";
					Sleep(1000);
					clearMenu();
					clearContacts();
					printMainMenuOptions();
					contact();
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





void List::printDetails(int n)
{
	Node *rptr = head;
	for (int i = 0; i < n; i++)
	{
		rptr = rptr->next;
	}

	gotoXY(15, 5); cout << setw(20) << left << "Phonetic Name    " << rptr->getName();//each length 0f 18
	gotoXY(15, 7); cout << setw(20) << left << "Contatc Number   " << rptr->getPhoneNo();
	gotoXY(15, 9); cout << setw(20) << left << "Nick Name        " << rptr->getNickName();
	gotoXY(15, 11); cout << setw(20) << left << "E-mail Address   " << rptr->getmail();
	gotoXY(15, 13); cout << setw(20) << left << "House Address    " << rptr->getadress();
	gotoXY(15, 15); cout << setw(20) << left << "Relationship     " << rptr->getrelation();

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
	{	//		down=Y increase
		//towrds right =X increases

	 // the >nul bit causes it the print no message
		system("pause>nul");
		if (GetAsyncKeyState(VK_DOWN) && x != 9) //down button pressed:17
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
		
		if (GetAsyncKeyState(VK_RETURN))
		{
			switch (menu_item) {//for exit make running=false

			case 0: {
				gotoXY(93, 5); cout << "  ";
				// making new node copy
			

				
				UpdateContact(rptr);
				break;
					}


			case 1: {
				deleteContact(rptr);
				gotoXY(85, 20); cout << "Contact Deleted Successfully...";
				Sleep(1000);
				gotoXY(85, 20); cout << "                                ";
				clearContacts();
				clearMenu();
				printMainMenuOptions();
				contact();


				break;
			}

			case 2: {
				
				break;
			}

			case 3: {
				
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
		}

		if (GetAsyncKeyState(VK_RETURN))
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
				gotoXY(20, 16);
				cout << "You chose Option 1     ";
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

			case 3: {
				gotoXY(20, 16);
				cout << "You chose Option 3     ";
				break;
			}
			}
		}



	}








}

void List::printContacts()
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

		if (GetAsyncKeyState(VK_RETURN)) { // Enter key pressed

			clearContacts();

			

			printDetails(menu_item);

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

void List::gotoXY(int x, int y)
{

	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);

}


List::~List()
{
}
class searchResults
{




};