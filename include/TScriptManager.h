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
    enum ScriptLanguage {slUnknown=0, slLUA};

    typedef TMap< stringc, IScript *> MAP_SCRIPTS;
    typedef MAP_SCRIPTS::Iterator MAP_SCRIPTS_ITR;

    class TScriptManager : public TSingleton<Tubras::TScriptManager>, TObject
    {
    private:
        TString             m_modPath;
        TString             m_mainModName;
        MAP_SCRIPTS         m_scripts;
        TEventDelegate*     m_eventDelegate;
        TIntervalDelegate*  m_funcIntervalDelegate;
        IScript*            m_mainModule;
        ScriptLanguage      m_scriptLang;
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
        int initialize(TString modPath, TString modName, TString appEXE, TString lang, int argc=0,const char **argv=0);
        TString getModPath() {return m_modPath;}
        IScript* loadScript(TString modName);
        int unloadScript(IScript* script);
        int unloadScript(TString scriptName);
        TEventDelegate* getEventDelegate() {return m_eventDelegate;}
        TIntervalDelegate* getIntervalDelegate() {return m_funcIntervalDelegate;}
        int createStates();
    };
}
#endif
