//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
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
    //-----------------------------------------------------------------------
    //                           T R e n d e r e r
    //-----------------------------------------------------------------------
    TRenderer::TRenderer(IRendererListener* listener) : m_device(0),
        m_videoDriver(0),
        m_sceneManager(0),
        m_guiManager(0),
        m_fileSystem(0),
        m_defaultCamera(0),
        m_backgroundNode(0),
        m_listener(listener),
        m_guiFactory(0),
        m_guiSkin(0),
        m_defaultFont(0),
        m_monoFont(0),
        m_guiCursor(0),
        m_bgColor(0),
        m_renderMode(rmNormal),
        m_capNumber(1),
        m_debugMode(EDS_OFF),
        m_display(0),
        m_windowId(0),
        m_whiteImage(0),
        m_whiteTexture(0),
        m_guiCursorEnabled(false)
    {
    }

    //-----------------------------------------------------------------------
    //                          ~ T R e n d e r e r
    //-----------------------------------------------------------------------
    TRenderer::~TRenderer()
    {
        if(m_guiCursor)
            m_guiCursor->drop();

        if(m_whiteImage)
            m_whiteImage->drop();

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

        if(m_device)
            m_device->drop();
    }

    //-----------------------------------------------------------------------
    //                         p a r s e R e s o l u t i o n
    //-----------------------------------------------------------------------
    bool TRenderer::parseResolution(stringc resolution, bool keepaspect,
        TDimension& dim)
    {
        u32 lowest=4096, highest=0, lidx, hidx, midx;
        irr::IrrlichtDevice* nullDevice = getApplication()->getNullDevice();
        dimension2du res;
        s32 depth,max_depth=0;
        float aspect;

        IVideoModeList* ml = nullDevice->getVideoModeList();
        u32 count = (u32)ml->getVideoModeCount();
        for(u32 i=0;i<count;i++)
        {
            res = ml->getVideoModeResolution(i);
            depth = ml->getVideoModeDepth(i);
            if(res.Width < lowest)
            {
                lowest = res.Width;
                lidx = i;
            }
            if(res.Width > highest)
            {
                highest = res.Width;
                hidx = i;
            }
            if(depth < max_depth)
                max_depth = depth;
        }

        // next resolution up from the lowest
        res = ml->getVideoModeResolution(lidx);
        lowest = res.Width;
        while((lowest == res.Width) && (lidx < count))
        {
            ++lidx;
            res = ml->getVideoModeResolution(lidx);
        }

        midx = count / 2;
        depth = ml->getVideoModeDepth(midx);
        while((depth < max_depth) && (midx < count))
        {
            ++midx;
            depth = ml->getVideoModeDepth(midx);
        }
        if(midx >= count)
            midx = count / 2;

        res = ml->getVideoModeResolution(hidx);
        aspect = (float)res.Width / (float)(res.Height);

        if(resolution.equals_ignore_case("maximum"))
        {
            res = ml->getVideoModeResolution(hidx);
            keepaspect = false;
        }
        else if(resolution.equals_ignore_case("minimum"))
            res = ml->getVideoModeResolution(lidx);
        else        
            res = ml->getVideoModeResolution(midx);

        dim.Width = res.Width;
        dim.Height = res.Height;

        if(keepaspect)
            dim.Height = (int)(((float)dim.Width / aspect) + .5f);

        return true;
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
        bool doublebuffer=true;
        bool keepaspect=true;
        u8 fsaa=false;
        TString temp;
        TApplication* app=getApplication();

        TSL* config = app->getConfig();

        deviceType = (E_DRIVER_TYPE)config->getInteger("video.driver", EDT_OPENGL);

        vsync = config->getBool("video.vsync");
        keepaspect = config->getBool("video.keepaspect", false);

        temp = config->getString("video.resolution", "notastring");
        if( temp.equals_ignore_case("minimum") ||
            temp.equals_ignore_case("medium") ||
            temp.equals_ignore_case("maximum") )
        {
            parseResolution(temp, keepaspect, dims);
        }
        else
        {
            dims = config->getDimension2du("video.resolution");
        }
        bits = config->getInteger("video.colordepth",32);
        fullscreen = config->getBool("video.fullscreen");
        fsaa = config->getInteger("video.antialias",0);
        stencilbuffer = config->getBool("video.stencilbuffer");
        doublebuffer = config->getBool("video.doublebuffer",true);
        m_bgColor = config->getColor("video.bgcolor");
        m_debugNormalLen = config->getFloat("video.debugNormalLength", 0.2f);
        m_debugNormalColor = config->getColor("video.debugNormalColor", SColor(255,34,231,231));

        app->logMessage(LOG_INFO, "Renderer vsync=%d, resolution=%dx%d, bpp=%d, aa=%d, sb=%d", vsync, 
            dims.Width, dims.Height, bits, fsaa, stencilbuffer);        

        SIrrlichtCreationParameters cp;
        cp.DriverType = deviceType;
        cp.WindowSize = dims;
        cp.Bits = bits;
        cp.Fullscreen = fullscreen;
        cp.Vsync = vsync;
        cp.Stencilbuffer = stencilbuffer;
        cp.Doublebuffer = doublebuffer;
        cp.AntiAlias = fsaa;
        cp.EventReceiver = getApplication();

        m_screenRect = TRecti(0,0,dims.Width,dims.Height);

        m_device = createDeviceEx(cp);

        if(!m_device)
            return 1;

        m_fileSystem = m_device->getFileSystem();
        m_videoDriver = m_device->getVideoDriver();
        m_sceneManager = m_device->getSceneManager();
        m_guiManager = m_device->getGUIEnvironment();

        m_sceneManager->getParameters()->setAttribute(DEBUG_NORMAL_LENGTH, m_debugNormalLen);
        m_sceneManager->getParameters()->setAttribute(DEBUG_NORMAL_COLOR, m_debugNormalColor);

        if(m_listener)
            m_listener->onDeviceCreated();

        m_fileSystem->addFileArchive(getApplication()->getDataRoot().c_str(),false, false);

        TString skinName = config->getString("video.guiskin");
        if(skinName.size() && !skinName.equals_ignore_case("default"))
        {
            skinName = app->getDataRoot();
            skinName += config->getString("video.guiskin");
            m_guiSkin = new TGUISkin(skinName);
            if(!((TGUISkin*)m_guiSkin)->initialize())
            {
                m_guiManager->setSkin(m_guiSkin);
            }
            else
            {
                app->logMessage(LOG_ERROR, "Error loading GUI skin: %s", skinName.c_str());
            }
        }

        if( app->getDebug() )
            logDebugInfo();

        //
        // our gui factory
        //
        app->logMessage(LOG_INFO, "Initialize GUI Factory...");
        
        m_guiFactory = new TGUIFactory(getGUIManager());
        if(m_guiFactory->initialize())
            return 1;            

        m_defaultCamera = getApplication()->createDefaultCamera();

        //
        // set up the default font
        //
        TString fontFolder = app->getDataRoot();
        fontFolder += "fnt/";
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

        //
        // create a base white texture
        //
        u32 idata[4]={0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};

        m_whiteImage = m_videoDriver->createImageFromData(ECF_A8R8G8B8,
            dimension2d<u32>(2,2), &idata);
        m_whiteTexture = m_videoDriver->addTexture("tbasewhite", m_whiteImage);

        m_guiCursor = new TGUICursor(m_guiManager);
        m_guiCursorEnabled = config->getBool("video.guicursor");

        return 0;
    }

    //-----------------------------------------------------------------------
    //                        l o g D e b u g I n f o
    //-----------------------------------------------------------------------
    void TRenderer::logDebugInfo()
    {
        bool value = m_videoDriver->queryFeature(EVDF_TEXTURE_NPOT);
        getApplication()->logMessage(LOG_INFO, "Supports NPOT: %d", value);

        value = m_videoDriver->queryFeature(EVDF_FRAMEBUFFER_OBJECT);
        getApplication()->logMessage(LOG_INFO, "Supports FrameBuffer: %d", value);

        value = m_videoDriver->queryFeature(EVDF_VERTEX_BUFFER_OBJECT);
        getApplication()->logMessage(LOG_INFO, "Supports VertexBuffer: %d", value);

        //
        // log video info
        // 
        IVideoModeList* ml = m_device->getVideoModeList();
        s32 count = ml->getVideoModeCount();
        getApplication()->logMessage(LOG_INFO, "Available Video Modes:");
        for(s32 i=0;i<count;i++)
        {
            dimension2du res = ml->getVideoModeResolution(i);
            s32 depth = ml->getVideoModeDepth(i);
            getApplication()->logMessage(LOG_INFO, "   mode %.2d %dx%d %dbpp",i, res.Width, res.Height, depth);
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
                default:
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
    //                           u p d a t e
    //-----------------------------------------------------------------------
    bool TRenderer::update()
    {
        m_videoDriver->beginScene(true, true, m_bgColor);

        if(m_backgroundNode)
            m_backgroundNode->render();

        m_sceneManager->drawAll();

        m_guiManager->drawAll();

        if(m_guiCursorEnabled)
            m_guiCursor->draw();

        m_videoDriver->endScene();

        return true;
    }
}
