//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
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
        else if(type.equals_ignore_case("rotation"))
            result = new TBRotation();

        return result;
    }

}
