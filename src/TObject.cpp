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
    TXMLConfig* TObject::getAppConfig()
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
    //                         g e t T e x t u r e
    //-----------------------------------------------------------------------
    ITexture* TObject::getTexture(TString name)
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
    void TObject::logMessage(TString msg)
    {
        m_app->logMessage(msg);
    }

    //-----------------------------------------------------------------------
    //                        a c c e p t E v e n t
    //-----------------------------------------------------------------------
    size_t TObject::acceptEvent(TString eventMsg,TEventDelegate* callback,void *extraData,
        int priority,bool enabled)
    {
        size_t id = 0;

        if(getEventManager())
            id = getEventManager()->accept(eventMsg,callback,extraData,priority,enabled);
        return id;
    }

    //-----------------------------------------------------------------------
    //                        r e g i s t e r E v e n t
    //-----------------------------------------------------------------------
    size_t TObject::registerEvent(TString eventName)
    {
        size_t id=0;

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
    TSound* TObject::loadSound(TString fileName, bool positional)
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



}
