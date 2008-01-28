//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to 
// deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
// sell copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------
#include "iwalktest.h"

//-----------------------------------------------------------------------
//                           T W a l k t e s t
//-----------------------------------------------------------------------
TWalktest::TWalktest(int argc,char **argv) : TApplication(argc,argv,"sandbox")
{
}

//-----------------------------------------------------------------------
//                          ~ T W a l k t e s t
//-----------------------------------------------------------------------
TWalktest::~TWalktest()
{
    m_dumpMemoryReport();
}

//-----------------------------------------------------------------------
//                        t o g g l e H e l p
//-----------------------------------------------------------------------
int TWalktest::toggleHelp(const TEvent* event)
{
    toggleHelpOverlay();
    return 1;
}

//-----------------------------------------------------------------------
//                        t o g g l e D e b u g
//-----------------------------------------------------------------------
int TWalktest::toggleDebug(const TEvent* event)
{
    toggleDebugOverlay();
    return 1;
}

//-----------------------------------------------------------------------
//                         c y c l e D e b u g
//-----------------------------------------------------------------------
int TWalktest::cycleDebug(const TEvent* event)
{
    cycleDebugData();
    return 1;
}

//-----------------------------------------------------------------------
//                 t o g g l e P h y s i c s D e b u g
//-----------------------------------------------------------------------
int TWalktest::togglePhysicsDebug(const TEvent* event)
{
    TApplication::togglePhysicsDebug();
    return 1;
}

//-----------------------------------------------------------------------
//                      c a p t u r e S c r e e n
//-----------------------------------------------------------------------
int TWalktest::captureScreen(const TEvent* event)
{
    getRenderer()->captureScreen();
    return 1;
}

//-----------------------------------------------------------------------
//                        t o g g l e W i r e
//-----------------------------------------------------------------------
int TWalktest::toggleWire(const TEvent* event)
{
    TRenderMode mode = getRenderMode();

    if(mode == rmNormal)
        setRenderMode(rmWire);
    else if(mode == rmWire)
        setRenderMode(rmPointCloud);
    else if(mode == rmPointCloud)
        setRenderMode(rmNormal);

    return 1;
}

//-----------------------------------------------------------------------
//                             q u i t
//-----------------------------------------------------------------------
int TWalktest::quit(const TEvent* event)
{
    TApplication::stopRunning();
    return 1;
}

//-----------------------------------------------------------------------
//                      O n R e a d U s e r D a t a
//-----------------------------------------------------------------------
void TWalktest::OnReadUserData(ISceneNode* forSceneNode, io::IAttributes* userData)
{
    bool value=false;

    if(userData->existsAttribute("collider"))
        value = userData->getAttributeAsBool("collider");

    if(value)
    {
        ESCENE_NODE_TYPE type = forSceneNode->getType();
        if(type == ESNT_MESH)
        {
            IMeshSceneNode* mnode = reinterpret_cast<IMeshSceneNode*>(forSceneNode);
            TColliderMesh* cm = new TColliderMesh(mnode);
            new TDynamicNode("testCollider",forSceneNode,cm);
            //
            // do mnode->remove() later...
            //
            mnode->setVisible(false);                       
        }
    }
}

//-----------------------------------------------------------------------
//                           i n i t i a l i z e
//-----------------------------------------------------------------------
int TWalktest::initialize()
{
    if(TApplication::initialize())
        return 1;

    
    addHelpText("wasd - Camera movement");
    addHelpText("   i - Invert mouse");
    addHelpText(" prt - Screen capture");
    addHelpText("  F1 - Toggle help");
    addHelpText("  F2 - Toggle debug");
    addHelpText("  F3 - Cycle wire/pts");
    addHelpText("  F4 - Toggle Phys dbg");
    addHelpText("  F5 - Cycle dbg data");
    
    acceptEvent("key.down.f1",EVENT_DELEGATE(TWalktest::toggleHelp));
    acceptEvent("key.down.f2",EVENT_DELEGATE(TWalktest::toggleDebug));      
    acceptEvent("key.down.f3",EVENT_DELEGATE(TWalktest::toggleWire));  
    acceptEvent("key.down.f4",EVENT_DELEGATE(TWalktest::togglePhysicsDebug));      
    acceptEvent("key.down.f5",EVENT_DELEGATE(TWalktest::cycleDebug));
    acceptEvent("key.down.prtscr",EVENT_DELEGATE(TWalktest::captureScreen));
    acceptEvent("key.down.esc",EVENT_DELEGATE(TWalktest::quit));    
        
    TString scene = m_config->getString("initialscene","options");

    if(!scene.equals_ignore_case(""))
        getSceneManager()->loadScene(scene.c_str(), this);
    

    TCameraNode* cam = getCurrentCamera();

    cam->setPosition(TVector3(0.6f,1.4f,-13.f));

    return 0;
}

//-----------------------------------------------------------------------
//                              m a i n
//-----------------------------------------------------------------------
#ifdef WIN32
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
{
    char    **argv=__argv;
    int     argc=__argc;
#else
extern "C" {
    int main(int argc, char **argv)
    {
#endif
        //m_breakOnAlloc(1538);
        //m_breakOnAlloc(1545);
        TWalktest app(argc,argv);

        if(!app.initialize())
            app.run();

        return 0;
    }