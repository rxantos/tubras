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

#ifndef _TAPPLICATION_H_
#define _TAPPLICATION_H_

namespace Tubras
{
    typedef std::map<TString, TState*> TStateMap;
    typedef std::map<TString, TState*>::iterator TStateMapItr;
    typedef std::list<TState*> TStateStack;

    /**
    TApplication Class.
    @remarks
    The main application class. Also acts as the state manager.
    */
    class TApplication : public TSingleton<Tubras::TApplication>,
        public TState
    {
    protected:
        int                     m_argc;
        char**                  m_argv;
        int                     m_lastError;
        TEventManager*          m_eventManager;
        TConfigFile*            m_configFile;
        TRenderEngine*          m_renderEngine;
        TInputManager*          m_inputManager;
        TPlayerController*		m_playerController;
        TTimer*                 m_globalClock;
        TSoundManager*          m_soundManager;
        TTaskManager*           m_taskManager;
        TControllerManager*     m_controllerManager;
        TIntervalManager*       m_intervalManager;
        TDatabaseManager*       m_databaseManager;
        TStateMap               m_states;
        TStateStack             m_stateStack;
        TState*                 m_currentState;
        TRandom*                m_random;
        TGUIManager*            m_GUIManager;
        TThemeManager*          m_themeManager;
        TGUI::TGScreen*         m_GUIScreen;
        TGUI::TGConsole*        m_console;
        TPhysicsManager*        m_physicsManager;
        TTextOverlay*           m_debugOverlay;
        TTextOverlay*           m_helpOverlay;
        TTask*                  m_debugTask;
        size_t					m_debugUpdateFreq;

        TString                 m_initialState;
        TString                 m_appExecutable;
        TString                 m_configName;
        TString                 m_logName;
        TString                 m_currentDirectory;
        TString                 m_appName;
        TString                 m_GUISchemeName;
        TString                 m_GUILookName;
        TString                 m_themeDirectory;

        double                  m_currentTime;
        double                  m_lastTime;
        double                  m_deltaTime;

        long long               m_frames;
        bool                    m_running;


        int                     m_hConsole;
        bool                    m_bConsole;
        bool                    m_bDebug;
        int                     m_windowHandle;

    protected:
        virtual int showDebugInfo(TTask* task);

    public:
        TApplication(int argc,char **argv,TString appName="Tubras App"); 
        virtual ~TApplication();

        static TApplication& getSingleton(void);
        static TApplication* getSingletonPtr(void);

        int getLastError() {return m_lastError;};
        TString changeFileExt(TString filename,TString newext);

        virtual int initConfig();
        virtual int initRenderEngine();
        virtual int initInputSystem();
        virtual int initSoundSystem();

        virtual void toggleConsole();
        virtual void toggleDebugOverlay();

        /**
        Override to include additional debug data on-screen
        */
        virtual void setUserDebugInfo(TStringVector& debugStrings) {};

        TGUI::TGConsole* getConsole() {return m_console;};
        TGUI::TGScreen*  getGUIScreen() {return m_GUIScreen;};

        /**
        Allow the application to override the default scene manager.
        */
        virtual TSceneManager* createSceneManager(Ogre::Root* root);

        /**
        Returns the global managers.
        */
        TEventManager*  getEventManager() {return m_eventManager;};
        TConfigFile*    getConfigFile() {return m_configFile;};
        TTimer*         getGlobalClock() {return m_globalClock;};
        TInputManager*  getInputManager() {return m_inputManager;};
        TTaskManager*   getTaskManager() {return m_taskManager;};
        TSoundManager*  getSoundManager() {return m_soundManager;};
        TRenderEngine*  getRenderEngine() {return m_renderEngine;};
        TIntervalManager* getIntervalManager() {return m_intervalManager;};
        TState*         getCurrentState() {return m_currentState;};
        TThemeManager*  getThemeManager() {return m_themeManager;};
        TGUIManager*    getGUIManager() {return m_GUIManager;};
        TPhysicsManager* getPhysicsManager() {return m_physicsManager;};
        TPlayerController* getPlayerController() {return m_playerController;};

        TRandom*        getRNG() {return m_random;};

        bool getDebug() {return m_bDebug;};
        TString getLogName() {return m_logName;};
        TString getAppName() {return m_appName;};

        void setThemeDirectory(TString themeDirectory);

        /**
        Set the frequency (ms) debug information is updated on-screen.
        */
        void setDebugUpdateFreq(size_t value) {m_debugUpdateFreq = value;};
        size_t getDebugUpdateFreq() {return m_debugUpdateFreq;};

        void captureScreen();
        void captureScreen(TString fileName);

        /**
        Create a theme class instance.
        */
        virtual TTheme* createThemeClass(TString baseDir);

        virtual TCameraNode* createDefaultCamera();
        virtual TPlayerController* createPlayerController();
        virtual TViewPort* createDefaultViewport();

        virtual void toggleHelp();
        virtual void addHelpText(TString text);

        int consoleToggled(TSEvent event);

        //
        // state management functions/
        //
        void setInitialState(TString stateName) {m_initialState = stateName;};

        int changeState(TString stateName);
        int pushState(TString stateName);
        int popState();

        /**
        Initializes the render, sound, and physics subsystems.
        */
        virtual int initialize();

        /*
        Delegate to handle main window resizing.
        */
        virtual int windowResized(Tubras::TSEvent event);
        virtual int windowFocusChanged(Tubras::TSEvent event);
        virtual int procConsoleCommand(Tubras::TSEvent event);

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
        Log a message to the log file and console if visible.
        */
        virtual void logMessage(const char* msg);

        /**
        Create a general purpose timer.
        */
        TTimer* createTimer();

        /**
        Quit the application render loop.
        */
        void stopRunning() {m_running=false;};

        /**
        Add a state to the state manager
        */
        int addState(TState *state);

        Ogre::Archive* findArchive(TString &filename);

    };

    typedef Ogre::SharedPtr<TApplication> TSApplication;

    TApplication *getApplication();


}

#endif