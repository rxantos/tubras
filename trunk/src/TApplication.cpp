//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006-2007 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 59 Temple
// Place - Suite 330, Boston, MA 02111-1307, USA, or go to
// http://www.gnu.org/copyleft/lesser.txt.
//
// You may alternatively use this source under the terms of a specific version of
// the Tubras Unrestricted License provided you have obtained such a license from
// Tubras Software Ltd.
//-----------------------------------------------------------------------------

#include "tubras.h"
#include <direct.h>

static Tubras::TApplication *theApp=0;


namespace Tubras
{
    extern TString keycodes[];

    char create_registry_sql[] =
        "CREATE TABLE registry (\n"
        "   section  VARCHAR(255),\n"
        "   key      VARCHAR(255),\n"
        "   value    VARCHAR(255)\n"
        ");\n";

    char select_registry_sql[] =
        "SELECT * from registry where section = \"default\"\n";

    TApplication *getApplication() {
        return theApp;
    }

    //-----------------------------------------------------------------------
    //                       T A p p l i c a t i o n
    //-----------------------------------------------------------------------
    TApplication::TApplication(int argc,char** argv,TString appName) : TState("TApplication"),
        m_argc(argc),
        m_argv(argv),
        m_random(0),
        m_currentState(0),
        m_render(0),
        m_eventManager(0),
        m_inputBinder(0),
        m_controllerManager(0),
        m_soundManager(0),
        m_config(0),
        m_logger(0),
        m_appName(appName),
        m_initialState("")
    {
        theApp = this;
    }

    //-----------------------------------------------------------------------
    //                      ~ T A p p l i c a t i o n
    //-----------------------------------------------------------------------
    TApplication::~TApplication()
    {
        if(m_soundManager)
            delete m_soundManager;

        if(m_nodeFactory)
            m_nodeFactory->drop();

        if(m_render)
            m_render->drop();

        if(m_controllerManager)
            delete m_controllerManager;

        if(m_eventManager)
            delete m_eventManager;

        if(m_inputBinder)
            delete m_inputBinder;

        if(m_config)
            m_config->drop();

        if(m_globalClock)
            m_globalClock->drop();

        if(m_random)
            m_random->drop();

        if(m_logger)
            delete m_logger;
    }

    //-----------------------------------------------------------------------
    //                   g e t S i n g l e t o n P t r
    //-----------------------------------------------------------------------
    template<> TApplication* TSingleton<TApplication>::ms_Singleton = 0;

    TApplication* TApplication::getSingletonPtr(void)
    {
        return ms_Singleton;
    }

    //-----------------------------------------------------------------------
    //                       g e t S i n g l e t o n
    //-----------------------------------------------------------------------
    TApplication& TApplication::getSingleton(void)
    {
        assert( ms_Singleton );  return ( *ms_Singleton );
    }

    //-----------------------------------------------------------------------
    //                       c h a n g e F i l e E x t
    //-----------------------------------------------------------------------
    TString TApplication::changeFileExt(TString filename,TString newext) {
        TString      res;
        char        path[_MAX_PATH];
        char        drive[_MAX_DRIVE];
        char        dir[_MAX_DIR];
        char        file[_MAX_FNAME];
        char        ext[_MAX_EXT];

        _splitpath_s(filename.c_str(),drive,sizeof(drive),
            dir,sizeof(dir),file,sizeof(file),ext,sizeof(ext));

        _makepath_s(path,sizeof(path),drive,dir,file,newext.c_str());

        res = path;

        return res;
    }

    //-----------------------------------------------------------------------
    //                         i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TApplication::initialize()
    {

        if(TObject::initialize())
            return 1;

        //
        // random number generator
        //
        m_random = new TRandom();
        m_random->randomize();

        //
        // configuration system
        //
        char* pdir = (char*)malloc(512);
        _getcwd(pdir,512);
        m_currentDirectory = pdir;
        free(pdir);

        m_appExecutable = m_argv[0];
        m_configName = changeFileExt(m_appExecutable,".cfg");
        m_logName = changeFileExt(m_appExecutable,".log");

        m_logger = new TLogger(m_logName);

        TString version = "Tubras Engine Version ";
        version += TUBRAS_VERSION_STRING;

        logMessage(version);


        logMessage("Initialize Configuration...");

        if(initConfig())
            return 1;

        logMessage("Initialize Input Binder...");
        m_inputBinder = new TInputBinder();
        if(m_inputBinder->initialize())
            return 1;

        //
        // render engine and global clock
        //
        logMessage("Initialize Render Engine...");
        if(initRenderEngine())
            return 1;

        stringw caption = m_appName.c_str();
        m_render->getDevice()->setWindowCaption(caption.c_str());

        m_globalClock = new TTimer(m_render->getTimer());

        //
        // event manager
        //
        logMessage("Initialize Event Manager...");
        m_eventManager = new TEventManager();
        if(m_eventManager->initialize())
            return 1;

        //
        // controller manager
        //
        logMessage("Initialize Controller Manager...");
        m_controllerManager = new TControllerManager();
        if(m_controllerManager->initialize())
            return 1;

        //
        // our scene node factory
        //

        logMessage("Initialize Tubras Node Factory...");
        m_nodeFactory = new TNodeFactory();
        if(m_nodeFactory->initialize())
            return 1;

        //
        // input system
        //
        logMessage("Initialize Input System...");
        if(initInputSystem())
            return 1;

        logMessage(" ");
        logMessage("*** Tubras Core Initialized ***");
        logMessage(" ");

        //
        // sound system
        //
        if(initSoundSystem())
            return 1;

        //
        // create and initialize the application/game states
        //
        logMessage("Initialize States...");
        if(createStates())
            return 1;

        TStateMapItr sit;
        sit = m_states.getIterator();
        

        for(sit = m_states.getIterator();!sit.atEnd(); sit++)
        {
            TState* state = sit->getValue();
            if(state->initialize())
                return 1;
        }

        return 0;
    }

    //-----------------------------------------------------------------------
    //                    i n i t S o u n d S y s t e m
    //-----------------------------------------------------------------------
    int TApplication::initSoundSystem()
    {
        m_soundManager = NULL;        
        TString temp = m_config->getString("engine","sound","NULL");
        if(temp == "NULL")
            m_soundManager = new TNullSoundManager();

        else if(temp == "FMOD")
        {
#ifdef USE_FMOD_SOUND
            try
            {
                m_soundManager = new TFMSoundManager();
            }
            catch(...)
            {
                m_soundManager = new TNullSoundManager();
            }
#endif
        }

        if(!m_soundManager)
            m_soundManager = new TNullSoundManager();


        if(m_soundManager->initialize())
            return 1;

        return 0;
    }

    //-----------------------------------------------------------------------
    //                    i n i t I n p u t S y s t e m
    //-----------------------------------------------------------------------
    int TApplication::initInputSystem()
    {
        return 0;
    }

    //-----------------------------------------------------------------------
    //                    i n i t R e n d e r E n g i n e
    //-----------------------------------------------------------------------
    int TApplication::initRenderEngine()
    {
        m_render = new TRender();
        return m_render->initialize();
    }

    //-----------------------------------------------------------------------
    //                        i n i t C o n f i g 
    //-----------------------------------------------------------------------
    int TApplication::initConfig()
    {
        m_config = new TXMLConfig();

        if(!m_config->load(m_configName))
            return 1;


        m_bConsole = m_config->getBool("console","options");
        m_debug = m_config->getInt("debug","options");

        //
        // create a console window
        //
#ifdef WIN32
        {
            if(m_bConsole)
            {
                AllocConsole();
                m_hConsole = (int)GetStdHandle( STD_OUTPUT_HANDLE );
                freopen("CONOUT$", "a", stdout);
            }
            else m_hConsole = 0;
        }
#else   
        m_hConsole = 0;
#endif



        return 0;
    }

    //-----------------------------------------------------------------------
    //                          a d d S t a t e
    //-----------------------------------------------------------------------
    int TApplication::addState(TState *state)
    {
        m_states[state->getName()]  = state;
        return 0;
    }

    //-----------------------------------------------------------------------
    //                       c h a n g e S t a t e
    //-----------------------------------------------------------------------
    int TApplication::changeState(TString stateName)
    {
        /*
        TState *state;
        bool GUIEnabled=false;

        if(!m_stateStack.empty())
        {
            state = m_stateStack.front();
            state->Pause();
        }

        state = m_states[stateName];
        if(state)
        {
            m_stateStack.push_front(state);
            state->Enter();
            m_currentState = state;
        }
        else
        {
            TStrStream msg;
            msg << "Invalid State: " << stateName << " (Not Found)";
            logMessage(msg.str().c_str());
            m_currentState = NULL;
        }
        */

        return 0;
    }

    //-----------------------------------------------------------------------
    //                         p u s h S t a t e
    //-----------------------------------------------------------------------
    int TApplication::pushState(TString stateName)
    {
        /*
        TState *state;

        if(!m_stateStack.empty())
        {
            state = m_stateStack.front();
            state->Pause();
        }

        state = m_states[stateName];
        m_stateStack.push_front(state);
        state->Enter();
        m_currentState = state;
        */

        return 0;
    }

    //-----------------------------------------------------------------------
    //                          p o p S t a t e
    //-----------------------------------------------------------------------
    int TApplication::popState()
    {
        /*
        TState *state;
        TStateInfo* prevInfo=NULL;

        m_currentState = NULL;
        if(!m_stateStack.empty())
        {
            state = m_stateStack.front();
            prevInfo = state->Exit();
            m_stateStack.pop_front();
        }

        if(!m_stateStack.empty())
        {
            state = m_stateStack.front();
            state->Resume(prevInfo);
            m_currentState = state;
        }
        else
        {
            //
            // the last state was popped
            //
            m_currentState = NULL;
        }
        */

        return 0;
    }

    //-----------------------------------------------------------------------
    //                         l o g M e s s a g e
    //-----------------------------------------------------------------------
    void TApplication::logMessage(TString msg,DEBUG_LEVEL level)
    {
        if(m_logger && m_debug && (level <= m_debug))
            m_logger->logMessage(msg);

        if(m_hConsole)
        {
            printf(msg.c_str());
            printf("\n");
        }

        return;
    }

    //-----------------------------------------------------------------------
    //                              O n E v e n t
    //-----------------------------------------------------------------------
    bool TApplication::OnEvent(const SEvent &  event)
    {
        if(event.EventType == EET_KEY_INPUT_EVENT)
        {
            sendKeyEvent(event.KeyInput);
            if(event.KeyInput.Key == KEY_ESCAPE)
            {
                m_running = false;
                return true;
            }
        }
        else if(event.EventType == EET_MOUSE_INPUT_EVENT)
        {
            sendMouseEvent(event.MouseInput);
        }
        else if(event.EventType == EET_LOG_TEXT_EVENT)
        {
            logMessage(event.LogEvent.Text);
            return true;
        }
        return false;
    }

    //-----------------------------------------------------------------------
    //                           s e n d K e y E v e n t
    //-----------------------------------------------------------------------
    bool TApplication::sendKeyEvent(const SEvent::SKeyInput& input)
    {
        TString msg = "key.";
        if(input.PressedDown)
            msg += "down.";
        else msg += "up.";
        msg += keycodes[input.Key];

        TEvent* event = new TEvent(msg);
        int rc = m_eventManager->send(event);
        event->drop();

        m_inputBinder->processKey(msg);
        return rc ? true : false;

    }

    //-----------------------------------------------------------------------
    //                        s e n d M o u s e E v e n t
    //-----------------------------------------------------------------------
    bool TApplication::sendMouseEvent(const SEvent::SMouseInput& input)
    {
        /*
        TString msg = "mouse.";
        if(input.
            msg += "down.";
        else msg += "up.";

        TEvent* event = new TEvent(msg);
        int rc = m_eventManager->send(event);
        event->drop();

        m_inputBinder->processKey(msg);
        return rc ? true : false;
        */
        return false;

    }

    //-----------------------------------------------------------------------
    //                              r u n 
    //-----------------------------------------------------------------------
    void TApplication::run()
    {

        TString msg; 

        //
        // using state management?
        //
        if(m_initialState != "")
        {
            pushState(m_initialState);
        }
        else m_currentState = (TState *) this;

        logMessage("Entering Run Loop");
        m_running = true;
        m_lastTime = m_globalClock->getMilliseconds();

        while(m_running)
        {
            //
            // calculate time since last update (milliseconds)
            // ... this can't be accurate - re-examine later ...
            //
            m_currentTime = m_globalClock->getMilliseconds();

            m_deltaTime = (m_currentTime - m_lastTime);

            m_lastTime = m_currentTime;

            preRender(m_deltaTime);

            //
            // process events
            //
            m_eventManager->step();

            //
            // process controllers
            //
            m_controllerManager->step();

            //
            // process sound
            //
            m_soundManager->step();

            //
            // render frame
            //
            if(!m_render->renderFrame())
                break;

            ++m_frames;
        }

        logMessage("Exiting Run Loop");
    }

}