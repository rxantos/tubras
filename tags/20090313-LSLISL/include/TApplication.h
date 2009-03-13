//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TAPPLICATION_H_
#define _TAPPLICATION_H_

namespace Tubras
{
    enum DEBUG_LEVEL
    {
        DBG_NORMAL = 1,
        DBG_EVENTS = 5
    };

    typedef TMap<TString, TState*> TStateMap;
    typedef TMap<TString, TState*>::Iterator TStateMapItr;
    typedef TList<TState*> TStateStack;

    /**
    TApplication Class.
    @remarks
    The main application class. Also acts as the state manager.
    */
    class TApplication : public TSingleton<Tubras::TApplication>,
        public TState, public IEventReceiver, public ISceneUserDataSerializer
    {
    protected:
        int                     m_argc;
        const char**            m_argv;
        TString                 m_initialState;
        TString                 m_appExecutable;
        TString                 m_configName;
        TString                 m_logName;
        TString                 m_regName;
        TString                 m_currentDirectory;
        TString                 m_dataRoot;
        TString                 m_appName;
        long long               m_frames;
        bool                    m_running;
        bool                    m_initialized;
        bool                    m_keys[KEY_KEY_CODES_COUNT];

        TStateStack             m_stateStack;
        TStateMap               m_states;
        TState*                 m_currentState;
        TTimer*                 m_globalClock;
        TSL*                    m_configScript;

        u32                     m_lastTime;
        u32                     m_currentTime;
        u32                     m_deltaTime;

        TRandom*                m_random;

        E_DEBUG_SCENE_TYPE      m_debugData;

        TLogger*                m_logger;
        TRenderer*              m_renderer;
        TEventManager*          m_eventManager;
        TControllerManager*     m_controllerManager;
        TSoundManager*          m_soundManager;
        TPhysicsManager*        m_physicsManager;
        TPlayerController*      m_playerController;
        TTaskManager*           m_taskManager;
        TInputManager*          m_inputManager;
        TScriptManager*         m_scriptManager;
        TParticleManager*       m_particleManager;
        IrrlichtDevice*         m_nullDevice;
        TSceneLoader*           m_sceneLoader;

        TTextOverlay*           m_debugOverlay;
        TTextOverlay*           m_helpOverlay;
        TDebugNode*             m_debugNode;
        TTask*                  m_debugTask;
        size_t                  m_debugUpdateFreq;
        s32                     m_fpsAvg,m_fpsMin,m_fpsMax;

        int                     m_hConsole;
        int                     m_debug;
        bool                    m_bConsole;
        void*                   m_windowHandle;
        u32                     m_display;

    protected:
        bool sendKeyEvent(const SEvent::SKeyInput& input);
        bool sendMouseEvent(const SEvent::SMouseInput& input);



    public:
        TApplication(const TString& appName=L"Tubras App"); 
        virtual ~TApplication();

        static TApplication& getSingleton(void);
        static TApplication* getSingletonPtr(void);

        virtual int initConfig();
        virtual int initRenderEngine();
        virtual int initInputSystem();
        virtual int initSoundSystem();
        virtual int initFileSystems();

        TRenderer* getRenderer() {return m_renderer;}
        TTimer*  getGlobalClock() {return m_globalClock;}
        TSL* getConfig() {return m_configScript;}

        TEventManager* getEventManager() {return m_eventManager;}
        TSoundManager* getSoundManager() {return m_soundManager;}
        TInputManager* getInputManager() {return m_inputManager;}
        TPhysicsManager* getPhysicsManager() {return m_physicsManager;}
        TScriptManager* getScriptManager() {return m_scriptManager;}
        TParticleManager* getParticleManager() {return m_particleManager;}

        IrrlichtDevice* getNullDevice() {return m_nullDevice;}

        TString changeFileExt(const TString& filename, const TString& newext);

        virtual bool OnEvent(const SEvent& event);

        void logMessage(const TString& msg,DEBUG_LEVEL level=DBG_NORMAL);
        int getDebug() {return m_debug;};
        TString getLogName() {return m_logName;}
        TString getAppName() {return m_appName;}
        TString getDataRoot() {return m_dataRoot;}

        virtual TCameraNode* createDefaultCamera();
        virtual ICameraSceneNode* getActiveCamera() {return m_renderer->getActiveCamera();}

        virtual TPlayerController* createPlayerController();
        TPlayerController* getPlayerController() {return m_playerController;}

        void toggleDebugOverlay();
        void cycleDebugData();
        int showDebugInfo(TTask* task);
        virtual void toggleHelpOverlay();
        virtual void togglePhysicsDebug();
        virtual void addHelpText(const TString& text);

        void setArgs(int argc,const char **argv) { m_argc = argc; m_argv = argv; }

        virtual void OnReadUserData(ISceneNode* forSceneNode, io::IAttributes* userData) {}
        virtual io::IAttributes* createUserData(ISceneNode* forSceneNode) {return 0;}
        virtual void OnCreateNode(ISceneNode* node) {}

        virtual void setWindowCaption(TString value);


        void setThemeDirectory(const TString& themeDirectory);

        //
        // state management functions/
        //
        void setInitialState(const TString& stateName) {m_initialState = stateName;}

        int changeState(const TString& stateName);
        int pushState(const TString& stateName);
        int popState();

        /**
        Override to include additional debug data on-screen
        */
        virtual void setUserDebugInfo(TStringVector& debugStrings) {}

        /**
        Initializes the render, sound, and physics subsystems.
        */
        virtual int initialize();

        /**
        Creates the application/game states.
        @remarks
        After this is invoked, each of the newly creates states 
        "initialize" member functions is automatically invoked.
        */
        virtual int createStates();

        /**
        The main render loop.
        */
        virtual void run();

        /**
        Called before updates & rendering (delta in milliseconds since last call).
        */
        virtual void preRender(int m_deltaTime) {}

        /**
        Quit the application render loop.
        */
        void stopRunning() {m_running=false;};

        /**
        Add a state to the state manager
        */
        int addState(TState *state);

    };

    Tubras::TApplication *getApplication();


}

#endif
