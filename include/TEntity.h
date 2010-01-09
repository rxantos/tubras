//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TENTITY_H_
#define _TENTITY_H_

namespace Tubras
{
    typedef TList<IListener*> TListenerList;

    class TEntity : public IReferenceCounted
    {
        friend class TEntityManager;

    private:
        TProperties         m_properties;
        TBehaviorMap        m_behaviors;
        TListenerList       m_listeners;
        TEvent              m_eventBAdded;
        TEvent              m_eventBRemoved;
        TEvent              m_eventBUpdated;
        TString             m_name;
        u32                 m_id;

    protected:
        TEntity(TString name, u32 id);
        virtual ~TEntity();

    public:
        TString getName() {return m_name;}
        u32 getID() {return m_id;}

        TProperties& properties() {return m_properties;}
        
        TProperty& operator[](TString name) {
            return m_properties[name];
        }

        TProperty& operator[](const char name[]) {
            return m_properties[name];
        }

        IBehavior* addBehavior(const TString type, TProperties& properties);
        bool addBehavior(IBehavior* value);

        IBehavior* getBehavior(TString name) 
        {
            if(m_behaviors.find(name))
                return m_behaviors[name];
            return 0;          
        }

        void addListener(IListener* listener);
        void removeListener(IListener* listener);
        void notifyListeners(TEvent& event);

    };
}

#endif
