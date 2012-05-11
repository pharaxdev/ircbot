#include "Commands.h"
#include "log.h"
#include "ArnoldFunctions.h"
void main()
{
	std::string name;
	std::string pass;
	std::cout << "Account name:\t\t" ;
	std::cin >> name;
	std::cout << std::endl << "Account password:\t";
	std::cin >> pass;
	std::cout << std::endl;
	Account * User = new Account(name,pass);
	Sleep(1000);
	if(!User->getLogined())
	{
		delete User;
		exit();
	}
	system("cls");
	std::cin >> pass;
}