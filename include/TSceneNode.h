//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TSCENENODE_H_
#define _TSCENENODE_H_

namespace Tubras
{
    class TSceneNode : public TDelegate, public ISceneNode
    {
    protected:
        TSceneNode(ISceneNode* parent=0, s32 id=-1,
				const TVector3& position = TVector3(0,0,0),
				const TVector3& rotation = TVector3(0,0,0),
				const TVector3& scale = TVector3(1.0f, 1.0f, 1.0f));
    public:
        virtual ~TSceneNode();
        virtual u32 getMaterialCount() const {return 0;}
        void attachPhysicsObject(TPhysicsObject* object);
    };
} 
#endif
