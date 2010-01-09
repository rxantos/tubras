//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "entitytest.h"

typedef rect<f32> rectf;
typedef rect<s32> rectd;

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

    //
    // todo: 
    //      Multiple entities share a single behavior? i.e. multiple mesh
    //      entities reference the same "rotation" behavior.  
    //
    //      Property update notifications?
    //

    TEntity* entity = addEntity("testEntity");
    props["name"] = "viewBehavior";
    entity->addBehavior("view", props); 

    entity = addEntity("meshEntity");
    //
    // this behavior will pick up the target node after the 
    // mesh behavior is added (via an update notification).
    //
    props.clear();
    props["velocity"] = 90.0;
    props["target"] = "testMesh";
    props["axis"] = &TVector3::UNIT_Y;
    props["enabled"] = true;
    entity->addBehavior("rotation", props);    

    props.clear();
    props["name"] = "testMesh";
    props["mesh"] = "mdl/Cube.irrmesh";
    props["position"] = &TVector3(0.f,2.f,-50.f);
    props["visible"] = true;
    entity->addBehavior("staticmesh", props);

}

//-----------------------------------------------------------------------------
//                              i n i t i a l i z e
//-----------------------------------------------------------------------------
int TEntityTest::initialize()
{
    if(TApplication::initialize())
        return 1;

    acceptEvent("quit",EVENT_DELEGATE(TEntityTest::quit));  

    /*
    m_tsl = new TSL();
    Tubras::TString sname = this->getConfig()->getString("options.loadscript");
    ScriptErrorHandler ehandler;

    if(m_tsl->loadScript(sname, false, false, &ehandler) != E_OK)
    {
        printf("Error loading script.\n");
        return 1;
    }
    */

    _createScene();

    // delete m_tsl;

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
