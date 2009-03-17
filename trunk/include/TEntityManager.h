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
    class TEntityManager : public Tubras::TSingleton<Tubras::TEntityManager>
    {
        friend class TApplication;
    private:
        u32                         m_currentID;
        TArray<IBehaviorFactory*>   m_factoryList;

    protected:
        TEntityManager();
        virtual ~TEntityManager();

    public:
        static TEntityManager& getSingleton(void);
        static TEntityManager* getSingletonPtr(void);

        int initialize();

        TEntity* createEntity(const TString name);
        IBehavior* createBehavior(const TString type, TProperties& properties,
            TEntity* owner);

        void registerBehaviorFactory(IBehaviorFactory* factory);
    };
}

#endif
