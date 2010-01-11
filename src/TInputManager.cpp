//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"
#ifndef TUBRAS_PLATFORM_WIN32
#ifdef _IRR_COMPILE_WITH_X11_
#include <X11/Xlib.h>
#endif
#endif

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                       T I n p u t M a n a g e r
    //-----------------------------------------------------------------------
    TInputManager::TInputManager(IrrlichtDevice* device) : m_inputHandler(0),
        m_device(device)

    {
    }

    //-----------------------------------------------------------------------
    //                      ~T I n p u t M a n a g e r
    //-----------------------------------------------------------------------
    TInputManager::~TInputManager()
    {
        if(m_inputHandler)
        {
            delete m_inputHandler;
            m_inputHandler = 0;
        }
    }

    //-----------------------------------------------------------------------
    //                          I n i t i a l i z e 
    //-----------------------------------------------------------------------
    int TInputManager::initialize()
    {
        int result=0;

        m_inputHandler = new TInputHandler();
        if(m_inputHandler->Initialize())
            return 1;       

        return result;
    }

    //-----------------------------------------------------------------------
    //                              u p d a t e
    //-----------------------------------------------------------------------
    void TInputManager::update(const f32 deltaTime)
    {
        if(!m_device->run())
            getApplication()->stopRunning();
    }

    //-----------------------------------------------------------------------
    //                         i s K e y D o w n 
    //-----------------------------------------------------------------------
    bool TInputManager::isKeyDown(EKEY_CODE key)
    {
        return m_inputHandler->isKeyDown(key);
    }

    //-----------------------------------------------------------------------
    //                         i s K e y D o w n 
    //-----------------------------------------------------------------------
    EKEY_CODE TInputManager::getKeyForCommand(core::stringc cmd)
    {
        EKEY_CODE result = (EKEY_CODE)0;
        core::stringc input = m_inputHandler->getBinder()->getInputForCommand(cmd);
        if(input.size())
        {
            s32 start = input.findLast('.');
            stringc key = input.subString(start+1, input.size());
            result = m_inputHandler->getKeyCode(key);
        }

        return result;
    }
}
