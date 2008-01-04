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
    //                          T R e g i s t r y
    //-----------------------------------------------------------------------
    TRegistry::TRegistry()
    {
        m_currentSection = "default";
    }

    //-----------------------------------------------------------------------
    //                         ~ T R e g i s t r y
    //-----------------------------------------------------------------------
    TRegistry::~TRegistry()
    {
    }

    //-----------------------------------------------------------------------
    //                         ~ T R e g i s t r y
    //-----------------------------------------------------------------------
    int TRegistry::callback(int cols,char** values, char** colNames)
    {
        m_currentValue = values[0];

        return TDatabase::callback(cols,values,colNames);
    }

    //-----------------------------------------------------------------------
    //                         o p e n S e c t i o n
    //-----------------------------------------------------------------------
    int TRegistry::openSection(TString section)
    {
        m_currentSection = section;
        return 0;
    }

    //-----------------------------------------------------------------------
    //                            r e a d K e y
    //-----------------------------------------------------------------------
    TString TRegistry::readKey(TString key,TString defaultValue)
    {
        TString result=defaultValue;
        TStrStream sql;
        sql << "select value from registry where (section = \"" << m_currentSection
            << "\") and (key = \"" << key << "\");";
        exec(sql.str());
        if(rowCount() > 0)
        {
            result = m_currentValue;
        }
        return result;
    }

    //-----------------------------------------------------------------------
    //                        r e a d K e y A s I n t
    //-----------------------------------------------------------------------
    int TRegistry::readKeyAsInt(TString key,int defaultValue)
    {
        int result=defaultValue;
        TStrStream sdefaultValue;
        sdefaultValue << defaultValue;

        TString strResult = readKey(key,sdefaultValue.str());

        result = atoi(strResult.c_str());

        return result;
    }

    //-----------------------------------------------------------------------
    //                           w r i t e K e y
    //-----------------------------------------------------------------------
    int TRegistry::writeKey(TString key, TString value)
    {
        TStrStream sql;
        int rc = 0;

        bool exists = keyExists(key);
        if(exists) 
        {
            sql << "update registry set value = \"" << value << "\" "
                << "where (section = \"" << m_currentSection << "\") "
                << "and (key = \"" << key << "\");";
        }
        else
        {
            sql << "insert into registry (section, key, value) values (\""
                << m_currentSection << "\", \""
                << key << "\", \""
                << value << "\");";
        }

        rc = exec(sql.str());

        return rc;
    }

    //-----------------------------------------------------------------------
    //                       w r i t e K e y A s I n t
    //-----------------------------------------------------------------------
    int TRegistry::writeKeyAsInt(TString key, int value)
    {
        int rc = 0;
        TStrStream sValue;
        sValue << value;

        rc = writeKey(key,sValue.str());

        return rc;
    }

    //-----------------------------------------------------------------------
    //                          k e y E x i s t s
    //-----------------------------------------------------------------------
    bool TRegistry::keyExists(TString key)
    {
        return keyExists(m_currentSection,key);
    }

    //-----------------------------------------------------------------------
    //                          k e y E x i s t s
    //-----------------------------------------------------------------------
    bool TRegistry::keyExists(TString section, TString key)
    {
        TString saveSection;
        saveSection = m_currentSection;
        m_currentSection = section;
        readKey(key);
        m_currentSection = saveSection;
        if(rowCount() > 0)
            return true;
        else return false;
    }



}