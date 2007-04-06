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

#ifndef _TASCRIPT_H_
#define _TASCRIPT_H_
#include "angelscript.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                             T A S c r i p t
    //-----------------------------------------------------------------------
    class TAScript : public TScript
    {
    private:
        asIScriptEngine*        m_engine;
        asIScriptContext*       m_ctx;
    protected:
        void configureEngine();
        int  compileScript();
        TString loadScript(TString filename);
        int loadByteCode(TString filename);

    public:
        TAScript(TString modName, TString modPath);
        virtual ~TAScript();
        int initialize(int argc,char** argv);
        int run();
    };

    //-----------------------------------------------------------------------
    //                      T A B y t e c o d e S t r e a m
    //-----------------------------------------------------------------------
    class TBytecodeStream : public asIBinaryStream
    {
    protected:
        string              m_filename;
        string              m_mode;
        FILE*               file;
    public:
        TBytecodeStream(const char *filename,const char* mode) : asIBinaryStream(),  m_filename(filename), m_mode(mode) {}

        void Write(const void *ptr, asUINT size)
        {
            fwrite(ptr,size,1,file);
        }

        void Read(void *ptr, asUINT size)
        {
            fread(ptr,size,1,file);
        }

        int save(asIScriptEngine* engine, const char* module)
        {
            file = fopen(m_filename.c_str(),m_mode.c_str());

            engine->SaveByteCode(module,this);

            fclose(file);
            return 0;
        }

        int load(asIScriptEngine* engine, const char* module)
        {
            file = fopen(m_filename.c_str(),m_mode.c_str());

            engine->LoadByteCode(module,this);

            fclose(file);
            return 0;
        }

    };

}

#endif