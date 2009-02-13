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
#include <stdlib.h>

using namespace Tubras;


class TSE : public TApplication {
public:
    TSE() : TApplication("TSE")
    {
    }

    ~TSE() 
    {
    }

    int initialize()
    {
        if(TApplication::initialize())
            return 1;


        return 0;
    }

};

//-----------------------------------------------------------------------
//                               m a i n
//-----------------------------------------------------------------------
#ifdef TUBRAS_PLATFORM_WIN32
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
{
    const char  **argv=(const char**)__argv;
    int         argc=__argc;
#else
extern "C" {
    int main(int argc, const char **argv)
    {
#endif

        TSE app;

        app.setArgs(argc,argv);

        if(!app.initialize())
            app.run();

        return 0;
    }
#ifndef TUBRAS_PLATFORM_WIN32
}
#endif

