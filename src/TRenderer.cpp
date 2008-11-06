//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
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
        m_guiSkin(0),
        m_nodeFactory(0),
        m_guiFactory(0),
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

        if(m_guiSkin)
            m_guiSkin->drop();

        if(m_guiFactory)
            m_guiFactory->drop();

        if(m_defaultCamera)
            m_defaultCamera->drop();

        if(m_nodeFactory)
            m_nodeFactory->drop();

        if(m_device)
            m_device->drop();
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

        CISL* config = getAppConfig();

        deviceType = (E_DRIVER_TYPE)config->getInteger("video.driver", EDT_OPENGL);

        vsync = config->getBool("video.vsync");
        dims = config->getDimension2di("video.resolution");
        bits = config->getInteger("video.colordepth",32);
        fullscreen = config->getBool("video.fullscreen");
        fsaa = config->getBool("video.fsaa",0);
        stencilbuffer = config->getBool("video.stencilbuffer");
        m_bgColour = config->getColor("video.bgcolor");


        SIrrlichtCreationParameters cp;
        cp.DriverType = deviceType;
        cp.WindowSize = dims;
        cp.Bits = bits;
        cp.Fullscreen = fullscreen;
        cp.Vsync = vsync;
        cp.Stencilbuffer = stencilbuffer;
        cp.AntiAlias = fsaa;
        cp.EventReceiver = getApplication();

        m_screenRect = TRectd(0,0,dims.Width,dims.Height);

#ifndef TUBRAS_PLATFORM_WIN32
        //
        // Tell Irrlicht to ignore X11 input.
        //

        cp.IgnoreInput = true;
#endif

        m_device = createDeviceEx(cp);

        if(!m_device)
            return 1;

        m_fileSystem = m_device->getFileSystem();
        m_videoDriver = m_device->getVideoDriver();
        m_sceneManager = m_device->getSceneManager();
        m_guiManager = m_device->getGUIEnvironment();

        TString skinName = config->getString("guiskin","video");
        if(skinName.size())
        {
            m_guiSkin = new TGUISkin2(skinName);
            if(!((TGUISkin2*)m_guiSkin)->initialize())
            {
                m_guiManager->setSkin(m_guiSkin);
            }
            else
            {
                TString msg="Error loading GUI skin: ";
                msg += skinName;
                logMessage(msg);
            }
        }
        else
        {
            logMessage("Config \"guiskin\" missing, using default.");
        }

        if( getApplication()->getDebug() )
            logDebugInfo();

        //
        // our scene node factory
        //
        logMessage("Initialize Tubras Node Factory...");
        m_nodeFactory = new TNodeFactory();
        if(m_nodeFactory->initialize())
            return 1;

        //
        // our gui factory
        //
        logMessage("Initialize GUI Factory...");
        
        m_guiFactory = new TGUIFactory(getGUIManager());
        if(m_guiFactory->initialize())
            return 1;            

        m_defaultCamera = getApplication()->createDefaultCamera();

        //
        // set up the default font
        //
        TString fontFolder = config->getString("fontfolder","media");
        if(fontFolder.size())
        {                        
            TString defFonts = fontFolder + "defaults.zip";
            if(getFileSystem()->existFile(defFonts.c_str()))
            {
                getFileSystem()->addZipFileArchive(defFonts.c_str());
                m_defaultFont = getGUIManager()->getFont("tdeffont.xml");
                if(m_defaultFont)
                {
                    m_defaultFont->grab();
                    getGUIManager()->getSkin()->setFont(m_defaultFont);
                }
                m_monoFont = getGUIManager()->getFont("monospace.xml");
                if(m_monoFont)
                    m_monoFont->grab();
            }                        
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
    //                    g e t A c t i v e C a m e r a 
    //-----------------------------------------------------------------------
    ICameraSceneNode* TRenderer::getActiveCamera()
    {
        return m_sceneManager->getActiveCamera();
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
