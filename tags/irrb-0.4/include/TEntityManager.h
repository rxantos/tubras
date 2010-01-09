//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TENTITYMANAGER_H_
#define _TENTITYMANAGER_H_

namespace Tubras
{
    typedef TMap<TString, TEntity*> TEntityMap;
    typedef TEntityMap::Iterator TEntityMapItr;

    class TEntityManager
    {
        friend class TApplication;
    private:
        u32                         m_currentID;
        TEntityMap                  m_entities;
        TArray<IBehaviorFactory*>   m_factories;

    protected:
        TEntityManager();
        virtual ~TEntityManager();
        int initialize();

    public:

        TEntity* addEntity(const TString name);
        IBehavior* createBehavior(const TString type, TProperties& properties,
            TEntity* owner);

        void registerBehaviorFactory(IBehaviorFactory* factory);
    };
}

#endif
