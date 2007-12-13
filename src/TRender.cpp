//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006-2007 Tubras Software, Ltd
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

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                            T R e n d e r
    //-----------------------------------------------------------------------
    TRender::TRender() : m_bgColour(0)
    {
    }

    //-----------------------------------------------------------------------
    //                           ~ T R e n d e r
    //-----------------------------------------------------------------------
    TRender::~TRender()
    {
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
    int TRender::initialize()
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

        m_driver = m_device->getVideoDriver();
        m_sceneManager = m_device->getSceneManager();
        m_guiManager = m_device->getGUIEnvironment();

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

        if(getFileSystem()->existFile("data/fnt/tdeffont.zip"))
        {
            getFileSystem()->addZipFileArchive("data/fnt/tdeffont.zip");
            IGUIFont* font = getGUIManager()->getFont("tdeffont.xml");
            getGUIManager()->getSkin()->setFont(font);
            getGUIManager()->getSkin()->setColor(EGDC_BUTTON_TEXT,TColour::White);
        }



        return 0;
    }

    //-----------------------------------------------------------------------
    //                            g e t T i m e r 
    //-----------------------------------------------------------------------
    ITimer* TRender::getTimer()
    {
        return m_device->getTimer();
    }

    //-----------------------------------------------------------------------
    //                         r e n d e r F r a m e
    //-----------------------------------------------------------------------
    bool TRender::renderFrame()
    {

        if(!m_device->run())
            return false;

	    m_driver->beginScene(true, true, m_bgColour);

	    m_sceneManager->drawAll();

        m_guiManager->drawAll();

	    m_driver->endScene();

        return true;
    }
}
