//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TSOUNDNODE_H_
#define _TSOUNDNODE_H_

namespace Tubras
{

    class TSoundNode : public TEmptyNode
    {
        TSound*                 m_sound;

    public:
        TSoundNode (TSound* sound, ISceneNode *parent);
        virtual ~TSoundNode();
        TSound* getSound() {return m_sound;}

    };

}
#endif

