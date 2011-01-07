#include "tubras.h"

//-----------------------------------------------------------------------
//                _ r e g i s t e r L u a I n t e r f a c e s
//-----------------------------------------------------------------------
namespace Tubras
{
    int _registerLuaInterfaces(lua_State* L)
    {
        // initialize OOLUA to use our Lua state pointer.
        OOLUA::setup_user_lua_state(L);

        // OOLUA class registration
        OOLUA::register_class<TString>(L);
        OOLUA::register_class<TEvent>(L);
        OOLUA::register_class<TApplication>(L);

        // set global variable "TubrasApp" to the application instance.
        TApplication* theApp = getApplication();
        OOLUA::set_global<TApplication *>(L, "TubrasApp", theApp);
        return 0;
    }
}

//-----------------------------------------------------------------------
//                           T S t r i n g
//-----------------------------------------------------------------------
EXPORT_OOLUA_FUNCTIONS_1_CONST(TString, size)
EXPORT_OOLUA_FUNCTIONS_NON_CONST(TString,
    make_lower
    )

//-----------------------------------------------------------------------
//                       T A p p l i c a t i o n
//-----------------------------------------------------------------------
EXPORT_OOLUA_FUNCTIONS_0_CONST(TApplication)
    
EXPORT_OOLUA_FUNCTIONS_NON_CONST(TApplication, 
    stopRunning,
    logMessage,
    acceptEvent,
    setWindowCaption
    )

int OOLUA::Proxy_class<class Tubras::TApplication>::acceptEvent(lua_State* L)
{
    int result=-1;

    int top=lua_gettop(L);

    if((lua_type(L, top) == LUA_TFUNCTION) && 
       (lua_type(L, top-1) == LUA_TSTRING))
    {
        void* ref = (void *)luaL_ref(L, LUA_REGISTRYINDEX);

        top=lua_gettop(L);
        const char* name = lua_tostring(L, -1);
        lua_pop(L, 1);

        result = Tubras::getApplication()->acceptEventToScript(name, ref);

    }

    lua_pushnumber(L, result);
    return 1; // number of values we're returning
}

int OOLUA::Proxy_class<class Tubras::TApplication>::logMessage(lua_State* l)
{
    stringc msg="(LUA) ";
    int n = lua_gettop(l);  // number of arguments 
    int i;
    lua_getglobal(l, "tostring");
    for (i=1; i<=n; i++) {
        const char *s;
        lua_pushvalue(l, -1);  // function to be called 
        lua_pushvalue(l, i);   // value to print 
        lua_call(l, 1, 1);
        s = lua_tostring(l, -1);  // get result 
        if (s == NULL)
            return luaL_error(l, LUA_QL("tostring") " must return a string to "
            LUA_QL("logMessage"));
        if (i>1) 
            msg += "\t";
        msg += s;
        lua_pop(l, 1);  // pop result 
    }
    Tubras::getApplication()->logMessage(LOG_INFO, msg.c_str());
    return 0;
}

//-----------------------------------------------------------------------
//                             T E v e n t
//-----------------------------------------------------------------------
EXPORT_OOLUA_FUNCTIONS_0_CONST(TEvent)
EXPORT_OOLUA_FUNCTIONS_NON_CONST(TEvent,
    getID
    )
