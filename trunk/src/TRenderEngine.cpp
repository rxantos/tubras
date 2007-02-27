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

        while(m_overlays.size() > 0)
        {
            LIST_OVERLAYS::iterator itr;
            TOverlay* overlay = *m_overlays.begin();
            delete overlay;
        }

        while(m_cameras.size() > 0) 
        {
            MAP_CAMERAS_ITR itr;
            itr = m_cameras.begin();
            TCameraNode* camera = itr->second;
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

        while(m_sceneNodes.size() > 0) 
        {
            MAP_SCENENODES_ITR itr;
            itr = m_sceneNodes.begin();
            TSceneNode* node = itr->second;
            delete node;
        }

        while(m_materials.size() > 0) 
        {
            MAP_MATERIALS_ITR itr;
            itr = m_materials.begin();
            TMaterial* mat = itr->second;
            delete mat;
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
    //                         a d d O v e r l a y
    //-----------------------------------------------------------------------
    void TRenderEngine::addOverlay(TOverlay* overlay)
    {
        m_overlays.push_back(overlay);
    }

    //-----------------------------------------------------------------------
    //                       r e m o v e O v e r l a y
    //-----------------------------------------------------------------------
    void TRenderEngine::removeOverlay(TOverlay* overlay)
    {
        LIST_OVERLAYS::iterator itr;
        itr = m_overlays.begin();
        while(itr != m_overlays.end())
        {
            TOverlay* o = *itr;
            if(o == overlay)
            {
                m_overlays.erase(itr);
                return;
            }

            ++itr;
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
        TString	msg;

        //
        // Initialize Render System
        //

        //
        // Initialize Ogre (plugin, config, and log names)
        //
        TString lname = m_pApplication->getLogName();
        m_pOgreRoot = new Ogre::Root("","",m_pApplication->getLogName());


        //
        // set resource locations ./resources
        //


        TString typeName,archName;
        Ogre::ConfigFile::SettingsIterator sit = m_pConfigFile->getSettingsIterator("Resources");
        try
        {
            TString parm,value;

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
                    TString msg;
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
            TString cs = (*it);
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
        TString val = m_pConfigFile->getSetting("resolution","Video");
        sscanf(val.c_str(), "%dx%d", &w, &h);


        val = m_pConfigFile->getSetting("fullscreen","Video");
        if (val == "true")
            fullscreen = true;
        // opts.erase("fullscreen");

        // false because we are not using an autocreated window
        m_pOgreRoot->initialise(false);


        Ogre::NameValuePairList pl;

        TString opt = m_pConfigFile->getSetting("vsync","Video");
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
        // possibly create default camera and viewport
        //
        m_camera = getApplication()->createDefaultCamera();

        m_viewPort = getApplication()->createDefaultViewport();

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
    void TRenderEngine::addCamera(TCameraNode* camera)
    {

        m_cameras[camera->getName()] = camera;

    }

    //-----------------------------------------------------------------------
    //                      r e m o v e C a m e r a
    //-----------------------------------------------------------------------
    void TRenderEngine::removeCamera(TString name)
    {

    }

    //-----------------------------------------------------------------------
    //                      g e t C a m e r a
    //-----------------------------------------------------------------------
    TCameraNode* TRenderEngine::getCamera(TString cameraName)
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
    void TRenderEngine::removeViewPort(TString name)
    {

    }

    //-----------------------------------------------------------------------
    //                      g e t V i e w P o r t
    //-----------------------------------------------------------------------
    TViewPort* TRenderEngine::getViewPort(TString viewPortName)
    {
        return m_viewports[viewPortName];
    }

    //-----------------------------------------------------------------------
    //                 s e t B a c k g r o u n d C o l o r
    //-----------------------------------------------------------------------
    int TRenderEngine::setBackgroundColor(TColor color)
    {
        if(m_viewPort)
            m_viewPort->setBackgroundColour(color);

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
    //                     g e t A m b i e n t L i g h t
    //-----------------------------------------------------------------------
    TColor TRenderEngine::getAmbientLight(void) 
    {
        return m_sceneManager->getAmbientLight();
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
    //                          a d d S c e n e N o d e
    //-----------------------------------------------------------------------
    void TRenderEngine::addSceneNode(TString name,TSceneNode* node)
    {
        if(m_sceneNodes.find(name) != m_sceneNodes.end())
        {
            TStrStream msg;
            msg << "Scene Node Already Exists: " << name;
            m_pApplication->logMessage(msg.str().c_str());
            return;
        }
        m_sceneNodes[name] = node;
    }

    //-----------------------------------------------------------------------
    //                      r e m o v e S c e n e N o d e
    //-----------------------------------------------------------------------
    void TRenderEngine::removeSceneNode(TString name)
    {
        MAP_SCENENODES_ITR itr = m_sceneNodes.find(name);

        if(itr != m_sceneNodes.end())
        {
            m_sceneNodes.erase(itr);
        }
        else
        {
            TStrStream msg;
            msg << "Scene Node Doesn't Exist: " << name;
            m_pApplication->logMessage(msg.str().c_str());
            return;
        }
    }

    //-----------------------------------------------------------------------
    //                      d e s t r o y S c e n e N o d e
    //-----------------------------------------------------------------------
    void TRenderEngine::destroySceneNode(TString name)
    {
        removeSceneNode(name);
        m_sceneManager->destroySceneNode(name);
    }

    //-----------------------------------------------------------------------
    //                         g e t S c e n e N o d e
    //-----------------------------------------------------------------------
    TSceneNode* TRenderEngine::getSceneNode(size_t idx)
    {
        if(idx >= m_sceneNodes.size())
            return NULL;

        MAP_SCENENODES::iterator itr = m_sceneNodes.begin();
        size_t i = 0;
        while(i < idx)
        {
            ++itr;
            ++i;
        }
        return itr->second;
    }

    //-----------------------------------------------------------------------
    //                         g e t S c e n e N o d e
    //-----------------------------------------------------------------------
    TSceneNode* TRenderEngine::getSceneNode(TString nodeName)
    {
        MAP_SCENENODES::iterator itr = m_sceneNodes.find(nodeName);
        if(itr != m_sceneNodes.end())
            return itr->second;
        return NULL;
    }



    //-----------------------------------------------------------------------
    //                          a d d M a t e r i a l
    //-----------------------------------------------------------------------
    void TRenderEngine::addMaterial(TString name,TMaterial* mat)
    {
        if(m_materials.find(name) != m_materials.end())
        {
            TStrStream msg;
            msg << "Material Already Exists: " << name;
            m_pApplication->logMessage(msg.str().c_str());
            return;
        }
        m_materials[name] = mat;
    }

    //-----------------------------------------------------------------------
    //                       r e m o v e M a t e r i a l
    //-----------------------------------------------------------------------
    void TRenderEngine::removeMaterial(TString name)
    {
        MAP_MATERIALS_ITR itr = m_materials.find(name);
        if(itr == m_materials.end())
        {
            TStrStream msg;
            msg << "Material Doesn't Exist: " << name;
            m_pApplication->logMessage(msg.str().c_str());
            return;
        }
        m_materials.erase(itr);
    }

    //-----------------------------------------------------------------------
    //                    t o g g l e W i r e f r a m e
    //-----------------------------------------------------------------------
    void TRenderEngine::toggleWireframe()
    {
        if(getCamera("Camera::Default")->getPolygonMode() == Ogre::PM_SOLID)
            getCamera("Camera::Default")->setPolygonMode(Ogre::PM_WIREFRAME);
        else getCamera("Camera::Default")->setPolygonMode(Ogre::PM_SOLID);
    }

    //-----------------------------------------------------------------------
    //                t o g g l e B o u n d i n g B o x e s
    //-----------------------------------------------------------------------
    void TRenderEngine::toggleBoundingBoxes()
    {
        if(m_sceneManager->getShowBoundingBoxes())
            m_sceneManager->showBoundingBoxes(false);
        else
            m_sceneManager->showBoundingBoxes(true);
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
    //                     g e t D i s p l a y S i z e
    //-----------------------------------------------------------------------
    void TRenderEngine::getDisplaySize(size_t& width, size_t& height)
    {

        width = m_pRenderWindow->getWidth();
        height = m_pRenderWindow->getHeight();
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
