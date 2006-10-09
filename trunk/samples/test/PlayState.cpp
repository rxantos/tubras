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
#include "test.h"

#define speed_delta 5.0f

//-----------------------------------------------------------------------
//                         T P l a y S t a t e
//-----------------------------------------------------------------------
TPlayState::TPlayState() : TState("playState")
{
}

//-----------------------------------------------------------------------
//                        ~ T P l a y S t a t e
//-----------------------------------------------------------------------
TPlayState::~TPlayState()
{
    if(m_interval)
        delete m_interval;

    if(m_finterval)
        delete m_finterval;

    if(sound)
        delete sound;
    if(sound2)
        delete sound2;
    if(sound3)
        delete sound3;
    if(sound4)
        delete sound4;
    if(sound5)
        delete sound5;
    if(m_rect)
        delete m_rect;

    if(m_parent)
        delete m_parent;

}

//-----------------------------------------------------------------------
//                            e s c a p e
//-----------------------------------------------------------------------
int TPlayState::escape(Tubras::TSEvent event)
{
    popState();
    return 0;
}

//-----------------------------------------------------------------------
//                         p l a y G u n S h o t
//-----------------------------------------------------------------------
int TPlayState::playGunShot(Tubras::TSEvent event)
{
    sound2->play();
    return 0;
}

//-----------------------------------------------------------------------
//                             f l a s h
//-----------------------------------------------------------------------
int TPlayState::flash(Tubras::TSEvent event)
{
    m_flashstate = 1;
    return 0;
}

//-----------------------------------------------------------------------
//                         a d j u s t S p e e d
//-----------------------------------------------------------------------
int TPlayState::adjustSpeed(Tubras::TSEvent event)
{
    if(event->getUserData())
        m_speed += speed_delta;
    else m_speed -= speed_delta;
    return 0;
}

//-----------------------------------------------------------------------
//                           p l a y D o n e
//-----------------------------------------------------------------------
int TPlayState::playDone(Tubras::TSEvent event)
{
    logMessage("playDone() invoked");
    return 0;
}

//-----------------------------------------------------------------------
//                            p r o c K e y
//-----------------------------------------------------------------------
int TPlayState::procKey(Tubras::TSEvent event)
{
    printf("procKey invoked\n");
    return 0;
}

//-----------------------------------------------------------------------
//                        i n t e r v a l D o n e
//-----------------------------------------------------------------------
int TPlayState::intervalDone(Tubras::TSEvent event)
{
    m_finterval->start();
    return 0;
}

//-----------------------------------------------------------------------
//                           t e s t T a s k
//-----------------------------------------------------------------------
int TPlayState::testTask(Tubras::TTask* task)
{
    if(m_interval->isPlaying() && getDebug())
    {
        double t = m_interval->getT();
        char msg[128];

        sprintf(msg,"Interval get_t(): %.5f",t);
        logMessage(msg);
    }

    ULONG curtime = m_globalClock->getMilliseconds();
    float delta = curtime - m_starttime;
    m_starttime = curtime;

    m_degrees = (m_speed * (delta/1000.0f));

    Ogre::Quaternion q(Ogre::Degree(m_degrees),TVector3::UNIT_Y);
    if(m_cube)
        m_cube->rotate(q,Ogre::Node::TS_LOCAL);

    std::list<Tubras::TSceneNode*>::iterator itr = m_cardNodes.begin();
    while(itr != m_cardNodes.end())
    {
        m_cardParent = *itr;
        Ogre::Quaternion q(Ogre::Degree(-m_degrees),TVector3::UNIT_Y);
        m_cardParent->rotate(q,Ogre::Node::TS_LOCAL);
        ++itr;
    }


    if((m_globalClock->getMilliseconds() - m_time) >= 1000)
    {
        //logMessage("tick");
        m_time = m_globalClock->getMilliseconds();
        ++m_counter;
    }

    if(m_counter == 15)
    {
        sound3->play();
        m_flashstate = 1;
        m_counter = 0;
    }

    if(!m_material.isNull())
    {
        switch(m_flashstate)
        {
        case 1:
            m_material->setAmbient(1,1,1);
            m_flashstate = 2;
            m_flashtime = m_globalClock->getMilliseconds();
            break;
        case 2:
            delta = curtime - m_flashtime;
            if(delta > 50)
            {
                m_material->setAmbient(0.5,0.5,0.5);
                m_flashstate = 3;
                m_flashtime = curtime;
            }
        case 3:
            delta = curtime - m_flashtime;
            if(delta > 100)
            {
                m_material->setAmbient(1,1,1);
                m_flashstate = 4;
                m_flashtime = curtime;
            }
        case 4:
            delta = curtime - m_flashtime;
            if(delta > 150)
            {
                m_material->setAmbient(0.5,0.5,0.5);
                m_flashstate = 5;
                m_flashtime = curtime;
            }
        case 5:
            delta = curtime - m_flashtime;
            if(delta > 150)
            {
                m_material->setAmbient(1,1,1);
                m_flashstate = 6;
                m_flashtime = curtime;
            }
        case 6:
            delta = curtime - m_flashtime;
            if(delta > 150)
            {
                m_material->setAmbient(0.5,0.5,0.5);
                ++m_flashstate2;
                if(m_flashstate2 != 2)
                    m_flashstate = 1;
                else
                {
                    m_flashstate2 = 0;
                    m_flashstate = 0;
                }
                m_flashtime = curtime;
            }


        }
    }

    return Tubras::TTask::cont;
}

//-----------------------------------------------------------------------
//                        f u n c I n t e r v a l
//-----------------------------------------------------------------------
void TPlayState::funcInterval(double T, void* userData)
{
    char msg[128];

    if(getDebug())
    {
        sprintf(msg,"funcInterval T: %.3f",T);
        logMessage(msg);
    }
}

//-----------------------------------------------------------------------
//                          c r e a t e C a r d
//-----------------------------------------------------------------------
Tubras::TSceneNode* TPlayState::createCard(int number,TVector3 pos,Ogre::SceneManager* sm)
{
    TStrStream ename;

    Tubras::TEntityNode* node;

    ename << "CardEntity" << number;
    node = loadEntity(ename.str(),"General","Card.mesh",m_parent);
    node->getSubEntity(1)->setVisible(true);
    node->setPosition(pos);

    return node;

}

//-----------------------------------------------------------------------
//                          c r e a t e S c e n e
//-----------------------------------------------------------------------
void TPlayState::createScene()
{        
    int ri;
    float rf;

    ri = getRandomInt(100);

    rf = getRandomFloat();


    Ogre::SceneManager* sm = m_app->getRenderEngine()->getSceneManager();


    m_parent = createSceneNode("PlayParent");

    // load background texture
    Tubras::TMaterial* material = loadTexture("Background","General","rockwall.tga");

    // Create background rectangle covering the whole screen
    m_rect = new Ogre::Rectangle2D(true);
    m_rect->setCorners(-1.0, 1.0, 1.0, -1.0);
    m_rect->setMaterial("Background");
    m_rect->setCastShadows(false);
    m_rect->getTechnique()->getPass(0)->setDepthCheckEnabled(false);
    m_rect->getTechnique()->getPass(0)->setDepthWriteEnabled(false);


    // Render the background before everything else
    m_rect->setRenderQueueGroup(Ogre::RENDER_QUEUE_BACKGROUND);

    // Use infinite AAB to always stay visible
    Ogre::AxisAlignedBox aabInf;
    aabInf.setInfinite();
    m_rect->setBoundingBox(aabInf);

    // Attach background to the scene
    m_parent->attachObject(m_rect);

    // save texture unit state to manipulate scrolling later on.
    m_backTextureUnitState = material->getMat()->getTechnique(0)->getPass(0)->getTextureUnitState(0);

    //
    // setup rotating cube
    //
    m_cube = loadEntity("Cube", "General", "Cube.mesh", m_parent);
    m_material = m_cube->getSubEntity(0)->getMaterial();
    m_material->setAmbient(0.3,0.3,0.3);
    m_cube->setPosition(Ogre::Vector3(0,0,5));

    m_degrees = 0.0f;

    //
    // setup card
    //
    Tubras::TSceneNode* snp;
    snp = createCard(0,TVector3(-6,3.5,-3),sm);
    m_cardNodes.push_back(snp);

    snp = createCard(1,TVector3(-3,3.5,-3),sm);
    m_cardNodes.push_back(snp);

    snp = createCard(2,TVector3(0,3.5,-3),sm);
    m_cardNodes.push_back(snp);

    snp = createCard(3,TVector3(3,3.5,-3),sm);
    m_cardNodes.push_back(snp);

    snp = createCard(4,TVector3(6,3.5,-3),sm);
    m_cardNodes.push_back(snp);

    snp = createCard(5,TVector3(-6,0,-3),sm);
    m_cardNodes.push_back(snp);

    snp = createCard(6,TVector3(-3,0,-3),sm);
    m_cardNodes.push_back(snp);

    snp = createCard(7,TVector3(0,0,-3),sm);
    m_cardNodes.push_back(snp);

    snp = createCard(8,TVector3(3,0,-3),sm);
    m_cardNodes.push_back(snp);

    snp = createCard(10,TVector3(6,0,-3),sm);
    m_cardNodes.push_back(snp);

    snp = createCard(11,TVector3(-6,-3.5,-3),sm);
    m_cardNodes.push_back(snp);

    snp = createCard(12,TVector3(-3,-3.5,-3),sm);
    m_cardNodes.push_back(snp);

    snp = createCard(13,TVector3(0,-3.5,-3),sm);
    m_cardNodes.push_back(snp);

    snp = createCard(14,TVector3(3,-3.5,-3),sm);
    m_cardNodes.push_back(snp);

    snp = createCard(15,TVector3(6,-3.5,-3),sm);
    m_cardNodes.push_back(snp);

    m_degrees = 0.0f;

    //
    // set up key event handlers
    //
    m_flashDelegate = EVENT_DELEGATE(TPlayState::flash);
    acceptEvent("key.down.f",m_flashDelegate,NULL,0,false);

    m_toggleDelegate = EVENT_DELEGATE(TPlayState::toggleParent);
    acceptEvent("key.down.h",m_toggleDelegate,NULL,0,false);

    m_speedDelegate = EVENT_DELEGATE(TPlayState::adjustSpeed);
    acceptEvent("key.down.subtract",m_speedDelegate,(void *)1,0,false);
    acceptEvent("key.down.add",m_speedDelegate,(void *)0,0,false);

    //
    // create gui overlay
    //

    m_GUIRoot = new Tubras::TWindow(getGUISheet(),"rootPlay");
    m_GUIRoot->setVisible(false);

    m_frame = new Tubras::TStaticImage(m_GUIRoot,"control_wnd","hud.png");
    m_frame->setPosition(0.125,0.82);
    m_frame->setSize(0.75,0.14);

    m_frame = new Tubras::TStaticImage(m_GUIRoot,"Ready","ready.png");
    m_frame->setPosition(0.16,0.85);
    m_frame->setSize(0.1,0.08);

}

//-----------------------------------------------------------------------
//                        t o g g l e P a r e n t
//-----------------------------------------------------------------------
int TPlayState::toggleParent(Tubras::TSEvent event)
{

    m_parent->flipVisibility();
    return 0;
}


//-----------------------------------------------------------------------
//                         i n i t i a l i z e
//-----------------------------------------------------------------------
int TPlayState::initialize()
{
    sound = sound2 = sound3 = NULL;
    m_flashstate = 0;
    m_cubeParent = NULL;
    m_material.setNull();
    m_rect = NULL;
    m_cubeNode = NULL;

    //
    // invoke TApplication initialize which initializes all of the
    // sub-systems (render, sound, input etc.)
    //
    if(TState::initialize())
        return 1;

    //
    // add key event handlers. delegate will be automatically destroyed
    // when the event handler is removed.
    //
    // note that we only need to save a reference to the delegate if we
    // want to remove it before the application terminates. otherwise
    // it is automatically deleted on termination.
    //

    m_quitDelegate = EVENT_DELEGATE(TPlayState::escape);
    acceptEvent("key.down.esc",m_quitDelegate,NULL,0,false);

    m_playGunShotDelegate = EVENT_DELEGATE(TPlayState::playGunShot);
    acceptEvent("key.down.g",m_playGunShotDelegate,NULL,0,false);

    //
    // add a task. delegate will be automatically destroyed 
    // when the task is terminated.
    //
    m_time = m_globalClock->getMilliseconds();
    m_counter = 0;

    m_testTask = new Tubras::TTask("testTask",TASK_DELEGATE(TPlayState::testTask),0,0,NULL,"testTaskDone");

    //
    // load some sounds
    //

    sound = loadSound("General", "bg4.ogg");
    sound->setLoop(true);
    sound2 = loadSound("General", "gunshot_bang.ogg");
    sound3 = loadSound("General", "lightning.ogg");

    Tubras::T1PCamera* cam = (Tubras::T1PCamera*)getRenderEngine()->getCamera("Default");
    sound4 = loadSound("General","zoom.ogg");
    sound5 = loadSound("General","zoomout.ogg");
    cam->setZoomSounds(sound4,sound5);


    //
    // notify us when ambient.ogg finishes playing.
    //
    sound->setFinishedEvent("ambient done");

    //
    // make some stuff to look at
    //

    createScene();

    //
    // set the applications initial state. ("") means we're not using 
    // the state manager - we don't really need to do this because
    // it is the default behavior.
    //

    m_app->getRenderEngine()->setBackgroundColor(TColor(0,0,0,1));

    m_app->getRenderEngine()->setAmbientLight(TColor(1,1,1,1));

    m_starttime = m_globalClock->getMilliseconds();
    m_speed = -90.0f;

    m_flashstate2 = 0;

    m_interval = new Tubras::TInterval("testInterval",3.2,false);
    m_interval->setDoneEvent("testIntervalDone");
    acceptEvent("testIntervalDone",EVENT_DELEGATE(TPlayState::intervalDone));

    //m_mouseDelegate = EVENT_DELEGATE(TPlayState::intervalDone);
    //acceptEvent("input.mousedown.0",m_mouseDelegate,NULL,0,false);

    m_finterval = new Tubras::TFunctionInterval("testFuncInterval",5.0,
        FUNCINT_DELEGATE(TPlayState::funcInterval));

    m_finterval->setDoneEvent("testFuncIntervalDone");

    //m_interval->start();

    setGUIEnabled(false);

    m_parent->flipVisibility();

    //
    // initially disable all events this class instance is
    // listening for.
    //
    disableEvents(this);

    return 0;
}

//-----------------------------------------------------------------------
//                            E n t e r
//-----------------------------------------------------------------------
int TPlayState::Enter()
{
    getRenderEngine()->getCamera("Default")->enableMovement(true);
    getRenderEngine()->getCamera("Default")->setPosition(TVector3(0,3,12));
    getRenderEngine()->getCamera("Default")->lookAt(TVector3(0,0,0));
    m_GUIRoot->setVisible(true);
    getGUISystem()->injectMouseMove(0,0);
    setGUIEnabled(true);

    m_backTextureUnitState->setScrollAnimation(-0.1, 0.0);
    m_backTextureUnitState->setRotateAnimation(0.05);
    sound->play();

    enableEvents(this);

    m_testTask->start();
    m_parent->flipVisibility();
    return 0;
}

//-----------------------------------------------------------------------
//                              E x i t
//-----------------------------------------------------------------------
Tubras::TStateInfo* TPlayState::Exit()
{
    sound->stop();
    m_testTask->stop();
    m_backTextureUnitState->setScrollAnimation(0.0, 0.0);
    m_backTextureUnitState->setRotateAnimation(0.0);
    disableEvents(this);
    m_parent->flipVisibility();
    m_GUIRoot->setVisible(false);
    getRenderEngine()->getCamera("Default")->enableMovement(false);
    return &m_info;
}

//-----------------------------------------------------------------------
//                             R e s e t
//-----------------------------------------------------------------------
int TPlayState::Reset()
{
    return 0;
}

//-----------------------------------------------------------------------
//                             P a u s e
//-----------------------------------------------------------------------
int TPlayState::Pause()
{
    return 0;
}

//-----------------------------------------------------------------------
//                             R e s u m e
//-----------------------------------------------------------------------
int TPlayState::Resume(Tubras::TStateInfo* prevStateInfo)
{
    return 0;
}


