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
    typedef TMap<TString, TState*> TStateMap;
    typedef TMap<TString, TState*>::Iterator TStateMapItr;
    typedef TList<TState*> TStateStack;

    /**
    TApplication Class.
    @remarks
    The main application class. Also acts as the state manager.
    */
    class TApplication : public TSingleton<Tubras::TApplication>,
        public IEventReceiver, public TState
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
       

        TStateMap               m_states;
        TState*                 m_currentState;
        TTimer*                 m_globalClock;
        TXMLConfig*             m_config;

        unsigned int            m_lastTime;
        unsigned int            m_currentTime;
        unsigned int            m_deltaTime;

        TRandom*                m_random;

        TLogger*                m_logger;
        TRender*                m_render;
        TEventManager*          m_eventManager;
        TInputBinder*           m_inputBinder;
        TControllerManager*     m_controllerManager;
        TNodeFactory*           m_nodeFactory;

        int                     m_hConsole;
        bool                    m_bDebug;
        bool                    m_bConsole;

    protected:
        bool sendKeyEvent(const SEvent::SKeyInput& input);
        bool sendMouseEvent(const SEvent::SMouseInput& input);



    public:
        TApplication(int argc,char **argv,TString appName=L"Tubras App"); 
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

        TString changeFileExt(TString filename,TString newext);

        virtual bool OnEvent(const SEvent& event);

        void logMessage(TString msg);
        bool getDebug() {return m_bDebug;};
        TString getLogName() {return m_logName;};
        TString getAppName() {return m_appName;};

        void setThemeDirectory(TString themeDirectory);

        //
        // state management functions/
        //
        void setInitialState(TString stateName) {m_initialState = stateName;}

        int changeState(TString stateName);
        int pushState(TString stateName);
        int popState();

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
