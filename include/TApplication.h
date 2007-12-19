//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to 
// deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
// sell copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
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
        public TState, public IEventReceiver
    {
    protected:
        int                     m_argc;
        char**                  m_argv;
        TString                 m_initialState;
        TString                 m_appExecutable;
        TString                 m_configName;
        TString                 m_logName;
        TString                 m_regName;
        TString                 m_currentDirectory;
        TString                 m_appName;
        long long               m_frames;
        bool                    m_running;
        bool                    m_keys[KEY_KEY_CODES_COUNT];


        TStateMap               m_states;
        TState*                 m_currentState;
        TTimer*                 m_globalClock;
        TXMLConfig*             m_config;

        u32                     m_lastTime;
        u32                     m_currentTime;
        u32                     m_deltaTime;

        TRandom*                m_random;

        TLogger*                m_logger;
        TRender*                m_render;
        TEventManager*          m_eventManager;
        TControllerManager*     m_controllerManager;
        TSoundManager*          m_soundManager;
        TPhysicsManager*        m_physicsManager;
        TPlayerController*      m_playerController;
        TTaskManager*           m_taskManager;
        TInputManager*          m_inputManager;

        TTextOverlay*           m_debugOverlay;
        TTextOverlay*           m_helpOverlay;
        TTask*                  m_debugTask;
        size_t                  m_debugUpdateFreq;
        s32                     m_fpsAvg,m_fpsMin,m_fpsMax;

        int                     m_hConsole;
        int                     m_debug;
        bool                    m_bConsole;
        int                     m_windowHandle;

    protected:
        bool sendKeyEvent(const SEvent::SKeyInput& input);
        bool sendMouseEvent(const SEvent::SMouseInput& input);



    public:
        TApplication(int argc,char **argv,const TString& appName=L"Tubras App"); 
        virtual ~TApplication();

        static TApplication& getSingleton(void);
        static TApplication* getSingletonPtr(void);

        virtual int initConfig();
        virtual int initRenderEngine();
        virtual int initInputSystem();
        virtual int initSoundSystem();

        TRender* getRenderer() {return m_render;}
        TTimer*  getGlobalClock() {return m_globalClock;}
        TXMLConfig* getConfig() {return m_config;}
        TEventManager* getEventManager() {return m_eventManager;}
        TSoundManager* getSoundManager() {return m_soundManager;}
        TInputManager* getInputManager() {return m_inputManager;}

        TString changeFileExt(const TString& filename, const TString& newext);

        virtual bool OnEvent(const SEvent& event);

        void logMessage(const TString& msg,DEBUG_LEVEL level=DBG_NORMAL);
        int getDebug() {return m_debug;};
        TString getLogName() {return m_logName;};
        TString getAppName() {return m_appName;};

        virtual TCameraNode* createDefaultCamera();
        virtual TPlayerController* createPlayerController();

        void toggleDebugOverlay();
        int showDebugInfo(TTask* task);
        virtual void toggleHelpOverlay();
        virtual void addHelpText(const TString& text);

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
        virtual int createStates() {return 0;};

        /**
        The main render loop.
        */
        virtual void run();

        /**
        Called before updates & rendering (delta in milliseconds since last call).
        */
        virtual void preRender(int m_deltaTime) {};

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
