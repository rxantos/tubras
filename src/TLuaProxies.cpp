#include "tubras.h"

namespace Tubras
{
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
    //                       T L u a P r o x y B a s e
    //-----------------------------------------------------------------------
    // based on "luna" (http://nornagon.net/luna.h)
    #define TLuaProxy_register(L, klass) (TLuaProxy<klass>::Register((L)))
    #define TLuaProxy_registermetatable(L, klass) (TLuaProxy<klass>::RegisterMetatable((L)))
    #define TLuaProxy_inject(L, klass, t) (TLuaProxy<klass>::inject((L), (t)))

    template<class T> class TLuaProxyBase {
    public:
        static void Register(lua_State *L)
        {
            RegisterMetatable(L);
        }

        // register the metatable without registering the class constructor
        static void RegisterMetatable(lua_State *L) {
            luaL_newmetatable(L, T::className); // create a metatable in the registry
            lua_pushstring(L, "__gc");
            lua_pushcfunction(L, &TLuaProxy<T>::gc_obj);
            lua_settable(L, -3); // metatable["__gc"] = TLuaProxy<T>::gc_obj
            lua_pop(L, 1);
        }

        static int inject(lua_State *L, T* obj) {
            lua_newtable(L); // create a new table for the class object ('self')

            lua_pushnumber(L, 0);

            T** a = static_cast<T**>(lua_newuserdata(L, sizeof(T*))); // store a ptr to the ptr
            *a = obj; // set the ptr to the ptr to point to the ptr... >.>
            luaL_newmetatable(L, T::className); // get (or create) the unique metatable
            lua_setmetatable(L, -2); // self.metatable = uniqe_metatable

            lua_settable(L, -3); // self[0] = obj;

            for (int i = 0; T::Register[i].name; i++) { // register the functions
                lua_pushstring(L, T::Register[i].name);
                lua_pushnumber(L, i); // let the thunk know which method we mean
                lua_pushcclosure(L, &TLuaProxy<T>::thunk, 1);
                lua_settable(L, -3); // self["function"] = thunk("function")
            }
            return 1;
        }

        static int thunk(lua_State *L) {
            // redirect method call to the proxy class member
            int i = (int)lua_tonumber(L, lua_upvalueindex(1)); // which function?
            lua_pushnumber(L, 0);
            lua_gettable(L, 1); // get the class table (i.e, self)

            T** obj = static_cast<T**>(luaL_checkudata(L, -1, T::className));
            lua_remove(L, -1); // remove the userdata from the stack

            return ((*obj)->*(T::Register[i].mfunc))(L); // execute the thunk
        }

        static int gc_obj(lua_State *L) {
            // clean up
            //printf("GC called: %s\n", T::className);
            T** obj = static_cast<T**>(luaL_checkudata(L, -1, T::className));
            delete (*obj);
            return 0;
        }

        struct RegType {
            const char *name;
            int(T::*mfunc)(lua_State*);
        };

    };

    //-----------------------------------------------------------------------
    //                          T L u a P r o x y
    //-----------------------------------------------------------------------
    template<class T> class TLuaProxy : public TLuaProxyBase<T> {
    public:
        static void Register(lua_State *L) {
            lua_pushcfunction(L, &TLuaProxy<T>::constructor);
            lua_setglobal(L, T::className); // T() in lua will make a new instance.
            RegisterMetatable(L);
        }

        static int constructor(lua_State *L) {
            return inject(L, new T(L));
        }

    };

    //-----------------------------------------------------------------------
    //                       L A p p l i c a t i o n
    //-----------------------------------------------------------------------
    class LApplication {
    private:
        TApplication*   m_application;
    public:

        LApplication()
        {
            m_application = getApplication();
        }

        int logMessage(lua_State *L) 
        {
            TString msg="(LUA) ";
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
            m_application->logMessage(LOG_INFO, msg.c_str());
            return 0;
        }

        static const char className[];
        static const TLuaProxyBase<LApplication>::RegType Register[];
    };
    const char LApplication::className[] = "TApplication";
    const TLuaProxyBase<LApplication>::RegType LApplication::Register[] = {
        { "logMessage", &LApplication::logMessage },
        { 0 }
    };

    //-----------------------------------------------------------------------
    //                          L V e c t o r 3
    //-----------------------------------------------------------------------
    class LVector3 {
    private:
        TVector3*       m_target;
    public: 
        LVector3(lua_State* L)
        {
            m_target = new TVector3();
        }

        int normalize(lua_State* L)
        {
            int top = lua_gettop(L);
            _dumpStack(L);

            m_target->normalize();

            return 0;
        }

        int __index(lua_State* L)
        {
            _dumpStack(L);

            return 0;
        }

        static const char className[];
        static const TLuaProxy<LVector3>::RegType Register[];
    };
    const char LVector3::className[] = "TVector3";
    const TLuaProxy<LVector3>::RegType LVector3::Register[] = {
        { "normalize", &LVector3::normalize },
        { "__index", &LVector3::__index }, 
        { 0 }
    };

    //-----------------------------------------------------------------------
    //                _ r e g i s t e r P r o x y C l a s s e s         
    //-----------------------------------------------------------------------
    int _registerProxyClasses(lua_State* L)
    {
        int n = lua_gettop(L);  /* number of arguments */

        TLuaProxyBase<LApplication>::Register(L);
        LApplication* app = new LApplication();
        TLuaProxyBase<LApplication>::inject(L, app);
        n  = lua_gettop(L);
        lua_setglobal(L, "TubrasApp");
        n  = lua_gettop(L);

        TLuaProxy<LVector3>::Register(L);
        n  = lua_gettop(L);

        return 0;
    }
}
