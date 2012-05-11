/* Schumix */

#ifndef _IRC_SESSION_H
#define _IRC_SESSION_H

#include "StdAfx.h"

#define CONN_CONNECTED 0
#define CONN_REGISTERING 1
#define CONN_REGISTERED 2

#define revision "0.3.6"
#define SVN_RSS 1

// funkciok
#define bekapcsol "be"

#ifdef SVN_RSS
#define AscRss "http://www.assembla.com/spaces/stream/ascnhalf.rss"
#define ArcRss "http://arcemu.info/trac/arcemu/timeline?ticket=on&changeset=on&milestone=on&wiki=on&max=50&daysback=90&format=rss"
#define ArcSRss "http://arcemu.info/trac/arcscripts/timeline?ticket=on&changeset=on&milestone=on&wiki=on&max=50&daysback=90&format=rss"
#define Lekerdezesi_ido Sleep(60*1000);
#endif

#define Admin "Megaxxx"

class MySQLConnection;
class SimpleSocket;

enum MessageType
{
	PRIVMSG,
	NOTICE,
};

#ifdef SVN_RSS
struct RSS_XHANDLER
{
   HANDLE instance;
   HANDLE rss;
};
#endif

struct IRCMessage
{
	string hostmask;
	string opcode;
	string target; // optional
	string args; 

	// these two are derived; :bob!jim@gym
	string source_nick; // bob
	string source_user; // jim
	string source_host; // gym

	// The number of argvs
	uint32 argc;

	/* Format for argv:
	 * argv is the space-delimited array of parameters sent from the 
	 * IRCd. This should be used when the standard parser fails.
	 * In cases where we run into a colon parameter, the colon is removed
	 * and everything after it appears as one argument.
	 * The argv begins recording AFTER the IRC RPL code.
	 */
	string *argv;
};

class IRCSession
{
public:
	IRCSession(std::string host, uint32 port);
	~IRCSession();

	/*
	  * Rehashes the schumix.conf configuration file.
	  */
	void RehashConfig();

	/*
	  * Outputs a message to the server. You need not include \n.
	  */
	void WriteLine(const char * format, ...);
	void WriteLineForce(const char * format, ...);

	/*
	  * Callback for SimpleSocket I/O. Do not invoke directly.
	  */
	void OnRecv(string recvString);

	/*
	  * Send a simple chat message. 
	  * @param MessageType Either "PRIVMSG" or "NOTICE" now.
	  * @param target The target of the message. Can be a channel or a user.
	  * @param format The message to send. May include formatters such as %s, %u, etc.
	  */
	void SendChatMessage(MessageType type, const char * target, const char * format, ...);

	/*
	  * Updates the IRC Session. Do not invoke directly.
	  */
	void Update();
	void Reconnect();

	bool Running() { return m_running; }
	DWORD ReadConsoleRoutine(void);
	static DWORD WINAPI StartRCR(LPVOID lpInst);
	DWORD Funkciok(void);
	static DWORD WINAPI StartFunkciok(LPVOID lpInst);

	/*
	  * AscNHalf
	  */
	void split(string str, string delim, vector<string>& results);
#ifdef SVN_RSS
	int getrfa(std::string title);
	static DWORD WINAPI StartAscNHalf(LPVOID lpParam);
	DWORD ThreadAscNHalf(LPVOID lpItem);
	void AscNHalf(void);
	void AscSvn(void);
	void AscSvn1(void);
	
	/*
	  * Arcemu
	  */
	static DWORD WINAPI StartArcemu(LPVOID lpParam);
	DWORD ThreadArcemu(LPVOID lpItem);
	void Arcemu(void);
	void ArcSvn(void);
	void ArcSvn1(void);

	/*
	  * ArcScripts
	  */
	static DWORD WINAPI StartArcSripts(LPVOID lpParam);
	DWORD ThreadArcSripts(LPVOID lpItem);
	void ArcScripts(void);
	void ArcSSvn(void);
	void ArcSSvn1(void);
#endif

	time_t UNIXTIME;

protected:
	/* Message Handlers
	  * --------------------------------
	  * Invoked automatically by OnRecv. Do not invoke directly.
	  */
	void HandleSuccessfulAuth(IRCMessage& recvData);
	void HandleMotdStart(IRCMessage& recvData);
	void HandleMotd(IRCMessage& recvData);
	void HandleMotdStop(IRCMessage& recvData);
	void HandlePrivmsg(IRCMessage& recvData);
	void HandleNotice(IRCMessage& recvData);
	void HandlePing(IRCMessage& recvData);
	void HandlePong(IRCMessage& recvData);
	void HandleKick(IRCMessage& recvData);
	void HandleMode(IRCMessage& recvData);
	void HandleJoin(IRCMessage& recvData);
	void HandleLeft(IRCMessage& recvData);
	void HandleQuit(IRCMessage& recvData);
	void HandleReConnect(IRCMessage& recvData);
	void HandleNick(IRCMessage& recvData);

	// Ismeretlenek
	void Ismeretlen0(IRCMessage& recvData);
	void Ismeretlen1(IRCMessage& recvData);
	void Ismeretlen2(IRCMessage& recvData);
	void Ismeretlen3(IRCMessage& recvData);
	void Ismeretlen4(IRCMessage& recvData);
	void Ismeretlen5(IRCMessage& recvData);
	void Ismeretlen6(IRCMessage& recvData);
	void Ismeretlen7(IRCMessage& recvData);
	void Ismeretlen8(IRCMessage& recvData);
	void Ismeretlen9(IRCMessage& recvData);
	void Ismeretlen10(IRCMessage& recvData);
	void Ismeretlen11(IRCMessage& recvData);
	void Ismeretlen12(IRCMessage& recvData);
	void Ismeretlen13(IRCMessage& recvData);
	void Ismeretlen14(IRCMessage& recvData);
	void Ismeretlen15(IRCMessage& recvData);
	void Ismeretlen16(IRCMessage& recvData);
	void Ismeretlen17(IRCMessage& recvData);

	// The current host we're connected to as specified in the config file.
	string mHost;
	// The current port we're connected to as specified in the config file.
	uint32 mPort;
	// The Socket ptr.
	SimpleSocket* mSocket;
	// Connection state: either CONN_CONNECTED, CONN_REGISTERING or CONN_REGISTERED
	uint32 mConnState;
	// The time of the last ping sent to the server.
	uint32 mLastPing;

	string mUserName;
	string mNickName;
	string mHostName;
	string mServerName;
	string mRealName;
	string mChannel;

	// Nickserv Module
	bool mUseNickServ;
	string mNickServPassword;

	// The name the server refers to itself as.
	string mServerRealName;

	// The last received MOTD. Be sure to check whether mHasFullMotd is true before using this.
	string mLastMotd;
	// Whether or not the mLastMotd variable is populated fully.
	bool mHasFullMotd;

	// A list of channels and their passwords.
	std::map<string, string> mChannelList;

	// Pointer to our mySQL connection.
	MySQLConnection * mSQLConn;

	// Time until we can accept a new privmsg "command"
	uint32 mAntiSpamTicker;

	// The random number generator
	MTRand * mRandGenerator;
	bool m_running;

#ifdef SVN_RSS
	CkRss rss;
	CkRss *rssItem;
	int AscRev;
	int AscRev1;
	int ArcRev;
	int ArcRev1;
	int ArcSRev;
	int ArcSRev1;
#endif
};

typedef void(IRCSession::*IRCCallback)(IRCMessage& recvData);
typedef std::map<std::string, IRCCallback> MessageHandlerMap;
extern MessageHandlerMap IRCMessageHandlerMap;
#endif