//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef __TSINGLETON_H_
#define __TSINGLETON_H_

#include <assert.h>
namespace Tubras {
    template <typename T> class TSingleton
    {
    protected:

        static T* ms_Singleton;

    public:
        TSingleton( void )
        {
            assert( !ms_Singleton );
#if defined( _MSC_VER ) && _MSC_VER < 1200	 
            int offset = (int)(T*)1 - (int)(TSingleton <T>*)(T*)1;
            ms_Singleton = (T*)((int)this + offset);
#else
	    ms_Singleton = static_cast< T* >( this );
#endif
        }
        ~TSingleton( void )
            {  assert( ms_Singleton );  ms_Singleton = 0;  }
        static T& getSingleton( void )
		{	assert( ms_Singleton );  return ( *ms_Singleton ); }
        static T* getSingletonPtr( void )
		{ return ms_Singleton; }
    };
}


#endif
