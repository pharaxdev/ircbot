/*		Entering system				*/
/*		Complete:0%					*/
/*		Author:B00st				*/

#include "Login.h"
Account::Account(std::string Accname, std::string Accpass)
{
	logined = FALSE;
	name = new std::string(Accname);
	pass = new std::string(Accpass);
	CreateHash();
	if(!Check())
	{
		WriteLine(RED, "Login unsuccesful");
		logined = FALSE;
	}
	else
	{
		logined = TRUE;
		WriteLine(RED, "Succesful login.");
	}
}
Account::~Account()
{
	delete name;
	delete pass;
	delete hash;
}
void Account::Login()
{
	WriteLine(DARK_YELLOW, "Login\n");
}
void Account::CreateHash()
{
	std::string acc = (*name)+(*pass);
	hash = new std::string (md5(acc));
}
void Account::Update()
{
	Notice("I am looking for your data");
}
int writer(char *data, size_t size, size_t nmemb, std::string *buffer)
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
}
bool Account::Check()
{
	CURL* curl;

	char URL[300];
	_snprintf(URL,550, "http://users.atw.hu/ascentemu/Emuk/accteszt.txt?atw_rnd=168741642");
	curl = curl_easy_init();
	if(curl)
    {
		std::string data;
		curl_easy_setopt(curl, CURLOPT_URL, URL);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
		CURLcode result = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if(result == CURLE_OK)
		{
			if(data == *hash)
			{
				return 1;
			}
			else
				return 0;
		}
		else
		{
			Notice("Error in the HTML Module.");
			return 0;
		}
	}
}