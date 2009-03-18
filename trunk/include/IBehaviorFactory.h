//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _IBEHAVIORFACTORY_H_
#define _IBEHAVIORFACTORY_H_

namespace Tubras
{
    class IBehaviorFactory : public virtual IReferenceCounted
    {

    public:
        virtual ~IBehaviorFactory() {}
        virtual IBehavior* createBehavior(const TString type, TProperties& properties,
            TEntity* owner) = 0;

    };
}

#endif