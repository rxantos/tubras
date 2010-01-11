//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
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
        IrrlichtDevice*         m_device;

    protected:
        TInputManager(IrrlichtDevice* device);
        ~TInputManager();
        int initialize();
    public:
        void update(const f32 deltaTime);
        TInputHandler* getHandler() {return m_inputHandler;}
        bool isKeyDown(EKEY_CODE key);
        void setCursorVisible(bool value) {m_inputHandler->setCursorVisible(value);}
        bool getCursorVisible() {return m_inputHandler->getCursorVisible();}

        u32 getInputMode() {return m_inputHandler->getInputMode();}
        void setInputMode(u32 value) {m_inputHandler->setInputMode(value);}

        void setKeyPreviewer(IKeyPreviewer* value) {m_inputHandler->setKeyPreviewer(value);}
        EKEY_CODE getKeyForCommand(core::stringc cmd);
    };
}
#endif
