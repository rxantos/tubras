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
    //                     T E n t i t y M a n a g e r
    //-----------------------------------------------------------------------
    TEntityManager::TEntityManager() : m_currentID(0)
    {
    }

    //-----------------------------------------------------------------------
    //                     ~ T E n t i t y M a n a g e r
    //-----------------------------------------------------------------------
    TEntityManager::~TEntityManager()
    {
	    for (u32 i=0; i<m_factories.size(); i++)
            m_factories[i]->drop();
        m_factories.clear();

        for ( TEntityMapItr it = m_entities.getIterator(); !it.atEnd(); it++)
        {
            TEntity*  entity = it->getValue();
            entity->drop();
        }
        m_entities.clear();

    }

    //-----------------------------------------------------------------------
    //                   g e t S i n g l e t o n P t r 
    //-----------------------------------------------------------------------
    template<> TEntityManager* TSingleton<TEntityManager>::ms_Singleton = 0;

    TEntityManager* TEntityManager::getSingletonPtr(void)
    {
        return ms_Singleton;
    }

    //-----------------------------------------------------------------------
    //                       g e t S i n g l e t o n 
    //-----------------------------------------------------------------------
    TEntityManager& TEntityManager::getSingleton(void)
    {  
        assert( ms_Singleton );  return ( *ms_Singleton );  
    }

    //-----------------------------------------------------------------------
    //                         i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TEntityManager::initialize()
    {
        TBehaviorFactory* factory = new TBehaviorFactory();
        registerBehaviorFactory(factory);
        factory->drop();
        return 0;
    }

    //-----------------------------------------------------------------------
    //                 r e g i s t e r B e h a v i o r F a c t o r y
    //-----------------------------------------------------------------------
    void TEntityManager::registerBehaviorFactory(IBehaviorFactory* factory)
    {
        if(factory)
        {
            factory->grab();
            m_factories.push_back(factory);
        }
        //
        // todo: behavior factory plugin loading/initialization
        //
    }

    //-----------------------------------------------------------------------
    //                           a d d E n t i t y
    //-----------------------------------------------------------------------
    TEntity* TEntityManager::addEntity(TString name)
    {
        TEntityMap::Node* node = m_entities.find(name);
        if(node)
            return node->getValue();

        ++m_currentID;
        TEntity* entity = new TEntity(name, m_currentID);
        m_entities[name] = entity;
        return entity;
    }

    //-----------------------------------------------------------------------
    //                       c r e a t e B e ha v i o r
    //-----------------------------------------------------------------------
    IBehavior* TEntityManager::createBehavior(const TString type, 
        TProperties& properties, TEntity* owner)
    {
	    IBehavior* result=0;

        // search back to front to allow factory plugins to override 
        // default behaviors.
	    for (int i=(int)m_factories.size()-1; i>=0 && !result; --i)
			result = m_factories[i]->createBehavior(type, properties, owner);

        if(result)
        {
            result->initialize(owner, properties);
        }
        else 
        {
            TString msg = "Error creating behavior - undefined: \"";
            msg += type;
            msg += "\"";
            getApplication()->logMessage(msg);
        }

        return result;
    }
}
