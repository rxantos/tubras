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
    typedef TMap< TString,TScript *> MAP_SCRIPTS;
    typedef MAP_SCRIPTS::Iterator MAP_SCRIPTS_ITR;

    class TScriptManager : public TSingleton<Tubras::TScriptManager>, TObject
    {
    private:
        TString             m_modPath;
        MAP_SCRIPTS         m_scripts;
        TEventDelegate*     m_eventDelegate;
        TIntervalDelegate*  m_funcIntervalDelegate;
        void*               m_funcIntervalArgs;
    protected:
        void setupRedirect();
        int handleEvent(const TEvent* event);
        void functionInterval(double T,void* userData);

    public:
        TScriptManager();
        ~TScriptManager();
        static TScriptManager& getSingleton(void);
        static TScriptManager* getSingletonPtr(void);
        int initialize(TString modPath, TString appEXE,int argc=0,const char **argv=0);
        TString getModPath() {return m_modPath;}
        TScript* loadScript(TString scriptName);
        int unloadScript(TScript* script);
        int unloadScript(TString scriptName);
        TEventDelegate* getEventDelegate() {return m_eventDelegate;}
        TIntervalDelegate* getIntervalDelegate() {return m_funcIntervalDelegate;}
    };
}
#endif
