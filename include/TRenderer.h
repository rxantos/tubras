//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TRENDERER_H_
#define _TRENDERER_H_

namespace Tubras
{
    class TRenderer : public IReferenceCounted, public TDelegate
    {
        friend class TApplication;
    protected:
        IrrlichtDevice*         m_device;
        IVideoDriver*           m_videoDriver;
        ISceneManager*          m_sceneManager;
        IGUIEnvironment*        m_guiManager;
        IFileSystem*            m_fileSystem;
        TCameraNode*            m_defaultCamera;
        TBackgroundNode*        m_backgroundNode;
        TNodeFactory*           m_nodeFactory;
        TGUIFactory*            m_guiFactory;
        IGUISkin*               m_guiSkin;
        IGUIFont*               m_defaultFont;
        IGUIFont*               m_monoFont;
        TGUICursor*             m_guiCursor;
        TColor                  m_bgColor;
        TRenderMode             m_renderMode;
        TRecti                  m_screenRect;
        s32                     m_capNumber;
        E_DEBUG_SCENE_TYPE      m_debugMode;
        void*                   m_display;
        void*                   m_windowId;
        void*                   m_glxContext;
        void*                   m_visual;
        IImage*                 m_whiteImage;
        ITexture*               m_whiteTexture;
        bool                    m_guiCursorEnabled;

    protected:
        void updateRenderMode(ISceneNode* node);
        void updateDebugMode(ISceneNode* node);
        void logDebugInfo();
        TRenderer();
        virtual ~TRenderer();
        int initialize();
        bool renderFrame();

    public:
        IrrlichtDevice* getDevice() {return m_device;}
        ISceneManager* getSceneManager() {return m_sceneManager;}
        IGUIEnvironment* getGUIManager() {return m_guiManager;}
        IVideoDriver* getVideoDriver() {return m_videoDriver;}
        IFileSystem* getFileSystem() {return m_fileSystem;}
        TGUIFactory* getGUIFactory() {return m_guiFactory;}

        ICameraSceneNode* getActiveCamera();
        ICameraSceneNode* getDefaultCamera() {return m_defaultCamera;}

        TColor getBGColor() {return m_bgColor;}
        void setBGColor(const TColor& value) {m_bgColor = value;}

        IImage* getWhiteImage() {return m_whiteImage;}
        ITexture* getWhiteTexture() {return m_whiteTexture;}

        void setBackgroundNode(TBackgroundNode* value) {m_backgroundNode = value;}
        void setRenderMode(TRenderMode value);
        void setDebugMode(E_DEBUG_SCENE_TYPE debugMode);
        TRenderMode getRenderMode();
        void captureScreen();
        TRecti getScreenRect() {return m_screenRect;}

        TGUICursor* getGUICursor() {return m_guiCursor;}
        void setGUICursorEnabled(bool value) {m_guiCursorEnabled=value;}
        bool getGUICursorEnabled() {return m_guiCursorEnabled;}

        ITimer* getTimer();
    };

}
#endif
