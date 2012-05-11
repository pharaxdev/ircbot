#include "stdafx.h"
#ifndef _LOGIN
#define _LOGIN
class Account
{
public:
	Account(std::string, std::string);
	~Account();
	void Login();
	void CreateHash();
	void Update();
	bool Check();
	bool getLogined() { return logined; };
private:
	std::string * name;
	std::string * pass;
	std::string * hash;
	bool logined;
	//std::string * level;
};
#endif