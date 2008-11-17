//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                            T O b j e c t
    //-----------------------------------------------------------------------
    TObject::TObject() : m_app(getApplication())
    {
    }

    //-----------------------------------------------------------------------
    //                           ~ T O b j e c t
    //-----------------------------------------------------------------------
    TObject::~TObject()
    {
    }

    //-----------------------------------------------------------------------
    //                           g e t A p p C o n f i g
    //-----------------------------------------------------------------------
#ifdef USE_ISL_SCRIPT
    CISL* TObject::getAppConfig()
#else
    CLSL* TObject::getAppConfig()
#endif
    {
        if(!m_app)
            initialize();
        if(!m_app)
            return 0;
        return m_app->getConfig();
    }

    //-----------------------------------------------------------------------
    //                           i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TObject::initialize()
    {
        m_app = getApplication();
        return 0;
    }

    //-----------------------------------------------------------------------
    //                      g e t R o o t S c e n e N o d e
    //-----------------------------------------------------------------------
    ISceneNode* TObject::getRootSceneNode()
    {
        return m_app->getRenderer()->getSceneManager()->getRootSceneNode();
    }

    //-----------------------------------------------------------------------
    //                      g e t S c e n e M a n a g e r
    //-----------------------------------------------------------------------
    ISceneManager* TObject::getSceneManager()
    {
        return m_app->getRenderer()->getSceneManager();
    }

    //-----------------------------------------------------------------------
    //                      g e t F i l e S y s t e m
    //-----------------------------------------------------------------------
    IFileSystem* TObject::getFileSystem()
    {
        return m_app->getRenderer()->getDevice()->getFileSystem();
    }

    //-----------------------------------------------------------------------
    //                        g e t G U I M a n a g e r
    //-----------------------------------------------------------------------
    IGUIEnvironment* TObject::getGUIManager()
    {
        return m_app->getRenderer()->getGUIManager();
    }

    //-----------------------------------------------------------------------
    //                        g e t R e n d e r e r
    //-----------------------------------------------------------------------
    TRenderer* TObject::getRenderer()
    {
        return m_app->getRenderer();
    }

    //-----------------------------------------------------------------------
    //                         g e t T e x t u r e
    //-----------------------------------------------------------------------
    ITexture* TObject::getTexture(const TString& name)
    {
        return m_app->getRenderer()->getVideoDriver()->getTexture(name.c_str());
    }

    //-----------------------------------------------------------------------
    //                    s e t C u r s o r V i s i b l e
    //-----------------------------------------------------------------------
    void TObject::setCursorVisible(bool value)
    {
        m_app->getRenderer()->getDevice()->getCursorControl()->setVisible(value);
    }

    //-----------------------------------------------------------------------
    //                        s e n d E v e n t
    //-----------------------------------------------------------------------
    bool TObject::sendEvent(TEvent* event)
    {
        return m_app->getEventManager()->send(event) ? true : false;
    }

    //-----------------------------------------------------------------------
    //                        q u e u e E v e n t
    //-----------------------------------------------------------------------
    bool TObject::queueEvent(TEvent* event)
    {
        return m_app->getEventManager()->queue(event) ? true : false;
    }

    //-----------------------------------------------------------------------
    //                        l o g M e s s a g e
    //-----------------------------------------------------------------------
    void TObject::logMessage(const TString& msg)
    {
        m_app->logMessage(msg);
    }

    //-----------------------------------------------------------------------
    //                        a c c e p t E v e n t
    //-----------------------------------------------------------------------
    u32 TObject::acceptEvent(const TString& eventMsg, TEventDelegate* callback,
        const void *extraData, int priority,bool enabled)
    {
        u32 id = 0;

        if(getEventManager())
            id = getEventManager()->accept(eventMsg,callback,extraData,priority,enabled);
        return id;
    }

    //-----------------------------------------------------------------------
    //                        r e g i s t e r E v e n t
    //-----------------------------------------------------------------------
    u32 TObject::registerEvent(const TString& eventName)
    {
        u32 id=0;

        if(getEventManager())
            id = getEventManager()->registerEvent(eventName);

        return id;
    }

    //-----------------------------------------------------------------------
    //                        d i s a b l e E v e n t s
    //-----------------------------------------------------------------------
    int TObject::disableEvents(void *classInstance)
    {
        int result = 0;
        if(getEventManager())
            result = getEventManager()->disable(classInstance);
        return result;
    }

    //-----------------------------------------------------------------------
    //                        e n a b l e E v e n t s
    //-----------------------------------------------------------------------
    int TObject::enableEvents(void *classInstance)
    {
        int result = 0;
        if(getEventManager())
            result = getEventManager()->enable(classInstance);
        return result;
    }

    //-----------------------------------------------------------------------
    //                        a d d S c e n e N o d e
    //-----------------------------------------------------------------------
    ISceneNode* TObject::addSceneNode(const char* sceneNodeTypeName, 
        ISceneNode* parent)
    {
        return getSceneManager()->addSceneNode(sceneNodeTypeName,parent);
    }

    //-----------------------------------------------------------------------
    //                          l o a d S o u n d
    //-----------------------------------------------------------------------
    TSound* TObject::loadSound(const TString& fileName, bool positional)
    {
        return getApplication()->getSoundManager()->getSound(fileName,positional);
    }

    //-----------------------------------------------------------------------
    //                       s e t R e n d e r M o d e
    //-----------------------------------------------------------------------
    void TObject::setRenderMode(TRenderMode value)
    {
        getApplication()->getRenderer()->setRenderMode(value);
    }

    //-----------------------------------------------------------------------
    //                       g e t R e n d e r M o d e
    //-----------------------------------------------------------------------
    TRenderMode TObject::getRenderMode()
    {
        return getApplication()->getRenderer()->getRenderMode();
    }

    //-----------------------------------------------------------------------
    //                       g e t G U I F a c t o r y
    //-----------------------------------------------------------------------
    TGUIFactory* TObject::getGUIFactory()
    {
        return getRenderer()->getGUIFactory();
    }

    //-----------------------------------------------------------------------
    //                          l o a d M o d e l
    //-----------------------------------------------------------------------
    IAnimatedMeshSceneNode* TObject::loadModel(const TString& fileName,ISceneNode* parent, const TString& name)
    {
        static int modelnum=0;
        IAnimatedMeshSceneNode* result = 0;
        TString aname=name;

        if(name == "default")
        {
            TStrStream str;
            str << "model" << modelnum++;
            aname = str.str().c_str();
        }

        IAnimatedMesh* pmesh  = getSceneManager()->getMesh(fileName.c_str());
        if(pmesh)
        {
            result = getSceneManager()->addAnimatedMeshSceneNode(pmesh, parent);   
            result->setName(aname.c_str());
        }
        return result;
    }

    //-----------------------------------------------------------------------
    //                   s e t C o n t r o l l e r E n a b l e d
    //-----------------------------------------------------------------------
    void TObject::setControllerEnabled(const TString controllerName, const bool value)
    {

    }

    //-----------------------------------------------------------------------
    //                  a c c e p t E v e n t T o S c r i p t
    //-----------------------------------------------------------------------
    u32 TObject::acceptEventToScript(const TString eventMsg, const void* scriptFunc)
    {
        u32 id = 0;
        TEventDelegate* pd = m_app->getScriptManager()->getEventDelegate();

        acceptEvent(eventMsg,pd,scriptFunc);

        return id;
    }

    //-----------------------------------------------------------------------
    //                        s e t B G C o l o u r
    //-----------------------------------------------------------------------
    void TObject::setBGColour(const TColour& value)
    {
        m_app->getRenderer()->setBGColour(value);
    }


}
