//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{
    TBRotation::~TBRotation()
    {

    }

    //-----------------------------------------------------------------------
    //                         i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TBRotation::initialize(TEntity* owner, TProperties& properties)
    {
        TBehavior::initialize(owner, properties);

        //
        // listen for other behvior events
        //
        owner->addListener(this);
        m_behaviorAddedID = getApplication()->getEventManager()->getEventID("entity:behaviorAdded");

        m_target = properties["target"].asString();
        m_velocity = properties["velocity"].asFloat();
        m_axis = *(TVector3 *)properties["axis"].asPointer();
        m_node = 0;

        IBehavior* behavior = owner->getBehavior(m_target);
        if(behavior)
        {
            m_node = (ISceneNode*) (*behavior)["node"].asPointer();
            if(m_node)
            {
                char name[64];
                sprintf(name,"e%d:rotation:%p",owner->getID(),this);
                m_controller = new TRotateController(name, m_node, 
                    m_velocity, m_axis);
            }
        }

        return 0;
    }

    //-----------------------------------------------------------------------
    //                             u p d a t e
    //-----------------------------------------------------------------------
    void TBRotation::update(TEvent& event)
    {
        if(m_node)
            return;

        u32 id = event.getID();

        if(id == m_behaviorAddedID)
        {
            IBehavior* behavior = (IBehavior*) event.getParameter(0)->getPointerValue();
            if(m_target == behavior->getName())
            {
                m_node = (ISceneNode*) (*behavior)["node"].asPointer();
                if(m_node)
                {
                    char name[64];
                    sprintf(name,"rotation:%p",this);
                    m_controller = new TRotateController(name, m_node, 
                        m_velocity, m_axis);
                }
            }
        }
    }
}
