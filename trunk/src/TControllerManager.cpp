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
#include "tubras.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                     T C o n t r o l l e r M a n a g e r
    //-----------------------------------------------------------------------
    TControllerManager::TControllerManager() : TObject()
    {

    }

    //-----------------------------------------------------------------------
    //                     T C o n t r o l l e r M a n a g e r
    //-----------------------------------------------------------------------
    TControllerManager::~TControllerManager()
    {

        for ( TControllerMapItr it = m_controllers.getIterator(); !it.atEnd(); it++)
        {
            TController*  controller = it->getValue();
            if(controller->getEnabled())
                controller->setEnabled(false);

            delete controller;
        }
        m_controllers.clear();

    }

    //-----------------------------------------------------------------------
    //                   g e t S i n g l e t o n P t r
    //-----------------------------------------------------------------------
    template<> TControllerManager* TSingleton<TControllerManager>::ms_Singleton = 0;

    TControllerManager* TControllerManager::getSingletonPtr(void)
    {
        return ms_Singleton;
    }

    //-----------------------------------------------------------------------
    //                       g e t S i n g l e t o n
    //-----------------------------------------------------------------------
    TControllerManager& TControllerManager::getSingleton(void)
    {
        assert( ms_Singleton );  return ( *ms_Singleton );
    }

    //-----------------------------------------------------------------------
    //                        i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TControllerManager::initialize()
    {
        TObject::initialize();
        m_clock = getApplication()->getGlobalClock();
        return 0;
    }

    //-----------------------------------------------------------------------
    //                     s e t G l o b a l C l o c k
    //-----------------------------------------------------------------------
    void TControllerManager::setGlobalClock(TTimer* clock)
    {
        m_clock = clock;
    }

    //-----------------------------------------------------------------------
    //                             s t a r t 
    //-----------------------------------------------------------------------
    int TControllerManager::start(TController* controller)
    {

        TControllerMapItr it = m_activeControllers.find(controller->getName());
        if(!it.atEnd())
            return 1;

        if(m_clock)
        {
            controller->m_startTime = m_clock->getMilliseconds();
            controller->m_lastTime = controller->m_startTime;
        }
        m_activeControllers[controller->getName()] = controller;

        return 0;
    }

    //-----------------------------------------------------------------------
    //                              s t o p
    //-----------------------------------------------------------------------
    int TControllerManager::stop(TController* controller)
    {
        //
        // remove from running list
        //

        TControllerMapItr itr;

        itr = m_activeControllers.find(controller->getName());
        if(!itr.atEnd())
        {
            m_activeControllers.delink(itr->getKey());
        }


        return 0;
    }

    //-----------------------------------------------------------------------
    //                       r e g i s t e r C o n t r o l l e r
    //-----------------------------------------------------------------------
    int TControllerManager::registerController(TController* controller)
    {
        TControllerMapItr itr;

        itr = m_controllers.find(controller->getName());

        if(!itr.atEnd())
        {
            TString msg;
            msg = "Duplicate Controller Registration: ";
            msg += controller->getName();
            logMessage(msg);
            return 1;
        }

        m_controllers[controller->getName()] = controller;

        return 0;
    }

    //-----------------------------------------------------------------------
    //                s e t C o n t r o l l e r E n a b l e d
    //-----------------------------------------------------------------------
    void TControllerManager::setControllerEnabled(const TString& controllerName, const bool value)
    {
        TControllerMapItr itr;
        itr = m_controllers.find(controllerName);
        if(!itr.atEnd())
            itr->getValue()->setEnabled(value);
    }

    //-----------------------------------------------------------------------
    //           s e t N o d e C o n t r o l l e r s E n a b l e d
    //-----------------------------------------------------------------------
    void TControllerManager::setNodeControllersEnabled(const TString& nodeName, const bool value)
    {
        TControllerMapItr itr = m_controllers.getIterator();
        while(!itr.atEnd())
        {
            TController* controller = itr->getValue();
            ISceneNode* node = controller->getNode();
            if(node && (nodeName.equals_ignore_case(node->getName())))
            {
                controller->setEnabled(value);
            }
            itr++;
        }
    }

    //-----------------------------------------------------------------------
    //                       g e t C o n t r o l l e r
    //-----------------------------------------------------------------------
    TController* TControllerManager::getController(const TString& controllerName)
    {
        TControllerMapItr itr = m_controllers.find(controllerName);
        if(!itr.atEnd())
            return itr->getValue();

        return NULL;
    }

    //-----------------------------------------------------------------------
    //                             r e m o v e
    //-----------------------------------------------------------------------
    int TControllerManager::remove(const TString& controllerName)
    {
        TControllerMapItr itr;

        itr = m_controllers.find(controllerName);
        if(itr.atEnd())
        {
            TString msg;
            msg = "Attempt to remove non-existent controller: ";
            msg += controllerName;
            logMessage(msg);
            return 1;
        }
        remove(itr->getValue());


        return 0;
    }

    //-----------------------------------------------------------------------
    //                             r e m o v e
    //-----------------------------------------------------------------------
    int TControllerManager::remove(TController* controller)
    {
        TControllerMapItr itr;

        itr = m_controllers.find(controller->getName());
        if(itr.atEnd())
        {
            TString msg;
            msg = "Attempt to remove non-existent controller: ";
            msg += controller->getName();
            logMessage(msg);
            return 1;
        }

        if(controller->getEnabled())
            controller->setEnabled(false);

        m_controllers.delink(itr->getKey());

        return 0;
    }

    //-----------------------------------------------------------------------
    //                               s t e p
    //-----------------------------------------------------------------------
    void TControllerManager::step()
    {
        //
        // run tasks
        //
        for ( TControllerMapItr it = m_controllers.getIterator(); !it.atEnd(); it++)
        {
            TController*  controller = it->getValue();
            if(controller->m_enabled)
            {
                //
                // set up controller specific timing
                //
                ULONG curTime = m_clock->getMilliseconds();
                if(!controller->m_startTime)
                {
                    controller->m_startTime = curTime;
                    controller->m_lastTime = curTime;
                    continue;
                }
                controller->m_elapsedTime = curTime - controller->m_startTime;
                controller->m_deltaTime = (float)(curTime - controller->m_lastTime);

                //
                // invoke the controller update function
                //

                controller->update(controller->getFunction()->step(controller->m_deltaTime));
                controller->m_lastTime = m_clock->getMilliseconds();
            }
        }

    }

}