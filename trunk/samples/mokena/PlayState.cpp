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
#include "mokena.h"


#define speed_delta 5.0f

struct TCardLayout
{
    size_t      rows;
    size_t      cols;
    TReal       vgap;
    TReal       hgap;
    TReal       distance;
};

struct TCardLayout difficulty[3] = 
{
    {4,4,0.24f,0.4f,20.0f},
    {4,6,0.24f,0.4f,20.0f},
    {4,8,0.24f,0.4f,20.0f}
};

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

    //
    // delete card nodes
    //

    while(m_cardNodes.size())
    {
        TCardListItr itr = m_cardNodes.begin();
        TCardInfo* pci = *itr;
        m_cardNodes.erase(itr);
        delete pci;
    }

    delete m_cardMesh;

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

    /*
    std::list<Tubras::TSceneNode*>::iterator itr = m_cardNodes.begin();
    while(itr != m_cardNodes.end())
    {
        m_cardParent = *itr;
        Ogre::Quaternion q(Ogre::Degree(-m_degrees),TVector3::UNIT_Y);
        m_cardParent->rotate(q,Ogre::Node::TS_LOCAL);
        ++itr;
    }
    */

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
Tubras::TModelNode* TPlayState::createCard(int number,TVector3 pos,Ogre::SceneManager* sm)
{
    TStrStream ename;
    TCardInfo*  pci;

    Tubras::TModelNode* node;

    ename << "CardEntity" << number;
    node = loadModel("cardMesh","General",ename.str(),m_parent);
    node->getEntity()->getSubEntity(0)->setMaterialName("Material/SOLID/TEX/CardFront.png");
    node->getEntity()->getSubEntity(1)->setMaterialName("Material/SOLID/TEX/CardBack.png");
    node->getSubEntity(1)->setVisible(false);
    node->setPos(pos);
    pci = new TCardInfo;
    pci->m_node = node;
    pci->m_pos = pos;
    m_cardNodes.push_back(pci);

    return node;
}

//-----------------------------------------------------------------------
//                          c r e a t e C a r d s
//-----------------------------------------------------------------------
void TPlayState::createCards()
{

    Ogre::SceneManager* sm = m_app->getRenderEngine()->getSceneManager();

    m_cardMesh = new TCardMesh("cardMesh");
    m_cardMesh->initialize();

    //Ogre::MaterialPtr mptr = snp->getEntity()->getSubEntity(0)->getMaterial()->clone("testmat");

    size_t maxCards = difficulty[cmHard].cols * difficulty[cmHard].rows;
    for(size_t i=0;i<maxCards;i++)
        createCard((int)i,TVector3(0,0,-difficulty[cmHard].distance),sm);

    /*
    
    snp = createCard(2,TVector3(-3,yPos,-Dist),sm);

    snp->getEntity()->getSubEntity(0)->setMaterialName("testmat");

    Ogre::TextureUnitState* tus = snp->getEntity()->getSubEntity(0)->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0);
    Ogre::Degree d(120.f);
    Ogre::Radian r(d);
    tus->setTextureRotate(r);
    tus->setTextureScroll(0.5f,0.5f);
    string name = tus->getTextureName();
    */

}

//-----------------------------------------------------------------------
//                         l a y o u t C a r d s
//-----------------------------------------------------------------------
void TPlayState::layoutCards(int mode)
{
    TCardLayout*    plo;
    size_t          totalCards;
    size_t          i;
    TCardListItr itr;

    m_activeCards.clear();
    plo = &difficulty[mode];

    Tubras::TCameraNode* camera = getCamera("Camera::Default");
    TReal fovY = camera->getCamera()->getFOVy().valueRadians();
    TReal Dist = plo->distance;
    TReal height = tan ( fovY / 2.0f) * Dist;
    TReal yStartPos = height-HHEIGHT-plo->vgap;

    TReal cols = plo->cols;
    TReal width = (HWIDTH * cols * 2.f) + ((cols-1.0) * plo->hgap);
    TReal xStartPos = (width / -2.f) + HWIDTH;


    totalCards = plo->rows * plo->cols;
    i = 0;
    itr = m_cardNodes.begin();
    while(itr != m_cardNodes.end())
    {
        TCardInfo* pci = *itr;
        pci->m_node->getNode()->setVisible(false);
        if(i<totalCards)
            m_activeCards.push_back(pci);
        ++i;
        ++itr;
    }

    size_t x,y;
    TReal xPos,yPos;

    xPos = xStartPos;
    yPos = yStartPos;
    itr = m_activeCards.begin();
    for(y=0;y<plo->rows;y++)
    {   xPos = xStartPos;
        yPos = yStartPos - ( (y * HHEIGHT * 2) + (y * plo->vgap) );
        for(x=0;x<plo->cols;x++)
        {
            TCardInfo*pci = *itr;
            xPos = xStartPos + ( ((TReal)x * HWIDTH * 2.f) + ((TReal)x * plo->hgap) );
            pci->m_pos = TVector3(xPos,yPos,-plo->distance);
            pci->m_node->setPos(pci->m_pos);
            pci->m_node->getNode()->setVisible(true);
            ++itr;
        }
    }

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

    m_parent = createSceneNode("PlayParent");

    //
    // create background card/plane
    //
    m_background = new Tubras::TCardNode("Background",m_parent);
    m_background->setImage("General","rockwall.tga");

    m_degrees = 0.0f;

    createCards();

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

    m_GUIScreen = new TGUI::TGScreen(TGUI::TGSystem::getSingleton().getActiveScreen(),"PlayScreen");

    m_frame = new TGUI::TGImage(m_GUIScreen,"Hud","hud.png");
    m_frame->setPos(0.125f,0.82f);
    m_frame->setSize(0.75f,0.14f);

    m_frame = new TGUI::TGImage(m_frame,"Ready","ready.png");
    m_frame->setPos(0.036f,0.18f);
    m_frame->setSize(0.16f,0.64f);
    m_GUIScreen->hide();
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
//                         s a v e O p t i o n s
//-----------------------------------------------------------------------
void TPlayState::saveOptions()
{
    regOpenSection("options");
    regWriteKey("difficulty",m_playOptions.m_difficulty);
    regWriteKey("bgmusic",m_playOptions.m_bgMusic);
    regWriteKey("bgmusicvolume",m_playOptions.m_bgMusicVolume);
    regWriteKey("theme",m_playOptions.m_theme);
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
    m_cubeNode = NULL;

    //
    // invoke TApplication initialize which initializes all of the
    // sub-systems (render, sound, input etc.)
    //
    if(TState::initialize())
        return 1;

    //
    // read options from the registry
    //

    regOpenSection("options");
    m_playOptions.m_difficulty = regReadKey("difficulty",1);
    m_playOptions.m_bgMusic = regReadKey("bgmusic",1);
    m_playOptions.m_bgMusicVolume = regReadKey("bgmusicvolume",75);
    m_playOptions.m_theme = regReadKey("theme","Random");

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

    sound = loadSound("bg4.ogg");
    sound->setLoop(true);
    sound2 = loadSound("gunshot_bang.ogg");
    sound3 = loadSound("lightning.ogg");

    Tubras::T1PCamera* cam = (Tubras::T1PCamera*)getRenderEngine()->getCamera("Camera::Default");
    sound4 = loadSound("zoom.ogg");
    sound5 = loadSound("zoomout.ogg");
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

    m_finterval = new Tubras::TFunctionInterval("testFuncInterval",5.0,
        FUNCINT_DELEGATE(TPlayState::funcInterval));

    m_finterval->setDoneEvent("testFuncIntervalDone");

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
    setControllerEnabled("DefaultPlayerController",false);

    getRenderEngine()->getCamera("Camera::Default")->setPos(TVector3(0,0,0));
    getRenderEngine()->getCamera("Camera::Default")->lookAt(TVector3(0,0,0),Ogre::Node::TS_PARENT);
    m_GUIScreen->show();
    setGUIEnabled(true);

    m_background->setScrollAnimation(-0.1, 0.0);
    m_background->setRotateAnimation(0.05);

    if(m_playOptions.m_bgMusic)
        sound->play();

    enableEvents(this);

    m_testTask->start();
    m_parent->flipVisibility();

    int cx = m_app->getRenderEngine()->getRenderWindow()->getWidth() / 2;
    int cy = m_app->getRenderEngine()->getRenderWindow()->getHeight() / 2;
    TGUI::TGSystem::getSingleton().getMouseCursor()->setPos(cx,cy);

    setGUICursorVisible(true);

    layoutCards(m_playOptions.m_difficulty);

    return 0;
}

//-----------------------------------------------------------------------
//                              E x i t
//-----------------------------------------------------------------------
Tubras::TStateInfo* TPlayState::Exit()
{
    setControllerEnabled("DefaultPlayerController",false);
    sound->stop();
    m_testTask->stop();
    m_background->setScrollAnimation(0.0, 0.0);
    m_background->setRotateAnimation(0.0);
    disableEvents(this);
    m_parent->flipVisibility();
    m_GUIScreen->hide();
    setGUICursorVisible(false);

    std::list<struct TCardInfo*>::iterator itr;
    itr = m_cardNodes.begin();
    while(itr != m_cardNodes.end())
    {
        TCardInfo* pci = *itr;
        pci->m_node->getNode()->setVisible(false);
        ++itr;
    }


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


