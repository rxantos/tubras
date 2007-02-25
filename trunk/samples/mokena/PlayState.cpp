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
//                            p r o c K e y
//-----------------------------------------------------------------------
int TPlayState::procKey(Tubras::TSEvent event)
{
    printf("procKey invoked\n");
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

    m_quitDelegate = EVENT_DELEGATE(TPlayState::escape);
    acceptEvent("key.down.esc",m_quitDelegate,NULL,0,false);

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

    //
    // set the applications initial state. ("") means we're not using 
    // the state manager - we don't really need to do this because
    // it is the default behavior.
    //

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

    //
    // assign front card material based on theme
    //
    Tubras::TMaterial* cfMat = m_curTheme->getCFMaterial();
    Tubras::TRandom random;
    random.randomize();

    itr = m_activeCards.begin();
    while(itr != m_activeCards.end())
    {
        TCardInfo* pci = *itr;
        Ogre::SubEntity* se;

        se = pci->m_node->getEntity()->getSubEntity(0);
        
        if(m_curTheme->getRandomTexture())
        {
            Tubras::TString cloneName = pci->m_node->getName() + "cfMat";
            Tubras::TMaterial* mat = cfMat->clone(cloneName);
            se->setMaterialName(cloneName);
            TReal rot = random.getRandomFloat() * 360.f;
            mat->rotateMat(rot);
            mat->offsetMat(random.getRandomFloat(),random.getRandomFloat());
        }
        else
        {
            se->setMaterialName(cfMat->getName());
        }
        ++itr;
    }

    //
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

        Ogre::SubEntity* se;
        se = pci->m_node->getEntity()->getSubEntity(1);

        Tubras::TMaterial* mat;
        mat = m_curTheme->getPickMat(pci->m_pick);
        se->setMaterialName(mat->getName());
        se->setVisible(true);
        

        //
        // move node behind the camera
        //
        TVector3 pos = pci->m_node->getPos();
        pos.z = 1.0f;
        pci->m_node->setPos(pos);

        ++idx;
        ++itr;
    }
    


}

//-----------------------------------------------------------------------
//                          l o a d S c e n e
//-----------------------------------------------------------------------
void TPlayState::loadScene(struct TPlayOptions* options)
{        
    layoutCards(options->m_difficulty);

    m_hudImage = new TGUI::TGImage(m_GUIScreen,"Hud","hud.png");
    m_hudImage->setPos(0.125f,0.82f);
    m_hudImage->setSize(0.75f,0.14f);

    m_readyImage = new TGUI::TGImage(m_hudImage,"Ready","ready.png");
    m_readyImage->setPos(0.036f,0.18f);
    m_readyImage->setSize(0.16f,0.64f);
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

    setControllerEnabled("DefaultPlayerController",true);

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


