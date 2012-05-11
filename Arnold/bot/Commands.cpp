/*		All Arnold function			*/
/*		Complete:1%					*/
/*		Author:B00st				*/

#include "Commands.h"
#include "log.h"

void help()		//print evry command to the terminal
{				//Complete:0%
	printf("\n");
	for(int i=0;i<10;i++)
		printf("help\n");
	Notice("Under development");
}
void mustang()	//all info about mustang :)
{				//Complete:0%
	/*I have to implement the web reading :) and download all info TO memory not to file as for now	*/
	printf("\n");
	for(int i=0;i<10;i++)
		printf("mustanginfo\n");
	Notice("Under development");
}
void game()		//Games
{				//Complete:0%
	/*I'm gonna make another place to games and this will be the main handler of games :)	*/
	printf("\n");
	printf("Place of Games!\n");
	Notice("Under development");
}
void calculator()	//Calculate evrything
{					//Complete:0%
	/*I have the formula but this will be one of the last things which im gonna made so bye a while	*/
	printf("\n");
	printf("I can calculate everything!\n");
	Notice("Under development");
}
void incorrect()	//If arnold doesnt know the command which the user typed
{					//Complete:20%
	printf("\n");
	printf("Incorrect Command!\n");
	Notice("Under development");
}
void exit()			//Shutdown the program with a bit elegance :)
{					//Complete:30%
	printf("Shut down");
	for(int j=0;j<3;j++)
	{
		std::cout << ".";
		Sleep(1000);
	}
	exit(1);
}
void colors()		//write 255 color to screen
{					//Complete:10%
	/*	I have to make a list which contains all the colors which this write to screen
	*	and store the list in the server
	*	!!!implement the web reader
	*/
	HANDLE hConsole;	//TODO:Make it independent from windows
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int k;
	for(k = 0; k < 255; k++)
	{
		SetConsoleTextAttribute(hConsole, k);
		printf("%3d %s\n", k, "I want to be nice today!");
	}
	SetConsoleTextAttribute(hConsole, DEFAULT);
	printf("\n\n");
}
void info()			//Information about me :)
{					//Complete:0%
	/*		ReWRITE			*/
	printf("\nMy revision is %d.\n", REV);
	printf("Written by ");
	WriteLine(DARK_GREEN, "B00st");
	printf("%s,%s\n",__DATE__, __TIME__);
}

void encrypt()		//MD5 hash
{					//Complete:75%
	/*		Must be rename the function		*/
	printf("What do you want to encrypt?\t");
	std::string what;
	std::cin >> what;
	std::string encrypted = md5(what);
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, YELLOW);
	printf("IN MD5:\t%s\n", encrypted);
	SetConsoleTextAttribute(hConsole, DEFAULT);
}
void fajl()		//remove file
{				//Complete:100%
	char * removable = "d:\\lol2.txt";
	remove(removable);
}
void web()		//web read with windows to file LoL
{				//Complete:150%
	/*		LOL MORE SIMPLE XD DAMN WINDOWS		*/
	char data[2048];
	URLDownloadToFile(NULL, "http://users.atw.hu/ascentemu/Emuk/lol.txt?atw_rnd=168741642", "d:\\lol2.txt", 0, NULL);
	
	URLDownloadToFile(NULL, "http://users.atw.hu/ascentemu/Emuk/AscentSVN.txt?atw_rnd=168741642", "d:\\lol3.txt", 0, NULL);
	FILE *fp = fopen("d:\\lol3.txt", "r");
	fgets(data, 2048, fp);
	printf("%s\n\n", data);
	fflush(fp);
	fclose(fp);
	URLDownloadToFile(NULL, "http://ajax.googleapis.com/ajax/services/search/web?v=1.0&start=0&rsz=small&q=ghostx", "d:\\text.txt", 0, NULL);
}
void red()		//write file word by word
{				//Complete:80%
	/*Must to implement a better way to work	*/
	std::ifstream input("d:\\text.txt");
	std::vector<std::string> v;
	int count = 0;
	while (input.good() && count < 1000)
	{
		std::string x;
		input >> x;
		v.push_back(x);
		count++;
	}
	input.close();
	std::vector<std::string>::iterator it;
	std::cout << "myvector contains:";
	for(it = v.begin(); it< v.end(); it++)
	{
		std::cout << " " << *it;
	}
	std::cout << "\n";
}
void sha()		//sha1 encrypt
{				//Complete:100%
	std::string text;
	std::cout << "what do you wanna to encrypt \t";
	std::cin >> text;
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, YELLOW);
	std::cout << "IN SHA1\t" << sha1(text) << std::endl;
	SetConsoleTextAttribute(hConsole, DEFAULT);
}


/*							WRITE THESE STUFFS BETTER							*/


/*int writer(char *data, size_t size, size_t nmemb, std::string *buffer)
{
        int result = NULL;

        // Is there anything in the buffer?
        if(buffer != NULL)
        {
                // Append the data to the buffer
                buffer->append(data, size * nmemb);

                // How much did we write?
                result = size * nmemb;
        }
        return result;
}*/
/*void web2(std::string text)
{
	CURL* curl;

	char eredmeny[550];
	_snprintf(eredmeny,550, "http://ajax.googleapis.com/ajax/services/search/web?v=1.0&start=0&rsz=small&q=%s", text.c_str());
	curl = curl_easy_init();
	if(curl)
    {
		std::string bufferdata;
		curl_easy_setopt(curl, CURLOPT_URL, eredmeny);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &bufferdata);
		CURLcode result = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if(result == CURLE_OK)
		{
			boost::regex re("(\\\"unescapedUrl\\\"):\\\"(?<url>\\S+)\\\",\\\"url\\\"");
			boost::cmatch matches;
			boost::regex_search(bufferdata.c_str(), matches, re);
			std::string matched(matches[2].first, matches[2].second);
			WriteLine(DARK_YELLOW,matched);
		}
		else
		{
			Notice("Hiba a Http lekerdezesben.");
			printf("Hibás találat");
		}
	}

}
void fordit(std::string lang, std::string text)
{
		char URL[700];
		_snprintf(URL, 700, "http://ajax.googleapis.com/ajax/services/language/translate?v=1.0&q=%s&langpair=%s", text.c_str(), lang.c_str());
		CURL* curl;
		curl = curl_easy_init();
		if(curl)
		{
			std::string buffer;

			curl_easy_setopt(curl, CURLOPT_URL, URL);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
			CURLcode result = curl_easy_perform(curl);
			curl_easy_cleanup(curl);
			if(result == CURLE_OK)
			{
				boost::regex search("(\\{.translatedText.:.(?<txt>.+).\\},\\s)");
				boost::cmatch match;

				boost::regex_search(buffer.c_str(), match, search);
				std::string matched(match[2].first, match[2].second);
				char trans[600];
				_snprintf(trans, 600, "Translated to:\t%s\t this:%s", lang.c_str(), text.c_str());
				WriteLine(CYAN,trans); 
				WriteLine(CYAN,matched);
			}
			else
			{
				Error("ERROR");
			}
		
		}

}*/


