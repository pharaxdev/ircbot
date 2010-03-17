/* Schumix IRC Bot */

#ifndef _MYSQL_CONNECTION_H
#define _MYSQL_CONNECTION_H

#include "StdAfx.h"

typedef void(*mySQLCallback)(QueryResult*);
struct ASyncQuery
{
	mySQLCallback callback;
	string query;
};

class MySQLConnection// : IRunnable
{
public:
	MySQLConnection(string host, string user, string password);
	~MySQLConnection();

	void UseDatabase(string database);
	void Execute(string query);
	QueryResult* Query(const char * query, ...);

	string EscapeString(string Escape);

	void Update();

	void QueryASync(mySQLCallback callback, const char * query, ...);

protected:
	MYSQL* handle;

	string mHost;
	string mUser;
	string mPassword;
	string mDatabase;

	deque<ASyncQuery*> AsynchronousQueries;
};

#endif