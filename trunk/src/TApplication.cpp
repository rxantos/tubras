//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
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

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#endif

#ifdef TUBRAS_PLATFORM_WIN32
	#if !defined ( _WIN32_WCE )
		#include <io.h>
		#include <direct.h>
	#endif
#endif

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
    TApplication::TApplication(int argc,char** argv,const TString& appName) : TState("TApplication"),
        m_argc(argc),
        m_argv(argv),
        m_random(0),
        m_currentState(0),
        m_renderer(0),
        m_eventManager(0),
        m_controllerManager(0),
        m_soundManager(0),
        m_physicsManager(0),
        m_taskManager(0),
        m_inputManager(0),
        m_sceneLoader(0),
        m_debugOverlay(0),
        m_helpOverlay(0),
        m_nullDevice(0),
        m_config(0),
        m_debugUpdateFreq(500), // milliseconds
        m_logger(0),
        m_fpsAvg(0),m_fpsMin(0),m_fpsMax(0),
        m_appName(appName),
        m_debugData(EDS_OFF),
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
        if(m_helpOverlay)
            delete m_helpOverlay;

        if(m_debugOverlay)
            delete m_debugOverlay;

        if(m_taskManager)
            delete m_taskManager;

        if(m_physicsManager)
            delete m_physicsManager;

        if(m_soundManager)
            delete m_soundManager;

        if(m_renderer)
            m_renderer->drop();

        if(m_controllerManager)
            delete m_controllerManager;

        if(m_inputManager)
            delete m_inputManager;

        if(m_eventManager)
            delete m_eventManager;

        if(m_sceneLoader)
            m_sceneLoader->drop();

        if(m_nullDevice)
            m_nullDevice->drop();

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
    TString TApplication::changeFileExt(const TString& filename, const TString& newext) {
        TString      res;

        TFile       fileName(filename.c_str());

        fileName.set_extension(newext.c_str());

        res = fileName.c_str();

        return res;
    }

    //-----------------------------------------------------------------------
    //                            W n d P r o c
    //-----------------------------------------------------------------------
#ifdef TUBRAS_PLATFORM_WIN32
    LRESULT TApplication::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }
        return DefWindowProc( hWnd, uMsg, wParam, lParam );
    }
#endif


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
#ifdef TUBRAS_PLATFORM_WIN32
	#if !defined ( _WIN32_WCE )
		_getcwd(pdir, 512);
	#endif
#endif

#if (defined(_IRR_POSIX_API_) || defined(_IRR_OSX_PLATFORM_))
	    getcwd(pdir, 512);
#endif
        
        m_currentDirectory = pdir;
        free(pdir);

        m_appExecutable = m_argv[0];
        m_configName = changeFileExt(m_appExecutable,"cfg");
        m_logName = changeFileExt(m_appExecutable,"log");

        m_logger = new TLogger(m_logName);

        TString version = "Tubras Engine Version ";
        version += TUBRAS_VERSION_STRING;

        logMessage(version);

        m_nullDevice = createDevice(EDT_NULL);

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
        m_renderer->getDevice()->setWindowCaption(caption.c_str());

        m_globalClock = new TTimer(m_renderer->getTimer());

        m_display = 0;
        if(m_renderer->getVideoDriver()->getDriverType() == EDT_OPENGL)
        {
#ifdef TUBRAS_PLATFORM_WIN32
            //
            // replace irrlicht wndproc with ours to make ois work properly. 
            // NOT 64 bit safe!
            //
            HWND hwnd = (HWND)(m_renderer->getVideoDriver()->getExposedVideoData().OpenGLWin32.HWnd);
            GetWindowLong(hwnd, GWL_WNDPROC);
            SetWindowLongPtr(hwnd, GWL_WNDPROC, (LONG)&WndProc);
            m_windowHandle = (u32)hwnd;
#else

            m_windowHandle = (int)m_renderer->getVideoDriver()->getExposedVideoData().OpenGLLinux.X11Window;
            //m_windowHandle = (int)m_renderer->getVideoDriver()->getExposedVideoData().OpenGLLinux.X11Drawable;
            m_display = (int)m_renderer->getVideoDriver()->getExposedVideoData().OpenGLLinux.X11Display;

#endif
        }
        else
        {
            m_windowHandle = m_renderer->getVideoDriver()->getExposedVideoData().D3D9.HWnd;
        }

        //
        // custom scene/mesh loaders...
        //
        CIrrBMeshFileLoader* loader = new CIrrBMeshFileLoader(getSceneManager(),getFileSystem());
        getSceneManager()->addExternalMeshLoader(loader);
        loader->drop();

        //
        // our version of ".irrmesh"
        //
        TIrrMeshFileLoader* loader2 = new TIrrMeshFileLoader(getSceneManager(),getFileSystem());
        getSceneManager()->addExternalMeshLoader(loader2);
        loader2->drop();

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
#ifdef TUBRAS_INCLUDE_PHYSICS
        m_physicsManager = new TPhysicsManager();
        if(m_physicsManager->initialize())
            return 1;
#endif

        //
        // task system
        //
        m_taskManager = new TTaskManager();
        if(m_taskManager->initialize())
            return 1;

        // 
        // file systems
        //
        if(initFileSystems())
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

        //
        // create default "player"
        //
        m_playerController = createPlayerController();

        //
        // create debug node initially invisible
        //
        m_debugNode = (TDebugNode *)addSceneNode("TDebugNode",getRootSceneNode());
        m_debugNode->setVisible(false);

        logMessage(" ");
        logMessage("*** Tubras Core Initialized ***");
        logMessage(" ");

        return 0;
    }

    //-----------------------------------------------------------------------
    //                    i n i t F i l e S y s t e m s
    //-----------------------------------------------------------------------
    int TApplication::initFileSystems()
    {
        IAttributes* pa = m_config->getSection("filesystems");
        u32 count = pa->getAttributeCount();

        TString fs="",fn="";
        for(u32 i=0;i<count;i++)
        {
            fn = pa->getAttributeName(i);
            fs = pa->getAttributeAsString(i);
            if(fn.equals_ignore_case("folder"))
            {
                if(!getFileSystem()->addFolderFileArchive(fs.c_str()))
                {
                    TString msg = "Error Adding FileSystem: ";
                    msg += fs;
                    logMessage(msg.c_str());
                }
            }
            else if(fn.equals_ignore_case("zipfile"))
            {
                if(!getFileSystem()->addZipFileArchive(fs.c_str()))
                {
                    TString msg = "Error Adding FileSystem: ";
                    msg += fs;
                    logMessage(msg.c_str());
                }
            }
            else if(fn.equals_ignore_case("pakfile"))
            {
                if(!getFileSystem()->addPakFileArchive(fs.c_str()))
                {
                    TString msg = "Error Adding FileSystem: ";
                    msg += fs;
                    logMessage(msg.c_str());
                }
            }
            else 
            {
                TString msg = "Unknown FileSystem Type: ";
                msg += fn;
                logMessage(msg.c_str());
            }

        }
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

        m_inputManager = new TInputManager(m_windowHandle,m_display);
        if(m_inputManager->initialize())
            return 1;

        dimension2di dims = m_renderer->getVideoDriver()->getScreenSize();

        m_inputManager->setDisplaySize(dims.Width,dims.Height);
        return 0;
    }

    //-----------------------------------------------------------------------
    //                    i n i t R e n d e r E n g i n e
    //-----------------------------------------------------------------------
    int TApplication::initRenderEngine()
    {
        m_renderer = new TRenderer();
        return m_renderer->initialize();
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
#ifdef TUBRAS_PLATFORM_WIN32
        {
            if(m_bConsole)
            {
                AllocConsole();
                m_hConsole = (int)((intptr_t)GetStdHandle( STD_OUTPUT_HANDLE ));
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
            m_renderer->getCamera());
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
    //                  t o g g l e P h y s i c s D e b u g
    //-----------------------------------------------------------------------
    void TApplication::togglePhysicsDebug()
    {
        m_physicsManager->toggleDebug();
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
    void TApplication::addHelpText(const TString& text)
    {
        if(!m_helpOverlay)
            toggleHelpOverlay();

        m_helpOverlay->addItem(text);
    }

    //-----------------------------------------------------------------------
    //                    c y c l e D e b u g D a t a
    //-----------------------------------------------------------------------
    void TApplication::cycleDebugData()
    {
        if(!m_debugOverlay || !m_debugOverlay->getVisible())
            return;

        switch(m_debugData)
        {
        case EDS_OFF: m_debugData = EDS_BBOX; break;

        case EDS_BBOX: m_debugData = EDS_NORMALS; break;

        case EDS_NORMALS: m_debugData = EDS_SKELETON; break;

        case EDS_SKELETON: m_debugData = EDS_MESH_WIRE_OVERLAY; break;

        case EDS_MESH_WIRE_OVERLAY: m_debugData = EDS_HALF_TRANSPARENCY; break;

        case EDS_HALF_TRANSPARENCY: m_debugData = EDS_BBOX_BUFFERS; break;

        case EDS_BBOX_BUFFERS: m_debugData = EDS_BBOX_ALL; break;

        case EDS_BBOX_ALL: m_debugData = EDS_FULL; break;

        case EDS_FULL: m_debugData = EDS_OFF; break;

        }
        m_renderer->setDebugMode(m_debugData);
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
            m_debugOverlay->addItem("Visible Debug Data:", taCenter);

            m_debugOverlay->setVisible(true);
            TTaskDelegate* td = TASK_DELEGATE(TApplication::showDebugInfo);
            m_renderer->setDebugMode(m_debugData);
            m_debugTask = new TTask("debugTask",td,0,0,NULL,"");
            m_debugTask->start();
            
        }
        else
        {
            if(m_debugOverlay->getVisible())
            {
                m_debugOverlay->setVisible(false);
                m_renderer->setDebugMode(EDS_OFF);
                m_debugTask->stop();
            }
            else 
            {
                m_debugOverlay->setVisible(true);
                m_renderer->setDebugMode(m_debugData);
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

            IVideoDriver* video = m_renderer->getVideoDriver();
            u32 tris = video->getPrimitiveCountDrawn();

            TCameraNode* camera = m_renderer->getCamera();

            TVector3 pos = camera->getAbsolutePosition();
            TVector3 dir = camera->getTarget();
            TVector3 rot = camera->getRotation();

            sprintf(buf,"Camera: Pos(%.1f,%.1f,%.1f) Hpr(%.1f,%.1f,%.1f) Dir(%.1f,%.1f,%.1f)",
                pos.X,pos.Y,pos.Z,rot.Y,rot.X,rot.Z,dir.X,dir.Y,dir.Z);
            m_debugOverlay->updateItem(0,buf);

            sprintf(buf,"Frame: Avg(%d) Min(%d) Max(%d), Tris(%d)",
                m_fpsAvg, m_fpsMin, m_fpsMax, tris);

            m_debugOverlay->updateItem(1,buf);
            TString ddata;
            switch(m_debugData)
            {
            case EDS_OFF: ddata = "None"; break;

            case EDS_BBOX: ddata = "Bounding Boxes"; break;

            case EDS_NORMALS: ddata = "Normals"; break;

            case EDS_SKELETON: ddata = "Skeleton"; break;

            case EDS_MESH_WIRE_OVERLAY: ddata = "Mesh Wire Overlay"; break;

            case EDS_HALF_TRANSPARENCY: ddata = "Half Transparency"; break;

            case EDS_BBOX_BUFFERS: ddata = "Bounding Box Buffers"; break;

            case EDS_BBOX_ALL: ddata = "Bounding Box & Buffers"; break;

            case EDS_FULL: ddata = "Full"; break;

            }
            sprintf(buf,"Visible Debug Data: %s",ddata.c_str());
            m_debugOverlay->updateItem(2,buf);

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
    int TApplication::changeState(const TString& stateName)
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
    int TApplication::pushState(const TString& stateName)
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
    void TApplication::logMessage(const TString& msg,DEBUG_LEVEL level)
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
        //
        // Eat all of the irrlicht generated events so OIS can do it's processing.
        // This means currently none of the irrlicht supplied camera will
        // receive input.  eventually we should supply a "mode" that 
        // controls whether or not we feed the scenemanager event receiver.
        //
        if(event.EventType == EET_LOG_TEXT_EVENT)
        {
            logMessage(event.LogEvent.Text);
        }
        else if(event.EventType == EET_GUI_EVENT)
        {
            EGUI_EVENT_TYPE etype = event.GUIEvent.EventType;
            if(etype == EGET_BUTTON_CLICKED)
            {
                int i = 0;
                TEvent* tevent = new TEvent("gui.clicked");
                tevent->addIntParameter(event.GUIEvent.Caller->getID());

                sendEvent(tevent);
                tevent->drop();                
            }
            else if(etype == EGET_MENU_ITEM_SELECTED)
            {
				IGUIContextMenu* menu = (IGUIContextMenu*)event.GUIEvent.Caller;
				s32 id = menu->getItemCommandId(menu->getSelectedItem());
                int i = 0;
                TEvent* tevent = new TEvent("gui.clicked");
                tevent->addIntParameter(id);

                sendEvent(tevent);
                tevent->drop();                
            }



            return false;
        }

        return false;
    }

    //-----------------------------------------------------------------------
    //                              r u n 
    //-----------------------------------------------------------------------
    void TApplication::run()
    {

        TStrStream msg; 
        IVideoDriver* video = m_renderer->getVideoDriver();


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
#ifdef TUBRAS_INCLUDE_PHYSICS
            m_physicsManager->step(m_deltaTime);
#endif

            //
            // process sound
            //
            m_soundManager->step();

            //
            // render frame
            //
            if(!m_renderer->renderFrame())
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
