/* Schumix */

#ifndef _QUERY_RESULT_H
#define _QUERY_RESULT_H

#include "StdAfx.h"

class Field;

class QueryResult
{
public:
	QueryResult(MYSQL_RES * res, uint32 uFields, uint32 uRows);
	~QueryResult();
	bool NextRow();
	Field* Fetch() { return mCurrentRow; }

	uint32 GetAffectedFields() { return mFields; }
	uint32 GetAffectedRows() { return mRows; }

protected:
	MYSQL_RES * m_res;
	Field *mCurrentRow;
	uint32 mFields;
	uint32 mRows;
};

#endif