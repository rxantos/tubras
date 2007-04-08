//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006-2007 Tubras Software Ltd
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
#include "angelscript.h"
#include "scriptstring.h"
#include "tappproxy.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                            T A p p P r o x y
    //-----------------------------------------------------------------------
    TAppProxy::TAppProxy(TAScript *script, int argc, char** argv, TString appName) : TApplication(argc,argv,appName)
    {
        m_script = script;
    }

    //-----------------------------------------------------------------------
    //                           ~ T A p p P r o x y
    //-----------------------------------------------------------------------
    TAppProxy::~TAppProxy()
    {
    }

    void TAppProxy::testFunc()
    {
        int i = 0;
        i += 1;
    }

    WModelNode* TAppProxy::loadModel(std::string& name)
    {
        TModelNode* model;
        model = TObject::loadModel(name);
        WModelNode* wmodel = new WModelNode(name);
        wmodel->m_model = model;

        return wmodel;
    }

    int TAppProxy::eventHandler(Tubras::TSEvent event)
    {
        int funcId,r;
        asIScriptContext* ctx=m_script->getContext();

        funcId = (int)event->getUserData();
        asCScriptString* sevent;
        sevent = new asCScriptString(event->getName());

        r = ctx->Prepare(funcId);

        r = ctx->SetArgObject(0,sevent);


        if( r < 0 ) 
        {
            cout << "Failed to prepare the context." << endl;
            return -1;
        }

        r = ctx->Execute();
        

        return 0;
    }

    void TAppProxy::acceptEvent(std::string& ename, std::string& funcname)
    {
        int funcId;
        asIScriptEngine* engine = m_script->getEngine();

        TString pfunc = "int ";
        pfunc += funcname;
        pfunc += "(string)";

        funcId = engine->GetFunctionIDByDecl(m_script->getModName().c_str(), pfunc.c_str());
        if(funcId >= 0)
        {
            TApplication::acceptEvent("key.down.esc",EVENT_DELEGATE(TAppProxy::eventHandler),(void *)funcId);
        }
        else 
        {
        }

    }


    //-----------------------------------------------------------------------
    //                      r e g i s t e r I n t e r f a c e s
    //-----------------------------------------------------------------------
    int TAppProxy::registerInterfaces()
    {
        int r=0;
        asIScriptEngine* engine = m_script->getEngine();

        // Register the script string type
        // Look at the implementation for this function for more information  
        // on how to register a custom string type, and other object types.
        // The implementation is in "/add_on/scriptstring/scriptstring.cpp"
        RegisterScriptString(engine);

        // Register the type
        r = engine->RegisterObjectType("Tubras", 0, asOBJ_CLASS); 
        r = engine->RegisterObjectMethod("Tubras","void testFunc()",asMETHOD(TAppProxy,testFunc),asCALL_THISCALL);

        r = engine->RegisterObjectMethod("Tubras","void setGUICursorVisible(bool)",asMETHOD(TObject,setGUICursorVisible),asCALL_THISCALL);
        r = engine->RegisterObjectMethod("Tubras","void stopRunning()",asMETHOD(TApplication,stopRunning),asCALL_THISCALL);

        WModelNode_Register(engine);

        r = engine->RegisterObjectMethod("Tubras","TModelNode& loadModel(string &in)",asMETHOD(TAppProxy,loadModel),asCALL_THISCALL);
        r = engine->RegisterObjectMethod("Tubras","void acceptEvent(string &in, string& funcname)",asMETHOD(TAppProxy,acceptEvent),asCALL_THISCALL);
        r = engine->RegisterGlobalProperty("Tubras tubras",this);




        return r;
    }

    //-----------------------------------------------------------------------
    //                            i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TAppProxy::initialize()
    {
        int rc=0;

        registerInterfaces();

        rc = m_script->loadModule();
        if(rc)
            return rc;

        rc = TApplication::initialize();
        if(rc)
            return rc;

        m_script->initialize(m_argc,m_argv);
        
        setControllerEnabled("DefaultPlayerController",true);


        return rc;
    }


}