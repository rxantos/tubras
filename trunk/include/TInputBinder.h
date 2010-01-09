//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TINPUTBINDER_H_
#define _TINPUTBINDER_H_

namespace Tubras
{
    typedef TMap<TString,TEvent *>  TBindingMap;

    /**
    TInputBinder Class.
    @remarks
    Binds simple input to logic commands.
    */
    class TInputBinder 
    {
        friend class TInputHandler;
    protected:
        TBindingMap         m_commands;
        TApplication*       m_app;
        TInputBinder();
    public:
        virtual ~TInputBinder();
        int initialize();

        TParamType getParamType(const TString& parm);
        TEvent* parseCommand(const TString& keyEvent, const TString& command);

        void processKey(const TString& key);

    };
}

#endif

