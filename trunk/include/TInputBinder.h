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
#ifndef _TINPUTBINDER_H_
#define _TINPUTBINDER_H_

namespace Tubras
{
    typedef std::map<string,TSEvent >  TBindingMap;

    /**
    TInputBinder Class.
    @remarks
    Binds simple input to logic commands.
    */
    class TInputBinder : public Tubras::TSingleton<Tubras::TInputBinder>, public TObject
    {
        TBindingMap         m_commands;
    public:
        TInputBinder();
        virtual ~TInputBinder();
        static TInputBinder& getSingleton(void);
        static TInputBinder* getSingletonPtr(void);
        int initialize();

        TParamType getParamType(string parm);
        TSEvent parseCommand(string keyEvent, string command);

        void processKey(string key);

    };
}

#endif