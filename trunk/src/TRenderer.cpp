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
#include "tubras.h"

#ifndef TUBRAS_PLATFORM_WIN32
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/gl.h>
#define GLX_GLXEXT_LEGACY 1
#include <GL/glx.h>
#include "glxext.h"
#endif

namespace Tubras
{
    static const char* wmDeleteWindow = "WM_DELETE_WINDOW";
    //-----------------------------------------------------------------------
    //                           T R e n d e r e r
    //-----------------------------------------------------------------------
    TRenderer::TRenderer() : m_bgColour(0), 
        m_sceneManager(0),
        m_capNumber(1),
        m_defaultFont(0),
        m_monoFont(0),
        m_display(0),
        m_windowId(0),
        m_debugMode(EDS_OFF),
        m_renderMode(rmNormal)
    {
    }

    //-----------------------------------------------------------------------
    //                          ~ T R e n d e r e r
    //-----------------------------------------------------------------------
    TRenderer::~TRenderer()
    {
        if(m_defaultFont)
            m_defaultFont->drop();

        if(m_monoFont)
            m_monoFont->drop();

        if(m_camera)
            m_camera->drop();

        if(m_nodeFactory)
            m_nodeFactory->drop();

        if(m_device)
            m_device->drop();
    }

    //-----------------------------------------------------------------------
    //                         c r e a t e X W i n d o w
    //-----------------------------------------------------------------------
    void* TRenderer::createXWindow(const SIrrlichtCreationParameters& cp)
    {
        void*   result=0;
#ifndef TUBRAS_PLATFORM_WIN32
		XSetWindowAttributes attributes;
        
        Display* display;
        display = XOpenDisplay(0);
        m_display = display;
        if (!m_display)
        {
            getApplication()->logMessage("Error opening X11 Display");
            return 0;
        }
	int screennr = DefaultScreen(display);

        //
        // duplicate code from CIrrDeviceLinux.cpp
        // 

    XVisualInfo* visual;
    GLXContext Context;
	Context=0;
    bool UseGLXWindow=false;
	GLXFBConfig glxFBConfig;
	int major, minor;
    bool AntiAlias=cp.AntiAlias;
    bool StencilBuffer = cp.Stencilbuffer;
	bool isAvailableGLX=false;
		isAvailableGLX=glXQueryExtension(display,&major,&minor);
		if (isAvailableGLX && glXQueryVersion(display, &major, &minor))
		{
			if (major==1 && minor>2)
			{
				const int MAX_SAMPLES = 16;
				// attribute array for the draw buffer
				int visualAttrBuffer[] =
				{
					GLX_RENDER_TYPE, GLX_RGBA_BIT,
					GLX_RED_SIZE, 4,
					GLX_GREEN_SIZE, 4,
					GLX_BLUE_SIZE, 4,
					GLX_ALPHA_SIZE, 4,
					GLX_DEPTH_SIZE, 16,
					GLX_DOUBLEBUFFER, GL_TRUE,
					GLX_STENCIL_SIZE, 1,
					GLX_SAMPLE_BUFFERS_ARB, GL_TRUE,
					GLX_SAMPLES_ARB, MAX_SAMPLES,
					None
				};

				GLXFBConfig *configList=0;
				int nitems=0;
				if (!AntiAlias)
				{
					visualAttrBuffer[17] = GL_FALSE;
					visualAttrBuffer[19] = 0;
				}
				if (StencilBuffer)
				{
					configList=glXChooseFBConfig(display, screennr, visualAttrBuffer,&nitems);
					if (!configList && AntiAlias)
					{
						while (!configList && (visualAttrBuffer[19]>1))
						{
							visualAttrBuffer[19] >>= 1;
							configList=glXChooseFBConfig(display, screennr, visualAttrBuffer,&nitems);
						}
						if (!configList)
						{
							visualAttrBuffer[17] = GL_FALSE;
							visualAttrBuffer[19] = 0;
							configList=glXChooseFBConfig(display, screennr, visualAttrBuffer,&nitems);
							if (configList)
							{
								//os::Printer::log("No FSAA available.", ELL_WARNING);
								AntiAlias=false;
							}
							else
							{
								//reenable multisampling
								visualAttrBuffer[17] = GL_TRUE;
								visualAttrBuffer[19] = MAX_SAMPLES;
							}
						}
					}
				}
				// Next try without stencil buffer
				if (!configList)
				{
					if (StencilBuffer)
                    {
						//os::Printer::log("No stencilbuffer available, disabling stencil shadows.", ELL_WARNING);
                    }
					StencilBuffer = false;
					visualAttrBuffer[15]=0;

					configList=glXChooseFBConfig(display, screennr, visualAttrBuffer,&nitems);
					if (!configList && AntiAlias)
					{
						while (!configList && (visualAttrBuffer[19]>1))
						{
							visualAttrBuffer[19] >>= 1;
							configList=glXChooseFBConfig(display, screennr, visualAttrBuffer,&nitems);
						}
						if (!configList)
						{
							visualAttrBuffer[17] = GL_FALSE;
							visualAttrBuffer[19] = 0;
							configList=glXChooseFBConfig(display, screennr, visualAttrBuffer,&nitems);
							if (configList)
							{
								//os::Printer::log("No FSAA available.", ELL_WARNING);
								AntiAlias=false;
							}
							else
							{
								//reenable multisampling
								visualAttrBuffer[17] = GL_TRUE;
								visualAttrBuffer[19] = MAX_SAMPLES;
							}
						}
					}
				}
				// Next try without double buffer
				if (!configList)
				{
					//os::Printer::log("No doublebuffering available.", ELL_WARNING);
					visualAttrBuffer[13] = GL_FALSE;
					configList=glXChooseFBConfig(display, screennr, visualAttrBuffer,&nitems);
					if (!configList && AntiAlias)
					{
						while (!configList && (visualAttrBuffer[19]>1))
						{
							visualAttrBuffer[19] >>= 1;
							configList=glXChooseFBConfig(display, screennr, visualAttrBuffer,&nitems);
						}
						if (!configList)
						{
							visualAttrBuffer[17] = GL_FALSE;
							visualAttrBuffer[19] = 0;
							configList=glXChooseFBConfig(display, screennr, visualAttrBuffer,&nitems);
							if (configList)
							{
								//os::Printer::log("No FSAA available.", ELL_WARNING);
								AntiAlias=false;
							}
							else
							{
								//reenable multisampling
								visualAttrBuffer[17] = GL_TRUE;
								visualAttrBuffer[19] = MAX_SAMPLES;
							}
						}
					}
				}
				if (configList)
				{
					glxFBConfig=configList[0];
					XFree(configList);
					UseGLXWindow=true;
					visual = glXGetVisualFromFBConfig(display,glxFBConfig);
				}
			}
			else
			{
				// attribute array for the draw buffer
				int visualAttrBuffer[] =
				{
					GLX_RGBA, GL_TRUE,
					GLX_RED_SIZE, 4,
					GLX_GREEN_SIZE, 4,
					GLX_BLUE_SIZE, 4,
					GLX_ALPHA_SIZE, 4,
					GLX_DEPTH_SIZE, 16,
					GLX_DOUBLEBUFFER, GL_TRUE,
					GLX_STENCIL_SIZE, 1,
					None
				};

				if (StencilBuffer)
					visual=glXChooseVisual(display, screennr, visualAttrBuffer);
				if (!visual)
				{
					if (StencilBuffer)
					{
						//os::Printer::log("No stencilbuffer available, disabling stencil shadows.", ELL_WARNING);
						StencilBuffer = false;
					}
					visualAttrBuffer[15]=0;

					visual=glXChooseVisual(display, screennr, visualAttrBuffer);
					if (!visual)
					{
						//os::Printer::log("No doublebuffering available.", ELL_WARNING);
						visualAttrBuffer[13] = GL_FALSE;
						visual=glXChooseVisual(display, screennr, visualAttrBuffer);
					}
				}
			}
		}
		else
        {
			//os::Printer::log("No GLX support available. OpenGL driver will not work.", ELL_WARNING);
        }
	
	// create visual with standard X methods
	if (!visual)
	{
		XVisualInfo visTempl; //Template to hold requested values
		int visNumber; // Return value of available visuals

		visTempl.screen = screennr;
		visTempl.depth = 16;
		while ((!visual) && (visTempl.depth<=32))
		{
			visual = XGetVisualInfo(display, VisualScreenMask|VisualDepthMask,
				&visTempl, &visNumber);
			visTempl.depth+=8;
		}
	}

	if (!visual)
	{
		//os::Printer::log("Fatal error, could not get visual.", ELL_ERROR);
		XCloseDisplay(display);
		display=0;
		return false;
	}

	// create color map
	Colormap colormap;
	colormap = XCreateColormap(display,
				RootWindow(display, visual->screen),
				visual->visual, AllocNone);

	attributes.colormap = colormap;
	attributes.border_pixel = 0;
	attributes.event_mask = KeyPressMask | ButtonPressMask |
			StructureNotifyMask | PointerMotionMask |
			ButtonReleaseMask | KeyReleaseMask;

	// create Window, either for Fullscreen or windowed mode
    Window window;
	u32 Width=cp.WindowSize.Width;
    u32 Height=cp.WindowSize.Height;
    u32 Depth=cp.Bits;
    
	if (cp.Fullscreen)
	{
		attributes.override_redirect = True;

		window = XCreateWindow(display,
				RootWindow(display, visual->screen),
				0, 0, Width, Height, 0, visual->depth,
				InputOutput, visual->visual,
				CWBorderPixel | CWColormap | CWEventMask |
				CWOverrideRedirect, &attributes);

		XWarpPointer(display, None, window, 0, 0, 0, 0, 0, 0);
		XMapRaised(display, window);
		XGrabKeyboard(display, window, True, GrabModeAsync,
			GrabModeAsync, CurrentTime);
		XGrabPointer(display, window, True, ButtonPressMask,
			GrabModeAsync, GrabModeAsync, window, None, CurrentTime);
	}
	else
	{ // we want windowed mode
		attributes.event_mask |= ExposureMask;
		attributes.event_mask |= FocusChangeMask;

			window = XCreateWindow(display,
				RootWindow(display, visual->screen),
				0, 0, Width, Height, 0, visual->depth,
				InputOutput, visual->visual,
				CWBorderPixel | CWColormap | CWEventMask,
				&attributes);
            
		Atom wmDelete;
		wmDelete = XInternAtom(display, wmDeleteWindow, True);
		XSetWMProtocols(display, window, &wmDelete, 1);
		XMapRaised(display, window);
	} 
#endif
        return result;
    }

    //-----------------------------------------------------------------------
    //                           i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TRenderer::initialize()
    {
        E_DRIVER_TYPE deviceType;
        TDimension    dims;
        u32 bits=16;
        bool fullscreen=false;
        bool stencilbuffer=false;
        bool vsync=false;
        bool fsaa=false;
        TString temp;

        TXMLConfig* config = getAppConfig();

        temp = config->getString("engine","renderer","opengl");

        if(temp.equals_ignore_case("direct3d9"))
            deviceType = EDT_DIRECT3D9;
        else if(temp.equals_ignore_case("opengl"))
            deviceType = EDT_OPENGL;
        else
            deviceType = EDT_OPENGL;

        vsync = config->getBool("vsync","video");
        dims = config->getDimension("resolution","video",TDimension(800,600));
        bits = config->getInt("colourdepth","video",32);
        fullscreen = config->getBool("fullscreen","video");
        fsaa = config->getBool("fsaa","video");
        m_bgColour = config->getColour("bgcolour","video");

        SIrrlichtCreationParameters cp;
        cp.DriverType = deviceType;
        cp.WindowSize = dims;
        cp.Bits = bits;
        cp.Fullscreen = fullscreen;
        cp.Vsync = vsync;
        cp.Stencilbuffer = stencilbuffer;
        cp.AntiAlias = fsaa;
        cp.EventReceiver = getApplication();


#ifndef TUBRAS_PLATFORM_WIN32
        //
        // Create our own Window ID and pass it in. We do this so that OIS 
        // is able to process X mouse events.
        //
        cp.WindowId = createXWindow(cp);
        
#endif

        m_device = createDeviceEx(cp);

        if(!m_device)
            return 1;

        m_fileSystem = m_device->getFileSystem();
        m_videoDriver = m_device->getVideoDriver();
        m_sceneManager = m_device->getSceneManager();
        m_guiManager = m_device->getGUIEnvironment();

        //
        // add here, until it's accepted...
        //
        CIrrBMeshFileLoader* loader = new CIrrBMeshFileLoader(m_sceneManager,m_fileSystem);
        m_sceneManager->addExternalMeshLoader(loader);
        loader->drop();

        if( getApplication()->getDebug() )
            logDebugInfo();
        
        //
        // our scene node factory
        //
        logMessage("Initialize Tubras Node Factory...");
        m_nodeFactory = new TNodeFactory();
        if(m_nodeFactory->initialize())
            return 1;


        m_camera = getApplication()->createDefaultCamera();

        //
        // set up the default font
        //
        if(getFileSystem()->existFile("data/fnt/defaults.zip"))
        {
            getFileSystem()->addZipFileArchive("data/fnt/defaults.zip");
            m_defaultFont = getGUIManager()->getFont("tdeffont.xml");
            m_defaultFont->grab();
            m_monoFont = getGUIManager()->getFont("monospace.xml");
            m_monoFont->grab();
            getGUIManager()->getSkin()->setFont(m_defaultFont);
            getGUIManager()->getSkin()->setColor(EGDC_BUTTON_TEXT,TColour::White);
        }

        return 0;
    }

    //-----------------------------------------------------------------------
    //                        l o g D e b u g I n f o
    //-----------------------------------------------------------------------
    void TRenderer::logDebugInfo()
    {
        TString info;
        bool value = m_videoDriver->queryFeature(EVDF_TEXTURE_NPOT);
        info = "Supports NPOT: ";
        info += (value ? "true" : "false");
        logMessage(info);

        value = m_videoDriver->queryFeature(EVDF_FRAMEBUFFER_OBJECT);
        info = "Supports FrameBuffer: ";
        info += (value ? "true" : "false");
        logMessage(info);

        value = m_videoDriver->queryFeature(EVDF_VERTEX_BUFFER_OBJECT);
        info = "Supports VertexBuffer: ";
        info += (value ? "true" : "false");
        logMessage(info);

        //
        // log video info
        // 
        IVideoModeList* ml = m_device->getVideoModeList();
        s32 count = ml->getVideoModeCount();
        logMessage("Available Video Modes:");
        for(s32 i=0;i<count;i++)
        {
            char buf[100];

            dimension2d<s32> res = ml->getVideoModeResolution(i);
            s32 depth = ml->getVideoModeDepth(i);
            TStrStream str;
            sprintf(buf,"   mode %.2d %dx%d %dbpp",i, res.Width, res.Height, depth);
            logMessage(buf);
        }
    }

    //-----------------------------------------------------------------------
    //                            g e t T i m e r 
    //-----------------------------------------------------------------------
    ITimer* TRenderer::getTimer()
    {
        return m_device->getTimer();
    }


    //-----------------------------------------------------------------------
    //                         s e t D e b u g M o d e
    //-----------------------------------------------------------------------
    void TRenderer::setDebugMode(E_DEBUG_SCENE_TYPE debugMode)
    {
        if(m_debugMode == debugMode)
            return;
        m_debugMode = debugMode;
        updateDebugMode(m_sceneManager->getRootSceneNode());
    }

    //-----------------------------------------------------------------------
    //                      u p d a t e D e b u g M o d e
    //-----------------------------------------------------------------------
    void TRenderer::updateDebugMode(ISceneNode* node)
    {
        if(!node)
            return;

        ESCENE_NODE_TYPE type = node->getType();

        node->setDebugDataVisible(m_debugMode);

        list<ISceneNode*> children = node->getChildren();
        list<ISceneNode*>::Iterator itr = children.begin();
        while(itr != children.end())
        {
            ISceneNode* child = *itr;
            updateDebugMode(child);
            itr++;
        }
    }

    //-----------------------------------------------------------------------
    //                       s e t R e n d e r M o d e
    //-----------------------------------------------------------------------
    void TRenderer::setRenderMode(TRenderMode value)
    {
        if(m_renderMode == value)
            return;
        m_renderMode = value;
        updateRenderMode(m_sceneManager->getRootSceneNode());
    }

    //-----------------------------------------------------------------------
    //                       s e t R e n d e r M o d e
    //-----------------------------------------------------------------------
    void TRenderer::updateRenderMode(ISceneNode* node)
    {
        if(!node)
            return;

        if(node->getMaterialCount())
        {
            for(u32 idx=0;idx<node->getMaterialCount();idx++)
            {
                SMaterial& mat = node->getMaterial(idx);

                switch(m_renderMode)
                {
                case rmNormal:
                    mat.setFlag(EMF_WIREFRAME,false);
                    mat.setFlag(EMF_POINTCLOUD,false);
                    break;
                case rmWire:
                    mat.setFlag(EMF_WIREFRAME,true);
                    mat.setFlag(EMF_POINTCLOUD,false);
                    break;
                case rmPointCloud:
                    mat.setFlag(EMF_WIREFRAME,false);
                    mat.setFlag(EMF_POINTCLOUD,true);
                    break;
                }
            }
        }

        list<ISceneNode*> children = node->getChildren();
        list<ISceneNode*>::Iterator itr = children.begin();
        while(itr != children.end())
        {
            ISceneNode* child = *itr;
            updateRenderMode(child);
            itr++;
        }
    }

    //-----------------------------------------------------------------------
    //                       g e t R e n d e r M o d e
    //-----------------------------------------------------------------------
    TRenderMode TRenderer::getRenderMode()
    {
        return m_renderMode;
    }

    //-----------------------------------------------------------------------
    //                       c a p t u r e S c r e e n
    //-----------------------------------------------------------------------
    void TRenderer::captureScreen()
    {
        char buf[100];

        IImage* image = m_videoDriver->createScreenShot();

        sprintf(buf,"cap%.2d.png",m_capNumber++);

        m_videoDriver->writeImageToFile(image,buf);

        image->drop();
    }

    //-----------------------------------------------------------------------
    //                        r e n d e r F r a m e
    //-----------------------------------------------------------------------
    bool TRenderer::renderFrame()
    {

        if(!m_device->run())
            return false;

	    m_videoDriver->beginScene(true, true, m_bgColour);

	    m_sceneManager->drawAll();

        m_guiManager->drawAll();

	    m_videoDriver->endScene();

        return true;
    }
}
