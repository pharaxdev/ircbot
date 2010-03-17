/* Schumix */

#ifndef _SINGLETON_H
#define _SINGLETON_H

#include "StdAfx.h"

/// Should be placed in the appropriate .cpp file somewhere
#define initialiseSingleton( type ) \
	template <> type * Singleton < type > :: mSingleton = 0

/// To be used as a replacement for initialiseSingleton( )
///  Creates a file-scoped Singleton object, to be retrieved with getSingleton
#define createFileSingleton( type ) \
	initialiseSingleton( type ); \
	type the##type

template < class type > class Singleton
{
public:
	/// Constructor
	Singleton( )
	{
		/// If you hit this assert, this singleton already exists -- you can't create another one!
		mSingleton = static_cast<type *>(this);
	}
	/// Destructor
	virtual ~Singleton( )
	{
		mSingleton = 0;
	}

#ifdef WIN32
	__forceinline static type & getSingleton( ) { return *mSingleton; }
	__forceinline static type * getSingletonPtr( ) { return mSingleton; }
#else
	inline static type & getSingleton( ) { WPAssert( mSingleton ); return *mSingleton; }
	inline static type * getSingletonPtr( ) { return mSingleton; }
#endif

protected:

	/// Singleton pointer, must be set to 0 prior to creating the object
	static type * mSingleton;
};

#endif

