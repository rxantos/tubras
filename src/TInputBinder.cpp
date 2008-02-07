//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"


namespace Tubras
{

    //-----------------------------------------------------------------------
    //                        T I n p u t B i n d e r
    //-----------------------------------------------------------------------
    TInputBinder::TInputBinder() : TObject()
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
    //                   g e t S i n g l e t o n P t r
    //-----------------------------------------------------------------------
    template<> TInputBinder* TSingleton<TInputBinder>::ms_Singleton = 0;

    TInputBinder* TInputBinder::getSingletonPtr(void)
    {
        return ms_Singleton;
    }

    //-----------------------------------------------------------------------
    //                       g e t S i n g l e t o n
    //-----------------------------------------------------------------------
    TInputBinder& TInputBinder::getSingleton(void)
    {
        assert( ms_Singleton );  return ( *ms_Singleton );
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

        TObject::initialize();

        TXMLConfig* cf;

        cf = getApplication()->getConfig();

        try
        {
            IAttributes* attr = cf->getSection("keybindings");
            if(!attr)
                return 0;

            for(u32 i=0;i<attr->getAttributeCount();i++)
            {
                TString key,command;
                key = attr->getAttributeName(i);
                command = attr->getAttributeAsString(key.c_str());
                m_commands[key] = parseCommand(key,command);
            }
        }
        catch(...)
        {
        }
        return 0;
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
            queueEvent(node->getValue());
        }
    }
}

