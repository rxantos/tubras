//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
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

    class TInputManager
    {
        friend class TApplication;
    private:
        void*			        m_windowHandle;
        u32                     m_display;
        TInputHandler*		    m_inputHandler;
        int                     m_numSticks;
    protected:
        TInputManager();
        ~TInputManager();
        int initialize();
    public:
        int step();
        TInputHandler* getHandler() {return m_inputHandler;}
        bool isKeyDown(EKEY_CODE key);
        void setCursorVisible(bool value) {m_inputHandler->setCursorVisible(value);}
        bool getCursorVisible() {return m_inputHandler->getCursorVisible();}

        u32 getInputMode() {return m_inputHandler->getInputMode();}
        void setInputMode(u32 value) {m_inputHandler->setInputMode(value);}
    };
}
#endif
