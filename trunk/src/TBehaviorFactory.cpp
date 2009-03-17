//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                       c r e a t e B e ha v i o r
    //-----------------------------------------------------------------------
    IBehavior* TBehaviorFactory::createBehavior(const TString type, 
        TProperties& properties, TEntity* owner)
    {
        IBehavior*  result=0;

        if(type.equals_ignore_case("view"))
            result = new TBView();
        else if(type.equals_ignore_case("staticmesh"))
            result = new TBStaticMesh();

        return result;
    }

}
