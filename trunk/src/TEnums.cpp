//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras {
    struct RegEnumType 
    {
        const char *name;
        int value;
    };

    //-----------------------------------------------------------------------
    //                          _ l u a E n u m s
    //-----------------------------------------------------------------------
    static const RegEnumType _luaEnums[] = {
        { "mdtError", mdtError },
        { "mdtOK", mdtOK },
        { "mdtYesNo", mdtYesNo },

        { "rmNormal", rmNormal },
        { "rmWire", rmWire },
        { "rmNormalWire", rmNormalWire },
        { "rmPointCloud", rmPointCloud },

        {0}};

    //-----------------------------------------------------------------------
    //                   _ r e g i s t e r L u a E n u m s
    //-----------------------------------------------------------------------
    int _registerLuaEnums(lua_State* L)
    {
        int i = -1;
        while(_luaEnums[++i].name)
        {
            lua_pushnumber(L, _luaEnums[i].value);
            lua_setglobal(L, _luaEnums[i].name);
        }

        return 0;
    }
}