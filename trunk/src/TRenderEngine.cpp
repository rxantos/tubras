//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006 Tubras Software Ltd
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

const char  *cs_FileSystem      = "FileSystem";
const char  *cs_resources		= "resources";
const char  *cs_General         = "General";

using namespace Ogre;

namespace Tubras {

    //-----------------------------------------------------------------------
    //                       T R e n d e r E n g i n e
    //-----------------------------------------------------------------------
    TRenderEngine::TRenderEngine(TConfigFile* pConfigFile)  
    {

        m_pConfigFile = pConfigFile;
        m_pApplication = getApplication();
    }

    //-----------------------------------------------------------------------
    //                      ~ T R e n d e r E n g i n e
    //-----------------------------------------------------------------------
    TRenderEngine::~TRenderEngine() 
    {
        Ogre::WindowEventUtilities::removeWindowEventListener(m_pRenderWindow,this);

        while(m_cameras.size() > 0) 
        {
            MAP_CAMERAS_ITR itr;
            itr = m_cameras.begin();
            TCamera* camera = itr->second;
            delete camera;
            m_cameras.erase(itr);
        }

        while(m_viewports.size() > 0) 
        {
            MAP_VIEWPORTS_ITR itr;
            itr = m_viewports.begin();
            TViewPort* viewport = itr->second;
            delete viewport;
            m_viewports.erase(itr);
        }

        if(m_rootNode)
            delete m_rootNode;

        if(m_pOgreRoot)
        {
            delete m_pOgreRoot;
            m_pOgreRoot = NULL;
        }
    }

    //-----------------------------------------------------------------------
    //                   g e t S i n g l e t o n P t r
    //-----------------------------------------------------------------------
    template<> TRenderEngine* TSingleton<TRenderEngine>::ms_Singleton = 0;

    TRenderEngine* TRenderEngine::getSingletonPtr(void)
    {
        return ms_Singleton;
    }

    //-----------------------------------------------------------------------
    //                       g e t S i n g l e t o n
    //-----------------------------------------------------------------------
    TRenderEngine& TRenderEngine::getSingleton(void)
    {
        assert( ms_Singleton );  return ( *ms_Singleton );
    }

    //-----------------------------------------------------------------------
    //                         i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TRenderEngine::initialize()
    {
        int result=0;
        string	msg;

        //
        // Initialize Render System
        //

        //
        // Initialize Ogre (plugin, config, and log names)
        //
        string lname = m_pApplication->getLogName();
        m_pOgreRoot = new Ogre::Root("","",m_pApplication->getLogName());


        //
        // set resource locations ./resources
        //


        string typeName,archName;
        Ogre::ConfigFile::SettingsIterator sit = m_pConfigFile->getSettingsIterator("Resources");
        try
        {
            string parm,value;

            while (sit.hasMoreElements())
            {
                typeName = sit.peekNextKey();
                archName = sit.getNext();
                try
                {
                    Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                        archName, typeName, cs_General);
                }
                catch (...)
                {
                    string msg;
                    msg = "** Error Adding Resource: ";
                    msg += archName;

                    m_pApplication->logMessage(msg.c_str());
                }
            }
        }
        catch(...)
        {
        }

        TStringVector pluginList;
        pluginList = m_pConfigFile->getMultiSetting("plugin","Plugins");

        for( TStringVector::iterator it = pluginList.begin(); it != pluginList.end(); ++it )
        {
            string cs = (*it);
            m_pOgreRoot->loadPlugin(cs);
        }

        Ogre::RenderSystemList *renderSystems = NULL;
        Ogre::RenderSystemList::iterator r_it;

        renderSystems = m_pOgreRoot->getAvailableRenderers();

        if(!renderSystems->size())
        {
            m_pApplication->logMessage("Render System Plugin Not Specified In Configuration");
            return 0;
        }

        r_it = renderSystems->begin();
        m_pRenderSystem = *r_it;

        msg = "Using Render System: " + m_pRenderSystem->getName();
        m_pApplication->logMessage(msg.c_str());

        m_pOgreRoot->setRenderSystem(m_pRenderSystem);

        //
        // Initialize the Render Window
        //
        unsigned int h, w;
        bool fullscreen = false;
        string val = m_pConfigFile->getSetting("resolution","Video");
        sscanf(val.c_str(), "%dx%d", &w, &h);


        val = m_pConfigFile->getSetting("fullscreen","Video");
        if (val == "true")
            fullscreen = true;
        // opts.erase("fullscreen");

        // false because we are not using an autocreated window
        m_pOgreRoot->initialise(false);


        Ogre::NameValuePairList pl;

        string opt = m_pConfigFile->getSetting("vsync","Video");
        pl["vsync"] = opt;

        opt = m_pConfigFile->getSetting("colourdepth","Video");
        pl["colourDepth"] = opt;

        opt = m_pConfigFile->getSetting("fsaa","Video");
        pl["FSAA"] = opt;

        m_pRenderWindow = m_pOgreRoot->createRenderWindow(m_pApplication->getAppName(), w, h, fullscreen, &pl);
        m_pRenderWindow->getCustomAttribute("WINDOW", &m_WindowHandle);


        Ogre::WindowEventUtilities::addWindowEventListener(m_pRenderWindow,this);

        //
        // Initialize the Scene Manger after the script has had
        // an opportunity to specify it.
        //

        m_sceneManager = getApplication()->createSceneManager(m_pOgreRoot);

        m_pRenderSystem->_initRenderTargets();

        m_rootNode = new TSceneNode("root3d", NULL, m_sceneManager->getRootSceneNode());

        // Initialise, parse scripts etc
        ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

        //
        // possibley create default camera and viewport
        //
        m_camera = getApplication()->createDefaultCamera();

        m_pViewPort = getApplication()->createDefaultViewport();

        return result;
    }

    //-----------------------------------------------------------------------
    //                       r e n d e r F r a m e
    //-----------------------------------------------------------------------
    int TRenderEngine::renderFrame()
    {
        //
        // break if the render window was closed
        //
        if(m_pRenderWindow->isClosed())
        {
            return 0;
        }

        return m_pOgreRoot->renderOneFrame();
    }

    //-----------------------------------------------------------------------
    //                         a d d C a m e r a
    //-----------------------------------------------------------------------
    void TRenderEngine::addCamera(TCamera* camera)
    {

        m_cameras[camera->getName()] = camera;

    }

    //-----------------------------------------------------------------------
    //                      r e m o v e C a m e r a
    //-----------------------------------------------------------------------
    void TRenderEngine::removeCamera(string name)
    {

    }

    //-----------------------------------------------------------------------
    //                      g e t C a m e r a
    //-----------------------------------------------------------------------
    TCamera* TRenderEngine::getCamera(string cameraName)
    {
        return m_cameras[cameraName];
    }

    //-----------------------------------------------------------------------
    //                       a d d V i e w P o r t
    //-----------------------------------------------------------------------
    void TRenderEngine::addViewPort(TViewPort* viewport)
    {

        m_viewports[viewport->getName()] = viewport;

    }

    //-----------------------------------------------------------------------
    //                   r e m o v e V i e w P o r t
    //-----------------------------------------------------------------------
    void TRenderEngine::removeViewPort(string name)
    {

    }

    //-----------------------------------------------------------------------
    //                      g e t V i e w P o r t
    //-----------------------------------------------------------------------
    TViewPort* TRenderEngine::getViewPort(string viewPortName)
    {
        return m_viewports[viewPortName];
    }

    //-----------------------------------------------------------------------
    //                 s e t B a c k g r o u n d C o l o r
    //-----------------------------------------------------------------------
    int TRenderEngine::setBackgroundColor(TColor color)
    {
        if(m_pViewPort)
            m_pViewPort->setBackgroundColour(color);

        return 0;
    }

    //-----------------------------------------------------------------------
    //                     s e t A m b i e n t L i g h t
    //-----------------------------------------------------------------------
    int TRenderEngine::setAmbientLight(TColor color)
    {
        m_sceneManager->setAmbientLight(color);
        return 0;
    }


    //-----------------------------------------------------------------------
    //                          c r e a t e E n t i t y
    //-----------------------------------------------------------------------
    TEntity* TRenderEngine::createEntity(const char* entityName, const char* meshName)
    {
        TEntity *ent = m_sceneManager->createEntity(entityName,meshName);

        return ent;
    }

    //-----------------------------------------------------------------------
    //                          g e t R o o t N o d e
    //-----------------------------------------------------------------------
    TSceneNode* TRenderEngine::getRootNode()
    {
        return m_rootNode;
    }

    //-----------------------------------------------------------------------
    //                       w i n d o w M o v e d
    //-----------------------------------------------------------------------
    void TRenderEngine::windowMoved(Ogre::RenderWindow* rw)
    {
        TSEvent event;
        event.bind(new TEvent("window.moved"));
        getApplication()->sendEvent(event);
    }

    //-----------------------------------------------------------------------
    //                      w i n d o w R e s i z e d
    //-----------------------------------------------------------------------
    void TRenderEngine::windowResized(Ogre::RenderWindow* rw)
    {
        TSEvent event;
        event.bind(new TEvent("window.resized"));
        event->addIntParameter(rw->getWidth());
        event->addIntParameter(rw->getHeight());
        getApplication()->sendEvent(event);
    }

    //-----------------------------------------------------------------------
    //                   w i n d o w F o c u s C h a n g e
    //-----------------------------------------------------------------------
    void TRenderEngine::windowFocusChange(Ogre::RenderWindow* rw)
    {
        TSEvent event;
        event.bind(new TEvent("window.focuschanged"));
        event->addIntParameter(rw->isActive());
        getApplication()->sendEvent(event);
    }




}
