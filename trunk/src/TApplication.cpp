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

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#endif

#ifdef TUBRAS_PLATFORM_WINDOWS
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
    TApplication::TApplication(const TString& appName) : TState("TApplication"),
        m_argc(0),
        m_argv(0),
        m_initialState(""),
        m_appExecutable(""),
        m_configFileName(""),
        m_appName(appName),
        m_initialized(false),
        m_currentState(0),
        m_globalClock(0),
        m_configScript(0),
        m_random(0),
        m_debugData(EDS_OFF),
        m_logger(0),
        m_renderer(0),
        m_eventManager(0),
        m_controllerManager(0),
        m_soundManager(0),
        m_physicsManager(0),
        m_characterController(0),
        m_taskManager(0),
        m_inputManager(0),
        m_scriptManager(0),
        m_particleManager(0),
        m_entityManager(0),
        m_nullDevice(0),
        m_sceneLoader(0),
        m_guiScreen(0),
        m_guiConsole(0),
        m_guiDebug(0),
        m_guiHelp(0),
        m_debugNode(0),
        m_debugTask(0),
        m_debugUpdateFreq(500), // milliseconds
        m_fpsAvg(0),m_fpsMin(0),m_fpsMax(0),
        m_debug(LOG_INFO)
    {
        theApp = this;
        memset(m_keys,0,sizeof(m_keys));
        m_nullDevice = createDevice(EDT_NULL);
        m_configOverride = m_nullDevice->getFileSystem()->createEmptyAttributes();
    }

    //-----------------------------------------------------------------------
    //                      ~ T A p p l i c a t i o n
    //-----------------------------------------------------------------------
    TApplication::~TApplication()
    {

        if(m_currentState)
            m_currentState->Exit();

        
        TStateMapItr itr = m_states.getIterator();

        while(!itr.atEnd())
        {
            TState* state = itr->getValue();
            delete state;
            itr++;
        }

        if(m_guiConsole)
            m_guiConsole->drop();

        if(m_guiDebug)
            m_guiDebug->drop();

        if(m_guiHelp)
            m_guiHelp->drop();

        if(m_guiScreen)
            m_guiScreen->drop();

        if(m_scriptManager)
            delete m_scriptManager;

        if(m_entityManager)
            delete m_entityManager;

        if(m_particleManager)
            delete m_particleManager;

        if(m_taskManager)
            delete m_taskManager;

        if(m_controllerManager)
            delete m_controllerManager;

        if(m_physicsManager)
            delete m_physicsManager;

        if(m_soundManager)
            delete m_soundManager;

        if(m_inputManager)
            delete m_inputManager;

        if(m_renderer)
            m_renderer->drop();

        if(m_eventManager)
            delete m_eventManager;

        if(m_sceneLoader)
            m_sceneLoader->drop();

        if(m_configOverride)
            m_configOverride->drop();

        if(m_nullDevice)
            m_nullDevice->drop();

        if(m_configScript)
            m_configScript->drop();

        if(m_globalClock)
            m_globalClock->drop();

        if(m_random)
            m_random->drop();

        if(m_logger)
            delete m_logger;
    }

    //-----------------------------------------------------------------------
    //                       c h a n g e F i l e E x t
    //-----------------------------------------------------------------------
    TString TApplication::changeFileExt(const TString& filename, const TString& newext) {
        IFileSystem* fs = m_nullDevice->getFileSystem();
        path base = fs->getFileBasename(filename, false);
        base += ".";
        base += newext;

        io::path newFileName = fs->getFileDir(filename) + "/" + base;
        return newFileName.replace('\\', '/');
    }

    //-----------------------------------------------------------------------
    //                         i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TApplication::initialize()
    {
        TState::initialize();

        m_globalClock = new TTimer();

        //
        // random number generator
        //
        m_random = new TRandom();
        m_random->randomize();

        //
        // configuration system
        //
        char* pdir = (char*)malloc(512);
#ifdef TUBRAS_PLATFORM_WINDOWS
#if !defined ( _WIN32_WCE )
        _getcwd(pdir, 512);
#endif
#endif

#if (defined(_IRR_POSIX_API_) || defined(_IRR_OSX_PLATFORM_))
        pdir = getcwd(pdir, 512);
#endif

        m_currentDirectory = pdir;
        free(pdir);


        if(m_argv)
        {
            m_appExecutable = m_argv[0];
        }
        else
        {
            m_appExecutable = m_appName;
        }

#ifdef TUBRAS_PLATFORM_WINDOWS
        char buf[MAX_PATH];
        GetModuleFileName(0, buf, sizeof(buf));
        m_appExecutable = buf;
#endif
        //
        // locate the data directory - underneath our executable or outside of it.
        IFileSystem* fs = m_nullDevice->getFileSystem();
        irr::io::path temp="data/";
        if(!fs->existFile(temp))
        {
            temp = "../data/";
            // todo - look for "data.zip"...
        }
        m_dataRoot = fs->getAbsolutePath(temp);
        
        // if previously set then make sure it exists
        if(m_configFileName.size())
        {
            if(!m_nullDevice->getFileSystem()->existFile(m_configFileName))
                m_configFileName = "";
        }

        // First, look for config file with ".cfg" extension if not already set.
        if(!m_configFileName.size())
        {
            temp = changeFileExt(m_appExecutable,"cfg").c_str();
            m_configFileName = m_dataRoot;
            m_configFileName += "cfg/";
            m_configFileName += fs->getFileBasename(temp.c_str());

            temp = m_configFileName.c_str();
            if(!fs->existFile(temp))
            {
                // no ".cfg" so look for default appropriate for language type.
                temp = changeFileExt(m_appExecutable,"cfg").c_str();
                m_configFileName = m_dataRoot;
                m_configFileName += "cfg/";
                m_configFileName += fs->getFileBasename(temp);
                if(!fs->existFile(m_configFileName))
                    m_configFileName = "default.cfg";
            }
        }

        m_logName = changeFileExt(m_appExecutable,"log");

        m_logger = new TLogger(m_logName);

        logMessage(LOG_INFO, "Tubras Engine Version %s", TUBRAS_VERSION_STRING);

        int arch=86;
		if(sizeof(char *) == 8)
			arch=64;
#ifdef _DEBUG
        logMessage(LOG_INFO, "Build Mode: Debug x%d",arch);
#else
        logMessage(LOG_INFO, "Build Mode: Release x%d", arch);
#endif
#ifdef PROFILING_ENABLED
        logMessage(LOG_INFO, "Profiling: Enabled");
#else
        logMessage(LOG_INFO, "Profiling: Disabled");
#endif
        logMessage(LOG_INFO, "Application: %s", m_appExecutable.c_str());
        logMessage(LOG_INFO, "Current Directory: %s", m_currentDirectory.c_str());
        logMessage(LOG_INFO, "Data Root: %s", m_dataRoot.c_str());
        logMessage(LOG_INFO, "Config File: %s", m_configFileName.c_str());

        logMessage(LOG_INFO, "Initialize Configuration...");

        if(initConfig())
            return 1;

        m_bConsole = m_configScript->getBool("options.console");
        m_debug = m_configScript->getInteger("options.debug");

        //
        // create a console window
        //
        m_hConsole = 0;
#ifdef TUBRAS_PLATFORM_WINDOWS
        {
            if(m_bConsole)
            {
                AllocConsole();
                m_hConsole = (int)((intptr_t)GetStdHandle( STD_OUTPUT_HANDLE ));
                FILE* fp;
                fp = freopen("CONOUT$", "a", stdout);
            }
        }
#else   
        if(m_bConsole)
            m_hConsole = 1;
#endif

        //
        // event manager
        //
        logMessage(LOG_INFO, "Initialize Event Manager...");
        m_eventManager = new TEventManager();
        if(m_eventManager->initialize())
            return 1;

        //
        // render engine and global clock
        //
        logMessage(LOG_INFO, "Initialize Render Engine...");
        if(initRenderEngine())
            return 1;

        stringw caption = m_appName.c_str();
        m_renderer->getDevice()->setWindowCaption(caption.c_str());

        m_display = 0;
        m_windowHandle = m_renderer->getVideoDriver()->getExposedVideoData().OpenGLWin32.HWnd;

        //
        // input system
        //
        logMessage(LOG_INFO, "Initialize Input Manager...");
        if(initInputSystem())
            return 1;

        //
        // gui windows
        //
        m_guiScreen = new TGUIScreen();
        m_guiScreen->setVisible(true);

        m_guiConsole = getGUIFactory()->addConsole(m_guiScreen);
        setGUICursorEnabled(false);
        acceptEvent("console.cmd",EVENT_DELEGATE(TApplication::onConsoleCommand));
        acceptEvent("tcon",EVENT_DELEGATE(TApplication::toggleConsole));
        m_consoleKey = m_inputManager->getKeyForCommand("tcon");

        m_guiDebug = new TGUIInfo("Debug Info - F2", m_guiScreen, EGUIA_LOWERRIGHT);
        m_guiDebug->setVisible(false);

        m_guiHelp = new TGUIInfo("Help - F1", m_guiScreen, EGUIA_UPPERLEFT, EGUIA_UPPERLEFT,
            225, 200, 0.35f);
        m_guiHelp->setVisible(false);

        //
        // custom scene/mesh loaders...
        //
        CIrrBMeshFileLoader* loader = new CIrrBMeshFileLoader(getSceneManager(),getFileSystem());
        getSceneManager()->addExternalMeshLoader(loader);
        loader->drop();

        //
        // our temporary version of ".irrmesh"
        //
        //CIrrMeshFileLoader* loader2 = new CIrrMeshFileLoader(getSceneManager(), getFileSystem());
        //getSceneManager()->addExternalMeshLoader(loader2);
        //loader2->drop();
        
        //
        // controller manager
        //
        logMessage(LOG_INFO, "Initialize Controller Manager...");
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
        // task system
        //
        m_taskManager = new TTaskManager();
        if(m_taskManager->initialize())
            return 1;

        //
        // particle system
        m_particleManager = new TParticleManager();
        if(m_particleManager->initialize())
            return 1;

        // 
        // file systems
        //
        if(initFileSystems())
            return 1;

        //
        // create default "player"
        //
        m_characterController = createCharacterController();
        if(m_configScript->getBool("options.godmode"))
        {
            m_characterController->setMode(ccmGod);
            m_characterController->setControllerTarget(CT_CAMERA);
        }
        m_physicsManager->setCharacterController(m_characterController);

        //
        // create debug node initially invisible
        //
        initDebugGUI();
        m_debugNode = new TDebugNode(getRootSceneNode());
        m_debugNode->setVisible(false);

        logMessage(LOG_INFO, "*** Tubras Core Initialized ***");

        //
        // Entity system
        //
        m_entityManager = new TEntityManager();
        if(m_entityManager->initialize())
            return 1;

        //
        // scripting, overriding application may optionally initialize.
        //
        m_scriptManager = new TScriptManager();
        if(m_scriptManager->initialize())
            return 1;

        m_initialized = true;

        return 0;
    }

    //-----------------------------------------------------------------------
    //                    i n i t F i l e S y s t e m s
    //-----------------------------------------------------------------------
    int TApplication::initFileSystems()
    {

        irr::core::array<irr::core::stringc> values;

        
        if(m_configScript->getStringArray("filesystems.folders", values))
        {
            for(u32 i=0;i < values.size(); i++)
            {
                if(!getFileSystem()->addFileArchive(values[i].c_str(), false, false))
                {
                    logMessage(LOG_INFO, "Error Adding FileSystem: %s", values[i].c_str());
                }
            }
            values.clear();
        }

        if(m_configScript->getStringArray("filesystems.zipfiles", values))
        {
            for(u32 i=0;i < values.size(); i++)
            {
                if(!getFileSystem()->addZipFileArchive(values[i].c_str()))
                {
                    logMessage(LOG_INFO, "Error Adding FileSystem: %s", values[i].c_str());
                }
            }
            values.clear();
        }

        if(m_configScript->getStringArray("filesystems.pakfiles", values))
        {
            for(u32 i=0;i < values.size(); i++)
            {
                if(!getFileSystem()->addPakFileArchive(values[i].c_str()))
                {
                    logMessage(LOG_INFO, "Error Adding FileSystem: %s", values[i].c_str());
                }
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
#ifdef USE_SOUND_FMOD
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
#elif USE_SOUND_IRR
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
        //
        // Initialize the Input System (OIS)
        //
        logMessage(LOG_INFO,"Initializing Input System...");

        m_inputManager = new TInputManager(m_renderer->getDevice());
        if(m_inputManager->initialize())
            return 1;
        m_inputManager->setKeyPreviewer(this);
        return 0;
    }

    //-----------------------------------------------------------------------
    //                    i n i t R e n d e r E n g i n e
    //-----------------------------------------------------------------------
    int TApplication::initRenderEngine()
    {
        m_renderer = new TRenderer(this);
        return m_renderer->initialize();
    }

    //-----------------------------------------------------------------------
    //                        i n i t C o n f i g 
    //-----------------------------------------------------------------------
    int TApplication::initConfig()
    {
        m_configScript = new TSL();

        if(m_nullDevice->getFileSystem()->existFile(m_configFileName))
        {
            if(m_configScript->loadScript(m_configFileName, false, false, this) == E_OK)
            {
                m_configScript->setOverrideAttributes(m_configOverride);
                return 0;
            }
            logMessage(LOG_INFO, "Error parsing config script");
            return 1;
        }

        logMessage(LOG_ERROR, "Config file missing: %s", m_configFileName.c_str());
        return 1;
    }

    //-----------------------------------------------------------------------
    //                c r e a t e C h a r a c t e r C o n t r o l l e r 
    //-----------------------------------------------------------------------
    TCharacterController* TApplication::createCharacterController()
    {
        TCharacterController* controller =  new TCharacterController("DefaulTCharacterController",
            m_renderer->getActiveCamera());
        controller->start();
        return controller;
    }

    //-----------------------------------------------------------------------
    //                 c r e a t e D e f a u l t C a m e r a 
    //-----------------------------------------------------------------------
    TCameraNode* TApplication::createDefaultCamera()
    {
        TCameraNode* camera = new TCameraNode(getRootSceneNode());
        camera->setName("tcam");
        camera->setPosition(TVector3(0,5,-100));
        camera->setTarget(TVector3(0,0,0));
        camera->setFOV(PI / 4.0f);

        getSceneManager()->setActiveCamera(camera);            
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
    //                    t o g g l e H e l p G U I
    //-----------------------------------------------------------------------
    void TApplication::toggleHelpGUI()
    {
        if(m_guiHelp->isVisible())
        {
            m_guiHelp->setVisible(false);
        }
        else
        {
            m_guiHelp->setVisible(true);
        }
    }

    //-----------------------------------------------------------------------
    //                         a d d H e l p T e x t
    //-----------------------------------------------------------------------
    u32 TApplication::addHelpText(const TString& cmd, const TString& note)
    {
        return m_guiHelp->addItem(cmd, note);
    }

    //-----------------------------------------------------------------------
    //                    c y c l e D e b u g D a t a
    //-----------------------------------------------------------------------
    void TApplication::cycleDebugData()
    {
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
    //                         i n i t D e b u g G U I 
    //-----------------------------------------------------------------------
    void TApplication::initDebugGUI()
    {
        TTaskDelegate* td = TASK_DELEGATE(TApplication::showDebugInfo);
        m_renderer->setDebugMode(m_debugData);
        m_debugTask = new TTask("debugTask",td,0,0,NULL,"");
        if(m_guiDebug)
        {
            m_guiDebug->addItem("FPS:");
            m_guiDebug->addItem("Triangles:");
            m_guiDebug->addItem("Visible Debug:");
            m_guiDebug->addItem("Physics Debug:");
            m_guiDebug->addItem("Active Camera:");
            m_guiDebug->addItem("Camera Pos:");
            m_guiDebug->addItem("Camera Rot:");
            m_guiDebug->addItem("Camera Tar:");
        }
    }

    //-----------------------------------------------------------------------
    //                    t o g g l e D e b u g G U I 
    //-----------------------------------------------------------------------
    void TApplication::toggleDebugGUI()
    {
        if(m_guiDebug->isVisible())
        {
            m_debugTask->stop();
            m_guiDebug->setVisible(false);
        }
        else 
        {
            m_debugTask->start();
            m_guiDebug->setVisible(true);
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

            ICameraSceneNode* camera = m_renderer->getActiveCamera();

            TVector3 pos = camera->getPosition();
            TVector3 rot = camera->getRotation();
            TVector3 dir = camera->getTarget();
            TString  nname = camera->getName();

            sprintf(buf,"%d",m_fpsAvg);
            m_guiDebug->updateValue(0, buf);

            sprintf(buf,"%d",tris);
            m_guiDebug->updateValue(1, buf);

            sprintf(buf,"%s (%d)", nname.c_str(), camera->getID());
            m_guiDebug->updateValue(4, buf);

            sprintf(buf,"%.1f, %.1f, %.1f", pos.X, pos.Y, pos.Z);
            m_guiDebug->updateValue(5, buf);

            sprintf(buf,"%.1f, %.1f, %.1f", rot.X, rot.Y, rot.Z);
            m_guiDebug->updateValue(6, buf);

            sprintf(buf,"%.1f, %.1f, %.1f", dir.X, dir.Y, dir.Z);
            m_guiDebug->updateValue(7, buf);

            TString ddata;
            switch(m_debugData)
            {
            case EDS_OFF: ddata = "None"; break;

            case EDS_BBOX: ddata = "BBoxes"; break;

            case EDS_NORMALS: ddata = "Normals"; break;

            case EDS_SKELETON: ddata = "Skeleton"; break;

            case EDS_MESH_WIRE_OVERLAY: ddata = "Wire Overlay"; break;

            case EDS_HALF_TRANSPARENCY: ddata = "Half Trans"; break;

            case EDS_BBOX_BUFFERS: ddata = "BBox Buffers"; break;

            case EDS_BBOX_ALL: ddata = "BBox & Buffers"; break;

            case EDS_FULL: ddata = "Full"; break;
            }
            m_guiDebug->updateValue(2, ddata);            


            if(m_physicsManager->getDebugMode())
            {
                m_guiDebug->updateValue(3, "On");
            }
            else
            {
                m_guiDebug->updateValue(3, "Off");
            }


            TStringVector debugStrings;
            setUserDebugInfo(debugStrings);

            if(debugStrings.size() > 0)
            {
                while((debugStrings.size()+3) > m_guiDebug->getItemCount())
                {
                    m_guiDebug->addItem(" " ,taCenter);
                }

                for(u32 i=0;i<debugStrings.size();i++)
                {
                    m_guiDebug->updateItem(i+3,debugStrings[i]);
                }

            }

            task->m_elapsedTime = 0;
        }

        return TTask::cont;
    }

    //-----------------------------------------------------------------------
    //                      s e t W i n d o w C a p t i o n
    //-----------------------------------------------------------------------
    void TApplication::setWindowCaption(const char* value)
    {
        stringw caption = value;
        m_renderer->getDevice()->setWindowCaption(caption.c_str());
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
        TState *state;

        if(!m_stateStack.empty())
        {
            state = *(m_stateStack.begin());
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
            logMessage(LOG_ERROR, "Invalid State: %s (Not Found)", stateName.c_str());
            m_currentState = 0;
        }
        return 0;
    }

    //-----------------------------------------------------------------------
    //                         p u s h S t a t e
    //-----------------------------------------------------------------------
    int TApplication::pushState(const TString& stateName)
    {        
        TState *state;

        if(!m_stateStack.empty())
        {
            state = *(m_stateStack.begin());
            state->Pause();
        }

        state = m_states[stateName];
        m_stateStack.push_front(state);
        state->Enter();
        m_currentState = state;

        return 0;
    }

    //-----------------------------------------------------------------------
    //                          p o p S t a t e
    //-----------------------------------------------------------------------
    int TApplication::popState()
    {
        TState *state;
        TStateInfo* prevInfo=NULL;

        m_currentState = NULL;
        if(!m_stateStack.empty())
        {
            TStateStack::Iterator itr = m_stateStack.begin();
            state = *itr;
            prevInfo = state->Exit();
            m_stateStack.erase(itr);
        }

        if(!m_stateStack.empty())
        {
            state = *(m_stateStack.begin());
            state->Resume(prevInfo);
            m_currentState = state;
        }
        else
        {
            //
            // the last state was popped
            //
            m_currentState = 0;
        }        

        return 0;
    }

    //-----------------------------------------------------------------------
    //                         l o g M e s s a g e
    //-----------------------------------------------------------------------
    void TApplication::logMessage(int level, const char* format, ...)
    {
        char buffer [1024], *buff = buffer;
        unsigned int len;
        va_list args;

        if(!m_logger || (level > m_debug))
            return;

        va_start(args, format);
        len = vsnprintf(buffer, sizeof(buffer), format, args); 

        if(len <= sizeof(buffer))
        {
            m_logger->logMessage(buffer);
            if(m_hConsole)
                printf("%s\n",buffer);
        }
        else
        {
            buff = (char *)malloc (++len);
            if (buff)
            {
                len = vsnprintf (buff, len, format, args);
                if (len > 0)
                {
                    m_logger->logMessage(buff);
                    if(m_hConsole)
                        printf("%s\n",buff);

                }
                free (buff);
            }
        }
        va_end(args);

        return;
    }

    //-----------------------------------------------------------------------
    //                     s h o w M e s s a g e Di a l o g
    //-----------------------------------------------------------------------
    int TApplication::showMessageDialog(const TString& caption, 
        const TString& message, const TMessageDialogType type, bool native)
    {
        int result=0;

        if(native)
        {
#ifdef TUBRAS_PLATFORM_WINDOWS
            HWND hwnd = 0;
            unsigned int flag;
            if(this->getRenderer() && this->getRenderer()->getVideoDriver())
                hwnd = (HWND)this->getRenderer()->getVideoDriver()->getExposedVideoData().OpenGLWin32.HWnd;
            switch(type)
            {
            case mdtError:
                flag = MB_OK | MB_ICONERROR;
                break;
            case mdtOK:
                flag = MB_OK;
                break;
            case mdtYesNo:
                flag = MB_YESNO;
                break;
            }
            result = MessageBox(hwnd, message.c_str(), caption.c_str(), flag);
#else
#endif
        }
        else // gui dialog
        {
        }

        return result;
    }

    //-----------------------------------------------------------------------
    //                        a d d G U I I m a g e
    //-----------------------------------------------------------------------
    TGUIImage* TApplication::addGUIImage(TString fileName, float x, float y, 
        float width, float height, bool relative, IGUIElement* parent)
    {
        TGUIImage* result=0;
        TRecti rect;
        dimension2du psize, size;
        position2di pos;
        bool wcenter=false, hcenter=false;

        IImage* image = this->getRenderer()->getVideoDriver()->createImageFromFile(fileName);
        ITexture* texture = this->getRenderer()->getVideoDriver()->addTexture(fileName, image);

        if(parent)
            psize = parent->getAbsoluteClippingRect().getSize();
        else
            psize = this->getRenderer()->getVideoDriver()->getScreenSize();

        if(width < 0.f)
        {
            width = (float)(image->getDimension().Width);
            wcenter = true;
        }
        if(height < 0.f)
        {
            height = (float)(image->getDimension().Height);
            hcenter = true;
        }

        if(relative)
        {
            if(x >= 0.f)
                rect.UpperLeftCorner.X = (s32)(x * psize.Width);
            else
                rect.UpperLeftCorner.X = (s32)((psize.Width / 2) - (width/2));
            if(y >= 0.f)
                rect.UpperLeftCorner.Y = (s32)(y * psize.Height);
            else
                rect.UpperLeftCorner.Y = (s32)((psize.Height / 2) - (height/2));
            if(!wcenter)
                rect.LowerRightCorner.X = (s32)(rect.UpperLeftCorner.X + (width * psize.Width));
            else 
                rect.LowerRightCorner.X = (s32)(rect.UpperLeftCorner.X+width);
            if(!hcenter)
                rect.LowerRightCorner.Y = (s32)(rect.UpperLeftCorner.Y + (height * psize.Height));
            else
                rect.LowerRightCorner.Y = (s32)(rect.UpperLeftCorner.Y+height);
        }
        else 
        {
            if(x >= 0.f)
                rect.UpperLeftCorner.X = (s32)x;
            else
                rect.UpperLeftCorner.X = (s32)((psize.Width / 2) - (width/2));
            if(y >= 0.f)
                rect.UpperLeftCorner.Y = (s32)y;
            else
                rect.UpperLeftCorner.Y = (s32)((psize.Height / 2) - (height/2));

            rect.LowerRightCorner.X = (s32)(rect.UpperLeftCorner.X+width);
            rect.LowerRightCorner.Y = (s32)(rect.UpperLeftCorner.Y+height);
        }

        result = this->getGUIFactory()->addImage(rect, parent);

        result->setImage(texture);
        result->setUseAlphaChannel(true);

        image->drop();
        return result;
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
            logMessage(LOG_INFO, event.LogEvent.Text);
        }
        else if(event.EventType == EET_GUI_EVENT)
        {
            EGUI_EVENT_TYPE etype = event.GUIEvent.EventType;
            if(etype == EGET_BUTTON_CLICKED)
            {
                TEvent* tevent = new TEvent("gui.clicked");
                tevent->addIntParameter(event.GUIEvent.Caller->getID());

                sendEvent(tevent);
                tevent->drop();                
            }
            else if(etype == EGET_MENU_ITEM_SELECTED)
            {
                IGUIContextMenu* menu = (IGUIContextMenu*)event.GUIEvent.Caller;
                s32 id = menu->getItemCommandId(menu->getSelectedItem());
                TEvent* tevent = new TEvent("gui.menu.clicked");
                tevent->addIntParameter(id);

                sendEvent(tevent);
                tevent->drop();                
            }
            return false;
        }

        if(m_inputManager)
            return m_inputManager->getHandler()->OnEvent(event);
        return false;

    }

    //-----------------------------------------------------------------------
    //                       t o g g l e C o n s o l e
    //-----------------------------------------------------------------------
    int TApplication::toggleConsole(const TEvent* event)
    {
        if(!m_guiConsole)
            return 0;

        bool visible = !m_guiConsole->isVisible();
        if(visible)
        {
            getApplication()->getGUIManager()->getRootGUIElement()->bringToFront(m_guiScreen);
            m_renderer->getGUICursor()->restorePosition();
            this->setInputMode(imGUI);
        }
        else {
            m_renderer->getGUICursor()->savePosition();
            this->setInputMode(imApp);            
        }

        m_guiConsole->setVisible(visible);
        setGUICursorEnabled(visible);
        return 1;
    }

    //-----------------------------------------------------------------------
    //                         p r e v i e w K e y
    //-----------------------------------------------------------------------
    bool TApplication::previewKey(EKEY_CODE keyCode, bool down)
    {
        if(keyCode == m_consoleKey ||
            ((keyCode == KEY_ESCAPE) && m_guiConsole->isVisible()))
        {
            if(down)
                toggleConsole(0);
            return true;
        }
        return false;
    }

    //-----------------------------------------------------------------------
    //                       o n C o n s o l e C o m m a n d
    //-----------------------------------------------------------------------
    int TApplication::onConsoleCommand(const TEvent* event)
    {
        int result=0;

        core::stringc cmd=((TEvent*)event)->getParameter(0)->getStringValue();
        core::stringc dtext = L"> ";
        dtext += cmd;

        if(event->getNumParameters() > 1)
        {
            dtext += " (";
            for(int i=1; i<event->getNumParameters(); i++)
            {
                if(i != 1)
                    dtext += ", ";
                dtext += ((TEvent*)event)->getParameter(i)->getStringValue();
            }
            dtext += ")";
        }

        m_guiConsole->addText(dtext);
        return result;
    }

    //-----------------------------------------------------------------------
    //                       s t e p S i m u l a t i o n
    //-----------------------------------------------------------------------
    void TApplication::stepSimulation(f32 timeStep)
    {
        //
        // process input
        //
        TPROFILE_START("Input");
        m_inputManager->update(timeStep);
        TPROFILE_STOP();

        //
        // process events
        //
        TPROFILE_START("Events");
        m_eventManager->update(timeStep);
        TPROFILE_STOP();

        //
        // process controllers
        //
        TPROFILE_START("Controllers");
        m_controllerManager->update(timeStep);
        TPROFILE_STOP();

        //
        // process tasks
        //
        TPROFILE_START("Tasks");
        m_taskManager->update();
        TPROFILE_STOP();

        //
        // update physics & collision detection
        //
        TPROFILE_START("Physics");
        m_physicsManager->update(timeStep);
        TPROFILE_STOP();

        //
        // particle system
        //
        TPROFILE_START("Particles");
        m_particleManager->update(timeStep);
        TPROFILE_STOP();

        //
        // process sound
        //
        TPROFILE_START("Sound");
        m_soundManager->update();
        TPROFILE_STOP();
    }

    //-----------------------------------------------------------------------
    //                              r u n 
    //-----------------------------------------------------------------------
    void TApplication::run()
    {
        TStrStream msg; 

        if(!m_initialized)
        {
            logMessage(LOG_ERROR, "Application NOT initialized.  Exiting run()");
            return;
        }

        IVideoDriver* video = m_renderer->getVideoDriver();

        //
        // using state management?
        //
        if(m_initialState.size())
        {
            pushState(m_initialState);
        }
        else m_currentState = (TState *) this;

        logMessage(LOG_INFO, "Entering Run Loop");
        m_running = true;

        // f32 fixedTimeStep = 1.f / 60.f;
        f32 dt;

        m_lastTime = m_globalClock->getMilliSeconds();
        TProfileManager::reset();
        while(m_running)
        {
            m_currentTime = m_globalClock->getMilliSeconds();
            dt = (float)(m_currentTime - m_lastTime) * 0.001f;
            m_lastTime = m_currentTime;

            TPROFILE_START("stepSimulation()");
            stepSimulation(dt);
            TPROFILE_STOP();

            //
            // render frame
            //
            preRender(dt);

            TPROFILE_START("render()");
            m_renderer->update();
            TPROFILE_STOP();

            //
            // update stats
            //
            m_fpsAvg = video->getFPS();
            if((m_fpsMin < 10) || (m_fpsAvg < m_fpsMin))
                m_fpsMin  = m_fpsAvg;
            if(!m_fpsMax || (m_fpsAvg > m_fpsMax))
                m_fpsMax  = m_fpsAvg;
#ifdef PROFILING_ENABLED
            TProfileManager::incrementFrameCounter();
#endif
        }

        logMessage(LOG_INFO, "Exiting Run Loop");
        msg << "Frame Rate - Avg: " << m_fpsAvg << ", Min: " << m_fpsMin
            << ", Max: " << m_fpsMax;
        logMessage(LOG_INFO, "Frame Rate - Avg: %d, Min: %d, Max: %d", 
            m_fpsAvg, m_fpsMin, m_fpsMax);

#ifdef PROFILING_ENABLED
        TProfileManager::dumpAll();
        TProfileManager::cleanUpMemory();
#ifndef BT_NO_PROFILE
        m_physicsManager->dumpBulletProfile(0, 0);
#endif // BT_NO_PROFILE
#endif // PROFILING_ENABLED

    }

    //-------------------------------------------------------------------
    //                       L A p p l i c a t i o n
    //-------------------------------------------------------------------
    LApplication::LApplication()
    {
        m_ptr = getApplication();
    }

    //-------------------------------------------------------------------
    //                        l o g M e s s a g e
    //-------------------------------------------------------------------
    // logMessage(...)
    // Arguments are converted to strings and concatenated. Note that we
    // start with argument number 2, as argument number 1 for all proxy
    // class methods is the Lua table class itself. 
    int LApplication::logMessage(lua_State *L) 
    {
        TString msg("");
        int n = lua_gettop(L);  /* number of arguments */
        int i;
        lua_getglobal(L, "tostring");
        for (i=2; i<=n; i++) {
            const char *s;
            lua_pushvalue(L, -1);  /* function to be called */
            lua_pushvalue(L, i);   /* value to print */
            lua_call(L, 1, 1);
            s = lua_tostring(L, -1);  /* get result */
            if (s == NULL)
                return luaL_error(L, LUA_QL("tostring") " must return a string to "
                LUA_QL("print"));
            msg += s;
            lua_pop(L, 1);  /* pop result */
        }
        m_ptr->logMessage(LOG_INFO, msg.c_str());
        return 0;
    }

    //-------------------------------------------------------------------
    //                       a c c e p t E v e n t
    //-------------------------------------------------------------------
    int LApplication::acceptEvent(lua_State *L) 
    {
        int result=-1;

        int top=lua_gettop(L);

        if((lua_type(L, top) == LUA_TFUNCTION) && 
            (lua_type(L, top-1) == LUA_TSTRING))
        {
            void* ref = (void *)luaL_ref(L, LUA_REGISTRYINDEX);

            top=lua_gettop(L);
            const char* name = lua_tostring(L, -1);
            lua_pop(L, 1);

            result = m_ptr->acceptEventToScript(name, ref);
        }

        lua_pushnumber(L, result);
        return 1; // number of values we're returning
    }
    template<> const char LProxyBase<TApplication>::className[] = "TApplication";
    const TLuaProxyBase<LApplication>::RegType LApplication::Register[] = {
        { "acceptEvent", &LApplication::acceptEvent },
        { "logMessage", &LApplication::logMessage },
        { "stopRunning", &LApplication::stopRunning },
        { 0 }};
}
