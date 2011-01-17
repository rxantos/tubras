//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                       T L u a P r o x y B a s e
    //-----------------------------------------------------------------------

    //-------------------------------------------------------------------
    //                     r e g i s t e r P r o x y
    //-------------------------------------------------------------------
    template<class T> void TLuaProxyBase<T>::registerProxy(lua_State* L)
    {
        registerMetatable(L);
    }

    //-------------------------------------------------------------------
    //                  r e g i s t e r M e t a t a b l e
    //-------------------------------------------------------------------
    // register the metatable without registering the class constructor
    template<class T> void TLuaProxyBase<T>::registerMetatable(lua_State* L) 
    {
        luaL_newmetatable(L, T::className); // create a metatable in the registry
        int metatable = lua_gettop(L);

        // metatable.__gc = TLuaProxy<T>::proxyGC()
        lua_pushstring(L, "__gc");
        lua_pushcfunction(L, &TLuaProxyBase<T>::proxyGC);
        lua_rawset(L, metatable); 

        // metatable.__index = TLuaProxy<T>::proxyGetProperty()
        lua_pushstring(L, "__index");
        lua_pushcfunction(L, &TLuaProxyBase<T>::proxyGetProperty);
        lua_rawset(L, metatable); 

        // metatable.__setindex = TLuaProxy<T>::proxyGetProperty()
        lua_pushstring(L, "__newindex");
        lua_pushcfunction(L, &TLuaProxyBase<T>::proxySetProperty);
        lua_rawset(L, metatable); 

        // metatable.__tostring = TLuaProxy<T>::proxyToString()
        lua_pushstring(L, "__tostring");
        lua_pushcfunction(L, &TLuaProxyBase<T>::proxyToString);
        lua_rawset(L, metatable); 

        // math metamethods

        // metatable.__add = TLuaProxy<T>::proxyAdd()
        lua_pushstring(L, "__add");
        lua_pushcfunction(L, &TLuaProxyBase<T>::proxyAdd);
        lua_rawset(L, metatable); 

        // metatable.__add = TLuaProxy<T>::proxyAdd()
        lua_pushstring(L, "__sub");
        lua_pushcfunction(L, &TLuaProxyBase<T>::proxySub);
        lua_rawset(L, metatable); 

        // metatable.__add = TLuaProxy<T>::proxyMul()
        lua_pushstring(L, "__mul");
        lua_pushcfunction(L, &TLuaProxyBase<T>::proxyMul);
        lua_rawset(L, metatable); 

        // metatable.__add = TLuaProxy<T>::proxyDiv()
        lua_pushstring(L, "__div");
        lua_pushcfunction(L, &TLuaProxyBase<T>::proxyDiv);
        lua_rawset(L, metatable); 

        // metatable.__unm = TLuaProxy<T>::proxyNeg()
        lua_pushstring(L, "__unm"); // unary minus (negate)
        lua_pushcfunction(L, &TLuaProxyBase<T>::proxyNeg);
        lua_rawset(L, metatable); 

        // comparison metamethods

        // metatable.__eq = TLuaProxy<T>::proxyEQ()
        lua_pushstring(L, "__eq");
        lua_pushcfunction(L, &TLuaProxyBase<T>::proxyEQ);
        lua_rawset(L, metatable); 

        // metatable.__eq = TLuaProxy<T>::proxyLT()
        lua_pushstring(L, "__lt");
        lua_pushcfunction(L, &TLuaProxyBase<T>::proxyLT);
        lua_rawset(L, metatable); 

        // metatable.__eq = TLuaProxy<T>::proxyLT()
        lua_pushstring(L, "__le");
        lua_pushcfunction(L, &TLuaProxyBase<T>::proxyLE);
        lua_rawset(L, metatable); 

        lua_pop(L, 1);
    }

    //-------------------------------------------------------------------
    //                            i n j e c t
    //-------------------------------------------------------------------
    // Creates a new Lua table for this proxy and injects the registered
    // methods. 
    template<class T> int TLuaProxyBase<T>::inject(lua_State* L, T* obj) 
    {
        // create a new table for the class object ('self')
        lua_newtable(L); 
        int newtable = lua_gettop(L);

        lua_pushnumber(L, 0);

        T** a = static_cast<T**>(lua_newuserdata(L, sizeof(T*))); // store a ptr to the ptr
        *a = obj; // set the ptr to the ptr to point to the ptr... >.>
        int userdata = lua_gettop(L);

        luaL_newmetatable(L, T::className); // get (or create) the unique metatable
        lua_setmetatable(L, userdata); // self.metatable = uniqe_metatable
        lua_settable(L, newtable); // self[0] = obj;

        luaL_newmetatable(L, T::className); // get (or create) the unique metatable
        lua_setmetatable(L, newtable); // self.metatable = uniqe_metatable

        for (int i = 0; T::Register[i].name; i++) { // register the functions
            lua_pushstring(L, T::Register[i].name);
            lua_pushnumber(L, i); // let the thunk know which method we mean
            lua_pushcclosure(L, &TLuaProxyBase<T>::thunk, 1);
            lua_settable(L, newtable); // self["function"] = thunk("function")
        }
        return 1;
    }

    //-------------------------------------------------------------------
    //                            t h u n k
    //-------------------------------------------------------------------
    template<class T> int TLuaProxyBase<T>::thunk(lua_State* L) 
    {
        // redirect method call to the proxy class member
        int i = (int)lua_tonumber(L, lua_upvalueindex(1)); // which function?
        lua_pushnumber(L, 0);
        lua_gettable(L, 1); // get the class table (i.e, self)

        T** obj = static_cast<T**>(luaL_checkudata(L, -1, T::className));
        lua_remove(L, -1); // remove the userdata from the stack

        return ((*obj)->*(T::Register[i].mfunc))(L); // execute the thunk
    }

    //-------------------------------------------------------------------
    //                         p r o x y G C
    //-------------------------------------------------------------------
    template<class T> int TLuaProxyBase<T>::proxyGC(lua_State* L) 
    {
        // clean up
        //printf("GC called: %s\n", T::className);
        T** obj = static_cast<T**>(luaL_checkudata(L, -1, T::className));
        delete (*obj);
        return 0;
    }

    //-------------------------------------------------------------------
    //                  p r o x y G e t P r o p e r t y
    //-------------------------------------------------------------------
    template<class T> int TLuaProxyBase<T>::proxyGetProperty(lua_State* L) 
    {
        // get & push userdata on the stack. Table<T>[0] -> userdata.              
        lua_pushnumber(L, 0);
        lua_rawget(L, 1);

        T** obj = static_cast<T**>(luaL_checkudata(L, -1, T::className));
        lua_pop(L, 1); // remove userdata from the stack

        const char* propName = lua_tostring(L, -1);
        int result = (*obj)->getProperty(L, propName);
        if(!result) 
        {
            lua_pushnil(L);
            result = 1;
        }
        return result;
    }

    //-------------------------------------------------------------------
    //                  p r o x y S e t P r o p e r t y
    //-------------------------------------------------------------------
    template<class T> int TLuaProxyBase<T>::proxySetProperty(lua_State* L) 
    {
        // get & push userdata on the stack. Table<T>[0] -> userdata.  
        lua_pushnumber(L, 0);
        lua_rawget(L, 1);

        T** obj = static_cast<T**>(luaL_checkudata(L, -1, T::className));
        lua_pop(L, 1); // remove userdata from the stack

        const char* propName = lua_tostring(L, -2);

        const TValue* propValue = L->base + 2;

        if(!obj || !(*obj)->setProperty(L, propName, propValue))
        {
            lua_rawset(L, 1);
        }

        return 0;
    }

    //-------------------------------------------------------------------
    //                    p r o x y T o S t r i n g
    //-------------------------------------------------------------------
    template<class T> int TLuaProxyBase<T>::proxyToString(lua_State* L) 
    {
        // get & push userdata on the stack. Table<T>[0] -> userdata.              
        lua_pushnumber(L, 0);
        lua_rawget(L, 1);

        T** obj = static_cast<T**>(luaL_checkudata(L, -1, T::className));
        lua_pop(L, 1); // remove userdata from the stack

        return (*obj)->__tostring(L);
    }

    //-------------------------------------------------------------------
    //                        p r o x y M a t h
    //-------------------------------------------------------------------
    template<class T> int TLuaProxyBase<T>::proxyMath(lua_State* L, LPMathOp op) 
    {
        _dumpTable(L);
        // get & push userdata on the stack. Table<T>[0] -> userdata.  
        lua_pushnumber(L, 0);
        lua_rawget(L, 1);
        T** obj = static_cast<T**>(luaL_checkudata(L, -1, T::className));
        lua_pop(L, 1); // remove userdata from the stack

        const TValue* propValue = L->base + 1;
        T* other=0;

        if(propValue->tt == LUA_TTABLE)
        {
            lua_pushnumber(L, 0);
            lua_rawget(L, 2);
            other = *static_cast<T**>(luaL_checkudata(L, -1, T::className));
            lua_pop(L, 1); // remove userdata from the stack
        }

        if(!obj)
        {
            return 0;
        }

        return (*obj)->__math(L, propValue, other, op);
    }

    //-------------------------------------------------------------------
    //                     p r o x y C o m p a r e 
    //-------------------------------------------------------------------
    template<class T> int TLuaProxyBase<T>::proxyCompare(lua_State* L,
        LPCompareOp op) 
    {
        // get & push userdata on the stack. Table<T>[0] -> userdata.  
        lua_pushnumber(L, 0);
        lua_rawget(L, 1);
        T** obj = static_cast<T**>(luaL_checkudata(L, -1, T::className));
        lua_pop(L, 1); // remove userdata from the stack

        lua_pushnumber(L, 0);
        lua_rawget(L, 2);
        T* other = *static_cast<T**>(luaL_checkudata(L, -1, T::className));
        lua_pop(L, 1); // remove userdata from the stack

        if(!obj)
        {
            lua_pushboolean(L, false);
            return 1;
        }

        return (*obj)->__compare(L, other, op);
    }

    //-----------------------------------------------------------------------
    //                          T L u a P r o x y
    //-----------------------------------------------------------------------
    template<class T> void TLuaProxy<T>::registerProxy(lua_State *L) {
        lua_pushcfunction(L, &TLuaProxy<T>::constructor);
        lua_setglobal(L, T::className); // T() in lua will make a new instance.
        TLuaProxyBase<T>::registerMetatable(L);
    }

    template<class T> int TLuaProxy<T>::constructor(lua_State *L) {
        return inject(L, new T(L));
    }
    //-------------------------------------------------------------------------
    //                         _ d u m p T a b l e
    //-------------------------------------------------------------------------
    void _dumpTable(lua_State* L)
    {

        int top = lua_gettop(L);
        lua_pushnil(L);          
        printf("\n---------------  Table Dump ---------------\n");
        while (lua_next(L, top)) 
        {
            // 'key' (at index -2) and 'value' (at index -1) 
            irr::core::stringc key, value;
            if(lua_type(L, -2) == LUA_TSTRING)
            {
                key = lua_tostring(L, -2);
            }
            else 
            {
                key = lua_typename(L, lua_type(L, -2));
            }

            if(lua_type(L, -1) == LUA_TSTRING)
            {
                value = lua_tostring(L, -1);
            }
            else if(lua_type(L, -1) == LUA_TNUMBER)
            {
                value = "";
                value += lua_tonumber(L, -1);
            }
            else
                value = lua_typename(L, lua_type(L, -1));


            fprintf(stdout, "%s - %s\n", key.c_str(), value.c_str());

            // removes 'value', keeps 'key' for next iteration 
            lua_pop(L, 1);
        }
        printf("----------------  End Dump ----------------\n");
    }

    //---------------------------------------------------------------------------
    //                            _ d u m p S t a c k
    //---------------------------------------------------------------------------
    void _dumpStack(lua_State* L)
    {
        int i;
        int top = lua_gettop(L);
        printf("\n---------------  Stack Dump ---------------\n");
        for (i = 1; i <= top; i++) 
        {  
            int t = lua_type(L, i);
            switch (t) 
            {
            case LUA_TSTRING:  /* strings */
                printf("STRING: '%s'\n", lua_tostring(L, i));
                break;

            case LUA_TBOOLEAN:  /* booleans */
                printf("BOOLEAN: %s\n",lua_toboolean(L, i) ? "true" : "false");
                break;

            case LUA_TNUMBER:  /* numbers */
                printf("NUMBER: %g\n", lua_tonumber(L, i));
                break;

            case LUA_TTABLE:
                printf("%s\n", lua_typename(L, t));
                //printf("TABLE: %x\n", lua_tonumber(L, i));

                break;

            default:  /* other values */
                printf("%s\n", lua_typename(L, t));
                break;
            }
        }
        printf("----------------  End Dump ----------------\n");
    }

    //-----------------------------------------------------------------------
    //                _ r e g i s t e r P r o x y C l a s s e s         
    //-----------------------------------------------------------------------
    int _registerProxyClasses(lua_State* L)
    {
        TLuaProxyBase<LApplication>::registerProxy(L);
        LApplication* app = new LApplication();
        TLuaProxyBase<LApplication>::inject(L, app);
        lua_setglobal(L, "TubrasApp");

        TLuaProxy<LVector3>::registerProxy(L);
        TLuaProxy<LEvent>::registerProxy(L);

        return 0;
    }
}
