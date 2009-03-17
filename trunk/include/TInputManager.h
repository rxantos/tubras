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

    class TInputManager : public Tubras::TSingleton<Tubras::TInputManager>
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
    public:
        static TInputManager& getSingleton(void);
        static TInputManager* getSingletonPtr(void);
        int initialize();
        int step();
        TInputHandler* getHandler() {return m_inputHandler;}
        void setGUIEnabled(bool enabled);
        bool getGUIEnabled() {return m_inputHandler->getGUIEnabled();}
        void setGUIExclusive(bool exclusive);
        bool isKeyDown(EKEY_CODE key);
        void setCursorVisible(bool value) {m_inputHandler->setCursorVisible(value);}
        bool getCursorVisible() {return m_inputHandler->getCursorVisible();}
    };
}
#endif
