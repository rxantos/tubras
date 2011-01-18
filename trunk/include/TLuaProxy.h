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
//    indices: (absolute (+), relative (-))
//             c (3, -1) (3rd parm) -1 always refers to the top of the stack
//             b (2, -2) (2nd parm)
//             a (1, -3) (1st parm)
//
//      if "x" is a proxy class method "class:x(a, b, c)", then:
//             lua_gettop() -> 4 (parameters on the stack)
//             c (4, -1) (4th parm) -1 always refers to the top of the stack
//             b (3, -2) (3rd parm)
//             a (2, -3) (2nd parm)
//             T (1, -4) (1st parm) - Lua proxy table/metaclass (self)
//-----------------------------------------------------------------------------
#ifndef _TLUAPROXY_H_
#define _TLUAPROXY_H_

namespace Tubras
{
    void _dumpStack(lua_State* L);
    void _dumpTable(lua_State* L);
    int _registerProxyClasses(lua_State*);
    enum LPMathOp {oAdd, oSub, oMul, oDiv, oNeg};
    enum LPCompareOp {oEQ, oLT, oLE};

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

        //-------------------------------------------------------------------
        //                   p r o x y T o S t r i n g
        //-------------------------------------------------------------------
        static int proxyToString(lua_State* L);

        //-------------------------------------------------------------------
        //                      p r o x y M a t h
        //-------------------------------------------------------------------
        static int proxyMath(lua_State* L, LPMathOp op);

        //-------------------------------------------------------------------
        //                       p r o x y A d d
        //-------------------------------------------------------------------
        static int proxyAdd(lua_State* L) { return proxyMath(L, oAdd); }

        //-------------------------------------------------------------------
        //                       p r o x y S u b
        //-------------------------------------------------------------------
        static int proxySub(lua_State* L) { return proxyMath(L, oSub); }

        //-------------------------------------------------------------------
        //                       p r o x y M u l
        //-------------------------------------------------------------------
        static int proxyMul(lua_State* L) { return proxyMath(L, oMul); }

        //-------------------------------------------------------------------
        //                       p r o x y D i v
        //-------------------------------------------------------------------
        static int proxyDiv(lua_State* L) { return proxyMath(L, oDiv); }

        //-------------------------------------------------------------------
        //                       p r o x y N e g
        //-------------------------------------------------------------------
        static int proxyNeg(lua_State* L) { return proxyMath(L, oNeg); }

        //-------------------------------------------------------------------
        //                      p r o x y C o m p a r e
        //-------------------------------------------------------------------
        static int proxyCompare(lua_State* L, LPCompareOp op);

        //-------------------------------------------------------------------
        //                         p r o x y E Q
        //-------------------------------------------------------------------
        static int proxyEQ(lua_State* L) { return proxyCompare(L, oEQ); }

        //-------------------------------------------------------------------
        //                         p r o x y L T
        //-------------------------------------------------------------------
        static int proxyLT(lua_State* L) { return proxyCompare(L, oLT); }

        //-------------------------------------------------------------------
        //                         p r o x y L T
        //-------------------------------------------------------------------
        static int proxyLE(lua_State* L) { return proxyCompare(L, oLE); }
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
    template<class T> class LProxyBase : public IReferenceCounted
    {
    public:
        T*          m_ptr;
        bool        m_canGC;
    public:
        LProxyBase() : m_ptr(0), m_canGC(true) {}
        ~LProxyBase()
        {
            if(m_ptr && m_canGC)
                delete m_ptr;
            m_ptr = 0;
        }

        void setGC(bool value) {m_canGC = value;}

        virtual int getProperty(lua_State* L, const char* propName)
        {
            return 0;
        }

        virtual int setProperty(lua_State* L, const char* propName, const TValue* propValue)
        {
            return 0;
        }

        // metamethod default behaviors
        virtual int __tostring(lua_State* L)
        {
            char result[64];            
            snprintf(result, sizeof(result)-1, "%s: 0x%p", className, this);
            lua_pushstring(L, result);
            return 1;
        }

        virtual int __math(lua_State* L, const TValue* ovalue, LProxyBase<T>* other, LPMathOp op)
        {
            return 0;
        }

        virtual int __compare(lua_State* L, LProxyBase<T>* other, LPCompareOp op)
        {
            bool result=false;
            if((op == oEQ) && (this == other))
                result = true;
            lua_pushboolean(L, result);
            return 1;
        }

        static const char className[];
    };

    // helper functions
    template <typename T> inline void push_to_lua(lua_State* L, T* obj)
    {
        TLuaProxyBase<T>::inject(L, obj);
    }
}
#endif
