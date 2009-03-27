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
        TEntityManager*         m_entityManager;
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
        TEntityManager* getEntityManager() {return m_entityManager;}
        TControllerManager* getControllerManager() {return m_controllerManager;}
        TTaskManager* getTaskManager() {return m_taskManager;}

        ISceneManager* getSceneManager() {
            if(m_renderer)
                return m_renderer->getSceneManager();
            else return 0;
            }

        ISceneNode* getRootSceneNode() {
            if(m_renderer)
                return m_renderer->getSceneManager()->getRootSceneNode();
            else return 0;
        }

        IGUIEnvironment* getGUIManager() {
            if(m_renderer)
                return m_renderer->getGUIManager();
            else return 0;
        }

        ISceneNode* addSceneNode(const char* sceneNodeTypeName, ISceneNode* parent=0) {
            return getSceneManager()->addSceneNode(sceneNodeTypeName,parent);
        }

        IAnimatedMeshSceneNode* loadModel(const TString& fileName, ISceneNode* parent=0, const TString& name="default") {
            static int modelnum=0;
            IAnimatedMeshSceneNode* result = 0;
            TString aname=name;

            if(name == "default")
            {
                TStrStream str;
                str << "model" << modelnum++;
                aname = str.str().c_str();
            }

            IAnimatedMesh* pmesh  = getSceneManager()->getMesh(fileName.c_str());
            if(pmesh)
            {
                result = getSceneManager()->addAnimatedMeshSceneNode(pmesh, parent);   
                result->setName(aname.c_str());
            }
            return result;
        }

        TSound* loadSound(const TString& fileName, const TString& finishedEvent="", bool positional=false) {
            TSound* sound = getSoundManager()->getSound(fileName,positional);
            if(sound && finishedEvent.size())
                sound->setFinishedEvent(finishedEvent);
            return sound;
        }

        void setRenderMode(TRenderMode value)
        {
            getRenderer()->setRenderMode(value);
        }

        TRenderMode getRenderMode()
        {
            return getRenderer()->getRenderMode();
        }

        IFileSystem* getFileSystem()
        {
            return m_renderer->getDevice()->getFileSystem();
        }

        TGUIFactory* getGUIFactory()
        {
            return m_renderer->getGUIFactory();
        }


        TParticleNode* createParticleNode(TString name,const size_t maxParticles, 
            TParticlePrimitive primitive, ISceneNode* parent=0)
        {
            return m_particleManager->createParticleNode(name, maxParticles,
                primitive, parent);
        }

        TEntity* addEntity(TString name)
        {
            return m_entityManager->addEntity(name);
        }

        void setBGColor(const TColor& value)
        {
            m_renderer->setBGColor(value);
        }

        void setBGColor(int r, int g, int b)
        {
            m_renderer->setBGColor(TColor(r, g, b));
        }

        void setControllerEnabled(const TString controllerName, const bool value) {}

        u32 acceptEvent(const TString& eventMsg, TEventDelegate* callback,
            const void *extraData=0, int priority=0,bool enabled=true)
        {
            u32 id = 0;

            if(m_eventManager)
                id = m_eventManager->accept(eventMsg,callback,extraData,priority,enabled);
            return id;
        }

        u32 acceptEventToScript(const TString eventMsg, const void* scriptFunc)
        {
            u32 id = 0;
            TEventDelegate* pd = m_scriptManager->getEventDelegate();
            return acceptEvent(eventMsg,pd,scriptFunc);
        }

        TIntervalController* addScriptFunctionInterval(const TString intervalName, const void* scriptFunc,
            float duration, TBlendType blendType, char* startedEvent, char* finishedEvent)
        {
            u32 id = 0;
            TIntervalDelegate* pd = m_scriptManager->getIntervalDelegate();
            return new TIntervalController(intervalName, 0, duration, duration, pd, scriptFunc, 
                blendType, startedEvent, finishedEvent);
        }

        ITexture* getTexture(const TString& name)
        {
            return m_renderer->getVideoDriver()->getTexture(name.c_str());
        }

        void setCursorVisible(bool value)
        {
            m_renderer->getDevice()->getCursorControl()->setVisible(value);
        }

        bool sendEvent(TEvent* event)
        {
            return m_eventManager->send(event) ? true : false;
        }

        bool queueEvent(TEvent* event)
        {
            return m_eventManager->queue(event) ? true : false;
        }

        void setGUICursorEnabled(bool value)
        {
            m_renderer->setGUICursorEnabled(value);
        }

        void centerGUICursor()
        {
            m_renderer->getGUICursor()->centerCursor();
        }

        TGUIImage* addGUIImage(TString fileName, float x=0.f, float y=0.f, 
            float width=1.f, float height=1.f, bool relative=true, IGUIElement* parent=0);

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
        Add a state to the state manager
        */
        int addState(TState *state);


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

    };

    Tubras::TApplication *getApplication();


}

#endif
