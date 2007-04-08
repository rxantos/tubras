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
#include "tascript.h"
#include "scriptstring.h"
#include "globals.h"

namespace Tubras
{
    static TAScript*    theScript=0;
    //-----------------------------------------------------------------------
    //                      m e s s a g e C a l l b a c k
    //-----------------------------------------------------------------------
    void messageCallback(const asSMessageInfo *msg, void *param)
    {
        const char *type = "ERR ";
        if( msg->type == asMSGTYPE_WARNING ) 
            type = "WARN";
        else if( msg->type == asMSGTYPE_INFORMATION ) 
            type = "INFO";

        printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
    }

    //-----------------------------------------------------------------------
    //                             T A S c r i p t
    //-----------------------------------------------------------------------
    TAScript::TAScript(TString modName, TString modPath) : TScript(modName,modPath) 
    {      
        m_engine = 0;
        m_ctx = 0;
        theScript = this;

        // Create the script engine
        m_engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
        if( m_engine == 0 )
        {
            cout << "Failed to create script engine." << endl;
            return;
        }

        // The script compiler will write any compiler messages to the callback.
        m_engine->SetMessageCallback(asFUNCTION(messageCallback), 0, asCALL_CDECL);

        // Create a context that will execute the script.
        m_ctx = m_engine->CreateContext();
        if( m_ctx == 0 ) 
        {
            cout << "Failed to create the context." << endl;
            return;
        }

    }

    //-----------------------------------------------------------------------
    //                           ~ T A S c r i p t
    //-----------------------------------------------------------------------
    TAScript::~TAScript()
    {
        if(m_ctx)
            m_ctx->Release();

        if(m_engine)
            m_engine->Release();

        theScript = 0;
    }

    //-----------------------------------------------------------------------
    //                      c o n f i g u r e E n g i n e
    //-----------------------------------------------------------------------
    void TAScript::configureEngine()
    {
        int r;
        const char* options;

        options = asGetLibraryOptions();
        if( !strstr(options, "AS_MAX_PORTABILITY") )
        {
            // Register the functions that the scripts will be allowed to use.
            // Note how the return code is validated with an assert(). This helps
            // us discover where a problem occurs, and doesn't pollute the code
            // with a lot of if's. If an error occurs in release mode it will
            // be caught when a script is being built, so it is not necessary
            // to do the verification here as well.
            r = m_engine->RegisterGlobalFunction("void print(string &in)", asFUNCTION(printString), asCALL_CDECL); assert( r >= 0 );
        }
        else
        {
            // Notice how the registration is almost identical to the above. 
            r = m_engine->RegisterGlobalFunction("void print(string &in)", asFUNCTION(printString_Generic), asCALL_GENERIC); assert( r >= 0 );
        }


        // It is possible to register the functions, properties, and types in 
        // configuration groups as well. When compiling the scripts it then
        // be defined which configuration groups should be available for that
        // script. If necessary a configuration group can also be removed from
        // the engine, so that the engine configuration could be changed 
        // without having to recompile all the scripts.
    }

    //-----------------------------------------------------------------------
    //                        l o a d S c r i p t
    //-----------------------------------------------------------------------
    TString TAScript::loadScript(TString filename)
    {
        // We will load the script from a file on the disk.
        FILE *f = fopen(filename.c_str(), "rb");
        if( f == 0 )
        {
            cout << "Failed to open the script file" << filename << endl;
            return "";
        }

        // Determine the size of the file	
        fseek(f, 0, SEEK_END);
        size_t len = ftell(f);
        fseek(f, 0, SEEK_SET);

        // On Win32 it is possible to do the following instead
        // int len = _filelength(_fileno(f));

        // Read the entire file
        TString script;
        script.resize(len);
        size_t c =	fread(&script[0], len, 1, f);
        fclose(f);

        if( c == 0 ) 
        {
            cout << "Failed to load script file." << endl;
            return "";
        }

        return script;
    }

    //-----------------------------------------------------------------------
    //                        l o a d B y t e C o d e
    //-----------------------------------------------------------------------
    int TAScript::loadByteCode(TString filename)
    {
        TBytecodeStream tbs(filename.c_str(),"rb");
        return tbs.load(m_engine,m_modName.c_str());

    }

    //-----------------------------------------------------------------------
    //                       c o m p i l e S c r i p t
    //-----------------------------------------------------------------------
    int  TAScript::compileScript()
    {
        int rc = 0;

        TString modPath = m_modPath;
        TString asName,asbName,osSpecific;
        TFile   asFile,asbFile;

        //
        // look for a byte code file (.asb).  if it exists compare timestamps.
        // if source is newer, recompile.  otherwise stream in the byte code file
        // and skip compiling.
        //
        if(modPath.length())
        {
            char c = modPath[modPath.length()-1];
            if(c != '/')
                modPath += "/";
        }

        asName = modPath + m_modName + ".as";
        asFile.set_fullpath(asName);

        asbName = modPath + m_modName + ".asb";
        asbFile.set_fullpath(asbName);
        if(asbFile.exists())
        {
            if(asbFile.compare_timestamps(asFile) >= 0)
            {
                
                osSpecific = asbFile.to_os_specific();
                return loadByteCode(osSpecific);
            }
        }

        osSpecific = asFile.to_os_specific();

        TString script = loadScript(osSpecific);

        if(!script.length())
        {
            cout << "script file is empty" << endl;
            return -1;
        }

        int r = m_engine->AddScriptSection(m_modName.c_str(),m_modName.c_str(), script.c_str(), 
            script.length(), 0, false);

        if( r < 0 ) 
        {
            cout << "AddScriptSection() failed" << endl;
            return -1;
        }

        r = m_engine->Build(m_modName.c_str());
        if( r < 0 )
        {
            cout << "Build() failed" << endl;
            return -1;
        }

        //
        // save the compiled bytecode
        //
        asbFile.unlink();
        osSpecific = asbFile.to_os_specific();
        TBytecodeStream tbs(osSpecific.c_str(),"wb");
        tbs.save(m_engine,m_modName.c_str());

        return rc;
    }

    //-----------------------------------------------------------------------
    //                          l o a d M o d u l e
    //-----------------------------------------------------------------------
    int TAScript::loadModule()
    {
        // Configure the script engine with all the functions, 
        // and variables that the script should be able to use.
        configureEngine();

        // Compile the script code
        int r = compileScript();
        if( r < 0 )
        {
            return -1;
        }

        return 0;
    }

    int TAScript::callFunction(TString function, char *fmt, ...)
    {
        int funcId,r;

        if(!(funcId = m_funcs[function]))
        {
            funcId = m_engine->GetFunctionIDByDecl(m_modName.c_str(), function.c_str());
            if(funcId >= 0)
                m_funcs[function] = ++funcId;
            else return -1;
        }
        --funcId;

        // Prepare the script context with the function we wish to execute. Prepare()
        // must be called on the context before each new script function that will be
        // executed. Note, that if you intend to execute the same function several 
        // times, it might be a good idea to store the function id returned by 
        // GetFunctionIDByDecl(), so that this relatively slow call can be skipped.
        r = m_ctx->Prepare(funcId);
        if( r < 0 ) 
        {
            cout << "Failed to prepare the context." << endl;
            return -1;
        }

        r = m_ctx->Execute();
        return r;
    }

    //-----------------------------------------------------------------------
    //                          i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TAScript::initialize(int argc,char** argv)
    {
        int r;

        r = callFunction("string initialize()","");

        if( r != asEXECUTION_FINISHED )
        {
            // The execution didn't finish as we had planned. Determine why.
            if( r == asEXECUTION_ABORTED )
                cout << "The script was aborted before it could finish. Probably it timed out." << endl;
            else if( r == asEXECUTION_EXCEPTION )
            {
                cout << "The script ended with an exception." << endl;

                // Write some information about the script exception
                int funcID = m_ctx->GetExceptionFunction();
                cout << "func: " << m_engine->GetFunctionDeclaration(funcID) << endl;
                cout << "modl: " << m_engine->GetFunctionModule(funcID) << endl;
                cout << "sect: " << m_engine->GetFunctionSection(funcID) << endl;
                cout << "line: " << m_ctx->GetExceptionLineNumber() << endl;
                cout << "desc: " << m_ctx->GetExceptionString() << endl;
            }
            else
                cout << "The script ended for some unforeseen reason (" << r << ")." << endl;
        }
        else
        {
            // Retrieve the return value from the context
            asCScriptString* returnValue = (asCScriptString *)m_ctx->GetReturnObject();
            returnValue->AddRef();
            cout << "The script function returned: " << returnValue->buffer << endl;
            returnValue->Release();
        }


        return 0;
    }

    //-----------------------------------------------------------------------
    //                               r u n
    //-----------------------------------------------------------------------
    int TAScript::run()
    {
        return 0;
    }

}