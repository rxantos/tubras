//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"
#include <stdlib.h>

using namespace Tubras;

//-----------------------------------------------------------------------
//                             i P r i n t f
//-----------------------------------------------------------------------
#ifdef TUBRAS_PLATFORM_WIN32
    HANDLE hStdOut=0;
    HANDLE hStdIn=0;
    void iPrintf(char *msg)
    {
        DWORD dwLen;
        WriteConsoleA(hStdOut,msg,strlen(msg),&dwLen,0);
    }
#else
    void iPrintf(char *msg)
    {
        printf(msg);
    }
#endif

//-----------------------------------------------------------------------
//                               T S E
//-----------------------------------------------------------------------
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
        toggleHelpGUI();
        return 1;
    }

    //-----------------------------------------------------------------------
    //                        t o g g l e D e b u g
    //-----------------------------------------------------------------------
    int toggleDebug(const TEvent* event)
    {
        toggleDebugGUI();
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
    //                             u s a g e
    //-----------------------------------------------------------------------
    void usage()
    {
#ifdef TUBRAS_PLATFORM_WIN32
        AttachConsole(ATTACH_PARENT_PROCESS);
        hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        hStdIn = GetStdHandle(STD_INPUT_HANDLE);
#endif
        iPrintf("\nUsage: tse [options]\n\n");
        iPrintf("options: -h, -?             This help.\n");
        iPrintf("         -i <script file>   Script file name to load.\n");        
        iPrintf("         -o <config option> Config option override.\n");

#ifdef TUBRAS_PLATFORM_WIN32
        DWORD dwEvents;
        INPUT_RECORD ir[2];
        ir[0].EventType = KEY_EVENT;
        ir[0].Event.KeyEvent.bKeyDown = TRUE;
        ir[0].Event.KeyEvent.dwControlKeyState = 0;
        ir[0].Event.KeyEvent.uChar.UnicodeChar = '\r';
        ir[0].Event.KeyEvent.wRepeatCount = 1;
        ir[0].Event.KeyEvent.wVirtualKeyCode = 0x0D;
        ir[0].Event.KeyEvent.wVirtualScanCode = MapVirtualKey(0x0D, MAPVK_VK_TO_VSC);
        ir[1].EventType = KEY_EVENT;
        ir[1].Event.KeyEvent.bKeyDown = FALSE;
        ir[1].Event.KeyEvent.dwControlKeyState = 0;
        ir[1].Event.KeyEvent.uChar.UnicodeChar = '\r';
        ir[1].Event.KeyEvent.wRepeatCount = 1;
        ir[1].Event.KeyEvent.wVirtualKeyCode = 0x0D;
        ir[1].Event.KeyEvent.wVirtualScanCode = MapVirtualKey(0x0D, MAPVK_VK_TO_VSC);
        WriteConsoleInputA(hStdIn, ir, 2, &dwEvents);
        FreeConsole();
#endif
    }

    //-----------------------------------------------------------------------
    //                          i n i t i a l i z e
    //-----------------------------------------------------------------------
    int initialize()
    {
        IAttributes* oattr = getConfigOverride();

        stringc scriptFileName="", option;

        int c;
        while ((c = getopt(m_argc,m_argv, "?hi:o:")) != EOF)
        {
            switch (c)
            {
            case 'i':
                scriptFileName = optarg;
                break;
            case 'o':
                {
                    option = optarg;
                    s32 sep = option.findFirstChar("=:", 2);
                    if(sep > 0)
                    {
                        stringc opt = option.subString(0, sep);
                        stringc val = option.subString(sep+1, option.size());
                        oattr->addString(opt.c_str(), val.c_str());
                    }
                }
                break;
            case 'h':
            case '?':
                usage();
                return 1;
                break;
            }        
        }

        if(TApplication::initialize())
            return 1;

        if(!scriptFileName.size())
        {
            if(optind < m_argc)
            {
                scriptFileName = m_argv[optind++];
            }
        }

        // script passed on command line?
        if(!scriptFileName.size())
            scriptFileName = m_configScript->getString("script.filepath");

        if(scriptFileName.size())
        {
            if(m_scriptManager->loadScript(scriptFileName))
                 return 1;
        }
        //
        // create and initialize the application/game states
        //
        logMessage(LOG_INFO, "Initialize States...");
        m_scriptManager->createStates();

        TStateMapItr sit;
        sit = m_states.getIterator();

        for(sit = m_states.getIterator();!sit.atEnd(); sit++)
        {
            TState* state = sit->getValue();
            if(state != this)
                if(state->initialize())
                    return 1;
        }

        //
        // add text to the help panel
        //
        addHelpText("wasd -", "Camera movement");
        addHelpText("   i -", "Invert mouse");
        addHelpText(" prt -", "Screen capture");
        addHelpText("  F1 -", "Toggle help");
        addHelpText("  F2 -", "Toggle debug");
        addHelpText("  F3 -", "Cycle wire/pts");
        addHelpText("  F4 -", "Toggle Phys dbg");
        addHelpText("  F5 -", "Cycle dbg data");
        addHelpText("  F6 -", "Toggle Xform");
        addHelpText("  F7 -", "Toggle Cursor");


        acceptEvent("help",EVENT_DELEGATE(TSE::toggleHelp));
        acceptEvent("idbg",EVENT_DELEGATE(TSE::toggleDebug));      
        acceptEvent("wire",EVENT_DELEGATE(TSE::toggleWire));  
        acceptEvent("pdbg",EVENT_DELEGATE(TSE::togglePhysicsDebug));      
        acceptEvent("cdbg",EVENT_DELEGATE(TSE::cycleDebug));
        acceptEvent("sprt",EVENT_DELEGATE(TSE::captureScreen));

        toggleHelpGUI();

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
