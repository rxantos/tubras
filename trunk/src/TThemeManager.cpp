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

    template<> TThemeManager* TSingleton<TThemeManager>::ms_Singleton = 0;

    //-----------------------------------------------------------------------
    //                       T T h e m e M a n a g e r
    //-----------------------------------------------------------------------
    TThemeManager::TThemeManager() : TSingleton(), TObject()
    {

    }

    //-----------------------------------------------------------------------
    //                      ~ T T h e m e M a n a g e r
    //-----------------------------------------------------------------------
    TThemeManager::~TThemeManager()
    {
        TThemeMapItr itr;

        itr = m_themes.begin();
        while(itr != m_themes.end())
        {
            TTheme* theme = itr->second;
            if(theme->isLoaded())
                theme->unload();
            delete theme;
            ++itr;
        }

    }

    //-----------------------------------------------------------------------
    //                   g e t S i n g l e t o n P t r
    //-----------------------------------------------------------------------
    TThemeManager* TThemeManager::getSingletonPtr(void)
    {
        return ms_Singleton;
    }


    //-----------------------------------------------------------------------
    //                      g e t S i n g l e t o n
    //-----------------------------------------------------------------------
    TThemeManager& TThemeManager::getSingleton(void)
    {  
        assert( ms_Singleton );  return ( *ms_Singleton );  
    }


    //-----------------------------------------------------------------------
    //                         g e t T h e m e
    //-----------------------------------------------------------------------
    TTheme* TThemeManager::getTheme(int index)
    {
        TTheme* pt=NULL;

        return pt;
    }

    //-----------------------------------------------------------------------
    //                    g e t T h e m e B y N a m e 
    //-----------------------------------------------------------------------
    TTheme* TThemeManager::getThemeByName(TString themeName)
    {
        TTheme* pt=NULL;

        return pt;
    }

    //-----------------------------------------------------------------------
    //                    g e t R a n d o m T h e m e
    //-----------------------------------------------------------------------
    TTheme* TThemeManager::getRandomTheme()
    {
        TTheme* pt=NULL;

        return pt;
    }


    //-----------------------------------------------------------------------
    //                       i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TThemeManager::initialize(TString basedir)
    {
        TTheme* pt;
        TFile  basePath;

        m_baseDir = basedir;
        basePath = basedir;

        //
        // verify base is a directory
        //
        if(!basePath.is_directory())
        {
            TStrStream msg;
            msg << "Theme Base Directory \"" << m_baseDir << "\" is NOT a directory.";
            logMessage(msg.str().c_str());
            return 1;
        }

        //
        // get base directory contents and pick out only directories
        // that contain a "theme.cfg" file.
        //

        vector_string contents;
        vector_string::iterator itr;

        basePath.scan_directory(contents);

        itr = contents.begin();
        while(itr != contents.end())
        {
            TString subDir = *itr;
            TFile configName;
            TFile themeBaseDir;
            themeBaseDir = m_baseDir + "/" + subDir + "/";
            configName = m_baseDir + "/" + subDir + "/theme.cfg";
            if(configName.exists())
            {
                pt = getApplication()->createThemeClass(themeBaseDir);
                m_themes[pt->getName()] = pt;

            }
            ++itr;
        }

        return 0;
    }


}

