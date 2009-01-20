//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TSCENENODE_H_
#define _TSCENENODE_H_

namespace Tubras
{
    class TSceneNode : public TObject, public ISceneNode
    {
    protected:
        TSceneNode(ISceneNode* parent=0, ISceneManager* mgr=0, s32 id=-1,
				const TVector3& position = TVector3(0,0,0),
				const TVector3& rotation = TVector3(0,0,0),
				const TVector3& scale = TVector3(1.0f, 1.0f, 1.0f));
    public:
        virtual ~TSceneNode();
        virtual u32 getMaterialCount() const {return 0;}
        void attachDynamicNode(TDynamicNode* node);

    };
} 
#endif
