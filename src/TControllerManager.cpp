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
    void TControllerManager::setControllerEnabled(TString controllerName, bool value)
    {
        TControllerMapItr itr;
        itr = m_controllers.find(controllerName);
        if(!itr.atEnd())
            itr->getValue()->setEnabled(value);
    }

    //-----------------------------------------------------------------------
    //           s e t N o d e C o n t r o l l e r s E n a b l e d
    //-----------------------------------------------------------------------
    void TControllerManager::setNodeControllersEnabled(TString nodeName, bool value)
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
    TController* TControllerManager::getController(TString controllerName)
    {
        TControllerMapItr itr = m_controllers.find(controllerName);
        if(!itr.atEnd())
            return itr->getValue();

        return NULL;
    }

    //-----------------------------------------------------------------------
    //                             r e m o v e
    //-----------------------------------------------------------------------
    int TControllerManager::remove(TString controllerName)
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
                controller->m_deltaTime = curTime - controller->m_lastTime;

                //
                // invoke the controller update function
                //

                controller->update(controller->getFunction()->step(controller->m_deltaTime));
                controller->m_lastTime = m_clock->getMilliseconds();
            }
        }

    }

}