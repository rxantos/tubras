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
    int testFunc(int v)
    {
        printf("testFunc: %d\n", v);
        return 2;
    }

    using namespace std;

    //-----------------------------------------------------------------------
    //                             T S c r i p t
    //-----------------------------------------------------------------------
    TScript::TScript(TScriptManager* manager, lua_State* lua) : m_manager(manager),
        m_lua(lua)
    {
    }

    //-----------------------------------------------------------------------
    //                           ~ T S c r i p t
    //-----------------------------------------------------------------------
    TScript::~TScript()
    {
        /*
        for(MAP_SCRIPTFUNCS_ITR it=m_functions.getIterator();!it.atEnd();it++)
        {
            PyObject* obj = it->getValue();
            Py_DECREF(obj);
        }

        if(m_module)
        {
            Py_DECREF(m_module);
            m_module = 0;
        }
        */
    }

    //-------------------------------------------------------------------------
    //                         _ e x t r a c t D i r 
    //-------------------------------------------------------------------------
    stringc _extractDir(stringc filename)
    {
        stringc result="";
        // find last forward or backslash
        s32 lastSlash = filename.findLast('/');
        const s32 lastBackSlash = filename.findLast('\\');
        lastSlash = lastSlash > lastBackSlash ? lastSlash : lastBackSlash;

        if ((u32)lastSlash < filename.size())
            return filename.subString(0, lastSlash+1);
        else
            return ".";
    }

    //-------------------------------------------------------------------
    //                       p r i n t L U A E r r
    //-------------------------------------------------------------------
    void TScript::printLUAErr()
    {
        return;
    }

    //-------------------------------------------------------------------
    //                        c h e c k E r r o r
    //-------------------------------------------------------------------
    int TScript::checkError()
    {
        int result=0;

        return result;
    }

    //-------------------------------------------------------------------
    //                      g e t R e t u r n I n t
    //-------------------------------------------------------------------
    int TScript::getReturnInt()
    {
        int result=0;

        int top = lua_gettop(m_lua);
        if(top >= 1)
        {  
            int t = lua_type(m_lua, top);
            switch (t) 
            {
            case LUA_TSTRING:  /* strings */
                break;

            case LUA_TBOOLEAN:  /* booleans */
                if(lua_toboolean(m_lua,top))
                    result = 1;
                break;

            case LUA_TNUMBER:  /* numbers */
                result = (int)lua_tonumber(m_lua, top);
                break;

            default:  /* other values */
                break;
            }
        }

        // pop the return value
        lua_pop(m_lua,top);

        return result;
    }

    //-------------------------------------------------------------------
    //                            u n R e f
    //-------------------------------------------------------------------
    int	TScript::unRef(void *pobj)
    {

        if(!pobj)
            return 0;

        return 0;
    }

    //-------------------------------------------------------------------
    //                       g e t F u n c t i o n
    //-------------------------------------------------------------------
    void *TScript::getFunction(void *pObj, TString funcname)
    {
        void* pFunc=0;

        return pFunc;
    }

    //-------------------------------------------------------------------
    //                       c a l l F u n c t i o n
    //-------------------------------------------------------------------
    SReturnValue* TScript::callFunction(TString function, const char *fmt, ...)
    {
        SReturnValue* pResult=0;

        return pResult;
    }

    //-------------------------------------------------------------------
    //                        i n i t i a l i z e
    //-------------------------------------------------------------------
    int TScript::initialize(const stringc modPath, const stringc modName)
    {
        stringc ext;
        m_modPath = modPath;
        m_modName = modName;

        getFileNameExtension(ext, m_modName);
        if(!ext.size())
            m_modName += ".lua";

        m_modFile = m_modPath + m_modName;

        // syntax checking
        if(luaL_loadfile(m_lua,m_modFile.c_str()) != 0)
        {
            stringc msg = "LSL Load Error: ";
            stringc lmsg = lua_tostring(m_lua, -1);
            stringc fileName, emsg;
            int line;

            m_manager->parseLUAError(lmsg, fileName, line, emsg);

            /*
            msg += emsg;
            if(errorHandler)
                errorHandler->handleError(fileName, line, E_BAD_SYNTAX, msg);
            */
#ifdef _DEBUG
            m_manager->dumpStack();
#endif
            return 1;
        }

        // no syntax errors so execute - loaded module is a function
        // at the top of the stack.
        m_manager->dumpStack();
        if (lua_pcall(m_lua,0,1,0) != 0)  
        {
            irr::core::stringc msg = "LSL Execution Error: ";
            irr::core::stringc lmsg = lua_tostring(m_lua, -1);
            irr::core::stringc fileName, emsg;
            int line;

            m_manager->parseLUAError(lmsg, fileName, line, emsg);

            /*
            msg += emsg;
            if(errorHandler)
                errorHandler->handleError(fileName, line, E_BAD_INPUT, msg);
            */
#ifdef _DEBUG
            m_manager->dumpStack();
#endif
            return 1;
        }

        return getReturnInt();
    }
}
