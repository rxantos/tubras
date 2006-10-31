//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006 Tubras Software Ltd
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
    //                    T P h y s i c s M a n a g e r
    //-----------------------------------------------------------------------
    TPhysicsManager::TPhysicsManager() : TObject()
    {
        m_mode = pmNone;
        m_world = NULL;
		m_userDebugString = "";
    }

    //-----------------------------------------------------------------------
    //                   ~ T P h y s i c s M a n a g e r
    //-----------------------------------------------------------------------
    TPhysicsManager::~TPhysicsManager()
    {

        //
        // bug in the bullet library that causes hang, leak for now.
        //

        if(m_world)
            delete m_world;
    }

    //-----------------------------------------------------------------------
    //                   g e t S i n g l e t o n P t r
    //-----------------------------------------------------------------------
    template<> TPhysicsManager* TSingleton<TPhysicsManager>::ms_Singleton = 0;

    TPhysicsManager* TPhysicsManager::getSingletonPtr(void)
    {
        return ms_Singleton;
    }

    //-----------------------------------------------------------------------
    //                       g e t S i n g l e t o n
    //-----------------------------------------------------------------------
    TPhysicsManager& TPhysicsManager::getSingleton(void)
    {
        assert( ms_Singleton );  return ( *ms_Singleton );
    }

    //-----------------------------------------------------------------------
    //                         i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TPhysicsManager::initialize()
    {
        m_world = new TDynamicWorld();

        return 0;
    }

    //-----------------------------------------------------------------------
    //                    t o g g l e D e b u g O v e r l a y
    //-----------------------------------------------------------------------
    void TPhysicsManager::toggleDebugOverlay()
    {

            if(!m_debugOverlay)
            {

                m_debugOverlay = new TTextOverlay("DebugPhysicsInfo",TDim(0.25,0.925,0.5,0.04),
                    "TrebuchetMSBold", TColor(1,1,1,1), 18,                    
                    TColor(1,1,1),0.5);
                m_debugOverlay->addItem("Nodes: Total(x) Active(x) Sleeping(x)", taCenter);
                m_debugOverlay->addItem("World: Gravity(x) Deactivation(x)", taCenter);
                m_debugOverlay->addItem("(User Data)", taCenter);


                m_debugOverlay->setVisible(true);
                m_debugTask = new TTask("debugPhysicsTask",TASK_DELEGATE(TPhysicsManager::showDebugInfo),0,0,NULL,"testTaskDone");
                m_debugTask->start();
            }
            else
            {
                if(m_debugOverlay->getVisible())
                {
                    m_debugOverlay->setVisible(false);
                    m_debugTask->stop();
                }
                else 
                {
                    m_debugOverlay->setVisible(true);
                    m_debugTask->start();
                }
            }


    }

    //-----------------------------------------------------------------------
    //                       s h o w D e b u g I n f o
    //-----------------------------------------------------------------------
    int TPhysicsManager::showDebugInfo(TTask* task)
    {
        if(task->m_elapsedTime >= 500)
        {
            //
            // update and reset time
            //
            char buf[128];

            int total=0,active=0,sleeping=0;

            total = m_world->getDynamicWorld()->getBodies().size();

            sprintf(buf,"Nodes: Total(%d) Active(%d) Sleeping(%d)",total,active,sleeping);
            m_debugOverlay->updateItem(0,buf);

            float gravity=0.0;
            string endis="";

            sprintf(buf,"World: Gravity(%.2f) Deactivation(%s)",gravity,endis.c_str());
            m_debugOverlay->updateItem(1,buf);

            sprintf(buf,"%s",m_userDebugString.c_str());
            m_debugOverlay->updateItem(2,buf);

            task->m_elapsedTime = 0;
        }

        return TTask::cont;
    }

    //-----------------------------------------------------------------------
    //                    s e t U s e r D e b u g S t r i n g
    //-----------------------------------------------------------------------
	void TPhysicsManager::setUserDebugString(string value)
	{
		m_userDebugString = value;
	}
}