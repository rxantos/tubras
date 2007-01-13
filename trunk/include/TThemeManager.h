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

#ifndef _TTHEMEMANAGER_H__
#define _TTHEMEMANAGER_H__

namespace Tubras
{
    typedef std::map<TString, TTheme*> TThemeMap;
    typedef std::map<TString, TTheme*>::iterator TThemeMapItr;

    class TThemeManager : public TSingleton<TThemeManager>, public TObject
    {
    protected:

        TThemeMap           m_themes;
        TString             m_baseDir;

    public:
        TThemeManager();
        virtual ~TThemeManager();

        TThemeManager* getSingletonPtr(void);
        TThemeManager& getSingleton(void);

        virtual int initialize(TString basedir);

        TTheme* getTheme(int index);
        TTheme* getThemeByName(TString themeName);
        TTheme* getRandomTheme();

        const TThemeMap& getThemes() {return m_themes;};

    };

}
#endif


