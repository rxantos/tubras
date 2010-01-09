//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
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
