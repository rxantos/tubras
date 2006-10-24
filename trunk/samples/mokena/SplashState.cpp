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
#include "mokena.h"

#define ALPHA_DURATION 3.6f

//-----------------------------------------------------------------------
//                        T S p l a s h S t a t e
//-----------------------------------------------------------------------
TSplashState::TSplashState() : TState("splashState")
{
}

//-----------------------------------------------------------------------
//                       ~ T S p l a s h S t a t e
//-----------------------------------------------------------------------
TSplashState::~TSplashState()
{
    if(m_finterval)
        delete m_finterval;

    if(m_finterval2)
        delete m_finterval2;

    if(m_logo)
        delete m_logo;

    if(m_sound)
        delete m_sound;
}

//-----------------------------------------------------------------------
//                         i n i t i a l i z e
//-----------------------------------------------------------------------
int TSplashState::initialize()
{
    if(TState::initialize())
        return 1;

    Ogre::SceneManager* sm = m_app->getRenderEngine()->getSceneManager();

    m_parent = createSceneNode("SplashParent");


    //
    // Create the logo material
    //

    TVector3 pos(-0.5,0.25,0);
    TVector3 size(0.5,-0.25,0);

    m_logo = new Tubras::TCardNode("logoSplash",m_parent,pos,size,Tubras::rpBack,true);
    m_logo->setImage("General","splash.png");
    m_logo->setAlpha(0.0);

    /*
    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("Splash", "General");
    material->getTechnique(0)->getPass(0)->createTextureUnitState("splash.png");
    material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
    material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
    material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);

    m_textureState = material->getTechnique(0)->getPass(0)->getTextureUnitState(0);
    m_textureState->setAlphaOperation(Ogre::LBX_BLEND_CURRENT_ALPHA, Ogre::LBS_TEXTURE, Ogre::LBS_MANUAL, 1, 1.0, 1);

    // Create the logo geometry 
    m_logo = new Ogre::Rectangle2D(true);
    m_logo->setCorners(-0.5, .25, 0.5, -0.25);
    m_logo->setMaterial("Splash");

    // Attach logo to our state parent scene node
    m_parent->attachObject(m_logo);
    */

    m_finterval = new Tubras::TFunctionInterval("alphaUp",ALPHA_DURATION,
        FUNCINT_DELEGATE(TSplashState::adjustAlpha),(void *)1);

    m_finterval->setDoneEvent("alphaDone");
    acceptEvent("alphaDone",EVENT_DELEGATE(TSplashState::alphaDone));

    m_finterval2 = new Tubras::TFunctionInterval("alphaDown",ALPHA_DURATION,
            FUNCINT_DELEGATE(TSplashState::adjustAlpha),(void*) 0);

    m_finterval2->setDoneEvent("alphaDone2");
    acceptEvent("alphaDone2",EVENT_DELEGATE(TSplashState::alphaDone),(void *)1);

    m_sound = loadSound("General","splash.ogg");

    return 0;
}

//-----------------------------------------------------------------------
//                         a l p h a D o n e
//-----------------------------------------------------------------------
int TSplashState::alphaDone(Tubras::TSEvent event)
{
    if(!event->getUserData())
    {
        m_finterval2->start();
    }
    else
    {
        popState();
        pushState("menuState");
        Tubras::getApplication()->toggleHelp();
    }
    return 0;
}

//-----------------------------------------------------------------------
//                         a d j u s t A l p h a 
//-----------------------------------------------------------------------
void TSplashState::adjustAlpha(double T, void* userData)
{

    double value;
    if(userData)
        value = T / ALPHA_DURATION;
    else value = 1 - (T / ALPHA_DURATION);

    m_logo->setAlpha(value);

    ULONG delta = m_globalClock->getMilliseconds() - m_starttime;
    if(delta >= m_shaketime)
    {
        shakeLogo();
        m_starttime = m_globalClock->getMilliseconds();
        m_shaketime = getRandomFloat() * 30.0f;
    }
}


//-----------------------------------------------------------------------
//                          s h a k e L o g o 
//-----------------------------------------------------------------------
void TSplashState::shakeLogo()
{
    float horz = getRandomFloat() * 0.01f;
    float vert = getRandomFloat() * 0.01f;

    int sign = getRandomInt(2);
    if(sign)
    {
        horz = -horz;
        vert = -vert;
    }

    m_logo->setCorners(-0.5+horz, .25+vert, 0.5+horz, -.25+vert);
}

//-----------------------------------------------------------------------
//                             E n t e r
//-----------------------------------------------------------------------
int TSplashState::Enter()
{
    m_parent->getNode()->setVisible(true);
    m_starttime = m_globalClock->getMilliseconds();
    m_shaketime = getRandomFloat() * 75.0f;


    m_finterval->start();
    m_sound->play();

    return 0;
}

//-----------------------------------------------------------------------
//                               E x i t
//-----------------------------------------------------------------------
Tubras::TStateInfo* TSplashState::Exit()
{
    m_parent->flipVisibility();
    return &m_info;
}

//-----------------------------------------------------------------------
//                              R e s e t
//-----------------------------------------------------------------------
int TSplashState::Reset()
{
    return 0;
}

//-----------------------------------------------------------------------
//                              P a u s e 
//-----------------------------------------------------------------------
int TSplashState::Pause()
{
    m_parent->flipVisibility();
    return 0;
}

//-----------------------------------------------------------------------
//                             R e s u m e
//-----------------------------------------------------------------------
int TSplashState::Resume(Tubras::TStateInfo* prevStateInfo)
{
    return 0;
}


