/* Schumix */

#include "StdAfx.h"

QueryResult::QueryResult(MYSQL_RES * res, uint32 uFields, uint32 uRows)
{
	m_res = res;
	mFields = uFields;
	mRows = uRows;
	mCurrentRow = new Field[uFields];
}

QueryResult::~QueryResult()
{
	mysql_free_result(m_res);
	delete [] mCurrentRow;
}

bool QueryResult::NextRow()
{
	MYSQL_ROW row = mysql_fetch_row(m_res);
	if(row == NULL)
		return false;

	for(uint32 i = 0; i < mFields; ++i)
		mCurrentRow[i].SetValue(row[i]);

	return true;
}