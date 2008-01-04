//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006-2007 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 59 Temple
// Place - Suite 330, Boston, MA 02111-1307, USA, or go to
// http://www.gnu.org/copyleft/lesser.txt.
//
// You may alternatively use this source under the terms of a specific version of
// the Tubras Unrestricted License provided you have obtained such a license from
// Tubras Software Ltd.
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
    TParamType TInputBinder::getParamType(TString parm)
    {
        TParamType pt=PT_int;

        for(size_t i=0;i<parm.length();i++)
        {
            char c = parm[i];  
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
    TSEvent TInputBinder::parseCommand(TString keyEvent, TString command)
    {
        int sidx,idx;
        TSEvent pevent;
        TString cmd,parm;
        TParamType pt;

        idx = 0;
        while((command[idx] != ' ') && command[idx])
            ++idx;

        cmd = command.substr(0,idx);

        pevent.bind(new TEvent(cmd));

        while(command[idx])
        {
            while((command[idx] == ' ') && command[idx])
                ++idx;

            sidx = idx;
            while((command[idx] != ' ') && command[idx])
                ++idx;

            parm = command.substr(sidx,idx-sidx);
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
        TConfigFile* cf;

        cf = getApplication()->getConfigFile();

        try
        {
            Ogre::ConfigFile::SettingsIterator sit = cf->getSettingsIterator("KeyBindings");

            while (sit.hasMoreElements())
            {
                TString key,command;
                key = sit.peekNextKey();
                command = sit.getNext();

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
    void TInputBinder::processKey(TString key)
    {
        TBindingMap::iterator itr;

        itr = m_commands.find(key);

        if(itr != m_commands.end())
        {
            queueEvent(itr->second);
        }
    }


}