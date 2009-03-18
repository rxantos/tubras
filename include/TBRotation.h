//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TBROTATION_H_
#define _TBROTATION_H_

namespace Tubras
{
    class TBRotation : public TBehavior
    {
        friend class TBehaviorFactory;
    private:
        ISceneNode*         m_node;
        TRotateController*  m_controller;

    protected:
        TBRotation() : TBehavior("rotation") {}
        virtual ~TBRotation();

    public:
        int initialize(TEntity* owner, TProperties& properties);
    };
}

#endif
