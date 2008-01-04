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
#include "tubras.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                          g e t F l o a t
    //-----------------------------------------------------------------------
    float TConfigFile::getFloat(const TString& key, const TString& section, float def)
    {
        float res=def;
        TString sval;

        sval = getSetting(key,section);
        if(sval.empty())
            return res;

        res = Ogre::StringConverter::parseReal(sval);

        return res;
    }

    //-----------------------------------------------------------------------
    //                           g e t I n t
    //-----------------------------------------------------------------------
    int TConfigFile::getInt(const TString& key, const TString& section, int def)
    {
        int res=def;

        return res;
    }

    //-----------------------------------------------------------------------
    //                           g e t B o o l
    //-----------------------------------------------------------------------
    bool TConfigFile::getBool(const TString& key, const TString& section, bool def)
    {
        bool res=def;

        return res;
    }

    //-----------------------------------------------------------------------
    //                          g e t S t r i n g
    //-----------------------------------------------------------------------
    TString TConfigFile::getString(const TString& key, const TString& section, TString def)
    {
        TString res=def;

        return res;
    }

    //-----------------------------------------------------------------------
    //                          g e t V e c t o r 2
    //-----------------------------------------------------------------------
    TVector2 TConfigFile::getVector2(const TString& key, const TString& section, TVector2 def)
    {
        TVector2 res=def;
        TString sval;

        sval = getSetting(key,section);
        if(sval.empty())
            return res;

        // Split on space
        std::vector<TString> vec = Ogre::StringUtil::split(sval);

        if (vec.size() >= 2)
        {
            return TVector2(Ogre::StringConverter::parseReal(vec[0]),
                Ogre::StringConverter::parseReal(vec[1]));
        }
        else if (vec.size() == 1)
        {
            return TVector2(Ogre::StringConverter::parseReal(vec[0]));
        }

        return res;
    }

    //-----------------------------------------------------------------------
    //                          g e t V e c t o r 3
    //-----------------------------------------------------------------------
    TVector3 TConfigFile::getVector3(const TString& key, const TString& section, TVector3 def)
    {
        TVector3 res=def;
        TString sval;

        sval = getSetting(key,section);
        if(sval.empty())
            return res;

        // Split on space
        std::vector<TString> vec = Ogre::StringUtil::split(sval);

        if (vec.size() >= 3)
        {
            return TVector3(Ogre::StringConverter::parseReal(vec[0]),
                Ogre::StringConverter::parseReal(vec[1]),
                Ogre::StringConverter::parseReal(vec[2]));
        }
        else if (vec.size() == 2)
        {
            return TVector3(Ogre::StringConverter::parseReal(vec[0]),
                Ogre::StringConverter::parseReal(vec[1]),0);
        }
        else if (vec.size() == 1)
        {
            return TVector3(Ogre::StringConverter::parseReal(vec[0]),0,0);
        }

        return res;
    }

}