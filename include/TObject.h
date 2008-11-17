//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TOBJECT_H_
#define _TOBJECT_H_

namespace Tubras
{
    class TEvent;

    class TObject
    {
    protected:
        TApplication*           m_app;

    public:
        TObject();
        virtual ~TObject();
        int initialize();

#ifdef USE_ISL_SCRIPT
        CISL* getAppConfig();
#else
        CLSL* getAppConfig();
#endif
        virtual ISceneNode* getRootSceneNode();
        virtual ISceneManager* getSceneManager();
        virtual IGUIEnvironment* getGUIManager();
        virtual IFileSystem* getFileSystem();
        virtual TRenderer* getRenderer();
        virtual ITexture* getTexture(const TString& name);
        virtual TGUIFactory* getGUIFactory();

        virtual void setCursorVisible(bool value);
        virtual bool sendEvent(TEvent* event);
        virtual bool queueEvent(TEvent* event);
        virtual void logMessage(const TString& msg);

        u32 acceptEvent(const TString& eventMsg,TEventDelegate* callback,const void *extraData=0,
                    int priority=0,bool enabled=true);

        u32 acceptEventToScript(const TString eventMsg, const void* scriptFunc);

        u32 registerEvent(const TString& eventName);
        int disableEvents(void *classInstance);
        int enableEvents(void *classInstance);

        virtual void setRenderMode(TRenderMode value);
        virtual TRenderMode getRenderMode();

        ISceneNode* addSceneNode(const char* sceneNodeTypeName, ISceneNode* parent=0);

        TSound* loadSound(const TString& fileName, bool positional=false);
        IAnimatedMeshSceneNode* loadModel(const TString& fileName, ISceneNode* parent=0, const TString& name="default");

        void setControllerEnabled(const TString controllerName, const bool value);

        void setBGColour(const TColour& value);



    };

}
#endif
