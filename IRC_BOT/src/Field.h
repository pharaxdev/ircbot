/* Schumix */

#ifndef _FIELD_H
#define _FIELD_H

#include "StdAfx.h"

class Field
{
public:

	void SetValue(char* value) { mValue = value; }

	const char *GetString() { return mValue; }
	float GetFloat() { return mValue ? static_cast<float>(atof(mValue)) : 0; }
	bool GetBool() { return mValue ? atoi(mValue) > 0 : false; }
	uint8 GetUInt8() { return mValue ? static_cast<uint8>(atol(mValue)) : 0; }
	int8 GetInt8() { return mValue ? static_cast<int8>(atol(mValue)) : 0; }
	uint16 GetUInt16() { return mValue ? static_cast<uint16>(atol(mValue)) : 0; }
	uint32 GetUInt32() { return mValue ? static_cast<uint32>(atol(mValue)) : 0; }
	uint32 GetInt32() { return mValue ? static_cast<int32>(atol(mValue)) : 0; }
	uint64 GetUInt64() 
	{
		if(mValue)
		{
			uint64 value;
			sscanf(mValue,I64FMTD,&value);
			return value;
		}
		else
			return 0;
	}

private:
	char *mValue;
};

#endif