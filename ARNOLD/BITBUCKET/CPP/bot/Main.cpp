/*		
*		Original Command listener
*		Complete:100%
*		Author:B00st
*/





/*#include "Commands.h"
#include "log.h"
void main()
{
	WriteLine(DARK_GREEN, "\t\t\t     Arnold is starting \t\t\t\n\n\n");
	Sleep(300);
	printf("Welcome here, please type any commands!\n");
	void (*choice) (void);
	std::string COMMAND;
	unsigned short int Space = 0;
	std::string *SubCMD;
	unsigned short int SpaceTwo = 0;
	std::string *SubSubCMD;
	while(1)
	{
		getline(std::cin,COMMAND);
/*				FiRST SPACE				*/
		/*Space = unsigned short int(COMMAND.find(' '));
		if(Space == NULL)
			Space = unsigned short int(COMMAND.length());
		if(Space > 0 && Space < 20)
		{
			SubCMD = new std::string (COMMAND.substr(Space+1));
		}
/*				2nd SPACE				*/
	/*	SpaceTwo = unsigned short int(SubCMD->find(' '));
		if(SpaceTwo == NULL)
			SpaceTwo = unsigned short int(SubCMD->length());
		if(SpaceTwo > 0 && SpaceTwo < 20)
		{
			SubSubCMD = new std::string (SubCMD->substr(SpaceTwo+1));
			//SubCMD->erase(SpaceTwo);
		}

		if(COMMAND == "help")
			choice=help;
		else if(COMMAND.substr(0,7) == "arnold,")
		{
			if(SubCMD->substr(0,3) == "for")
			{
				if(*SubSubCMD != "")
				{
					int szam;
					szam = atoi(SubSubCMD->c_str());
					for(int i = 0; i<szam;i++)
						std::cout << i<< "\t";
				}
			}
			else if(*SubCMD== "web")
				choice=web;
			else
				choice=info;
		}
		else if(COMMAND == "info")
			choice=info;
		else if(COMMAND == "exit")
		{
			choice=exit;
		}
		else if(COMMAND == "mustang")
			choice=mustang;
		else if(COMMAND == "game")
			choice=game;
		else if(COMMAND == "calculator")
			choice=calculator;
		else if(COMMAND == "color")
			choice=colors;
		else if(COMMAND.substr(0,7) == "encrypt")
		{
			if (SubCMD->substr(0,3) == "md5")
			{
				if(SubSubCMD !=NULL)
				{
					WriteLine(GREEN, "IN MD5\t");
					WriteLine(CYAN, md5(*SubSubCMD));
				}
				else
				choice=encrypt;
			}
			else if(SubCMD->substr(0,4) == "sha1")
			{
				if(SubSubCMD != NULL)
				{
					WriteLine(GREEN,"IN SHA1\t");
					WriteLine(CYAN, sha1(*SubSubCMD));
				}
				else
				choice=sha;
			}
			else
			{
				Error("Unknown Encrypting module");
			}
		}
		else if(COMMAND.substr(0,7) == "writeln")
		{
			WriteLine(CYAN, *SubCMD);
		}
		else if(COMMAND == "fajl")
			choice = fajl;
		else if(COMMAND == "web")
			choice=web;
		else if(COMMAND == "red")
			choice=red;
		else if(COMMAND == "Clean")
			system("cls");
		else if(COMMAND.substr(0,5) == "login")
		{
			std::string accname = *SubCMD;
			std::string accpass = *SubSubCMD;
			Account * newAcc = new Account(accname, accpass);
			printf("acckész");
			newAcc->Login();
			newAcc->Update();
			newAcc->Logout();
			printf("acc vege");
		}
		else if(COMMAND.substr(0,5) == "keres")
		{
			web2(*SubCMD);
		}
		else if(COMMAND.substr(0,9) == "translate")
				fordit(*SubCMD,*SubSubCMD);
		else
		{
			choice=incorrect;
		}
		
		if(choice != NULL)
			choice();
		choice = NULL;
		if(SubCMD!= NULL)
		delete SubCMD;
		if(SubSubCMD!=NULL)
		delete SubSubCMD;
		SubCMD = 0;
		SubSubCMD=0;
	}
}*/