//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "guidemo.h"
#define GID_QUIT 101
#define GID_NEW_WINDOW 102
#define GID_DLG_GRAPHICS 201
#define GID_ABOUT 301

//-----------------------------------------------------------------------
//                           T S a n d b o x
//-----------------------------------------------------------------------
TGUIDemo::TGUIDemo() : TApplication("guidemo"),
m_screen(0)
{
}

//-----------------------------------------------------------------------
//                          ~ T S a n d b o x
//-----------------------------------------------------------------------
TGUIDemo::~TGUIDemo()
{
    if(m_screen)
        m_screen->drop();
#ifdef _DEBUG
    m_dumpMemoryReport();
#endif
}

//-----------------------------------------------------------------------
//                        t o g g l e H e l p
//-----------------------------------------------------------------------
int TGUIDemo::toggleHelp(const TEvent* event)
{
    toggleHelpOverlay();
    return 1;
}

//-----------------------------------------------------------------------
//                        t o g g l e D e b u g
//-----------------------------------------------------------------------
int TGUIDemo::toggleDebug(const TEvent* event)
{
    toggleDebugOverlay();
    return 1;
}

//-----------------------------------------------------------------------
//                        c y c l e D e b u g
//-----------------------------------------------------------------------
int TGUIDemo::cycleDebug(const TEvent* event)
{
    cycleDebugData();
    return 1;
}

//-----------------------------------------------------------------------
//                 t o g g l e P h y s i c s D e b u g
//-----------------------------------------------------------------------
int TGUIDemo::togglePhysicsDebug(const TEvent* event)
{
    TApplication::togglePhysicsDebug();
    return 1;
}

//-----------------------------------------------------------------------
//                      c a p t u r e S c r e e n
//-----------------------------------------------------------------------
int TGUIDemo::captureScreen(const TEvent* event)
{
    getRenderer()->captureScreen();
    return 1;
}

//-----------------------------------------------------------------------
//                        t o g g l e W i r e
//-----------------------------------------------------------------------
int TGUIDemo::toggleWire(const TEvent* event)
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
//                             o n C l i c k
//-----------------------------------------------------------------------
int TGUIDemo::onClick(const TEvent* event)
{
    static int windowNum=1;
    static TRecti winRect(50,50,450,450);
    static position2d<s32> off(25,25);
    int result = 0;

    int id = ((TEvent*)event)->getParameter(0)->getIntValue();

    switch(id)
    {
    case GID_QUIT:
        stopRunning();
        return 1;
    case GID_NEW_WINDOW:
        {
            winRect += off;
            TStrStream title;
            title << "Test Window " << windowNum++;
            stringw wtitle = title.str().c_str();

            getGUIFactory()->addWindow(winRect,false,wtitle.c_str(), m_screen);

        }
        break;
    case GID_DLG_GRAPHICS:
        getGUIFactory()->addGraphicsDlg(m_screen);    
        break;
    }

    return result;
}

//-----------------------------------------------------------------------
//                             q u i t
//-----------------------------------------------------------------------
int TGUIDemo::quit(const TEvent* event)
{
    TApplication::stopRunning();
    return 1;
}

//-----------------------------------------------------------------------
//                       t e s t I n t e r v a l
//-----------------------------------------------------------------------
void TGUIDemo::testInterval(double T, void* userData)
{
    logMessage(LOG_INFO,"testInterval T: %.3f",T);
}

//-----------------------------------------------------------------------
//                          t e s t T a s k
//-----------------------------------------------------------------------
int TGUIDemo::testTask(TTask* task)
{
    return TTask::cont;
}

//-----------------------------------------------------------------------
//                      O n R e a d U s e r D a t a
//-----------------------------------------------------------------------
void TGUIDemo::OnReadUserData(ISceneNode* forSceneNode, io::IAttributes* userData)
{
}

//-----------------------------------------------------------------------
//                           i n i t i a l i z e
//-----------------------------------------------------------------------
int TGUIDemo::initialize()
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

    toggleHelpOverlay();
        
    acceptEvent("input.key.down.f1",EVENT_DELEGATE(TGUIDemo::toggleHelp));
    acceptEvent("input.key.down.f2",EVENT_DELEGATE(TGUIDemo::toggleDebug));      
    acceptEvent("input.key.down.f3",EVENT_DELEGATE(TGUIDemo::toggleWire));  
    acceptEvent("input.key.down.f4",EVENT_DELEGATE(TGUIDemo::togglePhysicsDebug));      
    acceptEvent("input.key.down.f5",EVENT_DELEGATE(TGUIDemo::cycleDebug));
    acceptEvent("input.key.down.prtscr",EVENT_DELEGATE(TGUIDemo::captureScreen));
    acceptEvent("input.key.down.esc",EVENT_DELEGATE(TGUIDemo::quit));  
    acceptEvent("gui.clicked",EVENT_DELEGATE(TGUIDemo::onClick));
    acceptEvent("gui.menu.clicked",EVENT_DELEGATE(TGUIDemo::onClick));
   
    ICameraSceneNode* cam = getActiveCamera();
    cam->setPosition(TVector3(0.6f,1.4f,-13.f));

    s32 w=256,x,y;

    TDimension d = getRenderer()->getVideoDriver()->getScreenSize();
    x = d.Width - w - 3;
    y = 3;

    
    m_screen = new TGUIScreen(5);
    m_screen->setVisible(true);

    
    getGUIManager()->addButton(TRecti(200,200,456,256),m_screen,-1,L"Test Button");
    
    

    getGUIManager()->addButton(TRecti(200,300,294,428),m_screen,-1,L"Test Button 2");
    

    
    getGUIManager()->addButton(TRecti(200,450,328,482),m_screen,-1,L"Test Button 3");
    
	// create menu
    
	gui::IGUIContextMenu* menu = getGUIManager()->addMenu(m_screen);
	menu->addItem(L"File", -1, true, true);
	menu->addItem(L"Dialogs", -1, true, true);
	menu->addItem(L"Help", -1, true, true);

	gui::IGUIContextMenu* submenu;
	submenu = menu->getSubMenu(0);
    submenu->addItem(L"New Window...",GID_NEW_WINDOW);
    submenu->addSeparator();
	submenu->addItem(L"Quit", GID_QUIT);

	submenu = menu->getSubMenu(1);
	submenu->addItem(L"Graphics Dialog", GID_DLG_GRAPHICS);

	submenu = menu->getSubMenu(2);
    submenu->addItem(L"Contents");
    submenu->addItem(L"Web Page");
    submenu->addSeparator();
	submenu->addItem(L"About", GID_ABOUT);
    

    /*
    TGraphicsDlg* gd = getGUIFactory()->addGraphicsDlg(m_screen);    

    IGUIWindow* win = getGUIManager()->addWindow(TRecti(50,50,450,450),false,L"Test Window", m_screen);
    win->getCloseButton()->setVisible(false);

    w = 192;
    getGUIManager()->addButton(TRecti(50,50,50+w/2,50+h/2), win, -1, L"Save");
    */
    


    //getGUIManager()->addCheckBox(false,TRecti(20,40,140,60),getGUIManager()->getRootGUIElement(),-1,L"Test Checkbox");

    
    //
    // interval 0.0-1.0 for a period of 4 seconds, ease in blending.
    //
    //TInterval* interval = new TInterval("testInterval",0.f,1.f,4.0f,INTERVAL_DELEGATE(TGUIDemo::testInterval),0,btEaseIn);

    return 0;
}

//-----------------------------------------------------------------------
//                              m a i n
//-----------------------------------------------------------------------
#ifdef TUBRAS_PLATFORM_WIN32
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
{
    const char  **argv=(const char**)__argv;
    int         argc=__argc;
#else
extern "C" {
    int main(int argc, const char **argv)
    {
#endif
        TGUIDemo app;

        app.setArgs(argc,argv);

        if(!app.initialize())
            app.run();

        return 0;
    }
#ifndef TUBRAS_PLATFORM_WIN32
} // extern "C"
#endif
