//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------

#ifndef _TSCRIPT_H_
#define _TSCRIPT_H_

struct lua_State;

namespace Tubras
{
    enum SReturnType {stInt, stFloat, stDouble, stString, stStringW, stObject};
    class SReturnValue : public IReferenceCounted
    {
        int         iValue;
        float       fValue;
        double      dValue;
        stringc     sValue;
        stringw     swValue;
        long        lValue;
        void*       oValue;
    public:
        SReturnType type;
        int getInt() {return iValue;}
        float getFloat() {return fValue;}
        double getDouble() {return dValue;}
        stringc getString() {return sValue;}
        stringw getStringW() {return swValue;}
        long getLong() {return lValue;}
        void* getObject() {return oValue;}
    };

    typedef TMap< TString, void *> MAP_SCRIPTFUNCS;
    typedef void*           TModule;

    typedef MAP_SCRIPTFUNCS::Iterator MAP_SCRIPTFUNCS_ITR;

    class TScript : public IReferenceCounted
    {
        friend class TScriptManager;
    private:
        TScriptManager*     m_manager;
        stringc             m_modPath;
        stringc             m_modName;
        stringc             m_modFile;
        lua_State*          m_lua;
        void*			    m_module;
        void*			    m_application;
        MAP_SCRIPTFUNCS	    m_functions;

    protected:
        void printLUAErr();
        int checkError();
        void* classToScriptObject(void *klass, TString type);
        int	unRef(void *pobj);
        void* getFunction(void*pObj, TString funcname);
        TScript(TScriptManager* manager, lua_State* lua);
        virtual ~TScript();
        void logMessage(TString msg) {}

        int getReturnInt();

    public:
        int initialize(const stringc modPath, const stringc modName);
        SReturnValue* callFunction(const stringc function,const char *fmt, ...);

        TModule getModule() {return m_module;}
        stringc getModuleName() {return m_modName;}
    };

    int testFunc(int v);
}


#endif
