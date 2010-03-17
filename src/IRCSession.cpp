/* Schumix */

#include "StdAfx.h"


MessageHandlerMap IRCMessageHandlerMap;

#define ADD_CODE(code,method) \
	IRCMessageHandlerMap.insert( make_pair(code, method) );



IRCSession::IRCSession(std::string host, uint32 port)
{
	
	mHost = host;
	mPort = port;
	mSocket = new SimpleSocket();
	if(!mSocket->Connect(host, port))
	{
		Log.Notice("IRCSession", "Unable to open socket to %s.", host.c_str());
		exit(1);
		return;
	}
	Log.Notice("IRCSession", "Connected to %s successfully.", host.c_str());
	RehashConfig();
	mConnState = CONN_CONNECTED;
	m_running = true;
	mRandGenerator = new MTRand;

	mHasFullMotd = false;
	mLastPing = GetTickCount();

	// Populate the giant IRCSession handler table
	ADD_CODE( RPL_SUCCESSFUL_AUTH,	&IRCSession::HandleSuccessfulAuth );
	ADD_CODE( RPL_MOTDSTART,		&IRCSession::HandleMotdStart );
	ADD_CODE( RPL_MOTD,				&IRCSession::HandleMotd );
	ADD_CODE( RPL_ENDOFMOTD,		&IRCSession::HandleMotdStop );
	ADD_CODE( RPL_NOTICE,			&IRCSession::HandleNotice );
	ADD_CODE( RPL_PRIVMSG,			&IRCSession::HandlePrivmsg );
	ADD_CODE( RPL_PING,				&IRCSession::HandlePing );
	ADD_CODE( RPL_PONG,				&IRCSession::HandlePong );

	// Ismeretlenek
	ADD_CODE( RPL_ISMERETLEN,		&IRCSession::Ismeretlen0 );
	ADD_CODE( RPL_ISMERETLEN1,		&IRCSession::Ismeretlen1 );
	ADD_CODE( RPL_ISMERETLEN2,		&IRCSession::Ismeretlen2 );
	ADD_CODE( RPL_ISMERETLEN3,		&IRCSession::Ismeretlen3 );
	ADD_CODE( RPL_ISMERETLEN4,		&IRCSession::Ismeretlen4 );
	ADD_CODE( RPL_ISMERETLEN5,		&IRCSession::Ismeretlen5 );
	ADD_CODE( RPL_ISMERETLEN6,		&IRCSession::Ismeretlen6 );
	ADD_CODE( RPL_ISMERETLEN7,		&IRCSession::Ismeretlen7 );
	ADD_CODE( RPL_ISMERETLEN8,		&IRCSession::Ismeretlen8 );
	ADD_CODE( RPL_ISMERETLEN9,		&IRCSession::Ismeretlen9 );
	ADD_CODE( RPL_ISMERETLEN10,		&IRCSession::Ismeretlen10 );
	ADD_CODE( RPL_ISMERETLEN11,		&IRCSession::Ismeretlen11 );
	ADD_CODE( RPL_ISMERETLEN12,		&IRCSession::Ismeretlen12 );
	ADD_CODE( RPL_ISMERETLEN13,		&IRCSession::Ismeretlen13 );
	ADD_CODE( RPL_ISMERETLEN14,		&IRCSession::Ismeretlen14 );
	ADD_CODE( RPL_ISMERETLEN15,		&IRCSession::Ismeretlen15 );
	ADD_CODE( RPL_ISMERETLEN16,		&IRCSession::Ismeretlen16 );
	ADD_CODE( RPL_ISMERETLEN17,		&IRCSession::Ismeretlen17 );

	string mySQLHost = Config.MainConfig.GetStringDefault("MySQL", "Host", "");
	string mySQLUser = Config.MainConfig.GetStringDefault("MySQL", "User", "");
	string mySQLPassword = Config.MainConfig.GetStringDefault("MySQL", "Password", "");
	string mySQLDatabase = Config.MainConfig.GetStringDefault("MySQL", "Database", "");

	mSQLConn = new MySQLConnection(mySQLHost, mySQLUser, mySQLPassword);
	mSQLConn->UseDatabase(mySQLDatabase);

	mAntiSpamTicker = 0;
	CreateThread(NULL, 0, StartRCR,			(LPVOID)this, 0, NULL);
	CreateThread(NULL, 0, StartFunkciok,	(LPVOID)this, 0, NULL);

#ifdef SVN_RSS
	RSS_XHANDLER* hData = new RSS_XHANDLER();
	hData->instance = (LPVOID)this;
	CkRss* pRss = &rss;
	hData->rss = (LPVOID)pRss;

	QueryResult * result = mSQLConn->Query("SELECT nev, status FROM funkciok WHERE nev = 'svn'");
	if(result)
	{
		do 
		{
			string nev = result->Fetch()[0].GetString();
			string status = result->Fetch()[1].GetString();

			if(status == bekapcsol)
			{
				CreateThread(NULL, 0, StartAscNHalf,	(LPVOID)hData, 0, NULL);
				CreateThread(NULL, 0, StartArcemu,		(LPVOID)hData, 0, NULL);
				CreateThread(NULL, 0, StartArcSripts,	(LPVOID)hData, 0, NULL);
			}
			else
				printf("A %s funkcio nem uzemel!\n", nev.c_str());

		} while(result->NextRow());
		delete result;
	}
#endif

	Update();
}

DWORD WINAPI IRCSession::StartRCR(LPVOID lpInst)
{
	return ((static_cast<IRCSession*>(lpInst))->ReadConsoleRoutine());
}

DWORD WINAPI IRCSession::StartFunkciok(LPVOID lpInst)
{
	return ((static_cast<IRCSession*>(lpInst))->Funkciok());
}

DWORD IRCSession::ReadConsoleRoutine(void)
{
		Sleep(1000);

		while(this->Running())
		{

			char txt[2048];

			fgets(txt, 2048, stdin);
			// txt bol irhatsz ki irc-re itt (sleep elott)
			this->SendChatMessage(PRIVMSG, mChannel.c_str(), "%s", txt);
			Sleep(200);
		}

		Log.Notice("Threading", "Console reading thread is exiting cleanly.");
		ExitThread(0);

}

DWORD IRCSession::Funkciok(void)
{
	ADD_CODE( RPL_KICK,		&IRCSession::HandleKick );
	ADD_CODE( RPL_MODE,		&IRCSession::HandleMode );
	ADD_CODE( RPL_JOIN,		&IRCSession::HandleJoin );
	ADD_CODE( RPL_LEFT,		&IRCSession::HandleLeft );
	ADD_CODE( RPL_QUIT,		&IRCSession::HandleQuit );
	ADD_CODE( RPL_404,		&IRCSession::HandleReConnect );
	ADD_CODE( RPL_NICK,		&IRCSession::HandleNick );

	return 0;
}

void IRCSession::RehashConfig()
{
	mNickName = Config.MainConfig.GetStringDefault("User", "Nick", "Test");
	mUserName = Config.MainConfig.GetStringDefault("User", "Username", "Test");
	mHostName = Config.MainConfig.GetStringDefault("User", "Host", "schumix");
	mServerName = mHostName;

	mUseNickServ = Config.MainConfig.GetBoolDefault("NickServ", "Enable", false);
	mNickServPassword = Config.MainConfig.GetStringDefault("NickServ", "Password", "");

	uint32 channelCount = Config.MainConfig.GetIntDefault("Channels", "Count", 0);
	if(channelCount)
	{
		for(uint32 i = 1; i <= channelCount; i++)
		{
			char term[256];
			memset(term, '\0', 255);
			sprintf(term, "Channel%u", i);

			string config = string(term);
			mChannel = Config.MainConfig.GetStringDefault(config.c_str(), "Name", "");
			if(mChannel == "")
			{
				Log.Notice("Config", "Error parsing channels configuration.");
				return;
			}

			string password = Config.MainConfig.GetStringDefault(config.c_str(), "Password", "");

			mChannelList.insert( make_pair(mChannel, password) );
		}
	}
	else
	{
		Log.Notice("Config", "Loaded 0 default channels.");
	}
}

IRCSession::~IRCSession()
{
	if(mSocket)
		mSocket->Disconnect();

	delete mSocket;
}

void IRCSession::OnRecv(string recvString)
{
	IRCMessage mess;

	char hostmask[256];
	char opcode[256];
	char target[256];
	char args[4096];

	char source_nick[256];
	char source_host[256];

	// Make these just giant arrays of null strings.
	// This will allow for .c_str() to properly transfer the char arrays to the console
	memset(hostmask, '\0', 255);
	memset(opcode, '\0', 255);
	memset(target, '\0', 255);
	memset(args, '\0', 4095);
	memset(source_nick, '\0', 255);
	memset(source_host, '\0', 255);

	uint32 r = sscanf(recvString.c_str(), ":%255s %255s %255s :%4095[^\r\n]", hostmask, opcode, target, args);
	if(r != 4)
	{
		// Parsing failed, let's go to the fallback method. :P
		r = sscanf(recvString.c_str(), ":%s %s %s", hostmask, opcode, args);
	}

	// Fallback method, argc/argv
	mess.argc = 0;
	string *argv = new string[1024];
	uint32 lastSpace = 0;
	uint32 offset = recvString.find(' ', recvString.find(' ')+1);
	uint32 newline = recvString.find('\n');
	while(true)
	{
		uint32 spaceLoc = recvString.find(' ', lastSpace+1);
		if(spaceLoc == string::npos)
			break;

		// Removing the first two arguments.
		if(spaceLoc <= offset)
		{
			lastSpace = spaceLoc;
			continue;
		}

		mess.argc++;

		argv[mess.argc - 1] = recvString.substr(lastSpace + 1, spaceLoc-lastSpace-1);
		if(argv[mess.argc - 1].find(':') != string::npos)
		{
			// We have a colon, this basically means the rest of the text
			// is one giant argument. Remove the colon and go on.
			argv[mess.argc - 1] = recvString.substr(lastSpace + 2);
			break;
		}

		lastSpace = spaceLoc;
	}
	// Lolcopy!
	mess.argv = new string[mess.argc];
	for(uint32 i = 0; i < mess.argc; i++)
	{
		if(i != mess.argc - 1)
			mess.argv[i] = argv[i];
		else
			mess.argv[i] = argv[i].substr(0, argv[i].length()-1);
	}

	mess.hostmask = string(hostmask);
	mess.opcode = string(opcode);
	mess.args = string(args);
	mess.target = string(target);

	// split the hostmask up into useful parts
	uint32 pos = uint32(mess.hostmask.find('!'));
	mess.source_nick = mess.hostmask.substr(0, pos);
	mess.source_host = mess.hostmask.substr(pos + 1);

	pos = uint32(mess.source_host.find('@'));
	mess.source_user = mess.source_host.substr(0, pos);
	mess.source_host = mess.source_host.substr(pos + 1);

	MessageHandlerMap::iterator itr = IRCMessageHandlerMap.find(mess.opcode);
	if(itr == IRCMessageHandlerMap.end())
	{
		// Do not process this, print out some debug information
		Log.Notice("IRCSession", "Received unhandled opcode: %s", mess.opcode.c_str());
		return;
	}

	// Pass this on to the correct handler.
	IRCCallback cb = itr->second;
	(this->*cb)(mess);

	if(mess.argc)
		delete [] mess.argv;
}

void IRCSession::Update()
{
	while(true)
	{
		if(!mSocket->IsConnected())
		{
			//mSocket->WipeBuffers();
			mSocket->Connect(mHost, mPort);
			Log.Notice("IRCSession", "Lost connection to %s, reconnecting...", mHost.c_str());
			mConnState = CONN_CONNECTED;
			Reconnect();
		}

		if(mConnState == CONN_CONNECTED)
		{
			WriteLine("NICK %s", mNickName.c_str());
			WriteLine("USER %s 8 * :%s", mNickName.c_str(), mNickName.c_str());
			mConnState = CONN_REGISTERING;
		}

		if(mSocket->HasLine())
		{
			string recv = mSocket->GetLine();
			OnRecv(recv);
		}

		if(GetTickCount() - mLastPing > 15000)
		{
			WriteLine("PING :%s", mHost.c_str());
			mLastPing = GetTickCount();
		}

		mSocket->UpdateQueue();

		Sleep(20);
	}
}

void IRCSession::Reconnect()
{
	/*while(1)
	{
		mSocket->Connect(mHost, mPort);

		WriteLine("NICK Schumixx");
		WriteLine("USER Schumixx 8 * :Schumixx");

		mConnState = CONN_CONNECTED;
	}*/
}

void IRCSession::SendChatMessage(MessageType type, const char * target, const char * format, ...)
{
	char obuf[65536];
	va_list ap;

	va_start(ap, format);
	vsnprintf(obuf, 65536, format, ap);
	va_end(ap);

	if( *obuf == '\0' )
		return;
	
	string oss = "";
	if(type == PRIVMSG)
		oss = oss + "PRIVMSG";
	else if(type == NOTICE)
		oss = oss + "NOTICE";
	oss = oss + " "; 
	oss = oss + target + " :" + obuf + NEWLINE;
	WriteLine(oss.c_str());
}

void IRCSession::WriteLine(const char * format, ...)
{
	char obuf[65536];
	va_list ap;

	va_start(ap, format);
	vsnprintf(obuf, 65536, format, ap);
	va_end(ap);

	if( *obuf == '\0' )
		return;

	string send = string(obuf) + NEWLINE;

	mSocket->SendLine(send);
	//mSendQueue.push_back(send);
}

void IRCSession::WriteLineForce(const char * format, ...)
{
	char obuf[65536];
	va_list ap;

	va_start(ap, format);
	vsnprintf(obuf, 65536, format, ap);
	va_end(ap);

	if( *obuf == '\0' )
		return;

	string send = string(obuf) + NEWLINE;

	mSocket->SendForcedLine(send);
	//mSendQueue.push_back(send);
}

void IRCSession::split(string str, string delim, vector<string>& results)
{
	int at;
	while((at = str.find_first_of(delim)) != str.npos)
	{
		if(at > 0)
		{
			results.push_back(str.substr(0, at));
		}

		str = str.substr(at+1);
	}

	if(str.length() > 0)
	{
		results.push_back(str);
	}
}