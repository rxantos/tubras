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

//-----------------------------------------------------------------------
//                         T T e s t T h e m e
//-----------------------------------------------------------------------
TTestTheme::TTestTheme(Tubras::TString baseDir) : Tubras::TTheme(baseDir)
{

    Tubras::TString     temp;

    m_bgImageName = m_configFile->getSetting("bgimage","images");
    m_cfImageName = m_configFile->getSetting("cardimage","images");

    m_randomTexture = false;
    temp = m_configFile->getSetting("randomizetexture","options");
    if(!temp.compare("1"))
        m_randomTexture = true;

    temp = m_configFile->getSetting("totalpicks","options");
    m_totalPicks = atoi(temp.c_str());

    temp = m_configFile->getSetting("totalbgsounds","options");
    m_totalBGSounds = atoi(temp.c_str());
}

//-----------------------------------------------------------------------
//                          g e t P i c k M a t
//-----------------------------------------------------------------------
Tubras::TMaterial* TTestTheme::getPickMat(int idx)
{
    return m_pickMats[idx-1];
}

//-----------------------------------------------------------------------
//                       g e t P i c k S o u n d
//-----------------------------------------------------------------------
Tubras::TSound* TTestTheme::getPickSound(int pick)
{
    TStrStream sname;
    sname << pick << ".ogg";

    return loadSound(sname.str().c_str(),getName());
}

//-----------------------------------------------------------------------
//                   g e t R a n d o m B G S o u n d
//-----------------------------------------------------------------------
Tubras::TSound* TTestTheme::getRandomBGSound()
{
    Tubras::TRandom ran;
    ran.randomize();

    TStrStream sname;
    sname << "bg" << (ran.getRandomInt(m_totalBGSounds)+1) << ".ogg";
    return loadSound(sname.str().c_str(),getName());

}

//-----------------------------------------------------------------------
//                             l o a d
//-----------------------------------------------------------------------
int TTestTheme::load(TGUI::TGScreen* screen)
{
    TVector2 v,bpos,bsize;

    if(TTheme::load())
        return 1;

    m_bgMaterial = loadTexture(getName() + "bgMat",getName(),m_bgImageName);
    m_cfMaterial = loadTexture(getName() + "cfMat",getName(),m_cfImageName);

    for(int i=1; i <= m_totalPicks; i++)
    {
        Tubras::TMaterial* mat;
        TStrStream tname,iname;
        tname << getName() << "pick" << i << "Mat";
        iname << i << ".png";

        mat = loadTexture(tname.str(),getName(),iname.str());
        m_pickMats.push_back(mat);
    }

    Tubras::TString fname;

    fname = m_configFile->getSetting("clicksound","sounds");

    m_click = loadSound(fname,getName());
    m_click->setFinishedEvent("clickSoundDone");

    fname = m_configFile->getSetting("clickmiss","sounds");
    m_clickMiss = loadSound(fname,getName());
    m_clickMiss->setFinishedEvent("clickMissSoundDone");

    fname = m_configFile->getSetting("spinsound","sounds");
    m_spin = loadSound(fname,getName());
    m_spin->setFinishedEvent("spinSoundDone");

    fname = m_configFile->getSetting("matchsound","sounds");
    m_match = loadSound(fname,getName());
    m_match->setFinishedEvent("matchSoundDone");

    fname = m_configFile->getSetting("hidesound","sounds");
    m_hide = loadSound(fname,getName());
    m_hide->setFinishedEvent("hideSoundDone");

    fname = m_configFile->getSetting("timeticksound","sounds");
    m_timer = loadSound(fname,getName());
    m_timer->setVolume(0.4f);

    fname = m_configFile->getSetting("countticksound","sounds");
    m_count = loadSound(fname,getName());
    m_count->setVolume(0.5f);

    fname = m_configFile->getSetting("dingsound","sounds");
    m_ding = loadSound(fname,getName());


    fname = m_configFile->getSetting("hudbgimage","images");
    m_hud = new TGUI::TGImage(screen,"Hud",fname,getName());
    v = m_configFile->getVector2("hudpos","options");
    m_hud->setPos(v.x,v.y);
    v = m_configFile->getVector2("hudsize","options");
    m_hud->setSize(v.x,v.y);
    int	x1, y1, x2, y2;
    m_hud->getBounds(x1, y1, x2, y2);
    m_hud->setBounds(x1-1,y1-1,x2+2,y2+3);


    bpos = m_configFile->getVector2("bpos","options");
    bsize = m_configFile->getVector2("bsize","options");

    fname = m_configFile->getSetting("readyon","images");
    m_ready = new TGUI::TGImage(m_hud,"Ready",fname,getName());
    m_ready->setPos(bpos.x,bpos.y);
    m_ready->setSize(bsize.x,bsize.y);
    m_ready->setVisible(false);


    fname = m_configFile->getSetting("readywait","images");
    m_wait = new TGUI::TGImage(m_hud,"Wait",fname,getName());
    m_wait->setPos(bpos.x,bpos.y);
    m_wait->setSize(bsize.x,bsize.y);
    m_wait->setVisible(false);

    fname = m_configFile->getSetting("readypaused","images");
    m_paused = new TGUI::TGImage(m_hud,"Paused",fname,getName());
    m_paused->setPos(bpos.x,bpos.y);
    m_paused->setSize(bsize.x,bsize.y);
    m_paused->setVisible(false);

    fname = m_configFile->getSetting("hudfont","options");
    m_font = new TGUI::TGFont(fname,getName());
    m_font->setHeight(36);

    m_timerText = new TGUI::TGLabel(m_hud,"timerText","0:00");
    v = m_configFile->getVector2("clockpos","options");
    m_timerText->setPos(v.x,v.y);
    m_timerText->setFont(m_font);

    m_scoreText = new TGUI::TGLabel(m_hud,"scoreText","0");
    v = m_configFile->getVector2("scorepos","options");
    m_scoreText->setPos(v.x,v.y);
    m_scoreText->setFont(m_font);

    m_cardsDY = m_configFile->getFloat("cardsdy","options");

    return 0;
}

//-----------------------------------------------------------------------
//                            u n l o a d
//-----------------------------------------------------------------------
int TTestTheme::unload()
{
    unloadMaterial(m_bgMaterial->getName());
    delete m_bgMaterial;
    m_bgMaterial = 0;

    delete m_font;
    m_font = 0;

    unloadMaterial(m_cfMaterial->getName());
    delete m_cfMaterial;
    m_cfMaterial = 0;

    while(m_pickMats.size())
    {
        Tubras::TMaterial* mat;
        mat = m_pickMats[m_pickMats.size()-1];
        unloadMaterial(mat->getName());
        delete mat;
        m_pickMats.pop_back();
    }
    
    //
    // remove resource group
    //
    if(TTheme::unload())
        return 1;

    return 0;
}
