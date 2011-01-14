//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TSCRIPT_H_
#define _TSCRIPT_H_

namespace Tubras
{
    class TScriptManager;
    enum SReturnType {stNumber, stBool, stString, stStringW, stTableRef};
    class SReturnValue : public IReferenceCounted
    {
    public:
        SReturnType type;
        double      dValue;
        bool        bValue;
        stringc     sValue;
        stringw     swValue;
        int         iTableRef;

        SReturnValue() : IReferenceCounted(), dValue(0.0), bValue(false), sValue(""), swValue(L""), iTableRef(-1) {}
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
        TString             m_initialState;
        int                 m_statesRef;

    protected:
        void printLUAErr();
        int checkError();
        void* classToScriptObject(void *klass, TString type);
        int	unRef(void *pobj);
        TScript(TScriptManager* manager, lua_State* lua);
        virtual ~TScript();
        void logMessage(TString msg) {}

        int createState();
        int initializeStates();
        TString getInitialState() {return m_initialState;}

    public:
        int initialize(const stringc modPath, const stringc modName);
        bool hasFunction(TString functionName);
        SReturnValue* callFunction(const stringc function, int resultCount, 
            const char *fmt=0, ...);

        TModule getModule() {return m_module;}
        stringc getModuleName() {return m_modName;}
        int getStatesRef() {return m_statesRef;}
    };

    int testFunc(int v);
}


#endif
