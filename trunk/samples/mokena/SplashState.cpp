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

}

//-----------------------------------------------------------------------
//                         i n i t i a l i z e
//-----------------------------------------------------------------------
int TSplashState::initialize()
{
    if(TState::initialize())
        return 1;


    TGUI::TGSystem* system = getGUISystem();

    m_GUIScreen = new TGUI::TGScreen(system->getActiveScreen(),"splashScreen");
    m_GUIScreen->setVisible(true);

    m_logo = new TGUI::TGImage(m_GUIScreen,"splashLogo","splash.png");
    m_logo->center();

    int x2,y2;
    m_logo->getBounds(m_posx,m_posy,x2,y2);

    m_logo->setAlpha(0);

    m_finterval = new Tubras::TFunctionInterval("alphaUp",ALPHA_DURATION,
        FUNCINT_DELEGATE(TSplashState::adjustAlpha),(void *)1);

    m_finterval->setDoneEvent("alphaDone");
    acceptEvent("alphaDone",EVENT_DELEGATE(TSplashState::alphaDone));

    m_finterval2 = new Tubras::TFunctionInterval("alphaDown",ALPHA_DURATION,
        FUNCINT_DELEGATE(TSplashState::adjustAlpha),(void*) 0);

    m_finterval2->setDoneEvent("alphaDone2");
    acceptEvent("alphaDone2",EVENT_DELEGATE(TSplashState::alphaDone),(void *)1);

    m_sound = loadSound("splash.ogg");
    m_tubras = loadSound("tubras2.ogg");
    acceptEvent("logoDone",EVENT_DELEGATE(TSplashState::logoDone));

    return 0;
}

//-----------------------------------------------------------------------
//                            l o g o D o n e
//-----------------------------------------------------------------------
int TSplashState::logoDone(Tubras::TSEvent event)
{
    popState();
    pushState("menuState");
    return 1;
}

//-----------------------------------------------------------------------
//                           a l p h a D o n e
//-----------------------------------------------------------------------
int TSplashState::alphaDone(Tubras::TSEvent event)
{
    if(!event->getUserData())
    {
        m_finterval2->start();
    }
    else
    {
        m_logo->setAlpha(1.0);
        m_tubras->setFinishedEvent("logoDone");
        m_tubras->play();
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
    int horz = getRandomInt(3);
    int vert = getRandomInt(3);

    int sign = getRandomInt(2);
    if(sign)
    {
        horz = -horz;
        vert = -vert;
    }

    m_logo->setPos(m_posx+horz, m_posy+vert);
}

//-----------------------------------------------------------------------
//                             E n t e r
//-----------------------------------------------------------------------
int TSplashState::Enter()
{
    m_GUIScreen->show();
    setGUIEnabled(true);

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
    m_GUIScreen->hide();

    //
    // because we are a one off state, delete all resources.
    //
    delete m_logo;
    delete m_sound;
    delete m_GUIScreen;
    destroyInterval(m_finterval);
    destroyInterval(m_finterval2);

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
    return 0;
}

//-----------------------------------------------------------------------
//                             R e s u m e
//-----------------------------------------------------------------------
int TSplashState::Resume(Tubras::TStateInfo* prevStateInfo)
{
    return 0;
}


