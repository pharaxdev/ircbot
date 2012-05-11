/* Schumix */

#include "StdAfx.h"


// Ismeretlen
void IRCSession::Ismeretlen0(IRCMessage& recvData){}
void IRCSession::Ismeretlen1(IRCMessage& recvData){}
void IRCSession::Ismeretlen2(IRCMessage& recvData){}
void IRCSession::Ismeretlen3(IRCMessage& recvData){}
void IRCSession::Ismeretlen4(IRCMessage& recvData){}
void IRCSession::Ismeretlen5(IRCMessage& recvData){}
void IRCSession::Ismeretlen6(IRCMessage& recvData){}
void IRCSession::Ismeretlen7(IRCMessage& recvData){}
void IRCSession::Ismeretlen8(IRCMessage& recvData){}
void IRCSession::Ismeretlen9(IRCMessage& recvData){}
void IRCSession::Ismeretlen10(IRCMessage& recvData){}
void IRCSession::Ismeretlen11(IRCMessage& recvData){}
void IRCSession::Ismeretlen12(IRCMessage& recvData){}
void IRCSession::Ismeretlen13(IRCMessage& recvData){}
void IRCSession::Ismeretlen14(IRCMessage& recvData){}
void IRCSession::Ismeretlen15(IRCMessage& recvData){}
void IRCSession::Ismeretlen16(IRCMessage& recvData){}
void IRCSession::Ismeretlen17(IRCMessage& recvData){}


void IRCSession::HandleSuccessfulAuth(IRCMessage& recvData)
{
	// We're good to go.
	mConnState = CONN_REGISTERED;
	Log.Notice("IRCSession", "Authentication successful.");
	mServerRealName = recvData.hostmask;

	// Nickserv identification
	if(mUseNickServ)
	{
		Log.Notice("NickServ", "Sending NickServ identification.");
		SendChatMessage(PRIVMSG, "NickServ", "identify %s", mNickServPassword.c_str());
	}

	// Join the default channels
	std::map<string, string>::iterator itr = mChannelList.begin();
	for(; itr != mChannelList.end(); itr++)
	{
		string join = itr->first;
		if(itr->second != "")
			join += " " + itr->second;

		WriteLine("JOIN %s", join.c_str());
	}

}

void IRCSession::HandleMotdStart(IRCMessage& recvData)
{
	// The MOTD is coming 
	mHasFullMotd = false;
	mLastMotd = "";
}

void IRCSession::HandleMotd(IRCMessage& recvData)
{
	// Part of the MOTD, append it to the rest.
	if(mHasFullMotd)
		return;

	mLastMotd += recvData.args + NEWLINE;
}

void IRCSession::HandleMotdStop(IRCMessage& recvData)
{
	// The MOTD is over.
	Log.Notice("IRCSession", "Server Message of the Day received.");
	mHasFullMotd = true;
}

void IRCSession::HandleNotice(IRCMessage& recvData)
{
	Log.Color(TRED);
	printf("%s", recvData.source_nick.c_str());
	Log.Color(TYELLOW);
	printf(" sends notice: ");
	Log.Color(TNORMAL);
	printf("%s%s", recvData.args.c_str(), NEWLINE);
}

void IRCSession::HandlePrivmsg(IRCMessage& recvData)
{
	/*string szokoz = "(?<wsn>\\s*)";
	boost::cmatch matches;
	boost::regex re;
	re.assign(szokoz, boost::regex_constants::icase);

	string test_svn = "test svn";
	if(boost::regex_match(test_svn.c_str(), matches, re))
	{
		string matched(matches[1].first, matches[1].second);
	}*/

	Log.Color(TYELLOW);
	printf("[%s] <%s> %s%s", recvData.target.c_str(), recvData.source_nick.c_str(), recvData.args.c_str(), NEWLINE);
	Log.Color(TNORMAL);

	char log[512];
	snprintf((char*)log, 512, "<%s> %s%s", recvData.source_nick.c_str(), recvData.args.c_str(), NEWLINE);

	QueryResult * result = mSQLConn->Query("SELECT nev, status FROM funkciok WHERE nev = 'log'");
	if(result)
	{
		do 
		{
			string nev = result->Fetch()[0].GetString();
			string status = result->Fetch()[1].GetString();

			if(status == bekapcsol)
			{
				char fajl[500];
				snprintf(fajl, 500, "szoba/%s.log", recvData.target.c_str());

				if(recvData.target.c_str())
				{
					FILE* LogSzoba = fopen(fajl, "a+");
					if(!LogSzoba || LogSzoba == NULL)
					{
						printf("Sikertelen olvasas.\n");
						return;
					}
		
					fprintf(LogSzoba, "%s", log);
					fclose(LogSzoba);
				}
			}
			else
				printf("A %s funkcio nem uzemel!\n", nev.c_str());

		} while(result->NextRow());
		delete result;
	}

	// It's a command!
	if(recvData.args.substr(0, 1) != "!")
		return;

/*	if(mAntiSpamTicker + 2500 > GetTickCount())
		return;

	mAntiSpamTicker = GetTickCount();*/		// kikapcsolva

	uint32 firstSpace = uint32(recvData.args.find(' '));
	if(firstSpace == 0)
		firstSpace = uint32(recvData.args.length());

	string cmd = string(strlwr((char*)recvData.args.substr(1, firstSpace - 1).c_str()));

	if(cmd == "xbot")
	{
		SendChatMessage(PRIVMSG, recvData.target.c_str(), "Verzió: 10%s", revision);
		SendChatMessage(PRIVMSG, recvData.target.c_str(), "Parancsok: !info | !xrev | !irc | !roll | !szam");
		SendChatMessage(PRIVMSG, recvData.target.c_str(), "Programmed by: 3Csabix");
		return;
	}

	if(cmd == "admin")
	{
		if(recvData.source_nick == Admin)
		{
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "3Parancsok: !nick | !join | !left | !kick | !mode | !szinek | !funkcio | !kikapcs | !s | !sznap");
			return;
		}
	}

	if(cmd == "szinek")
	{
		if(recvData.source_nick == Admin)
		{
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "1teszt1");
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "2teszt2");
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "3teszt3");
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "4teszt4");
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "5teszt5");
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "6teszt6");
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "7teszt7");
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "8teszt8");
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "9teszt9");
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "10teszt10");
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "11teszt11");
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "12teszt12");
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "13teszt13");
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "14teszt14");
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "15teszt15");
			return;
		}
	}

	if(cmd == "info")
	{
		SendChatMessage(PRIVMSG, recvData.target.c_str(), "Programozom: Csabix, Scymex és Pharax.");
		return;
	}

	if(cmd == "online")
	{
		SendChatMessage(PRIVMSG, recvData.target.c_str(), "Nem üzemel a funkció!");
		return;
	}

	if(cmd == "anyad")
	{
		SendChatMessage(PRIVMSG, recvData.target.c_str(), "TIED!");
		return;
	}

	if(cmd == "enyem?")
	{
		SendChatMessage(PRIVMSG, recvData.target.c_str(), "Az ám :)");
		return;
	}

	// Irc parancsok
	if(cmd == "irc")
	{
		if(recvData.args.length() <= firstSpace+1)
			return;

		string irc = mSQLConn->EscapeString(recvData.args.substr(firstSpace+1));
		QueryResult * result = mSQLConn->Query("SELECT parancs, hasznalata FROM irc_parancsok WHERE parancs = '%s'", irc.c_str());
		if(result)
		{
			do 
			{
				string parancs = result->Fetch()[0].GetString();
				string hasznalata = result->Fetch()[1].GetString();

				SendChatMessage(PRIVMSG, recvData.target.c_str(), "%s", hasznalata.c_str());
			} while(result->NextRow());
			delete result;
		}
		else
		{
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "Segítség az irc-hez!");
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "Parancsok: !irc rang | !irc nick | !irc kick");
		}
	}

	if(cmd == "nick")
	{
		if(recvData.args.length() <= firstSpace+1)
			return;

		if(recvData.source_nick == Admin)
		{
			string nick = recvData.args.substr(firstSpace+1);
			{
				WriteLine("NICK %s", nick.c_str());
			}
		}
	}

	if(cmd == "join")
	{
		if(recvData.args.length() <= firstSpace+1)
			return;

		if(recvData.source_nick == Admin)
		{
			string join = recvData.args.substr(firstSpace+1);
			{
				WriteLine("JOIN %s", join.c_str());
			}
		}
	}

	if(cmd == "left")
	{
		if(recvData.args.length() <= firstSpace+1)
			return;

		if(recvData.source_nick == Admin)
		{
			string left = recvData.args.substr(firstSpace+1);
			{
				WriteLine("PART %s", left.c_str());
			}
		}
	}

	if(cmd == "kick")
	{
		if(recvData.args.length() <= firstSpace+1)
			return;

		if(recvData.source_nick == Admin)
		{
			string kick = recvData.args.substr(firstSpace+1);
			{
				WriteLine("KICK %s %s", recvData.target.c_str(), kick.c_str());
			}
		}
	}

	if(cmd == "mode")
	{
		if(recvData.args.length() <= firstSpace+1)
			return;

		if(recvData.source_nick == Admin)
		{
			string mode = recvData.args.substr(firstSpace+1);
			{
				WriteLine("MODE %s %s", recvData.target.c_str(), mode.c_str());
			}
		}
	}

	// revision
	if(cmd == "xrev")
	{
		SendChatMessage(PRIVMSG, recvData.target.c_str(), "Emulátorok: <ascnhalf>");
		return;
	}

	if(cmd == "xrev_help")
	{
		SendChatMessage(PRIVMSG, recvData.target.c_str(), "Parancs használata: !xrev <emulátor neve>");
		return;
	}

	if(cmd == "xrev_ascnhalf")
	{
		if(recvData.args.length() <= firstSpace+1)
			return;

		string revid = mSQLConn->EscapeString(recvData.args.substr(firstSpace+1));
		QueryResult * result = mSQLConn->Query("SELECT emu, rev, irta, szoveg FROM xrev WHERE rev = '%s'", revid.c_str());
		if(result)
		{
			do 
			{
				string emu = result->Fetch()[0].GetString();
				uint32 rev = result->Fetch()[1].GetUInt32();
				string irta = result->Fetch()[2].GetString();
				string szoveg = result->Fetch()[3].GetString();

				SendChatMessage(PRIVMSG, recvData.target.c_str(), "%s rev %u. Fejlesztõ: %s < Commit: %s >", emu.c_str(), rev, irta.c_str(), szoveg.c_str());
			} while(result->NextRow());
			delete result;
		}
		else
		{
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "Nincs ilyen rev.");
		}
	}

	if(cmd == "roll")
	{
		uint32 result = mRandGenerator->randInt(100);
		SendChatMessage(PRIVMSG, recvData.target.c_str(), "Százalékos aránya %u!", result);
	}

	if(cmd == "s")
	{
		if(recvData.args.length() <= firstSpace+1)
			return;

		string sc = mSQLConn->EscapeString(recvData.args.substr(firstSpace+1));
		QueryResult * result = mSQLConn->Query("SELECT guid, szoveg FROM szoveg WHERE guid = '1'", sc.c_str());
		if(result)
		{
			do 
			{
				uint32 guid = result->Fetch()[0].GetUInt32();
				string szoveg = result->Fetch()[1].GetString();

				SendChatMessage(PRIVMSG, recvData.target.c_str(), "%s", szoveg.c_str());
			} while(result->NextRow());
			delete result;
		}
	}

	if(cmd == "sznap")
	{
		if(recvData.args.length() <= firstSpace+1)
			return;

		string adat = mSQLConn->EscapeString(recvData.args.substr(firstSpace+1));
		QueryResult * result = mSQLConn->Query("SELECT nev, honap, nap FROM sznap WHERE nev = '%s'", adat.c_str());
		if(result)
		{
			do 
			{
				string nev = result->Fetch()[0].GetString();
				string honap = result->Fetch()[1].GetString();
				uint32 nap = result->Fetch()[2].GetUInt32();

				SendChatMessage(PRIVMSG, recvData.target.c_str(), "%s születés napja: %s %u", nev.c_str(), honap.c_str(), nap);
			} while(result->NextRow());
			delete result;
		}
		else
		{
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "Nincs ilyen ember.");
		}
	}

	if(cmd == "test")
	{
		QueryResult * result = mSQLConn->Query("SELECT nev, status FROM funkciok WHERE nev = 'test'");
		if(result)
		{
			do 
			{
				string nev = result->Fetch()[0].GetString();
				string status = result->Fetch()[1].GetString();

				if(status == bekapcsol)
				{
					char tartalom[2048];

					FILE* fp = fopen("test.txt", "r");
					fgets(tartalom, 2048, fp);
					SendChatMessage(PRIVMSG, recvData.target.c_str(), "%s", tartalom);
				}
				else
					printf("A %s funkcio nem uzemel!\n", nev.c_str());

			} while(result->NextRow());
			delete result;
		}
	}

	if(cmd == "test" && firstSpace+1 && "svn")
	{
		AscNHalf();
		Arcemu();
		ArcScripts();
	}

	if(cmd == "szam")
	{
		if(recvData.args.length() <= firstSpace+1)
			return;
/*
		double x, y, eredmeny = 0;
		char op;
		int siker = 1;

		scanf ("%lf%c%lf", &x, &op, &y);

		switch (op)
		{
			case '+': eredmeny = x + y; break;
			case '-': eredmeny = x - y; break;
			case '*': eredmeny = x * y; break;
			case '/':
			if (y)
				eredmeny = x / y;
			else
				siker = 0;
			break;
			default : siker = -1;
		}

		switch (siker)
		{
			case 1 : printf("%.2lf %c %.2lf = %.2lf", x,op,y,eredmeny);
				break;
			case 0 : printf ("\nA mûvelet nem végezhetõ el."); break;
			case -1: printf ("Hibás mûveleti jel !");
		}
*/
		SendChatMessage(PRIVMSG, recvData.target.c_str(), "Jelenleg nem üzemel a funkció.");
	}

	if(cmd == "funkcio")
	{
		if(recvData.source_nick == Admin)
		{
			if(recvData.args.length() <= firstSpace+1)
				return;

			string status = mSQLConn->EscapeString(recvData.args.substr(firstSpace+1,2));
			string nev = mSQLConn->EscapeString(recvData.args.substr(firstSpace+4));
			QueryResult * result = mSQLConn->Query("UPDATE funkciok SET status = '%s' WHERE nev = '%s'", status.c_str(), nev.c_str());

			delete result;
		}
	}

	if(cmd == "uzenet")
	{
		if(recvData.args.length() <= firstSpace+1)
			return;

		string nev = recvData.args.substr(firstSpace+1);
		{
			WriteLine("MSG %s Keresnek téged itt: %s", nev.c_str(), recvData.target.c_str());
		}
	}

	if(cmd == "kikapcs")
	{
		if(recvData.source_nick == Admin)
		{
			SendChatMessage(PRIVMSG, recvData.target.c_str(), "Viszlát :(");
			if(!m_running)
				m_running = false;
			Sleep(1100);
			exit(1);
		}
	}
}

void IRCSession::HandlePing(IRCMessage& recvData)
{
	// Ping? Pong!
	WriteLine("PONG :%s", recvData.args.c_str());
	//Log.Notice("IRCSession", "Ping? Pong!");
}

void IRCSession::HandlePong(IRCMessage& recvData)
{
	// Ping? Pong!
	WriteLine("PONG :%s", recvData.args.c_str());
	//Log.Notice("IRCSession", "Ping? Pong!");
}

void IRCSession::HandleKick(IRCMessage& recvData)
{
	string kickedby = recvData.source_nick;
	string channel = recvData.argv[0];
	string kicked = recvData.argv[1];
	string reason = "";
	if(recvData.argc >= 3)
		reason = recvData.argv[2];

	SendChatMessage(PRIVMSG, recvData.target.c_str(),"%s kickelte a következõ felhasználot: %s! oka: %s", kickedby.c_str(), kicked.c_str(), reason.c_str());
}

#define ora st.wHour+1

void IRCSession::HandleJoin(IRCMessage& recvData)
{
	if(recvData.source_nick == mNickName)
		return;

	string koszones;

	switch(rand()%7)
	{
		case 0:
			koszones = "Hello";
			break;
		case 1:
			koszones = "Csáó";
			break;
		case 2:
			koszones = "Hy";
			break;
		case 3:
			koszones = "Szevasz";
			break;
		case 4:
			koszones = "Üdv";
			break;
		case 5:
			koszones = "Szervusz";
			break;
		case 6:
			koszones = "Aloha";
			break;
	}

	std::string title = recvData.target.c_str();
	vector<string> res(1);
	split(title, ":", res);

	SYSTEMTIME st;
	GetSystemTime(&st);

	QueryResult * result = mSQLConn->Query("SELECT nev, status FROM funkciok WHERE nev = 'koszones'");
	if(result)
	{
		do 
		{
			string nev = result->Fetch()[0].GetString();
			string status = result->Fetch()[1].GetString();

			if(status == bekapcsol)
			{
				if(ora <= 9)
				{
					SendChatMessage(PRIVMSG, res[1].c_str(), "Jó reggelt %s", recvData.source_nick.c_str());
				}
				else if(ora >= 20)
				{
					SendChatMessage(PRIVMSG, res[1].c_str(), "Jó estét %s", recvData.source_nick.c_str());
				}
				else
				{
					if(recvData.source_nick == "Narancs")
						SendChatMessage(PRIVMSG, res[1].c_str(), "Üdvözöllek kedves barátom!");
					else if(recvData.source_nick == Admin)
						SendChatMessage(PRIVMSG, res[1].c_str(), "Üdv fõnök");
					else
						SendChatMessage(PRIVMSG, res[1].c_str(), "%s %s", koszones.c_str(), recvData.source_nick.c_str());
				}
			}
			else
				printf("A %s funkcio nem uzemel!\n", nev.c_str());

		} while(result->NextRow());
		delete result;
	}
}

void IRCSession::HandleLeft(IRCMessage& recvData)
{
	if(recvData.source_nick == mNickName)
		return;

	string elkoszones;

	switch(rand()%2)
	{
		case 0:
			elkoszones = "Viszlát";
			break;
		case 1:
			elkoszones = "Bye";
			break;
	}

	SYSTEMTIME st;
	GetSystemTime(&st);

	QueryResult * result = mSQLConn->Query("SELECT nev, status FROM funkciok WHERE nev = 'elkoszones'");
	if(result)
	{
		do 
		{
			string nev = result->Fetch()[0].GetString();
			string status = result->Fetch()[1].GetString();

			if(status == bekapcsol)
			{
				if(ora >= 20)
					SendChatMessage(PRIVMSG, recvData.target.c_str(), "Jóét %s", recvData.source_nick.c_str());
				else
					SendChatMessage(PRIVMSG, recvData.target.c_str(), "%s %s", elkoszones.c_str(), recvData.source_nick.c_str());
			}
			else
				printf("A %s funkcio nem uzemel!\n", nev.c_str());

		} while(result->NextRow());
		delete result;
	}
}

void IRCSession::HandleQuit(IRCMessage& recvData)
{
	if(recvData.source_nick == mNickName)
		return;

	string elkoszones;

	switch(rand()%2)
	{
		case 0:
			elkoszones = "Viszlát";
			break;
		case 1:
			elkoszones = "Bye";
			break;
	}

	SYSTEMTIME st;
	GetSystemTime(&st);

	QueryResult * result = mSQLConn->Query("SELECT nev, status FROM funkciok WHERE nev = 'elkoszones'");
	if(result)
	{
		do 
		{
			string nev = result->Fetch()[0].GetString();
			string status = result->Fetch()[1].GetString();

			if(status == bekapcsol)
			{
				if(ora >= 20)
					SendChatMessage(PRIVMSG, recvData.target.c_str(), "Jóét %s", recvData.source_nick.c_str());
				else
					SendChatMessage(PRIVMSG, recvData.target.c_str(), "%s %s", elkoszones.c_str(), recvData.source_nick.c_str());
			}
			else
				printf("A %s funkcio nem uzemel!\n", nev.c_str());

		} while(result->NextRow());
		delete result;
	}
}

void IRCSession::HandleReConnect(IRCMessage& recvData)
{
	QueryResult * result = mSQLConn->Query("SELECT nev, status FROM funkciok WHERE nev = 'reconnect'");
	if(result)
	{
		do 
		{
			string nev = result->Fetch()[0].GetString();
			string status = result->Fetch()[1].GetString();

			if(status == bekapcsol)
			{
				// ReConnect
				std::map<string, string>::iterator itr = mChannelList.begin();
				for(; itr != mChannelList.end(); itr++)
				{
					string join = itr->first;
					if(itr->second != "")
						join += " " + itr->second;

					WriteLine("JOIN %s", join.c_str());
				}
			}
			else
				printf("A %s funkcio nem uzemel!\n", nev.c_str());

		} while(result->NextRow());
		delete result;
	}
}

void IRCSession::HandleMode(IRCMessage& recvData)
{
	if(recvData.target == mNickName)
		return;

	printf("Megvaltozot rangod a ");
	Log.Color(TRED);
	printf("%s ", recvData.target.c_str());
	Log.Color(TNORMAL);
	printf("szobaban!\n");
}

void IRCSession::HandleNick(IRCMessage& recvData)
{
	Log.Color(TRED);
	printf("%s", recvData.source_nick.c_str());
	Log.Color(TWHITE);
	printf(" nev cserelve erre: ");
	Log.Color(TRED);
	printf("%s\n", recvData.args.c_str());
	Log.Color(TNORMAL);
}
