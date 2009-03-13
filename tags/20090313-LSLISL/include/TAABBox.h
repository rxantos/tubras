//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TAABBOX_H_
#define _TAABBOX_H_

namespace Tubras
{
    class TAABBox : public aabbox3df
    {
    public:
        TAABBox();
        TAABBox(const aabbox3df& other) : aabbox3df(other.MinEdge,other.MaxEdge) {}
        TVector3 getHalfSize() {return getExtent() / 2.0f;}
    };
} 
#endif
