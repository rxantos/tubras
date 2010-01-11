//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"


namespace Tubras
{

    //-----------------------------------------------------------------------
    //                        T I n p u t B i n d e r
    //-----------------------------------------------------------------------
    TInputBinder::TInputBinder() : m_app(0)
    {
    }


    //-----------------------------------------------------------------------
    //                       ~ T I n p u t B i n d e r
    //-----------------------------------------------------------------------
    TInputBinder::~TInputBinder()
    {
        TBindingMap::Iterator itr;

        itr = m_commands.getIterator();

        while(!itr.atEnd())
        {
            itr->getValue()->drop();
            itr++;
        }
        m_commands.clear();

    }

    //-----------------------------------------------------------------------
    //                        g e t P a r a m T y p e
    //-----------------------------------------------------------------------
    TParamType TInputBinder::getParamType(const TString& parm)
    {
        TParamType pt=PT_int;

        for(u32 i=0;i<parm.size();i++)
        {
            char c =  parm[i];  
            if(isalpha(c) || (c == '.'))
            {
                if((c == '.') && (pt == PT_int))
                    pt = PT_double;
                else pt = PT_string;
            }
        }
        return pt;
    }

    //-----------------------------------------------------------------------
    //                        p a r s e C o m m a n d
    //-----------------------------------------------------------------------
    TEvent* TInputBinder::parseCommand(const TString& keyEvent, const TString& command)
    {
        int sidx,idx;
        TEvent* pevent;
        TString cmd,parm;
        TParamType pt;

        idx = 0;
        while((command[idx] != ' ') && command[idx])
            ++idx;

        cmd = command.subString(0,idx);

        pevent = new TEvent(cmd);

        while(command[idx])
        {
            while((command[idx] == ' ') && command[idx])
                ++idx;

            sidx = idx;
            while((command[idx] != ' ') && command[idx])
                ++idx;

            parm = command.subString(sidx,idx-sidx);
            pt = getParamType(parm);
            switch(pt)
            {
            case PT_int:
                pevent->addIntParameter(atoi(parm.c_str()));
                break;
            case PT_double:
                pevent->addDoubleParameter(atof(parm.c_str()));
                break;
            default:
                pevent->addStringParameter(parm);
                break;
            };
        }

        return pevent;
    }

    //-----------------------------------------------------------------------
    //                        i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TInputBinder::initialize()
    {


        m_app = getApplication();
        TSL* cf;
        cf = m_app->getConfig();

        try
        {
            STRINGMAP kbm;
            cf->getStringMap("keybindings", kbm);

            for ( STRINGMAPITR itr = kbm.getIterator(); !itr.atEnd(); itr++)
            {
                TString key,command;
                key = itr->getKey();
                command = itr->getValue();
                m_commands[key] = parseCommand(key,command);
            }

        }
        catch(...)
        {
        }
        return 0;
    }

    //-----------------------------------------------------------------------
    //                    g e t I n p u t F o r C o m m a n d
    //-----------------------------------------------------------------------
    core::stringc TInputBinder::getInputForCommand(stringc cmd)
    {
        TBindingMap::Iterator itr;

        itr = m_commands.getIterator();

        while(!itr.atEnd())
        {
            stringc vcmd = itr->getValue()->getName();
            if(vcmd.equals_ignore_case(cmd))
            {
                return itr->getKey();
            }
            itr++;
        }

        return "";
    }

    //-----------------------------------------------------------------------
    //                         p r o c e s s K e y
    //-----------------------------------------------------------------------
    void TInputBinder::processKey(const TString& key)
    {
        TBindingMap::Node* node;

        node = m_commands.find(key);

        if(node)
        {
            m_app->queueEvent(node->getValue());
        }
    }
}

