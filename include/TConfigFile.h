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

#ifndef _TCONFIGFILE_H_
#define _TCONFIGFILE_H_

namespace Tubras
{
    class TConfigFile : public Ogre::ConfigFile
    {

    public:
        TConfigFile() : Ogre::ConfigFile() {};
        float getFloat(const TString& key, const TString& section = "",float def=0.f);
        int getInt(const TString& key, const TString& section = "", int def=0);
        bool getBool(const TString& key, const TString& section = "", bool def=false);
        TString getString(const TString& key, const TString& section = "", TString def="");
        TVector3 getVector3(const TString& key, const TString& section = "", TVector3 def=TVector3::ZERO);
        TVector2 getVector2(const TString& key, const TString& section = "", TVector2 def=TVector2::ZERO);

    };

}
#endif