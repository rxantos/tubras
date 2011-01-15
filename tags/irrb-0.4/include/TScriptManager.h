//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TSCRIPTMANAGER_H_
#define _TSCRIPTMANAGER_H_

namespace Tubras
{
    typedef TMap< stringc, TScript *> TScriptMap;
    typedef TScriptMap::Iterator TScriptMapItr;

    class TScriptManager : public TDelegate
    {
        friend class TApplication;
    private:
        TString             m_scriptPath;
        TString             m_scriptName;
        TScriptMap          m_scripts;
        TEventDelegate*     m_eventDelegate;
        TIntervalDelegate*  m_funcIntervalDelegate;
        TScript*            m_mainScript;
        void*               m_funcIntervalArgs;
        lua_State*          m_lua;

    protected:
        TScriptManager();
        ~TScriptManager();
        void setupRedirect();
        int handleEvent(const TEvent* event);
        void functionInterval(double T,void* userData);
        void _setPackagePath();
        int getReturnInt();
        int initialize(TString scriptPath, TString scriptName, TString appEXE, int argc=0,const char **argv=0);

    public:
        TString getModPath() {return m_scriptPath;}
        TScript* loadScript(TString scriptName);
        TScript* getMainModule() {return m_mainScript;}
        int unloadScript(TScript* script);
        int unloadScript(TString scriptName);
        TEventDelegate* getEventDelegate() {return m_eventDelegate;}
        TIntervalDelegate* getIntervalDelegate() {return m_funcIntervalDelegate;}

        int createStates();

        const char* getTableFieldString (const char* table, const char *key);
        bool setTableFieldString (const char* table, const char *key, const char* value);
        void parseLUAError(stringc& lmsg, stringc& fileName, int& line, stringc& emsg);
        void dumpStack();
        void dumpTable();

    };
}
#endif