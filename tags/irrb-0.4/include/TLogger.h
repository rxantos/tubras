//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TLOGGER_H_
#define _TLOGGER_H_

namespace Tubras
{

    /**
    TLogger Class.
    @remarks
    A logging utility class.
    */
    class TLogger : public TSingleton<Tubras::TLogger>
    {
        std::ofstream	    m_fp;
        TString             m_logFileName;
        TTimer*             m_timer;
    public:
        TLogger(const TString& logFileName);
        ~TLogger();

        static TLogger& getSingleton(void);
        static TLogger* getSingletonPtr(void);

        void logMessage(const TString& msg);
    };

}
#endif

