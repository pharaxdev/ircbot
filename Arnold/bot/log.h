#include "stdafx.h"
#ifndef _LOG
#define _LOG
void Log(std::string);
void Error(std::string);
void Notice(std::string);
void WriteLine(int, std::string);
/*		COLORS		*/
// MADE IT TO ENUM
#define BLACK 0
#define DARK_BLUE 1
#define DARK_GREEN 2
#define DARK_CYAN 3
#define DARK_RED 4
#define DARK_PURPLE 5
#define DARK_YELLOW 6
#define DEFAULT 7
#define GREY 8
#define BLUE 9
#define GREEN 10
#define CYAN 11
#define RED 12
#define PURPLE 13
#define YELLOW 14
#define WHITE 15
#endif