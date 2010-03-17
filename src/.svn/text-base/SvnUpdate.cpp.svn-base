/* Schumix */

#include "StdAfx.h"

#ifdef SVN_RSS

DWORD WINAPI IRCSession::StartAscNHalf(LPVOID lpParam)
{
	RSS_XHANDLER* local = (RSS_XHANDLER*)lpParam;
	return ((static_cast<IRCSession*>(local->instance))->ThreadAscNHalf(local->rss));
}

DWORD WINAPI IRCSession::StartArcemu(LPVOID lpParam)
{
	RSS_XHANDLER* local = (RSS_XHANDLER*)lpParam;
	return ((static_cast<IRCSession*>(local->instance))->ThreadArcemu(local->rss));
}

DWORD WINAPI IRCSession::StartArcSripts(LPVOID lpParam)
{
	RSS_XHANDLER* local = (RSS_XHANDLER*)lpParam;
	return ((static_cast<IRCSession*>(local->instance))->ThreadArcSripts(local->rss));
}

DWORD IRCSession::ThreadAscNHalf(LPVOID lpItem)
{
	while(1)
	{
		AscSvn();

		if(AscRev != AscRev1)
		{
			AscNHalf();
		}

		AscSvn1();
		Lekerdezesi_ido;
	}
	return 0;
}

DWORD IRCSession::ThreadArcemu(LPVOID lpItem)
{
	while(1)
	{
		ArcSvn();

		if(ArcRev != ArcRev1)
		{
			Arcemu();
		}

		ArcSvn1();
		Lekerdezesi_ido;
	}
	return 0;
}

DWORD IRCSession::ThreadArcSripts(LPVOID lpItem)
{
	while(1)
	{
		ArcSSvn();

		if(ArcSRev != ArcSRev1)
		{
			ArcScripts();
		}

		ArcSSvn1();
		Lekerdezesi_ido;
	}
	return 0;
}

int IRCSession::getrfa(std::string title)
{
	pcre* re;
	const char* error;
	int erroffset;
	int ovector[30];

 	int rc;

	re = pcre_compile("^(\\S+\\s+\\[(\\d+)\\])", 0, &error, &erroffset, NULL);

	if(re == NULL)
	{
		printf("PCRE compilation failed at offset %d: %s\n", erroffset, error);
    	return 1;
	}

	rc = pcre_exec(re, NULL, title.c_str(), (int)strlen(title.c_str()), 0, 0, ovector, 30);

	if (rc < 0)
   	{
   		switch(rc)
     	{
     		case PCRE_ERROR_NOMATCH: /*printf("No match\n");*/ break; // blokolva mert sokszor nincs rev
     		/*
				Handle other special cases if you like
			*/
     		default: printf("Matching error %d\n", rc); break;
     	}

   		return 1;
	}

  		char *substring_start = const_cast<char*>(title.c_str()) + ovector[2*2];
  		int substring_length = ovector[2*2+1] - ovector[2*2];

		char* holdsrev = new char[40];
		sprintf(holdsrev, "%.*s", substring_length, substring_start);

		return atoi(holdsrev);
		delete holdsrev;
}

void IRCSession::AscSvn(void)
{
	bool success;

	success = rss.DownloadRss(AscRss);
	if(success != true)
	{
		printf("%s\n", rss.lastErrorText());
		return;
	}

	CkRss *rssChannel = 0;

	rssChannel = rss.GetChannel(0);
	if(rssChannel == 0 )
	{
		printf("No channel found in RSS feed.\n");
		return;
	}

	long numItems;
	numItems = rssChannel->get_NumItems();
	long i;

	for(i = 0; i < 1; i++)
	{
		rssItem = 0;
		rssItem = rssChannel->GetItem(i);

		AscRev = getrfa(std::string(rssItem->getString("title")));

		delete rssItem;
	}

	delete rssChannel;
}

void IRCSession::AscSvn1(void)
{
	bool success;

	success = rss.DownloadRss(AscRss);
	if(success != true)
	{
		printf("%s\n", rss.lastErrorText());
		return;
	}

	CkRss *rssChannel = 0;

	rssChannel = rss.GetChannel(0);
	if(rssChannel == 0 )
	{
		printf("No channel found in RSS feed.\n");
		return;
	}

	long numItems;
	numItems = rssChannel->get_NumItems();
	long i;

	for(i = 0; i < 1; i++)
	{
		rssItem = 0;
		rssItem = rssChannel->GetItem(i);

		AscRev1 = getrfa(std::string(rssItem->getString("title")));

		delete rssItem;
	}

	delete rssChannel;
}

void IRCSession::ArcSvn(void)
{
	bool success;

	success = rss.DownloadRss(ArcRss);
	if(success != true)
	{
		printf("%s\n", rss.lastErrorText());
		return;
	}

	CkRss *rssChannel = 0;

	rssChannel = rss.GetChannel(0);
	if(rssChannel == 0 )
	{
		printf("No channel found in RSS feed.\n");
		return;
	}

	long numItems;
	numItems = rssChannel->get_NumItems();
	long i;

	for(i = 0; i < 1; i++)
	{
		rssItem = 0;
		rssItem = rssChannel->GetItem(i);

		ArcRev = getrfa(std::string(rssItem->getString("title")));

		delete rssItem;
	}

	delete rssChannel;
}

void IRCSession::ArcSvn1(void)
{
	bool success;

	success = rss.DownloadRss(ArcRss);
	if(success != true)
	{
		printf("%s\n", rss.lastErrorText());
		return;
	}

	CkRss *rssChannel = 0;

	rssChannel = rss.GetChannel(0);
	if(rssChannel == 0 )
	{
		printf("No channel found in RSS feed.\n");
		return;
	}

	long numItems;
	numItems = rssChannel->get_NumItems();
	long i;

	for(i = 0; i < 1; i++)
	{
		rssItem = 0;
		rssItem = rssChannel->GetItem(i);

		ArcRev1 = getrfa(std::string(rssItem->getString("title")));

		delete rssItem;
	}

	delete rssChannel;
}

void IRCSession::ArcSSvn(void)
{
	bool success;

	success = rss.DownloadRss(ArcSRss);
	if(success != true)
	{
		printf("%s\n", rss.lastErrorText());
		return;
	}

	CkRss *rssChannel = 0;

	rssChannel = rss.GetChannel(0);
	if(rssChannel == 0 )
	{
		printf("No channel found in RSS feed.\n");
		return;
	}

	long numItems;
	numItems = rssChannel->get_NumItems();
	long i;

	for(i = 0; i < 1; i++)
	{
		rssItem = 0;
		rssItem = rssChannel->GetItem(i);

		ArcSRev = getrfa(std::string(rssItem->getString("title")));

		delete rssItem;
	}

	delete rssChannel;
}

void IRCSession::ArcSSvn1(void)
{
	bool success;

	success = rss.DownloadRss(ArcSRss);
	if(success != true)
	{
		printf("%s\n", rss.lastErrorText());
		return;
	}

	CkRss *rssChannel = 0;

	rssChannel = rss.GetChannel(0);
	if(rssChannel == 0 )
	{
		printf("No channel found in RSS feed.\n");
		return;
	}

	long numItems;
	numItems = rssChannel->get_NumItems();
	long i;

	for(i = 0; i < 1; i++)
	{
		rssItem = 0;
		rssItem = rssChannel->GetItem(i);

		ArcSRev1 = getrfa(std::string(rssItem->getString("title")));

		delete rssItem;
	}

	delete rssChannel;
}

void IRCSession::AscNHalf(void)
{
	bool success;

    //  Download from the feed URL:
	success = rss.DownloadRss(AscRss);
	if(success != true)
	{
		printf("%s\n", rss.lastErrorText());
		return;
	}

	//  Get the 1st channel.
	CkRss *rssChannel = 0;

	rssChannel = rss.GetChannel(0);
	if(rssChannel == 0 )
	{
		printf("No channel found in RSS feed.\n");
		return;
	}

	long numItems;
	numItems = rssChannel->get_NumItems();
	long i;

	for(i = 0; i < 1; i++)
	{
		rssItem = 0;
		rssItem = rssChannel->GetItem(i);

		std::string title = rssItem->getString("title");
		vector<string> res(16);
		split(title, ":", res);
		int rev = getrfa(std::string(rssItem->getString("title")));

		std::map<string, string>::iterator itr = mChannelList.begin();
		for(; itr != mChannelList.end(); itr++)
		{
			string Channel = itr->first;
			if(itr->second != "")
				Channel += " " + itr->second;

			if(rev == 1)
			{
				SendChatMessage(PRIVMSG, Channel.c_str(), "3AscNHalf: Ticket: by %s\n", rssItem->getString("author"));
				SendChatMessage(PRIVMSG, Channel.c_str(), "3AscNHalf: Info: %s\n", rssItem->getString("title"));
			}
			else
			{
				SendChatMessage(PRIVMSG, Channel.c_str(), "3AscNHalf: Revision: 10r%d by %s\n", rev, rssItem->getString("author"));
				SendChatMessage(PRIVMSG, Channel.c_str(), "3AscNHalf: Info: %s\n", rssItem->getString("title")/*res[1].c_str()*/);
			}
		}

		delete rssItem;
	}

	delete rssChannel;
}

void IRCSession::Arcemu(void)
{
	bool success;

    //  Download from the feed URL:
	success = rss.DownloadRss(ArcRss);
	if(success != true)
	{
		printf("%s\n", rss.lastErrorText());
		return;
	}

	//  Get the 1st channel.
	CkRss *rssChannel = 0;

	rssChannel = rss.GetChannel(0);
	if(rssChannel == 0 )
	{
		printf("No channel found in RSS feed.\n");
		return;
	}

	long numItems;
	numItems = rssChannel->get_NumItems();
	long i;

	for(i = 0; i < 1; i++)
	{
		rssItem = 0;
		rssItem = rssChannel->GetItem(i);

		std::string title = rssItem->getString("title");
		vector<string> res(17);
		split(title, ":", res);
		int rev = getrfa(std::string(rssItem->getString("title")));

		std::map<string, string>::iterator itr = mChannelList.begin();
		for(; itr != mChannelList.end(); itr++)
		{
			string Channel = itr->first;
			if(itr->second != "")
				Channel += " " + itr->second;

			if(rev == 1)
			{
				SendChatMessage(PRIVMSG, Channel.c_str(), "3Arcemu: Ticket: by %s\n", rssItem->getString("dc:creator"));
				SendChatMessage(PRIVMSG, Channel.c_str(), "3Arcemu: Info: %s\n", rssItem->getString("title"));
			}
			else
			{
				SendChatMessage(PRIVMSG, Channel.c_str(), "3Arcemu: Revision: 10r%d by %s\n", rev, rssItem->getString("dc:creator"));
				SendChatMessage(PRIVMSG, Channel.c_str(), "3Arcemu: Info: %s\n", rssItem->getString("title")/*res[1].c_str()*/);
			}
		}

		delete rssItem;
	}

	delete rssChannel;
}

void IRCSession::ArcScripts(void)
{
	bool success;

    //  Download from the feed URL:
	success = rss.DownloadRss(ArcSRss);
	if(success != true)
	{
		printf("%s\n", rss.lastErrorText());
		return;
	}

	//  Get the 1st channel.
	CkRss *rssChannel = 0;

	rssChannel = rss.GetChannel(0);
	if(rssChannel == 0 )
	{
		printf("No channel found in RSS feed.\n");
		return;
	}

	long numItems;
	numItems = rssChannel->get_NumItems();
	long i;

	for(i = 0; i < 1; i++)
	{
		rssItem = 0;
		rssItem = rssChannel->GetItem(i);

		std::string title = rssItem->getString("title");
		vector<string> res(17);
		split(title, ":", res);
		int rev = getrfa(std::string(rssItem->getString("title")));

		std::map<string, string>::iterator itr = mChannelList.begin();
		for(; itr != mChannelList.end(); itr++)
		{
			string Channel = itr->first;
			if(itr->second != "")
				Channel += " " + itr->second;

			if(rev == 1)
			{
				SendChatMessage(PRIVMSG, Channel.c_str(), "3ArcScripts: Ticket: by %s\n", rssItem->getString("dc:creator"));
				SendChatMessage(PRIVMSG, Channel.c_str(), "3ArcScripts: Info: %s\n", rssItem->getString("title"));
			}
			else
			{
				SendChatMessage(PRIVMSG, Channel.c_str(), "3ArcScripts: Revision: 10r%d by %s\n", rev, rssItem->getString("dc:creator"));
				SendChatMessage(PRIVMSG, Channel.c_str(), "3ArcScripts: Info: %s\n", rssItem->getString("title")/*res[1].c_str()*/);
			}
		}

		delete rssItem;
	}

	delete rssChannel;
}

#endif