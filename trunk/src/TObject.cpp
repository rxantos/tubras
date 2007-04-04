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

static size_t  m_modelnum = 1;
static size_t  m_actornum = 1;

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                            T O b j e c t
    //-----------------------------------------------------------------------
    TObject::TObject()
    {
        m_app = getApplication();
    }

    //-----------------------------------------------------------------------
    //                           ~ T O b j e c t
    //-----------------------------------------------------------------------
    TObject::~TObject()
    {
    }

    //-----------------------------------------------------------------------
    //                          i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TObject::initialize()
    {
        if(!m_app)
            m_app = getApplication();
        m_globalClock = m_app->getGlobalClock();
        return 0;
    }

    //-----------------------------------------------------------------------
    //                           r e m o v e T a s k
    //-----------------------------------------------------------------------
    int TObject::removeTask(TString taskName)
    {
        return m_app->getTaskManager()->remove(taskName);
    }

    //-----------------------------------------------------------------------
    //                           r e m o v e T a s k
    //-----------------------------------------------------------------------
    int TObject::removeTask(TTask* task)
    {
        return m_app->getTaskManager()->remove(task);
    }


    //-----------------------------------------------------------------------
    //                           l o a d S o u n d
    //-----------------------------------------------------------------------
    TSound* TObject::loadSound(TString soundFileName,TString resourceGroup, bool positional)
    {
        return m_app->getSoundManager()->getSound(soundFileName, resourceGroup, positional);
    }

    //-----------------------------------------------------------------------
    //                         l o a d M o d e l
    //-----------------------------------------------------------------------
    TModelNode* TObject::loadModel(TString meshFileName, TString resourceGroup, TString name, 
        TSceneNode* parent, bool isStatic)
    {
        TModelNode*   model=NULL;

        if(!name.compare("default"))
        {
            TStrStream sname;
            sname << "model" << m_modelnum;
            ++m_modelnum;

            name = sname.str();
        }

        model = new TModelNode(name,resourceGroup,meshFileName,parent,isStatic);

        return model;
    }

    //-----------------------------------------------------------------------
    //                          l o a d A c t o r
    //-----------------------------------------------------------------------
    TActorNode* TObject::loadActor(TString meshFileName, TString resourceGroup,TString name, TSceneNode* parent)
    {
        TActorNode*   actor=NULL;

        if(!name.compare("default"))
        {
            TStrStream sname;
            sname << "actor" << m_actornum;
            ++m_actornum;

            name = sname.str();
        }

        actor = new TActorNode(name,resourceGroup,meshFileName,parent);

        return actor;
    }



    //-----------------------------------------------------------------------
    //                         c r e a t e S c e n e N o d e
    //-----------------------------------------------------------------------
    TSceneNode* TObject::createSceneNode(TString name,TSceneNode* parent)
    {
        return new TSceneNode(name,parent);
    }

    //-----------------------------------------------------------------------
    //                         c r e a t e M a t e r i a l
    //-----------------------------------------------------------------------
    TMaterial* TObject::createMaterial(TString name, TString resourceGroup)
    {
        TMaterial* mat;
        mat = new TMaterial(name,resourceGroup);
        return mat;
    }

    //-----------------------------------------------------------------------
    //                            l o a d T e x t u r e
    //-----------------------------------------------------------------------
    TMaterial* TObject::loadTexture(TString name, TString resourceGroup, TString imageName)
    {
        TMaterial* mat;
        mat = new TMaterial(name,resourceGroup);
        mat->loadImage(imageName,0);
        return mat;
    }

    //-----------------------------------------------------------------------
    //                         u n l o a d M a t e r i a l
    //-----------------------------------------------------------------------
    void TObject::unloadMaterial(TString name)
    {
        Ogre::MaterialManager::getSingleton().remove(name);
    }

    //-----------------------------------------------------------------------
    //                         g e t R a n d o m I n t
    //-----------------------------------------------------------------------
    int TObject::getRandomInt(int n)
    {
        return m_app->getRNG()->getRandomInt(n);
    }

    //-----------------------------------------------------------------------
    //                      g e t R a n d o m F l o a t
    //-----------------------------------------------------------------------
    float TObject::getRandomFloat()
    {
        return m_app->getRNG()->getRandomFloat();
    }

    //-----------------------------------------------------------------------
    //                        l o g M e s s a g e
    //-----------------------------------------------------------------------
    void TObject::logMessage(const char* msg)
    {
        m_app->logMessage(msg);
    }

    //-----------------------------------------------------------------------
    //                         g e t D e b u g 
    //-----------------------------------------------------------------------
    bool TObject::getDebug()
    {
        return m_app->getDebug();
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
    //                 r e m o v e E v e n t D e l e g a t e
    //-----------------------------------------------------------------------
    int TObject::removeEventDelegate(TEventDelegate* callback)
    {
        if(getEventManager())
            getEventManager()->remove(callback);
        return 0;
    }

    //-----------------------------------------------------------------------
    //                 d e s t r o y E v e n t D e l e g a t e
    //-----------------------------------------------------------------------
    int TObject::destroyEventDelegate(TEventDelegate* callback)
    {
        if(getEventManager())
            getEventManager()->destroy(callback);
        return 0;
    }

    //-----------------------------------------------------------------------
    //                         s e n d E v e n t
    //-----------------------------------------------------------------------
    int TObject::sendEvent(TSEvent& event)
    {
        if(getEventManager())
            return getEventManager()->send(event);
        return 0;
    }

    //-----------------------------------------------------------------------
    //                        q u e u e E v e n t
    //-----------------------------------------------------------------------
    int TObject::queueEvent(TSEvent& event)
    {
        if(getEventManager())
            return getEventManager()->queue(event);
        return 0;
    }
    //-----------------------------------------------------------------------
    //                      s e t E v e n t P r e f i x 
    //-----------------------------------------------------------------------
    TString TObject::setEventPrefix(TString value)
    {
        if(getEventManager())
            return getEventManager()->setEventPrefix(value);
        return "";
    }

    //-----------------------------------------------------------------------
    //             s e t E v e n t D e l e g a t e P r i o r i t y
    //-----------------------------------------------------------------------
    int TObject::setEventDelegatePriority(TEventDelegate* callback, int priority)
    {
        callback->setPriority(priority);
        //
        // todo: notify event manager - priority update
        //
        return 0;
    }

    //-----------------------------------------------------------------------
    //             s e t E v e n t D e l e g a t e E n a b l e d
    //-----------------------------------------------------------------------
    int TObject::setEventDelegateEnabled(TEventDelegate* callback, bool enabled)
    {
        callback->setEnabled(enabled);
        return 0;
    }

    //-----------------------------------------------------------------------
    //                   g e t R e n d e r E n g i n e
    //-----------------------------------------------------------------------
    TRenderEngine* TObject::getRenderEngine()
    {
        return getApplication()->getRenderEngine();
    }

    //-----------------------------------------------------------------------
    //                s e t C o n t r o l l e r E n a b l e d
    //-----------------------------------------------------------------------
    void TObject::setControllerEnabled(TString controllerName, bool value)
    {
        TControllerManager::getSingleton().setControllerEnabled(controllerName,value);
    }

    //-----------------------------------------------------------------------
    //           s e t N o d e C o n t r o l l e r s E n a b l e d
    //-----------------------------------------------------------------------
    void TObject::setNodeControllersEnabled(TString nodeName, bool value)
    {
        TControllerManager::getSingleton().setNodeControllersEnabled(nodeName,value);
    }

    //-----------------------------------------------------------------------
    //                     g e t C o n t r o l l e r
    //-----------------------------------------------------------------------
    TController* TObject::getController(TString controllerName)
    {
        return TControllerManager::getSingleton().getController(controllerName);
    }

    //-----------------------------------------------------------------------
    //                     g e t S c e n e M a n a g e r
    //-----------------------------------------------------------------------
    TSceneManager* TObject::getSceneManager()
    {
        return getRenderEngine()->getSceneManager();
    }

    //-----------------------------------------------------------------------
    //                     g e t D y n a m i c W o r l d
    //-----------------------------------------------------------------------
    TDynamicWorld* TObject::getDynamicWorld()
    {
        return TPhysicsManager::getSingleton().getWorld();
    }

    //-----------------------------------------------------------------------
    //                         i s K e y D o w n  
    //-----------------------------------------------------------------------
    bool TObject::isKeyDown( OIS::KeyCode key )
    {
        return m_app->getInputManager()->isKeyDown(key);
    }

    //-----------------------------------------------------------------------
    //                         g e t C a m e r a
    //-----------------------------------------------------------------------
    TCameraNode* TObject::getCamera(TString name)
    {
        return getRenderEngine()->getCamera(name);
    }

    //-----------------------------------------------------------------------
    //                 s e t G U I C u r s o r V i s i b l e 
    //-----------------------------------------------------------------------
    void TObject::setGUICursorVisible(bool visible)
    {
        if(visible)
            TGUI::TGSystem::getSingleton().getMouseCursor()->show();
        else TGUI::TGSystem::getSingleton().getMouseCursor()->hide();
    }

    //-----------------------------------------------------------------------
    //                          g e t S t a t e
    //-----------------------------------------------------------------------
    TState* TObject::getState(TString stateName)
    {
        return m_app->findState(stateName);
    }


    //-----------------------------------------------------------------------
    //                 g e t G U I C u r s o r V i s i b l e 
    //-----------------------------------------------------------------------
    bool TObject::getGUICursorVisible()
    {
        return TGUI::TGSystem::getSingleton().getMouseCursor()->isVisible();
    }

    //-----------------------------------------------------------------------
    //                    r e g O p e n S e c t i o n
    //-----------------------------------------------------------------------
    int TObject::regOpenSection(TString section)
    {
        return m_app->getRegistry()->openSection(section);
    }

    //-----------------------------------------------------------------------
    //                       r e g R e a d K e y
    //-----------------------------------------------------------------------
    TString TObject::regReadKey(TString key, TString defaultValue)
    {
        return m_app->getRegistry()->readKey(key,defaultValue);
    }

    //-----------------------------------------------------------------------
    //                       r e g R e a d K e y
    //-----------------------------------------------------------------------
    int TObject::regReadKey(TString key, int defaultValue)
    {
        return m_app->getRegistry()->readKeyAsInt(key,defaultValue);
    }

    //-----------------------------------------------------------------------
    //                       r e g W r i t e K e y
    //-----------------------------------------------------------------------
    int TObject::regWriteKey(TString key,TString value)
    {
        return m_app->getRegistry()->writeKey(key,value);
    }

    //-----------------------------------------------------------------------
    //                       r e g W r i t e K e y
    //-----------------------------------------------------------------------
    int TObject::regWriteKey(TString key,int value)
    {
        return m_app->getRegistry()->writeKeyAsInt(key,value);
    }

    //-----------------------------------------------------------------------
    //                       r e g K e y E x i t s
    //-----------------------------------------------------------------------
    bool TObject::regKeyExists(TString section, TString key)
    {
        return m_app->getRegistry()->keyExists(section,key);
    }

    //-----------------------------------------------------------------------
    //                       r e g K e y E x i t s
    //-----------------------------------------------------------------------
    bool TObject::regKeyExists(TString key)
    {
        return m_app->getRegistry()->keyExists(key);
    }

    //-----------------------------------------------------------------------
    //                     d e s t r o y I n t e r v a l
    //-----------------------------------------------------------------------
    int TObject::destroyInterval(TInterval* interval)
    {

        return m_app->getIntervalManager()->destroyInterval(interval);
    }

    //-----------------------------------------------------------------------
    //                     g e t T h e m e M a n a g e r 
    //-----------------------------------------------------------------------
    TThemeManager* TObject::getThemeManager()
    {
        return m_app->getThemeManager();
    }

    //-----------------------------------------------------------------------
    //                     g e t S o u n d M a n a g e r 
    //-----------------------------------------------------------------------
    TSoundManager* TObject::getSoundManager()
    {
        return m_app->getSoundManager();
    }

    //-----------------------------------------------------------------------
    //                     g e t G U I M a n a g e r
    //-----------------------------------------------------------------------
    TGUIManager* TObject::getGUIManager()
    {
        return m_app->getGUIManager();
    }

    //-----------------------------------------------------------------------
    //                    s e t S o u n d L i s t e n e r
    //-----------------------------------------------------------------------
    void TObject::setSoundListener(TSceneNode* listener)
    {
        getSoundManager()->setListenerNode(listener);
    }

}