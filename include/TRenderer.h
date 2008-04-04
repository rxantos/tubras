//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TRENDERER_H_
#define _TRENDERER_H_

namespace Tubras
{
    class TRenderer : public IReferenceCounted, public TObject
    {
    protected:
        IrrlichtDevice*         m_device;
        IVideoDriver*           m_videoDriver;
        ISceneManager*          m_sceneManager;
        IGUIEnvironment*        m_guiManager;
        IFileSystem*            m_fileSystem;
        TCameraNode*            m_defaultCamera;
        TNodeFactory*           m_nodeFactory;
        TGUIFactory*            m_guiFactory;
        IGUISkin*               m_guiSkin;
        IGUIFont*               m_defaultFont;
        IGUIFont*               m_monoFont;
        TColour                 m_bgColour;
        TRenderMode             m_renderMode;
        TRectd                  m_screenRect;
        s32                     m_capNumber;
        E_DEBUG_SCENE_TYPE      m_debugMode;
        void*                   m_display;
        void*                   m_windowId;
        void*                   m_glxContext;
        void*                   m_visual;

    protected:
        void updateRenderMode(ISceneNode* node);
        void updateDebugMode(ISceneNode* node);
        void logDebugInfo();

    public:
        TRenderer();
        virtual ~TRenderer();

        IrrlichtDevice* getDevice() {return m_device;}
        ISceneManager* getSceneManager() {return m_sceneManager;}
        IGUIEnvironment* getGUIManager() {return m_guiManager;}
        IVideoDriver* getVideoDriver() {return m_videoDriver;}
        IFileSystem* getFileSystem() {return m_fileSystem;}
        TGUIFactory* getGUIFactory() {return m_guiFactory;}

        ICameraSceneNode* getActiveCamera();
        ICameraSceneNode* getDefaultCamera() {return m_defaultCamera;}

        TColour getBGColour() {return m_bgColour;}
        void setBGColour(const TColour& value) {m_bgColour = value;}

        int initialize();
        bool renderFrame();

        void setRenderMode(TRenderMode value);
        void setDebugMode(E_DEBUG_SCENE_TYPE debugMode);
        TRenderMode getRenderMode();
        void captureScreen();
        TRectd getScreenRect() {return m_screenRect;}

        ITimer* getTimer();
    };

}
#endif
