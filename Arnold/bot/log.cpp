/*		Arnold's message system		*/
/*		Complete:50%				*/
/*		Author:B00st				*/

//TODO:MAKE IT INDEPENDENT PLATFORM

#include "log.h"
void Log(std::string text)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, CYAN);
	std::cout << text << std::endl;
	SetConsoleTextAttribute(hConsole, DEFAULT);
}
void Notice(std::string text)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, YELLOW);
	std::cout << text << std::endl;
	SetConsoleTextAttribute(hConsole, DEFAULT);
}
void Error(std::string text)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, RED);
	std::cout << text << std::endl;
	SetConsoleTextAttribute(hConsole, DEFAULT);
}
void WriteLine(int COLOR, std::string text)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, COLOR);
	std::cout << text << std::endl;
	SetConsoleTextAttribute(hConsole, DEFAULT);
}
