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
protected:
    TScript*        m_mainModule;

public:
    TSE() : TApplication("TSE")
    {
    }

    ~TSE() 
    {
    }

    //-----------------------------------------------------------------------
    //                        t o g g l e H e l p
    //-----------------------------------------------------------------------
    int toggleHelp(const TEvent* event)
    {
        toggleHelpOverlay();
        return 1;
    }

    //-----------------------------------------------------------------------
    //                        t o g g l e D e b u g
    //-----------------------------------------------------------------------
    int toggleDebug(const TEvent* event)
    {
        toggleDebugOverlay();
        return 1;
    }

    //-----------------------------------------------------------------------
    //                        c y c l e D e b u g
    //-----------------------------------------------------------------------
    int cycleDebug(const TEvent* event)
    {
        cycleDebugData();
        return 1;
    }

    //-----------------------------------------------------------------------
    //                 t o g g l e P h y s i c s D e b u g
    //-----------------------------------------------------------------------
    int togglePhysicsDebug(const TEvent* event)
    {
        TApplication::togglePhysicsDebug();
        return 1;
    }

    //-----------------------------------------------------------------------
    //                        t o g g l e W i r e
    //-----------------------------------------------------------------------
    int toggleWire(const TEvent* event)
    {
        TRenderMode mode = getRenderMode();

        if(mode == rmNormal)
            setRenderMode(rmWire);
        else if(mode == rmWire)
            setRenderMode(rmPointCloud);
        else if(mode == rmPointCloud)
            setRenderMode(rmNormal);

        return 1;
    }

    //-----------------------------------------------------------------------
    //                        c a p t u r e S c r e e n
    //-----------------------------------------------------------------------
    int captureScreen(const TEvent* event)
    {
        getRenderer()->captureScreen();
        return 1;
    }

    //-----------------------------------------------------------------------
    //                          i n i t i a l i z e
    //-----------------------------------------------------------------------
    int initialize()
    {
        if(TApplication::initialize())
            return 1;

        //
        // add text to the help panel
        //
        addHelpText("wasd - Camera movement");
        addHelpText("   i - Invert mouse");
        addHelpText(" prt - Screen capture");
        addHelpText("  F1 - Toggle help");
        addHelpText("  F2 - Toggle debug");
        addHelpText("  F3 - Cycle wire/pts");
        addHelpText("  F4 - Toggle Phys dbg");
        addHelpText("  F5 - Cycle dbg data");
        addHelpText("  F6 - Toggle Xform");
        addHelpText("  F7 - Toggle Cursor");


        acceptEvent("help",EVENT_DELEGATE(TSE::toggleHelp));
        acceptEvent("idbg",EVENT_DELEGATE(TSE::toggleDebug));      
        acceptEvent("wire",EVENT_DELEGATE(TSE::toggleWire));  
        acceptEvent("pdbg",EVENT_DELEGATE(TSE::togglePhysicsDebug));      
        acceptEvent("cdbg",EVENT_DELEGATE(TSE::cycleDebug));
        acceptEvent("sprt",EVENT_DELEGATE(TSE::captureScreen));

        this->toggleHelpOverlay();

        return 0;
    }

    //-----------------------------------------------------------------------
    //                        c r e a t e S t a t e s
    //-----------------------------------------------------------------------
    int createStates()
    {
        if(TApplication::createStates())
            return 1;

        if(!m_scriptManager)
        {
            logMessage(LOG_ERROR, "Error intializing script manager.");
            return 1;
        }

        m_scriptManager->createStates();

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
        //m_breakOnAlloc(150219);

        app.setArgs(argc,argv);

        if(!app.initialize())
            app.run();

        return 0;
    }
#ifndef TUBRAS_PLATFORM_WIN32
}
#endif

