//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to 
// deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
// sell copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------
#include "tubras.h"

#if (defined(_IRR_POSIX_API_) || defined(_IRR_OSX_PLATFORM_))
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

#ifdef _IRR_WINDOWS_API_
	#if !defined ( _WIN32_WCE )
		#include <io.h>
		#include <direct.h>
	#endif
#endif


static Tubras::TApplication *theApp=0;


namespace Tubras
{
    //-----------------------------------------------------------------------
    //                            T L o g g e r 
    //-----------------------------------------------------------------------
    TLogger::TLogger(const TString& logFileName) : m_logFileName(logFileName)
    {
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
        struct tm *pTime;
        time_t ctTime; time(&ctTime);
        pTime = localtime( &ctTime );
        m_fp << std::setw(2) << std::setfill('0') << pTime->tm_hour
            << ":" << std::setw(2) << std::setfill('0') << pTime->tm_min
            << ":" << std::setw(2) << std::setfill('0') << pTime->tm_sec 
            << ": " << msg.c_str() << std::endl;

        m_fp.flush();
    }
}

