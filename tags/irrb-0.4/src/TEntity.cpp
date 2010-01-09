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
    //                            T E n t i t y 
    //-----------------------------------------------------------------------
    TEntity::TEntity(TString name, u32 id) : m_name(name), m_id(id)
    {
        m_eventBAdded.setName("entity:behaviorAdded");
        m_eventBRemoved.setName("entity:behaviorRemoved");
        m_eventBUpdated.setName("entity:behaviorUpdated");
        m_eventBAdded.addPointerParameter(0);
        m_eventBRemoved.addPointerParameter(0);
        m_eventBUpdated.addPointerParameter(0);
    }

    //-----------------------------------------------------------------------
    //                           ~ T E n t i t y 
    //-----------------------------------------------------------------------
    TEntity::~TEntity()
    {
        for ( TBehaviorMapItr it = m_behaviors.getIterator(); !it.atEnd(); it++)
        {
            IBehavior*  behavior = it->getValue();
            behavior->drop();
        }
        m_behaviors.clear();

    }

    //-----------------------------------------------------------------------
    //                         a d d B e h a v i o r
    //-----------------------------------------------------------------------
    IBehavior* TEntity::addBehavior(const TString type, TProperties& properties)
    {
        IBehavior* result = getApplication()->getEntityManager()->createBehavior(type, properties, this);

        if(result)
        {
            m_behaviors[result->getName()] = result;
            m_eventBAdded.getParameter(0)->setPointerValue(result);
            notifyListeners(m_eventBAdded);
        }

        return result;
    }

    //-----------------------------------------------------------------------
    //                         a d d B e h a v i o r
    //-----------------------------------------------------------------------
    bool TEntity::addBehavior(IBehavior* value)
    {
        if(value->addOwner(this))
        {
            m_behaviors[value->getName()] = value;
            m_eventBAdded.getParameter(0)->setPointerValue(value);
            notifyListeners(m_eventBAdded);
            return true;
        }
        return false;
    }

    //-----------------------------------------------------------------------
    //                          a d d L i s t e n e r
    //-----------------------------------------------------------------------
    void TEntity::addListener(IListener* listener)
    {
        m_listeners.push_back(listener);
    }

    //-----------------------------------------------------------------------
    //                       r e m o v e L i s t e n e r
    //-----------------------------------------------------------------------
    void TEntity::removeListener(IListener* listener)
    {
        TListenerList::Iterator itr = m_listeners.begin();
        while(*itr != listener)
            itr++;

        if(*itr == listener)
            m_listeners.erase(itr);
    }

    //-----------------------------------------------------------------------
    //                       n o t i f y L i s t e n e r s
    //-----------------------------------------------------------------------
    void TEntity::notifyListeners(TEvent& event)
    {
        TListenerList::Iterator itr = m_listeners.begin();
        while(itr != m_listeners.end())
        {
            (*itr)->update(event);
            itr++;
        }
    }
}
