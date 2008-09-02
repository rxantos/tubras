//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "main.h"

#define WINDOW_SIZE_X       800
#define WINDOW_SIZE_Y       600
#define DEVICE_BPP          24

static IrrlichtDevice*      m_device;
static IVideoDriver*        m_videoDriver;
static ISceneManager*       m_sceneManager;
static IFileSystem*         m_fileSystem;
static IEventReceiver*      m_eventReceiver;
static IGUIEnvironment*     m_gui;
static IGUIFont*            m_defaultFont=0;
static IGUIFont*            m_monoFont=0;
static ICameraSceneNode*    m_camera;
static bool                 m_running=true;
static CTextOverlay*        m_debugOverlay;
static int                  m_capNumber=1;

//static E_DRIVER_TYPE        m_driverType=EDT_OPENGL;  
static E_DRIVER_TYPE        m_driverType=EDT_DIRECT3D9; 

IGUIEnvironment* getGUI()
{
    return m_gui;
}

//-----------------------------------------------------------------------------
//                             E v e n t R e c e i v er
//-----------------------------------------------------------------------------
// used to suppress/enable engine debug messages
class EventReceiver : public IEventReceiver
{
    bool OnEvent(const SEvent& event)
    {
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            if( !event.KeyInput.PressedDown ) // key up?
            {
                switch(event.KeyInput.Key)
                {
                case KEY_ESCAPE:
                    m_running = false;
                    return true;
                case KEY_SNAPSHOT:
                    IImage* image = m_videoDriver->createScreenShot();
                    char buf[32];

                    sprintf(buf,"cap%.2d.png",m_capNumber++);

                    m_videoDriver->writeImageToFile(image,buf);

                    image->drop();
                    break;
                }

            }
            return false;
    }

public:
    bool suppressEvents;
    EventReceiver() : IEventReceiver() {}

};

//-----------------------------------------------------------------------------
//                           _ c r e a t e D e v i c e
//-----------------------------------------------------------------------------
static IrrlichtDevice* _createDevice()
{
    m_eventReceiver = new EventReceiver();
    SIrrlichtCreationParameters cp;
    cp.DriverType = m_driverType;
    cp.WindowSize = dimension2d<s32>(WINDOW_SIZE_X,WINDOW_SIZE_Y);
    cp.Bits = DEVICE_BPP;
    cp.Fullscreen = false;
    cp.Vsync = false;
    cp.Stencilbuffer = false;
    cp.AntiAlias = false;
    cp.EventReceiver = m_eventReceiver;
    cp.WindowId = 0;

    return createDeviceEx(cp);
}

//-----------------------------------------------------------------------------
//                               _ i n i t
//-----------------------------------------------------------------------------
static void _init()
{

    //
    // set up the default font
    //        

    
    stringc fontFolder = "data/fnt/";
    stringc defFonts = fontFolder + "defaults.zip";
    if(m_fileSystem->existFile(defFonts.c_str()))
    {
        m_fileSystem->addZipFileArchive(defFonts.c_str());
        m_defaultFont = m_gui->getFont("tdeffont.xml");
        if(m_defaultFont)
        {
            m_defaultFont->grab();
            m_gui->getSkin()->setFont(m_defaultFont);
        }
        m_monoFont = m_gui->getFont("monospace.xml");
        if(m_monoFont)
        {
            m_monoFont->grab();
            //m_gui->getSkin()->setFont(m_monoFont);
        }
    }
    
    
    

    //
    // setup debug overlay
    //
    
    m_debugOverlay = new CTextOverlay("DebugInfo",rectf(0.25f,0.005f,0.75f,0.05f));
    m_debugOverlay->addItem("Node: Pos(x,y,z) Hpr(x,y,z) Dir(x,y,z)", EGUIA_CENTER);
    m_debugOverlay->addItem("Frame: Avg(0.0) Min(0.0) Max(0.0)", EGUIA_CENTER);
    m_debugOverlay->addItem("Visible Debug Data:", EGUIA_CENTER);

    m_debugOverlay->setVisible(true);
    
}

//-----------------------------------------------------------------------------
//                                  t e s t 1
//-----------------------------------------------------------------------------
void test1()
{

    /*
    IGUIStaticText* stext = getGUI()->addStaticText(L" ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789 ",
        rect<s32>(50,200,350,225),false,false,0,true);
    stext->setBackgroundColor(SColor(255,128,0,0));
    stext->setOverrideColor(SColor(255,255,255,255));

    stext = getGUI()->addStaticText(L" ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789 ",
        rect<s32>(0,200,300,225),false,false,0,true);
    stext->setBackgroundColor(SColor(255,0,255,0));
    stext->setOverrideColor(SColor(255,255,255,255));
    */
}

//-----------------------------------------------------------------------------
//                                 m a i n
//-----------------------------------------------------------------------------
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup") 
int main(int argc, char* argv[])
{

    m_device = _createDevice();
    if(!m_device)
        return -1;

    m_fileSystem = m_device->getFileSystem();
    m_videoDriver = m_device->getVideoDriver();
    m_sceneManager = m_device->getSceneManager();
    m_gui = m_device->getGUIEnvironment();

    _init();

    m_device->setWindowCaption(L"nbtest");

    m_camera = m_sceneManager->addCameraSceneNodeFPS(0, 100.0f, 100.0f);
	scene::ISceneNode* n = m_sceneManager->addCubeSceneNode();

	if (n)
	{
		n->setMaterialTexture(0, m_videoDriver->getTexture("data/tex/t351sml.jpg"));
		n->setMaterialFlag(video::EMF_LIGHTING, false);
		scene::ISceneNodeAnimator* anim =
			m_sceneManager->createFlyCircleAnimator(core::vector3df(0,0,30), 20.0f);
		if (anim)
		{
			n->addAnimator(anim);
			anim->drop();
		}
	}

    test1();
    
    int lastFPS = -1;


    while(m_device->run() && m_running)
    {
        m_videoDriver->beginScene(true, true, SColor(255,100,101,140));

        m_sceneManager->drawAll();
        m_gui->drawAll();

        m_videoDriver->endScene();
        
		int fps = m_videoDriver->getFPS();

		if (lastFPS != fps)
		{
            
			core::stringc str = "Frame: Avg(";
			str += fps;
            str += ") Min(0) Max(0)";
            m_debugOverlay->updateItem(1, str);

			lastFPS = fps;
		}
        
    }

    if(m_defaultFont)
        m_defaultFont->drop();
    if(m_monoFont)
        m_monoFont->drop();
    m_device->drop();
    delete m_eventReceiver;

    return 0;
}

