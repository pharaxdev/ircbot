/* Schumix */

#include "StdAfx.h"
using namespace std;
CLog Log;

#ifdef WIN32
  static const char* config_file = "./schumix.conf";
#else
  static const char* config_file = CONFDIR "/schumix.conf";
#endif


int main()
{
	if(!Config.MainConfig.SetSource(config_file))
	{
		Log.Notice("Config", "Error a config fajl betoltesenel.");
	}

	printf("Schumix Verzio: %s\n", revision);
	printf("\n");
	printf("Keszitette Valroft, Megax es Scymex http://megaxx.info\n");
	printf("This program is licensed under the GNU Affero GPL.\n");
	printf("==============================================================================\n");
	printf("\n");
	Log.Notice("Schumix", "Starting up...\n");

#ifdef WIN32
	// WSA Setup
	WSADATA info;
	WSAStartup(MAKEWORD(2, 0), &info);
#endif

	std::string server = Config.MainConfig.GetStringDefault("IRC", "Server", "");
	uint32 port = Config.MainConfig.GetIntDefault("IRC", "Port", 6667);
	new IRCSession(server, port);
	
	return 0;
}

