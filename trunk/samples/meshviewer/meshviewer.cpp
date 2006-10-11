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
#include "meshviewer.h"
#include "meshdlg.h"
#include <stdlib.h>

using namespace Tubras;
#define SCALE_FACTOR    0.05f

class TMeshViewer : public TApplication
{
private:
    int             screenNumber;
    TMeshDlg*       m_meshDlg;
    TEntityNode*    m_entity;
    TCardNode*      m_background;

public:
    TMeshViewer(int argc,char **argv) : TApplication(argc,argv,"Tubras Mesh Viewer") 
    {
        m_entity = NULL;
        getApplication()->setGUIScheme("TaharezLookSkin.scheme","TaharezLook");
    }

    virtual ~TMeshViewer()
    {
    }

    int TMeshViewer::quitApp(TSEvent event)
    {
        stopRunning();
        return 1;
    }

    int TMeshViewer::toggleWire(TSEvent event)
    {
        getRenderEngine()->toggleWireframe();
        return 1;
    }

    int TMeshViewer::openMesh(TSEvent event)
    {
        m_meshDlg->show();
        return 1;
    }

    int TMeshViewer::dlgCanceled(TSEvent event)
    {
        m_meshDlg->hide();
        return 1;
    }

    int TMeshViewer::dlgOpen(TSEvent event)
    {
        m_meshDlg->hide();
        string meshName = event->getParameter(0)->getStringValue();
        float scale = event->getParameter(1)->getDoubleValue();

        if(m_entity)
        {
            delete m_entity;
            m_entity = NULL;
        }

        TFile f = meshName;
        m_entity = loadEntity(f.get_basename_wo_extension(),"General",meshName,NULL);
        m_entity->getNode()->setScale(scale,scale,scale);

        //
        // reset the camera
        //
        getRenderEngine()->getCamera("Default")->setPos(TVector3(0,3,12));
        getRenderEngine()->getCamera("Default")->lookAt(TVector3(0,0,0));

        return 1;
    }

    int TMeshViewer::toggleBB(TSEvent event)
    {
        getRenderEngine()->toggleBoundingBoxes();
        return 1;
    }

    int TMeshViewer::toggleDebug(TSEvent event)
    {
        toggleDebugOverlay();
        return 1;
    }

    int TMeshViewer::scaleMesh(TSEvent event)
    {
        int dir = (int)event->getUserData();

        if(m_entity)
        {
            float amt;
            if(dir > 0)
                amt = 1.0f + SCALE_FACTOR;
            else amt = 1.0f - SCALE_FACTOR;

            m_entity->getNode()->scale(amt,amt,amt);
        }

        return 1;
    }

    //
    // show/hide the console
    //
    int TMeshViewer::showConsole(TSEvent event)
    {
        toggleConsole();
        return 1;
    }

    //
    // take a screen shot of our window.
    //
    int TMeshViewer::saveScreen(TSEvent event)
    {
        
        TStrStream fileName;
        string ext;

        ext = getConfigFile()->getSetting("ScreenCapExt","Options");

        fileName << "cap" << screenNumber++ << "." << ext;

        captureScreen(fileName.str().c_str());
        return 0;
    }

    int TMeshViewer::showHelp(TSEvent event)
    {
        toggleHelp();
        return 0;
    }

    //
    // normally we would only override this if we aren't using
    // the state management functionality. 
    //
    int initialize()
    {
        //
        // invoke TApplication initialize which initializes all of the
        // sub-systems (render, sound, input etc.)
        //
        if(TApplication::initialize())
            return 1;

        //
        // take a screen shot when the Print-Scrn is pressed
        //
        acceptEvent("key.down.sysrq",EVENT_DELEGATE(TMeshViewer::saveScreen));

        //
        // allow the engine console to be toggled
        //
        acceptEvent("key.down.f12",EVENT_DELEGATE(TMeshViewer::showConsole));

        //
        // allow the engine console to be toggled
        //
        acceptEvent("key.down.o",EVENT_DELEGATE(TMeshViewer::openMesh));

        //
        // allow the help overlay to be toggled
        //
        acceptEvent("key.down.f1",EVENT_DELEGATE(TMeshViewer::showHelp));

        //
        // toggle wireframe view
        //
        acceptEvent("key.down.f2",EVENT_DELEGATE(TMeshViewer::toggleWire));

        //
        // toggle debug view
        //
        acceptEvent("key.down.f3",EVENT_DELEGATE(TMeshViewer::toggleDebug));

        //
        // bounding box view
        //
        acceptEvent("key.down.f4",EVENT_DELEGATE(TMeshViewer::toggleBB));

        //
        // "Escape" quits the app
        //
        acceptEvent("key.down.esc",EVENT_DELEGATE(TMeshViewer::quitApp));

        acceptEvent("meshdlg.canceled",EVENT_DELEGATE(TMeshViewer::dlgCanceled));
        acceptEvent("meshdlg.open",EVENT_DELEGATE(TMeshViewer::dlgOpen));

        TEventDelegate* ed = EVENT_DELEGATE(TMeshViewer::scaleMesh);

        acceptEvent("key.down.add",ed,(void*)1);
        acceptEvent("key.down.subtract",ed,(void*)-1);

        screenNumber = 1;

        //
        // add help text
        //
        addHelpText("wasd - Camera movement");
        addHelpText("ec   - Elevate camera");
        addHelpText("m    - Toggle mouse move");
        addHelpText("i    - Invert mouse");
        addHelpText("o    - Open mesh");
        addHelpText("arrows - pitch/rotate");
        addHelpText("shift- Double speed");
        addHelpText("num+ - Increase scale");
        addHelpText("num- - Decrease scale");
        addHelpText("F1   - Toggle help");
        addHelpText("F2   - Toggle wire");
        addHelpText("F3   - Toggle debug");
        addHelpText("F4   - Toggle BBox");
        addHelpText("F12  - Toggle console");
        addHelpText("Esc  - Quit");

        setGUIEnabled(true);

        getGUISystem()->setDefaultMouseCursor(
                (CEGUI::utf8*)"TaharezLook", (CEGUI::utf8*)"MouseArrow");


        string meshName = getConfigFile()->getSetting("InitialMesh","Options");

        if(!meshName.empty())
        {
            TFile f = meshName;

            m_entity = loadEntity(f.get_basename_wo_extension(),"General",meshName,NULL);
            //m_entity->getNode()->scale(0.05,0.05,0.05);
            m_entity->setPos(0,0,0);
        }

        getRenderEngine()->getCamera("Default")->enableMovement(true);
        getRenderEngine()->getCamera("Default")->enableMouseMovement(true);

        //
        // load backplane image if specified
        //
        string bpimage = getConfigFile()->getSetting("BackPlane","Options");

        if(!bpimage.empty())
        {
            m_background = new Tubras::TCardNode("Background",getRenderEngine()->getRootNode());
            m_background->setImage("General",bpimage);
        }

        //
        // create open mesh dialog
        //


        TSearchPath sp;
        TSearchPath::TResults res;
        vector_string files;
        vector_string meshfiles;

        TFile file("resources/models");
        file.scan_directory(files);

        for(int i=0;i<(int)files.size();i++)
        {
            TFile f = files[i];
            if(f.get_extension() == "mesh")
                meshfiles.push_back(f);
        }

        //
        // "meshfiles" contains all files with ".mesh" extension
        //

        m_meshDlg = new TMeshDlg(getGUISheet(),meshfiles);        
        return 0;
    }
};

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
{
    char    **argv=__argv;
    int     argc=__argc;
#else
extern "C" {
    int main(int argc, char **argv)
    {
#endif

        TMeshViewer app(argc,argv);

        if(!app.initialize())
            app.run();

        return 0;

    }

