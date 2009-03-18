//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TBVIEW_H_
#define _TBVIEW_H_

namespace Tubras
{
    class TBView : public virtual IBehavior
    {
        friend class TBehaviorFactory;
    protected:
        TBView() : IBehavior("view") {}
    public:
        int initialize(TEntity* owner, TProperties& properties);
    };
}

#endif
