//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
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
    class TLogger
    {
        std::ofstream	    m_fp;
        TString             m_logFileName;
        TTimer*             m_timer;
    public:
        TLogger(const TString& logFileName);
        ~TLogger();

        void logMessage(const TString& msg);
    };

}
#endif

