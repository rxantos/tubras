//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TRENDERER_H_
#define _TRENDERER_H_

namespace Tubras
{
    class IRendererListener
    {
    public:
        virtual int onDeviceCreated() = 0;
    };

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
        IRendererListener*      m_listener;
        TGUIFactory*            m_guiFactory;
        IGUISkin*               m_guiSkin;
        IGUIFont*               m_defaultFont;
        IGUIFont*               m_monoFont;
        TGUICursor*             m_guiCursor;
        TColor                  m_bgColor;
        f32                     m_debugNormalLen;
        SColor                  m_debugNormalColor;

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
        TRenderer(IRendererListener* listener=0);
        virtual ~TRenderer();
        int initialize();
        bool update();

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
