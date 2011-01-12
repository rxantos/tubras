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
#include "tubras.h"

namespace Tubras
{
    void _dumpTable(lua_State* L);
    void _dumpStack(lua_State* L);

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
        static void registerProxy(lua_State* L)
        {
            registerMetatable(L);
        }

        //-------------------------------------------------------------------
        //                  r e g i s t e r M e t a t a b l e
        //-------------------------------------------------------------------
        // register the metatable without registering the class constructor
        static void registerMetatable(lua_State* L) 
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

            lua_pop(L, 1);
        }

        //-------------------------------------------------------------------
        //                            i n j e c t
        //-------------------------------------------------------------------
        // Creates a new Lua table for this proxy and injects the registered
        // methods. 
        static int inject(lua_State* L, T* obj) 
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
        static int thunk(lua_State* L) 
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
        static int proxyGC(lua_State* L) 
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
        static int proxyGetProperty(lua_State* L) 
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
    };

    //-----------------------------------------------------------------------
    //                          T L u a P r o x y
    //-----------------------------------------------------------------------
    template<class T> class TLuaProxy : public TLuaProxyBase<T> {
    public:
        static void registerProxy(lua_State *L) {
            lua_pushcfunction(L, &TLuaProxy<T>::constructor);
            lua_setglobal(L, T::className); // T() in lua will make a new instance.
            TLuaProxyBase<T>::registerMetatable(L);
        }

        static int constructor(lua_State *L) {
            return inject(L, new T(L));
        }
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
    };

    //-----------------------------------------------------------------------
    //                       L A p p l i c a t i o n
    //-----------------------------------------------------------------------
    class LApplication : public LProxyBase<TApplication> {
    public:

        //-------------------------------------------------------------------
        //                       L A p p l i c a t i o n
        //-------------------------------------------------------------------
        LApplication()
        {
            m_ptr = getApplication();
        }

        //-------------------------------------------------------------------
        //                        l o g M e s s a g e
        //-------------------------------------------------------------------
        // logMessage(...)
        // Arguments are converted to strings and concatenated. Note that we
        // start with argument number 2, as argument number 1 for all proxy
        // class methods is the Lua table class itself. 
        int logMessage(lua_State *L) 
        {
            TString msg("");
            int n = lua_gettop(L);  /* number of arguments */
            int i;
            lua_getglobal(L, "tostring");
            for (i=2; i<=n; i++) {
                const char *s;
                lua_pushvalue(L, -1);  /* function to be called */
                lua_pushvalue(L, i);   /* value to print */
                lua_call(L, 1, 1);
                s = lua_tostring(L, -1);  /* get result */
                if (s == NULL)
                    return luaL_error(L, LUA_QL("tostring") " must return a string to "
                    LUA_QL("print"));
                msg += s;
                lua_pop(L, 1);  /* pop result */
            }
            getApplication()->logMessage(LOG_INFO, msg.c_str());
            return 0;
        }

        static const char className[];
        static const TLuaProxyBase<LApplication>::RegType Register[];
    };
    const char LApplication::className[] = "TApplication";
    const TLuaProxyBase<LApplication>::RegType LApplication::Register[] = {
        { "logMessage", &LApplication::logMessage },
        { 0 }};

    //-----------------------------------------------------------------------
    //                          L V e c t o r 3
    //-----------------------------------------------------------------------
    class LVector3 : public LProxyBase<TVector3> {
    public: 
        //-------------------------------------------------------------------
        //                          L V e c t o r 3
        //-------------------------------------------------------------------
        LVector3(lua_State* L)
        {
            f32 x=0.f, y=0.f, z=0.f;
            int top = lua_gettop(L);

            if(top > 0)
                x = (f32)lua_tonumber(L, 1);
            if(top > 1)
                y = (f32)lua_tonumber(L, 2);
            if(top > 2)
                z = (f32)lua_tonumber(L, 3);

            m_ptr = new TVector3(x, y , z);
        }

        //-------------------------------------------------------------------
        //                       g e t P r o p e r t y
        //-------------------------------------------------------------------
        int getProperty(lua_State* L, const char* propName)
        {
            int result = 1;
            if(!strcmp(propName, "x"))
                lua_pushnumber(L, m_ptr->X);
            else if(!strcmp(propName, "y"))
                lua_pushnumber(L, m_ptr->Y);
            else if(!strcmp(propName, "z"))
                lua_pushnumber(L, m_ptr->Z);
            else
                result = 0;
            
            return result;
        }

        //-------------------------------------------------------------------
        //                         n o r m a l i z e
        //-------------------------------------------------------------------
        int normalize(lua_State* L)
        {
            m_ptr->normalize();
            return 0;
        }

        static const char className[];
        static const TLuaProxy<LVector3>::RegType Register[];
    };
    const char LVector3::className[] = "TVector3";
    const TLuaProxy<LVector3>::RegType LVector3::Register[] = {
        { "normalize", &LVector3::normalize },
        { 0 }};

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

        return 0;
    }
}
