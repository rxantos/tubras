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
