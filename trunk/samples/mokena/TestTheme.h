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
#ifndef _TESTTHEME_H_
#define _TESTTHEME_H_


typedef std::vector<Tubras::TMaterial*> TMatList;
typedef std::vector<Tubras::TMaterial*>::iterator TMatListItr;

class TTestTheme : public Tubras::TTheme
{
private:
    Tubras::TString         m_bgImageName;
    Tubras::TString         m_cfImageName;
    Tubras::TMaterial*      m_bgMaterial;
    Tubras::TMaterial*      m_cfMaterial;
    bool                    m_randomTexture;
    int                     m_totalPicks;
    TMatList                m_pickMats;
    Tubras::TSound*         m_click;
    
public:
    TTestTheme(Tubras::TString basedir);
    int load();
    int unload();

    Tubras::TString getBGImageName() {return m_bgImageName;}
    Tubras::TMaterial* getBGMaterial() {return m_bgMaterial;}
    Tubras::TMaterial* getCFMaterial() {return m_cfMaterial;}
    bool getRandomTexture() {return m_randomTexture;}
    int getTotalPicks() {return m_totalPicks;}
    Tubras::TMaterial* getPickMat(int idx);

    Tubras::TSound* getClickSound() {return m_click;}

};

#endif
