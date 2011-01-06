//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TSTRING_H_
#define _TSTRING_H_

namespace Tubras
{
    typedef irr::core::stringc TString;
    typedef irr::core::stringw TStringW;
    typedef TArray<TString> TStringVector;
    typedef TList<TString> TStringList;
}
namespace OOLUA
{
    typedef Tubras::TString TString;
} 
OOLUA_PROXY_CLASS(TString)
    OOLUA_TYPEDEFS
        No_public_constructors,
        No_public_destructor
    OOLUA_END_TYPES
    OOLUA_MEM_FUNC_CONST(u32, size)
    OOLUA_MEM_FUNC(TString&, make_lower)
OOLUA_CLASS_END

#endif
