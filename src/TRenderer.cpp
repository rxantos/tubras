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

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                           T R e n d e r e r
    //-----------------------------------------------------------------------
    TRenderer::TRenderer() : m_bgColour(0), 
        m_sceneManager(0),
        m_capNumber(1),
        m_defaultFont(0),
        m_monoFont(0),
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
        CIrrBMeshFileLoader* loader = new CIrrBMeshFileLoader(m_videoDriver,m_sceneManager,m_fileSystem);
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
    void TRenderer::updateDebugMode(ISceneNode* parent)
    {
        if(!parent)
            return;

        parent->setDebugDataVisible(m_debugMode);

        list<ISceneNode*> children = parent->getChildren();
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
    void TRenderer::updateRenderMode(ISceneNode* parent)
    {
        if(!parent)
            return;

        if(parent->getMaterialCount())
        {
            for(u32 idx=0;idx<parent->getMaterialCount();idx++)
            {
                SMaterial& mat = parent->getMaterial(idx);

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

        list<ISceneNode*> children = parent->getChildren();
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
