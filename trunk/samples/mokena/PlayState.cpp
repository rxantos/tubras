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
    {4,4,0.24f,1.0f,20.0f},
    {4,6,0.24f,0.4f,20.0f},
    {4,8,0.24f,0.4f,20.0f}
};

//-----------------------------------------------------------------------
//                         T P l a y S t a t e
//-----------------------------------------------------------------------
TPlayState::TPlayState() : TState("playState")
{
    m_curThemeIdx = -1;
    m_curTheme = NULL;
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
//                          m o u s e P i c k 
//-----------------------------------------------------------------------
int TPlayState::mousePick(Tubras::TSEvent event)
{
    if(!m_pickState.canPick())
        return 0;

    int x,y;
    getGUISystem()->getMouseCoordinates(x,y);

    if(getDebug())
    {
        TStrStream msg;
        msg << "mousePick (x,y) - (" << x << "," << y << ")";
        logMessage(msg.str().c_str());
    }

    Tubras::TCameraNode* pCam = getCamera("Camera::Default");
    Tubras::TRay ray = pCam->getRay(x,y,1000.f);
    Tubras::TRayResult res = getDynamicWorld()->rayTest(ray);
    if(res.hasHit())
    {
        Tubras::TDynamicNode* pdn=res.getCollisionNode();
        TCardInfo* pci;
        pci = (TCardInfo*)pdn->getUserData();

        if (m_pickState.getCard1() != pci)
        {
            m_curTheme->getClickSound()->play();
            m_pickState.setActiveCard(pci);
            m_pickState.setCanPick(false);
        }
        else
        {
            m_curTheme->getClickMissSound()->play();
        }


    }
    else
    {
        m_curTheme->getClickMissSound()->play();
    }

    return 0;
}

//-----------------------------------------------------------------------
//                          s e t u p D o n e
//-----------------------------------------------------------------------
int TPlayState::setupDone(Tubras::TSEvent event)
{
    m_pickState.setCanPick(true);

    return 0;
}

//-----------------------------------------------------------------------
//                          c l i c k D o n e
//-----------------------------------------------------------------------
int TPlayState::clickDone(Tubras::TSEvent event)
{
    TCardInfo *pci;
    pci = m_pickState.getActiveCard();
    pci->m_eBack->setVisible(true);
    Tubras::TSound* sound = m_curTheme->getSpinSound();
    sound->setFinishedEvent("spinSoundDone");
    float time = sound->length();
    TVector3 toHpr(-180,0,0);
    pci->m_rotLerp1 = new Tubras::TLerpHprInterval("testrot",pci->m_node,time,toHpr);

    sound->play();
    pci->m_rotLerp1->start();

    return 0;
}

//-----------------------------------------------------------------------
//                          s p i n D o n e
//-----------------------------------------------------------------------
int TPlayState::spinDone(Tubras::TSEvent event)
{

    TCardInfo* pci = m_pickState.getActiveCard();

    Tubras::TSound* sound = m_curTheme->getPickSound(pci->m_pick);
    sound->setFinishedEvent("pickSoundDone");
    sound->play();

    return 0;
}

//-----------------------------------------------------------------------
//                          p i c k D o n e
//-----------------------------------------------------------------------
int TPlayState::pickDone(Tubras::TSEvent event)
{

    if(m_pickState.getActiveCards() == 2)
    {
        TCardInfo* pci1 = m_pickState.getCard1();
        TCardInfo* pci2 = m_pickState.getCard2();
        if(pci1->m_pick == pci2->m_pick)
        {
            m_curTheme->getMatchSound()->play();
            m_app->getTaskManager()->doMethodLater(TASK_DELEGATE(TPlayState::goodMatch),500);
        }
        else
        {
            m_app->getTaskManager()->doMethodLater(TASK_DELEGATE(TPlayState::badMatch),500);
        }
    }
    else
    {
        m_pickState.setCanPick(true);
    }
    return 0;
}

//-----------------------------------------------------------------------
//                         g o o d M a t c h
//-----------------------------------------------------------------------
int TPlayState::goodMatch(Tubras::TTask* task)
{

    
    return Tubras::TTask::done;
}

//-----------------------------------------------------------------------
//                          b a d M a t c h
//-----------------------------------------------------------------------
int TPlayState::badMatch(Tubras::TTask* task)
{
    TVector3 toHpr(-180,0,0);
    Tubras::TLerpHprInterval* l1, *l2;
    TCardInfo* pci1 = m_pickState.getCard1();
    TCardInfo* pci2 = m_pickState.getCard2();
    float time = m_curTheme->getSpinSound()->length();

    l1 = new Tubras::TLerpHprInterval("i1",pci1->m_node,time,toHpr);
    l2 = new Tubras::TLerpHprInterval("i2",pci2->m_node,time,toHpr);
    

    Tubras::TSound* sound = m_curTheme->getSpinSound();
    sound->setFinishedEvent("resetPick");
    sound->play();
    l1->start();
    l2->start();

    return Tubras::TTask::done;
}

//-----------------------------------------------------------------------
//                          r e s e t P i c k
//-----------------------------------------------------------------------
int TPlayState::resetPick(Tubras::TSEvent event)
{
    m_pickState.reset();
    return 0;
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

    node->setPos(pos);
    pci = new TCardInfo;
    pci->m_node = node;
    pci->m_pos = pos;
    pci->m_eFront = node->getSubEntity(0);
    pci->m_eBack = node->getSubEntity(1);
    pci->m_eBack->setVisible(false);

    Tubras::TString dname;
    dname = ename.str().c_str();

    pci->m_shape = new Tubras::TColliderBox(node);
    pci->m_dnode = new Tubras::TDynamicNode(dname+"::dnode",node,pci->m_shape,1.f,Tubras::btKinematic);
    pci->m_dnode->allowDeactivation(false);
    pci->m_dnode->setUserData(pci);


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
    sound = NULL;
    m_cubeParent = NULL;
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

    acceptEvent("key.down.esc",EVENT_DELEGATE(TPlayState::escape));
    acceptEvent("input.mouse.down.0",EVENT_DELEGATE(TPlayState::mousePick));
    acceptEvent("setupDone",EVENT_DELEGATE(TPlayState::setupDone));
    acceptEvent("clickSoundDone",EVENT_DELEGATE(TPlayState::clickDone));
    acceptEvent("spinSoundDone",EVENT_DELEGATE(TPlayState::spinDone));
    acceptEvent("pickSoundDone",EVENT_DELEGATE(TPlayState::pickDone));
    acceptEvent("resetPick",EVENT_DELEGATE(TPlayState::resetPick));



    //
    // load some sounds
    //

    sound = loadSound("bg4.ogg");
    sound->setLoop(true);
    Tubras::T1PCamera* cam = (Tubras::T1PCamera*)getRenderEngine()->getCamera("Camera::Default");
    sound4 = loadSound("zoom.ogg");
    sound5 = loadSound("zoomout.ogg");
    cam->setZoomSounds(sound4,sound5);


    //
    // notify us when ambient.ogg finishes playing.
    //
    sound->setFinishedEvent("ambient done");

    //
    // initialize the scene
    //

    m_parent = createSceneNode("PlayParent");

    m_background = new Tubras::TCardNode("Background",m_parent);

    //
    // create the card geometry
    //
    createCards();

    //
    // create gui overlay
    //
    m_GUIScreen = new TGUI::TGScreen(TGUI::TGSystem::getSingleton().getActiveScreen(),"PlayScreen");
    m_GUIScreen->hide();

    m_app->getRenderEngine()->setBackgroundColor(TColor(0,0,0,1));

    m_app->getRenderEngine()->setAmbientLight(TColor(1,1,1,1));

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
//                           l o a d T h e m e
//-----------------------------------------------------------------------
int TPlayState::loadTheme(struct TPlayOptions* options)
{
    Tubras::TThemeManager*  tMgr;
    TTestTheme* theme;
    Tubras::TString  curThemeName;

    if(!m_curTheme)
        curThemeName = "";
    else
        curThemeName = m_curTheme->getName();


    tMgr = getThemeManager();

    //
    // pick out theme based on theme options
    //
    if(!options->m_theme.compare("Random"))
    {
        theme = (TTestTheme*) tMgr->getRandomTheme();
    }
    else if (!options->m_theme.compare("Sequential"))
    {
        ++m_curThemeIdx;
        if((size_t)m_curThemeIdx >= tMgr->getThemeCount())
            m_curThemeIdx = 0;

        theme = (TTestTheme*) tMgr->getTheme(m_curThemeIdx);
    }
    else
    {
        theme = (TTestTheme*) tMgr->getThemeByName(options->m_theme);
        if(!theme)
            theme = (TTestTheme*) tMgr->getRandomTheme();
    }

    //
    // Current theme == new theme? if true, do nothing.  If false,
    // unload the old theme and load the new one.
    //
    if(m_curTheme)
    {
        if(m_curTheme->getName().compare(theme->getName()))
        {
            m_curTheme->unload();
            m_curTheme = theme;
            m_curTheme->load();
        }
    }
    else 
    {
        m_curTheme = theme;
        m_curTheme->load();
    }

    m_background->setMaterial(m_curTheme->getBGMaterial());
   
    return 0;
}

//-----------------------------------------------------------------------
//                 g e t R a n d o m C a r d I t e r a t o r
//-----------------------------------------------------------------------
TCardListItr TPlayState::getRandomCardIterator(Tubras::TRandom& random,TCardList& temp)
{
    int idx;
    TCardListItr itr;

    idx = random.getRandomInt((unsigned int)temp.size());

    itr = temp.begin();
    while(idx)
    {
        ++itr;
        --idx;
    }

    return itr;
}

//-----------------------------------------------------------------------
//                  g e t R a n d o m I n t I t e r a t o r
//-----------------------------------------------------------------------
TIntListItr TPlayState::getRandomIntIterator(Tubras::TRandom& random,TIntList& temp)
{
    int idx;
    TIntListItr itr;

    idx = random.getRandomInt((unsigned int)temp.size());

    itr = temp.begin();
    while(idx)
    {
        ++itr;
        --idx;
    }

    return itr;
}

//-----------------------------------------------------------------------
//                         l a y o u t C a r d s
//-----------------------------------------------------------------------
void TPlayState::layoutCards(int mode)
{
    TCardLayout*    plo;
    size_t          totalCards;
    size_t          i;
    TCardListItr itr,itr2;

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
        pci->m_node->getNode()->setVisible(true);
        if(i<totalCards)
            m_activeCards.push_back(pci);

        //
        // all cards initially behind the camera
        //
        pci->m_node->setPos(0,0,15);
        Tubras::TQuaternion q(TRadian(0),TVector3::UNIT_Y);
        pci->m_node->setOrientation(q);

        ++i;
        ++itr;
    }

    //
    // assign target positions for active cards
    //
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
            pci->m_node->getNode()->setVisible(false);
            ++itr;
        }
    }

    //-------------------------------------------------------------
    // assign front card material based on theme
    //
    Tubras::TMaterial* cfMat = m_curTheme->getCFMaterial();
    Tubras::TRandom random;
    random.randomize();

    itr = m_activeCards.begin();
    while(itr != m_activeCards.end())
    {
        TCardInfo* pci = *itr;
        if(m_curTheme->getRandomTexture())
        {
            Tubras::TMaterial* mat;
            Tubras::TString cloneName = pci->m_node->getName() + "cfMat";  

            Ogre::ResourcePtr mptr = Ogre::MaterialManager::getSingleton().getByName(cloneName);

            if(mptr.isNull())
            {
                mat = cfMat->clone(cloneName);
                pci->m_eFront->setMaterialName(cloneName);
                pci->m_eFrontMat = mat;
            }
            else
            {
                mat = pci->m_eFrontMat;
            }
            TReal rot = random.getRandomFloat() * 360.f;
            mat->rotateMat(rot);
            mat->offsetMat(random.getRandomFloat(),random.getRandomFloat());
        }
        else
        {
            pci->m_eFront->setMaterialName(cfMat->getName());
        }
        ++itr;
    }

    //-------------------------------------------------------------
    // assign random back images to cards
    //
    int tPicks = m_curTheme->getTotalPicks();

    std::vector<int> picks;
    for(int i=1;i <= tPicks;i++)
    {
        picks.push_back(i);
    }
        
    TCardList   temp;
    temp.assign(m_activeCards.begin(),m_activeCards.end());

    while(temp.size() > 0)
    {
        TCardInfo* pci;

        //
        // refill picks list?
        //
        if(picks.size() == 0)
        {
            for(int i=1;i <= tPicks;i++)
            {
                picks.push_back(i);
            }
        }

        //
        // assign random int (image) to two random cards, then remove
        // from the list of possibilities.
        //
        TIntListItr iitr;
        iitr = getRandomIntIterator(random, picks);

        itr = getRandomCardIterator(random,temp);
        pci = *itr;

        pci->m_pick = *iitr;
        temp.erase(itr);

        itr = getRandomCardIterator(random,temp);
        pci = *itr;
        pci->m_pick = *iitr;
        temp.erase(itr);

        picks.erase(iitr);
    }

    
    itr = m_activeCards.begin();
    int idx=0;

    //
    // assign the newly selected materials
    //
    while(itr != m_activeCards.end())
    {
        TCardInfo* pci;
        pci = *itr;

        if(getDebug())
        {
            TStrStream str;
            str << "Card Idx: " << idx << ", pick: " << pci->m_pick;
            logMessage(str.str().c_str());
        }

        Tubras::TMaterial* mat;
        mat = m_curTheme->getPickMat(pci->m_pick);
        pci->m_eBack->setMaterialName(mat->getName());
        pci->m_eBack->setVisible(false);
        
        //
        // move node behind the camera
        //
        TVector3 pos = pci->m_node->getPos();
        pos.z = 1.0f;
        pci->m_node->setPos(pos);

        Tubras::TString lname = "lerpstart" + pci->m_node->getName();
        pci->m_startLerp = new Tubras::TLerpPosInterval(lname,pci->m_node,1.5f,pci->m_pos);

        ++idx;
        ++itr;
    }

    TCardInfo *pci;
    for(size_t i=0;i<m_activeCards.size();i++)
    {
        pci = m_activeCards[i];
        pci->m_startLerp->start();
    }    

    pci->m_startLerp->setDoneEvent("setupDone");

}

//-----------------------------------------------------------------------
//                          l o a d S c e n e
//-----------------------------------------------------------------------
void TPlayState::loadScene(struct TPlayOptions* options)
{        
    m_hudImage = new TGUI::TGImage(m_GUIScreen,"Hud","hud.png");
    m_hudImage->setPos(0.125f,0.82f);
    m_hudImage->setSize(0.75f,0.14f);

    m_readyImage = new TGUI::TGImage(m_hudImage,"Ready","ready.png");
    m_readyImage->setPos(0.036f,0.18f);
    m_readyImage->setSize(0.16f,0.64f);

    layoutCards(options->m_difficulty);

}

//-----------------------------------------------------------------------
//                            E n t e r
//-----------------------------------------------------------------------
int TPlayState::Enter()
{
    TOptionsState* state = (TOptionsState*) getState("optionsState");
    struct TPlayOptions* options = state->getOptions();

    loadTheme(options);

    loadScene(options);

    setControllerEnabled("DefaultPlayerController",false);

    getRenderEngine()->getCamera("Camera::Default")->setPos(TVector3(0,0,0));
    getRenderEngine()->getCamera("Camera::Default")->resetOrientation();
    m_GUIScreen->show();
    setGUIEnabled(true);

    m_background->setScrollAnimation(-0.1, 0.0);
    m_background->setRotateAnimation(0.05);

    if(options->m_bgMusic)
        sound->play();

    enableEvents(this);

    m_parent->flipVisibility();

    int cx = m_app->getRenderEngine()->getRenderWindow()->getWidth() / 2;
    int cy = m_app->getRenderEngine()->getRenderWindow()->getHeight() / 2;
    TGUI::TGSystem::getSingleton().getMouseCursor()->setPos(cx,cy);

    setGUICursorVisible(true);
    enableEvents(this);

    m_pickState.setCanPick(false);

    return 0;
}

//-----------------------------------------------------------------------
//                              E x i t
//-----------------------------------------------------------------------
Tubras::TStateInfo* TPlayState::Exit()
{
    setControllerEnabled("DefaultPlayerController",false);
    sound->stop();
    m_background->setScrollAnimation(0.0, 0.0);
    m_background->setRotateAnimation(0.0);
    disableEvents(this);
    m_parent->flipVisibility();
    m_GUIScreen->hide();
    setGUICursorVisible(false);

    std::vector<struct TCardInfo*>::iterator itr;
    itr = m_cardNodes.begin();
    while(itr != m_cardNodes.end())
    {
        TCardInfo* pci = *itr;
        pci->m_node->getNode()->setVisible(false);
        ++itr;
    }

    //
    // kludge - need to rethink material creation/destroying...
    //
    m_background->setMaterial(NULL);
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


