#include"List.h"

int  main()
{
	List fav;
	
	Node *ptr1 = new Node("ali","023456789");
	List lis;
	lis.insert(ptr1);
	ptr1 = new Node("salman", "45678765");
	lis.insert(ptr1);
	ptr1 = new Node("arbaz", "030456789056");
	lis.insert(ptr1);
	
	//88888888888888888888888888888888888888888888888888888888888888888888

	system("color a");

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
	lis.gotoXY(95, 8); cout << "* More Options";
	lis.contact();
	

	_getch();
	system("pause");
	return 0;
}