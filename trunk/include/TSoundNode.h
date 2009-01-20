//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
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

