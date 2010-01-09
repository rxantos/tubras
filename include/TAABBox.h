//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TAABBOX_H_
#define _TAABBOX_H_

namespace Tubras
{
    class TAABBox : public aabbox3df
    {
    public:
        TAABBox();
        TAABBox(const vector3df& init) : aabbox3df(init) {}
        TAABBox(const aabbox3df& other) : aabbox3df(other.MinEdge,other.MaxEdge) {}
        TVector3 getHalfSize() {return getExtent() / 2.0f;}
    };
} 
#endif
