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
    TEntityManager::TEntityManager() : m_currentID(0), m_behaviorFactory(0)
    {
    }

    //-----------------------------------------------------------------------
    //                     ~ T E n t i t y M a n a g e r
    //-----------------------------------------------------------------------
    TEntityManager::~TEntityManager()
    {
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
        m_behaviorFactory = new TBehaviorFactory();

        return 0;
    }

    //-----------------------------------------------------------------------
    //                       c r e a t e E n t i t y
    //-----------------------------------------------------------------------
    TEntity* TEntityManager::createEntity(TString name)
    {
        ++m_currentID;
        TEntity* entity = new TEntity(name, m_currentID);
        return entity;
    }

    //-----------------------------------------------------------------------
    //                       c r e a t e B e ha v i o r
    //-----------------------------------------------------------------------
    IBehavior* TEntityManager::createBehavior(const TString type, 
        TProperties& properties, TEntity* owner)
    {
        return m_behaviorFactory->createBehavior(type, properties, owner);
    }
}
