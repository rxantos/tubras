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
    //                            T T h e m e
    //-----------------------------------------------------------------------
    TTheme::TTheme(TString baseDir) : TObject()
    {
        m_baseDir = baseDir;
        m_themeName = "";
        m_loaded = false;

        TFile configName = m_baseDir + "/theme.cfg";
        TString osConfigName = configName.to_os_specific();

        m_configFile = new TConfigFile();
        m_configFile->load(osConfigName);

        m_themeName = m_configFile->getSetting("name","theme");
        m_author = m_configFile->getSetting("author","theme");
        m_copyRight = m_configFile->getSetting("copyright","theme");

        //
        // options
        //
        Ogre::ConfigFile::SettingsIterator sit = m_configFile->getSettingsIterator("options");

        while (sit.hasMoreElements())
        {
            TString name = sit.peekNextKey();
            TString value = sit.getNext();
            m_optionProps[name] = value;
        }

        //
        // images
        //
        sit = m_configFile->getSettingsIterator("images");

        while (sit.hasMoreElements())
        {
            TString name = sit.peekNextKey();
            TString value = sit.getNext();
            m_imageProps[name] = value;
        }

        //
        // sounds
        //
        sit = m_configFile->getSettingsIterator("sounds");

        while (sit.hasMoreElements())
        {
            TString name = sit.peekNextKey();
            TString value = sit.getNext();
            m_soundProps[name] = value;
        }


    }

    //-----------------------------------------------------------------------
    //                           ~T T h e m e
    //-----------------------------------------------------------------------
    TTheme::~TTheme() 
    {
        if(m_configFile)
            delete m_configFile;
    }

    //-----------------------------------------------------------------------
    //                             l o a d
    //-----------------------------------------------------------------------
    int TTheme::load()
    {
        m_loaded = true;
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
            m_baseDir, "FileSystem", m_themeName);
        Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(m_themeName);
        Ogre::ResourceGroupManager::getSingleton().loadResourceGroup(m_themeName);

        return 0;
    }

    //-----------------------------------------------------------------------
    //                            u n l o a d
    //-----------------------------------------------------------------------
    int TTheme::unload()
    {
        m_loaded = false;
        Ogre::ResourceGroupManager::getSingleton().unloadResourceGroup(m_themeName);
        Ogre::ResourceGroupManager::getSingleton().removeResourceLocation(m_themeName);
        Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup(m_themeName);
        return 0;
    }


}