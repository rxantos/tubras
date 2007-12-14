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
        m_controllerManager(0),
        m_soundManager(0),
        m_physicsManager(0),
        m_taskManager(0),
        m_inputManager(0),
        m_debugOverlay(0),
        m_helpOverlay(0),
        m_config(0),
        m_debugUpdateFreq(500), // milliseconds
        m_logger(0),
        m_fpsAvg(0),m_fpsMin(0),m_fpsMax(0),
        m_appName(appName),
        m_initialState("")
    {
        theApp = this;
        memset(m_keys,0,sizeof(m_keys));
    }

    //-----------------------------------------------------------------------
    //                      ~ T A p p l i c a t i o n
    //-----------------------------------------------------------------------
    TApplication::~TApplication()
    {
        if(m_taskManager)
            delete m_taskManager;

        if(m_physicsManager)
            delete m_physicsManager;

        if(m_soundManager)
            delete m_soundManager;

        if(m_render)
            m_render->drop();

        if(m_controllerManager)
            delete m_controllerManager;

        if(m_inputManager)
            delete m_inputManager;

        if(m_eventManager)
            delete m_eventManager;

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

        //
        // event manager
        //
        logMessage("Initialize Event Manager...");
        m_eventManager = new TEventManager();
        if(m_eventManager->initialize())
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


        if(m_render->getVideoDriver()->getDriverType() == EDT_OPENGL)
            m_windowHandle = m_render->getVideoDriver()->getExposedVideoData().OpenGLWin32.HWnd;
        else m_windowHandle = m_render->getVideoDriver()->getExposedVideoData().D3D9.HWnd;

        //
        // input system
        //
        logMessage("Initialize Input Manager...");
        if(initInputSystem())
            return 1;

        //
        // controller manager
        //
        logMessage("Initialize Controller Manager...");
        m_controllerManager = new TControllerManager();
        if(m_controllerManager->initialize())
            return 1;

        //
        // sound system
        //
        if(initSoundSystem())
            return 1;

        //
        // collision/physics system
        //
        m_physicsManager = new TPhysicsManager();
        if(m_physicsManager->initialize())
            return 1;

        //
        m_taskManager = new TTaskManager();
        if(m_taskManager->initialize())
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

        m_playerController = createPlayerController();

        logMessage(" ");
        logMessage("*** Tubras Core Initialized ***");
        logMessage(" ");

        return 0;
    }

    //-----------------------------------------------------------------------
    //                    i n i t S o u n d S y s t e m
    //-----------------------------------------------------------------------
    int TApplication::initSoundSystem()
    {
        m_soundManager = NULL;        
#ifdef USE_FMOD_SOUND
        {
            try
            {
                m_soundManager = new TFMSoundManager();
            }
            catch(...)
            {
                m_soundManager = new TNullSoundManager();
            }
        }
#elif USE_IRR_SOUND
        {
            try
            {
                m_soundManager = new TIrrSoundManager();
            }
            catch(...)
            {
                m_soundManager = new TNullSoundManager();
            }
        }
#endif

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
        TString	msg;

        //
        // Initialize the Input System (OIS)
        //
        msg = "Initializing Input System";
        logMessage(msg.c_str());

        m_inputManager = new TInputManager(m_windowHandle);
        if(m_inputManager->initialize())
            return 1;

        dimension2di dims = m_render->getVideoDriver()->getScreenSize();

        m_inputManager->setDisplaySize(dims.Width,dims.Height);
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
                FILE* fp;
                freopen_s(&fp,"CONOUT$", "a", stdout);
            }
            else m_hConsole = 0;
        }
#else   
        m_hConsole = 0;
#endif
        return 0;
    }

    //-----------------------------------------------------------------------
    //                c r e a t e P l a y e r C o n t r o l l e r 
    //-----------------------------------------------------------------------
    TPlayerController* TApplication::createPlayerController()
    {
        TPlayerController* controller =  new TPlayerController("DefaultPlayerController",
            m_render->getCamera());
        controller->setEnabled(true);
        return controller;
    }

    //-----------------------------------------------------------------------
    //                 c r e a t e D e f a u l t C a m e r a 
    //-----------------------------------------------------------------------
    TCameraNode* TApplication::createDefaultCamera()
    {

        TCameraNode* camera = (TCameraNode*)addSceneNode("TCameraNode", getRootSceneNode());

        camera->setPosition(TVector3(0,5,-100));
        camera->setTarget(TVector3(0,0,0));

        return camera;
    }

    //-----------------------------------------------------------------------
    //                    t o g g l e H e l p O v e r l a y
    //-----------------------------------------------------------------------
    void TApplication::toggleHelpOverlay()
    {
        if(!m_helpOverlay)
        {
            m_helpOverlay = new TTextOverlay("DebugInfo",TRect(0.005f,0.005f,0.245f,0.05f));
            m_helpOverlay->setVisible(true);
            IGUIFont* font = getGUIManager()->getFont("monospace.xml");
            if(font)
                m_helpOverlay->setFont(font);
            m_helpOverlay->addItem("Help", taCenter); 

        }
        else
        {
            if(m_helpOverlay->getVisible())
            {
                m_helpOverlay->setVisible(false);
            }
            else
            {
                m_helpOverlay->setVisible(true);
            }
        }
    }

    //-----------------------------------------------------------------------
    //                         a d d H e l p T e x t
    //-----------------------------------------------------------------------
    void TApplication::addHelpText(TString text)
    {
        if(!m_helpOverlay)
            toggleHelpOverlay();

        m_helpOverlay->addItem(text);
    }

    //-----------------------------------------------------------------------
    //                    t o g g l e D e b u g O v e r l a y
    //-----------------------------------------------------------------------
    void TApplication::toggleDebugOverlay()
    {

        if(!m_debugOverlay)
        {
            m_debugOverlay = new TTextOverlay("DebugInfo",TRect(0.25f,0.005f,0.75f,0.05f));
            m_debugOverlay->addItem("Camera: Pos(x,y,z) Hpr(x,y,z) Dir(x,y,z)", taCenter);
            m_debugOverlay->addItem("Frame: Avg(0.0) Min(0.0) Max(0.0)", taCenter);

            m_debugOverlay->setVisible(true);
            TTaskDelegate* td = TASK_DELEGATE(TApplication::showDebugInfo);
            m_debugTask = new TTask("debugTask",td,0,0,NULL,"");
            m_debugTask->start();
        }
        else
        {
            if(m_debugOverlay->getVisible())
            {
                m_debugOverlay->setVisible(false);
                m_debugTask->stop();
            }
            else 
            {
                m_debugOverlay->setVisible(true);
                m_debugTask->start();
            }
        }
    }

    //-----------------------------------------------------------------------
    //                       s h o w D e b u g I n f o
    //-----------------------------------------------------------------------
    int TApplication::showDebugInfo(TTask* task)
    {


        if(task->m_elapsedTime >= m_debugUpdateFreq)
        {

            //
            // update and reset time
            //
            char buf[128];

            IVideoDriver* video = m_render->getVideoDriver();
            u32 tris = video->getPrimitiveCountDrawn();

            TCameraNode* camera = m_render->getCamera();

            TVector3 pos = camera->getAbsolutePosition();
            TVector3 dir = camera->getTarget();
            TVector3 rot = camera->getRotation();

            sprintf(buf,"Camera: Pos(%.1f,%.1f,%.1f) Hpr(%.1f,%.1f,%.1f) Dir(%.1f,%.1f,%.1f)",
                pos.X,pos.Y,pos.Z,rot.Y,rot.X,rot.Z,dir.X,dir.Y,dir.Z);
            m_debugOverlay->updateItem(0,buf);

            sprintf(buf,"Frame: Avg(%d) Min(%d) Max(%d), Tris(%d)",
                m_fpsAvg, m_fpsMin, m_fpsMax, tris);

            m_debugOverlay->updateItem(1,buf);

            TStringVector debugStrings;
            setUserDebugInfo(debugStrings);

            if(debugStrings.size() > 0)
            {
                while((debugStrings.size()+3) > m_debugOverlay->getItemCount())
                {
                    m_debugOverlay->addItem(" " ,taCenter);
                }

                for(u32 i=0;i<debugStrings.size();i++)
                {
                    m_debugOverlay->updateItem(i+3,debugStrings[i]);
                }

            }

            task->m_elapsedTime = 0;
        }

        return TTask::cont;
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
        if(event.EventType == EET_LOG_TEXT_EVENT)
        {
            logMessage(event.LogEvent.Text);
            return true;
        }
        return true;
    }

    //-----------------------------------------------------------------------
    //                              r u n 
    //-----------------------------------------------------------------------
    void TApplication::run()
    {

        TStrStream msg; 
        IVideoDriver* video = m_render->getVideoDriver();


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
            // process input
            //
            m_inputManager->step();

            //
            // process events
            //
            m_eventManager->step();

            //
            // process controllers
            //
            m_controllerManager->step();

            //
            // process tasks
            //
            m_taskManager->step();

            //
            // update physics & collision detection
            //
            m_physicsManager->step(m_deltaTime);

            //
            // process sound
            //
            m_soundManager->step();

            //
            // render frame
            //
            if(!m_render->renderFrame())
                break;

            //
            // update stats
            //
            m_fpsAvg = video->getFPS();
            if((m_fpsMin < 10) || (m_fpsAvg < m_fpsMin))
                m_fpsMin  = m_fpsAvg;
            if(!m_fpsMax || (m_fpsAvg > m_fpsMax))
                m_fpsMax  = m_fpsAvg;
            ++m_frames;
        }

        logMessage("Exiting Run Loop");
        msg << "Frame Rate - Avg: " << m_fpsAvg << ", Min: " << m_fpsMin
            << ", Max: " << m_fpsMax;
        logMessage(msg.str().c_str());
    }

}