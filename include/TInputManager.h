//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TINPUTMANAGER_H_
#define _TINPUTMANAGER_H_

namespace Tubras
{
    class TEventManager;

    class TInputManager : public Tubras::TSingleton<Tubras::TInputManager>
    {
    private:
        OIS::InputManager*      m_inputManager;
        u32				        m_windowHandle;
        u32                     m_display;
        TInputHandler*		    m_inputHandler;
        OIS::Keyboard*		    m_keyboard;
        OIS::Mouse*			    m_mouse;
        OIS::JoyStick*          m_joys[4];
        OIS::ForceFeedback*     m_ff[4];
        int                     m_numSticks;
    public:
        TInputManager(u32 window_handle, u32 window_display);
        ~TInputManager();
        static TInputManager& getSingleton(void);
        static TInputManager* getSingletonPtr(void);
        int initialize();
        int step();
        void setGUIEnabled(bool enabled);
        bool getGUIEnabled() {return m_inputHandler->getGUIEnabled();}
        void setGUIExclusive(bool exclusive);
        bool isKeyDown(OIS::KeyCode key);
        void setDisplaySize(int width, int height);
    };
}
#endif
