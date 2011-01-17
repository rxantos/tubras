//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

#ifndef TUBRAS_PLATFORM_WINDOWS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

#ifdef TUBRAS_PLATFORM_WINDOWS
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
        m_fp.open(m_logFileName.c_str());
    }

    //-----------------------------------------------------------------------
    //                           ~ T L o g g e r 
    //-----------------------------------------------------------------------
    TLogger::~TLogger()
    {
        m_fp.close();
    }

    //-----------------------------------------------------------------------
    //                       l o g M e s s a g e
    //-----------------------------------------------------------------------
    void TLogger::logMessage(const TString& msg)
    {
        int h,m,s,ms;
        char tbuf[16];
        m_timer->getLocalTime(&h, &m, &s, &ms);

        sprintf(tbuf, "%02d:%02d:%02d:%03d ", h, m, s, ms);

        m_fp << tbuf << msg.c_str() << std::endl;

        m_fp.flush();
    }
}

