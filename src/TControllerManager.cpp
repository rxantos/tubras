//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                     T C o n t r o l l e r M a n a g e r
    //-----------------------------------------------------------------------
    TControllerManager::TControllerManager() : TDelegate()
    {
    }

    //-----------------------------------------------------------------------
    //                     T C o n t r o l l e r M a n a g e r
    //-----------------------------------------------------------------------
    TControllerManager::~TControllerManager()
    {
        while(m_activeControllers.size())
        {
            TControllerMapItr itr = m_activeControllers.getIterator();
            TControllerMap::Node* node = m_activeControllers.delink(itr->getKey());
            delete node;
        }
        while(m_controllers.size())
        {
            TControllerMapItr itr = m_controllers.getIterator();
            TController*  controller = itr->getValue();
            TControllerMap::Node* node = m_controllers.delink(itr->getKey());
            delete node;
            delete controller;
        }
    }

    //-----------------------------------------------------------------------
    //                        i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TControllerManager::initialize()
    {
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
        TString cname = controller->getName();
        TControllerMap::Node* node = m_controllers.find(cname);
        if(!node)
            return 1;

        controller->m_startTime = 0;
        m_activeControllers[cname] = controller;

        // remove from stopped
        for(u32 i=0; i<m_stoppedControllers.size(); i++)
            if(m_stoppedControllers[i] == cname)
            {
                m_stoppedControllers.erase(i);
                break;
            }

        return 0;
    }

    //-----------------------------------------------------------------------
    //                              s t o p
    //-----------------------------------------------------------------------
    int TControllerManager::stop(TController* controller)
    {
        //
        // remove from active list
        //
        TString cname = controller->getName();

        TControllerMap::Node* node = m_activeControllers.find(cname);
        if(node)
            m_stoppedControllers.push_back(cname);

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
            getApplication()->logMessage(LOG_WARNING, 
                "Duplicate Controller Registration: %s", controller->getName().c_str());
            return 1;
        }
        m_controllers[controller->getName()] = controller;

        return 0;
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
                //controller->setEnabled(value);
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

        TControllerMap::Node* node = m_controllers.find(controllerName);
        if(!node)
        {
            getApplication()->logMessage(LOG_WARNING, 
                "Attempt to remove non-existent controller: %s", controllerName.c_str());
            return 1;
        }
        remove(node->getValue());
        return 0;
    }

    //-----------------------------------------------------------------------
    //                             r e m o v e
    //-----------------------------------------------------------------------
    int TControllerManager::remove(TController* controller)
    {

        TControllerMap::Node* node = m_controllers.find(controller->getName());
        if(!node)
        {
            getApplication()->logMessage(LOG_WARNING, 
                "Attempt to remove non-existent controller: %s", controller->getName().c_str());
            return 1;
        }


        delete node->getValue();
        node = m_controllers.delink(node->getKey());
        delete node;

        return 0;
    }

    //-----------------------------------------------------------------------
    //                               s t e p
    //-----------------------------------------------------------------------
    void TControllerManager::step()
    {
        // run active controllers
        for ( TControllerMapItr it = m_activeControllers.getIterator(); !it.atEnd(); it++)
        {
            TController*  controller = it->getValue();
            //
            // set up controller specific timing
            //
            u32 curTime = m_clock->getMilliseconds();
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

        // remove stopped controllers from active list        
        if(u32 size=m_stoppedControllers.size())
        {
            for(u32 i=0;i<size;i++)
            {
                TString cname = m_stoppedControllers[i];
                TControllerMap::Node* node = m_activeControllers.find(cname);
                if(node)
                {
                    node = m_activeControllers.delink(cname);
                    if(node)
                        delete node;
                }
            }
            m_stoppedControllers.clear();
        }
    }
}
