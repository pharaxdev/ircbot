/*		Functions by B00st			*/
/*		Complete:0%					*/
/*		Author:B00st				*/
#include "ArnoldFunctions.h"
int writer2(char *data, size_t size, size_t nmemb, std::string *buffer)
{
        int result = NULL;
        if(buffer != NULL)
        {
                buffer->append(data, size * nmemb);
                result = size * nmemb;
        }
        return result;
}
void CacheToMemory()//(const char * preWeb/*, bool Exp, std::string anotherData*/)
{
	CURL* curl;
	char CWeb[1024];
	//if(Exp == FALSE)
	_snprintf(CWeb,1024,"http://ajax.googleapis.com/ajax/services/search/web?v=1.0&start=0&rsz=small&q=citromail");
	curl = curl_easy_init();
	if(curl)
	{
		std::string *buffer;
		curl_easy_setopt(curl, CURLOPT_URL, CWeb);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer2);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
		CURLcode result = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if(result == CURLE_OK)
		{
			boost::regex re("(\\\"unescapedUrl\\\"):\\\"(?<url>\\S+)\\\",\\\"url\\\"");
			boost::cmatch matches;
			boost::regex_search(buffer->c_str(), matches, re);
			std::string matched(matches[2].first, matches[2].second);
			printf("%s",matched.c_str());
			WriteLine(DARK_YELLOW,matched);
			//std::string Match = new std::string(matched);
			//return matched;
		}
		else
		{	
			Notice("Hiba a Http lekerdezesben.");
			printf("Hibás találat");
			//return NULL;
		}
	}
}