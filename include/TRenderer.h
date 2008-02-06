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
        TCameraNode*            m_camera;
        TNodeFactory*           m_nodeFactory;
        IGUIFont*               m_defaultFont;
        IGUIFont*               m_monoFont;
        TColour                 m_bgColour;
        TRenderMode             m_renderMode;
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
        void* createXWindow(const SIrrlichtCreationParameters& cp);

    public:
        TRenderer();
        virtual ~TRenderer();

        IrrlichtDevice* getDevice() {return m_device;}
        ISceneManager* getSceneManager() {return m_sceneManager;}
        IGUIEnvironment* getGUIManager() {return m_guiManager;}
        IVideoDriver* getVideoDriver() {return m_videoDriver;}
        IFileSystem* getFileSystem() {return m_fileSystem;}

        TCameraNode* getCamera() {return m_camera;}

        TColour getBGColour() {return m_bgColour;}
        void setBGColour(TColour value) {m_bgColour = value;}

        int initialize();
        bool renderFrame();

        void setRenderMode(TRenderMode value);
        void setDebugMode(E_DEBUG_SCENE_TYPE debugMode);
        TRenderMode getRenderMode();
        void captureScreen();

        ITimer* getTimer();
    };

}
#endif
