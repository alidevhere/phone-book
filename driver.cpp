#include"List.h"

int  main()
{
	
	system("color a");
	List lis;
	lis.loadContacts("contacts.txt");
	lis.loadFav();
	lis.start();
	lis.contact();
	system("pause");
	return 0;
}