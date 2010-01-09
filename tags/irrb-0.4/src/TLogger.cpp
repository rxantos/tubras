//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"

#ifndef TUBRAS_PLATFORM_WIN32
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

#ifdef TUBRAS_PLATFORM_WIN32
	#if !defined ( _WIN32_WCE )
		#include <io.h>
		#include <direct.h>
	#endif
#endif

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                            T L o g g e r 
    //-----------------------------------------------------------------------
    TLogger::TLogger(const TString& logFileName) : m_logFileName(logFileName)
    {
        m_timer = getApplication()->getGlobalClock();
        try
        {
            m_fp.open(m_logFileName.c_str());
        }
        catch(...) {};
    }

    //-----------------------------------------------------------------------
    //                           ~ T L o g g e r 
    //-----------------------------------------------------------------------
    TLogger::~TLogger()
    {
        m_fp.close();
    }

    //-----------------------------------------------------------------------
    //                   g e t S i n g l e t o n P t r
    //-----------------------------------------------------------------------
    template<> TLogger* TSingleton<TLogger>::ms_Singleton = 0;

    TLogger* TLogger::getSingletonPtr(void)
    {
        return ms_Singleton;
    }

    //-----------------------------------------------------------------------
    //                       g e t S i n g l e t o n
    //-----------------------------------------------------------------------
    TLogger& TLogger::getSingleton(void)
    {
        assert( ms_Singleton );  return ( *ms_Singleton );
    }

    //-----------------------------------------------------------------------
    //                       l o g M e s s a g e
    //-----------------------------------------------------------------------
    void TLogger::logMessage(const TString& msg)
    {
        int h,m,s,ms;
        char tbuf[16];
        m_timer->getLocalTime(&h, &m, &s, &ms);

        sprintf(tbuf, "%0.2d:%0.2d:%0.2d:%0.3d ", h, m, s, ms);

        m_fp << tbuf << msg.c_str() << std::endl;

        m_fp.flush();
    }
}

