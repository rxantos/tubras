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

#ifndef _TTHEME_H__
#define _TTHEME_H__

namespace Tubras
{
    typedef std::map<string,string> TPropMap;

    class TTheme 
    {
    protected:
        string          m_baseDir;
        string          m_themeName;
        string          m_author;
        string          m_copyRight;
        TPropMap        m_imageProps;
        TPropMap        m_soundProps;
        TPropMap        m_optionProps;
        bool            m_loaded;

        TConfigFile*    m_configFile;

    public:

        TTheme(string baseDir);
        virtual ~TTheme();
        virtual int load();
        virtual int unload();
        string getName() {return m_themeName;};
        string getAuthor() {return m_author;};
        string getCopyright() {return m_copyRight;};
        bool isLoaded() {return m_loaded;};

        const TPropMap optionProps() {return m_optionProps;};
        const TPropMap imageProps() {return m_imageProps;};
        const TPropMap soundProps() {return m_soundProps;};

    };

}

#endif