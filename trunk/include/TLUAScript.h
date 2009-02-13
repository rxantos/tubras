//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------

#ifndef _TLUASCRIPT_H_
#define _TLUASCRIPT_H_

struct lua_State;

namespace Tubras
{
    typedef TMap< TString, void *> MAP_SCRIPTFUNCS;
    typedef void*           TModule;

    typedef MAP_SCRIPTFUNCS::Iterator MAP_SCRIPTFUNCS_ITR;

    class TLUAScript : public IScript
    {
        friend class TScriptManager;
    private:
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
        TLUAScript();
        virtual ~TLUAScript();
        void logMessage(TString msg) {}
        void _setPackagePath();
        const char* _getTableFieldString (const char* table, const char *key);
        bool _setTableFieldString (const char* table, const char *key, const char* value);
        void _parseLUAError(stringc& lmsg, stringc& fileName, int& line, stringc& emsg);
        void _dumpStack();

    public:
        int initialize(const stringc modPath, const stringc modName);
        SReturnValue* callFunction(const stringc function,const char *fmt, ...);

        bool inheritedFrom(void* obj, TString cname);
        TModule getModule() {return m_module;}
        stringc getModuleName() {return m_modName;}
        bool inheritsFrom(const stringc className);

    };
}

#endif
