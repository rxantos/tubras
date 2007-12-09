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

}
