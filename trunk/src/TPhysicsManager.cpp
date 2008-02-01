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
    //                    T P h y s i c s M a n a g e r
    //-----------------------------------------------------------------------
    TPhysicsManager::TPhysicsManager() : TObject()
    {
        m_mode = pmNone;
        m_world = NULL;
        //m_debugOverlay = NULL;
        m_userDebugString = "";
    }

    //-----------------------------------------------------------------------
    //                   ~ T P h y s i c s M a n a g e r
    //-----------------------------------------------------------------------
    TPhysicsManager::~TPhysicsManager()
    {
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
        /*

        if(!m_debugOverlay)
        {

            m_debugOverlay = new TTextOverlay("DebugPhysicsInfo",TDim(0.25,0.925,0.5,0.04),
                "TrebuchetMSBold", TColour(1,1,1,1), 18,                    
                TColour(1,1,1),0.5);
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
        */


    }

    //-----------------------------------------------------------------------
    //                       s h o w D e b u g I n f o
    //-----------------------------------------------------------------------
    /*
    int TPhysicsManager::showDebugInfo(TTask* task)
    {
        if(task->m_elapsedTime >= 500)
        {
            //
            // update and reset time
            //
            char buf[128];

            size_t total=0,active=0,sleeping=0,wants=0;

            TDynamicNodeList nl = m_world->getDynamicWorld()->getDynamicNodes();
            total = nl.size();

            TDynamicNodeList::iterator itr = nl.begin();
            while(itr != nl.end())
            {
                TRigidBody* body = (*itr)->getRigidBody();
                switch(body->getActivationState())
                {
                case ACTIVE_TAG:
                    ++active; break;
                case ISLAND_SLEEPING:
                    ++sleeping; break;
                case WANTS_DEACTIVATION:
                    ++wants; break;
                default:
                    break;
                };
                ++itr;
            }

            sprintf(buf,"Nodes: Total(%d) Active(%d) Sleeping(%d) Wants Deactivation(%d)",total,active,sleeping,wants);
            m_debugOverlay->updateItem(0,buf);

            TVector3 gravity=m_world->getGravity();
            TString endis="";

            sprintf(buf,"World: Gravity(%.2f) Deactivation(%s)",gravity.y,endis.c_str());
            m_debugOverlay->updateItem(1,buf);

            sprintf(buf,"%s",m_userDebugString.c_str());
            m_debugOverlay->updateItem(2,buf);

            task->m_elapsedTime = 0;
        }

        return TTask::cont;
    }
    */

    //-----------------------------------------------------------------------
    //                    s e t U s e r D e b u g S t r i n g
    //-----------------------------------------------------------------------
    void TPhysicsManager::setUserDebugString(const TString& value)
    {
        m_userDebugString = value;
    }
}

