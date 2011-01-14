//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
// Based on "Luna" (http://lua-users.org/wiki/LunaFour)
//
// Stack indices:
//      given: x(a, b, c)
//             lua_gettop() -> 3 (parameters on the stack)
//    indices:    (absolute (+), relative (-))
//              a (1, -3) (1st parm)
//              b (2, -2) (2nd parm)
//              c (3, -1) (3rd parm) -1 always refers to the top of the stack
//
//      if "x" is a proxy class method, then:
//              lua_gettop() -> 4 (parameters on the stack)
//              T (1, -4) (1st parm) - Lua proxy table/metaclass (self)
//              a (2, -3) (2nd parm)
//              b (3, -2) (3rd parm)
//              c (4, -1) (4th parm) -1 always refers to the top of the stack
//-----------------------------------------------------------------------------
#ifndef _TLUAPROXY_H_
#define _TLUAPROXY_H_

namespace Tubras
{
    void _dumpStack(lua_State* L);
    void _dumpTable(lua_State* L);
    int _registerProxyClasses(lua_State*);

    //-----------------------------------------------------------------------
    //                       T L u a P r o x y B a s e
    //-----------------------------------------------------------------------
    template<class T> class TLuaProxyBase {
    public:
        struct RegType 
        {
            const char *name;
            int(T::*mfunc)(lua_State*);
        };

        //-------------------------------------------------------------------
        //                     r e g i s t e r P r o x y
        //-------------------------------------------------------------------
        static void registerProxy(lua_State* L);

        //-------------------------------------------------------------------
        //                  r e g i s t e r M e t a t a b l e
        //-------------------------------------------------------------------
        // register the metatable without registering the class constructor
        static void registerMetatable(lua_State* L);

        //-------------------------------------------------------------------
        //                            i n j e c t
        //-------------------------------------------------------------------
        // Creates a new Lua table for this proxy and injects the registered
        // methods. The generated table is located at the top of the stack.
        static int inject(lua_State* L, T* obj);

        //-------------------------------------------------------------------
        //                            t h u n k
        //-------------------------------------------------------------------
        static int thunk(lua_State* L);

        //-------------------------------------------------------------------
        //                         p r o x y G C
        //-------------------------------------------------------------------
        static int proxyGC(lua_State* L);

        //-------------------------------------------------------------------
        //                  p r o x y G e t P r o p e r t y
        //-------------------------------------------------------------------
        static int proxyGetProperty(lua_State* L);

        //-------------------------------------------------------------------
        //                  p r o x y S e t P r o p e r t y
        //-------------------------------------------------------------------
        static int proxySetProperty(lua_State* L);
    };

    //-----------------------------------------------------------------------
    //                          T L u a P r o x y
    //-----------------------------------------------------------------------
    template<class T> class TLuaProxy : public TLuaProxyBase<T> {
    public:
        static void registerProxy(lua_State *L);
        static int constructor(lua_State *L);
    };

    //-----------------------------------------------------------------------
    //                         L P r o x y B a s e
    //-----------------------------------------------------------------------
    template<class T> class LProxyBase
    {
    protected:
        T*          m_ptr;
    public:
        LProxyBase() : m_ptr(0) {}

        virtual int getProperty(lua_State* L, const char* propName)
        {
            return 0;
        }

        virtual int setProperty(lua_State* L, const char* propName, const TValue* propValue)
        {
            return 0;
        }
    };

    // helper functions
    template <typename T> inline void push_to_lua(lua_State* L, T* obj)
    {
        TLuaProxyBase<T>::inject(L, obj);
    }
}
#endif
