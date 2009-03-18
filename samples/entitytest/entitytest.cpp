//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "entitytest.h"

typedef rect<f32> rectf;
typedef rect<s32> rectd;

#define DEVICE_BPP          24

#define ID_DBGCONSOLE       101
#define ID_ALPHA            102
#define ID_MAGNITUDE        103


//-----------------------------------------------------------------------------
//                        S c r i p t E r r o r H a n d l e r  
//-----------------------------------------------------------------------------
class ScriptErrorHandler : public TSLErrorHandler
{
public:
    int handleError(irr::core::stringc fileName, int line, int code, irr::core::stringc errMessage)
    {
        printf("TSL Error (%d), line: %d, message: %s\n",code, line, errMessage.c_str());
        return 0;
    }
};

//-----------------------------------------------------------------------------
//                                q u i t
//-----------------------------------------------------------------------------
int TEntityTest::quit(const TEvent* event)
{
    TApplication::stopRunning();
    return 1;
}

//-----------------------------------------------------------------------------
//                           _ c r e a t e S c e n e
//-----------------------------------------------------------------------------
void TEntityTest::_createScene()
{
    TProperties props;

    TEntity* entity = createEntity("testEntity");
    props["name"] = "viewBehavior";
    entity->addBehavior("view", props); 

    entity = createEntity("meshEntity");
    props.clear();
    props["name"] = "testMesh";
    props["mesh"] = "mdl/cube.irrmesh";
    props["position"] = &TVector3(0.f,2.f,-50.f);
    IBehavior& behavior = *(entity->addBehavior("staticmesh", props));

    props.clear();
    props["velocity"] = 90.0;
    props["node"] = behavior["node"].asPointer();;
    props["axis"] = &TVector3::UNIT_Y;
    entity->addBehavior("rotation", props);    
}

//-----------------------------------------------------------------------------
//                              i n i t i a l i z e
//-----------------------------------------------------------------------------
int TEntityTest::initialize()
{
    if(TApplication::initialize())
        return 1;

    acceptEvent("quit",EVENT_DELEGATE(TEntityTest::quit));  

    m_tsl = new TSL();
    Tubras::TString sname = this->getConfig()->getString("options.loadscript");
    ScriptErrorHandler ehandler;

    if(m_tsl->loadScript(sname, false, false, &ehandler) != E_OK)
    {
        printf("Error loading script.\n");
        return 1;
    }

    _createScene();

    delete m_tsl;

    return 0;
}

//-----------------------------------------------------------------------------
//                                 m a i n
//-----------------------------------------------------------------------------
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:console /ENTRY:mainCRTStartup")
#endif

int main(int argc, const char* argv[])
{
    //m_breakOnAlloc(144047);
    TEntityTest app;

    app.setArgs(argc,argv);

    if(!app.initialize())
        app.run();

    return 0;
}
