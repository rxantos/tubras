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
#ifndef _SPLASHSTATE_H_
#define _SPLASHSTATE_H_

class TSplashState : public Tubras::TState
{
private:
    Ogre::SceneNode* m_parent;
    Ogre::Rectangle2D* m_logo;
    Ogre::TextureUnitState* m_textureState;
    Tubras::TFunctionInterval* m_finterval,*m_finterval2;
    Tubras::TSound* m_sound;
    ULONG m_starttime,m_shaketime;

public:
    TSplashState();
    virtual ~TSplashState();

    void shakeLogo();
    void adjustAlpha(double T, void* userData);
    int alphaDone(Tubras::TSEvent event);

    virtual int initialize();

    int Enter();
    Tubras::TStateInfo* Exit();
    int Reset();
    int Pause();
    int Resume(Tubras::TStateInfo* prevStateInfo);
};

#endif
