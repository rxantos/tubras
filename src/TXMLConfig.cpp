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
#include "cattributeimpl.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                          T X M L C o n f i g
    //-----------------------------------------------------------------------
    TXMLConfig::TXMLConfig()
    {
    }

    //-----------------------------------------------------------------------
    //                          T X M L C o n f i g
    //-----------------------------------------------------------------------
    TXMLConfig::~TXMLConfig()
    {
        TSectionsItr sit;

        for(sit = m_sections.getIterator();!sit.atEnd(); sit++)
        {
            IAttributes* attr = sit->getValue();
            attr->clear();
            attr->drop();
        }

        m_sections.clear();
    }

    //-----------------------------------------------------------------------
    //                               l o a d
    //-----------------------------------------------------------------------
    bool TXMLConfig::load(TString filename)
    {
        IrrXMLReader* xml = createIrrXMLReader(filename.c_str());
        IAttributes* attr;

        if(!xml)
            return false;

        IrrlichtDevice* device = createDevice(EDT_NULL);
        attr = device->getFileSystem()->createEmptyAttributes();


        TString sectionName, nodeName, nodeValue;

        //
        // read past header
        //
        xml->read();

        //
        // read first section name
        //
        xml->read();
        if(xml->getNodeType() != EXN_ELEMENT)
            return false;
        sectionName = xml->getNodeName();
        m_sections.insert(sectionName,attr);

        while(xml->read())
        {
            switch(xml->getNodeType())
            {
            case EXN_ELEMENT:
                nodeName = xml->getNodeName();
                nodeValue = xml->getAttributeValue("value");
                attr->addString(nodeName.c_str(),nodeValue.c_str());
                
                break;
            case EXN_ELEMENT_END:
                nodeName = xml->getNodeName();
                //
                // read next section name and create attributes for it
                //
                if(xml->read())
                {
                    sectionName = xml->getNodeName();
                    TSections::Node* node = m_sections.find(sectionName);
                    if(!node)
                    {
                        attr = device->getFileSystem()->createEmptyAttributes();
                        m_sections.insert(sectionName,attr);
                    }
                }
                break;
            }
        }

        device->drop();
        delete xml;
        return true;
    }

    //-----------------------------------------------------------------------
    //                         g e t S e c t i o n
    //-----------------------------------------------------------------------
    IAttributes* TXMLConfig::getSection(TString name)
    {
        TSections::Node* node;

        node = m_sections.find(name);
        if(!node)
            return NULL;

        return node->getValue();
    }


    //-----------------------------------------------------------------------
    //                         g e t S t r i n g
    //-----------------------------------------------------------------------
    TString TXMLConfig::getString(TString key, TString section, TString def)
    {
        TString result = def;

        IAttributes* attr;
        attr = getSection(section);
        if(!attr)
            return result;

        u32 idx = attr->findAttribute(key.c_str());
        if(idx >= 0)
            result = attr->getAttributeAsString(idx);

        return result;
    }

    //-----------------------------------------------------------------------
    //                            g e t B o o l
    //-----------------------------------------------------------------------
    bool TXMLConfig::getBool(TString key, TString section, bool def)
    {
        bool result = def;

        IAttributes* attr;
        attr = getSection(section);
        if(!attr)
            return result;

        u32 idx = attr->findAttribute(key.c_str());
        if(idx >= 0)
            result = attr->getAttributeAsBool(idx);

        return result;
    }

    //-----------------------------------------------------------------------
    //                             g e t I n t
    //-----------------------------------------------------------------------
    int TXMLConfig::getInt(TString key, TString section, int def)
    {
        int result = def;

        IAttributes* attr;
        attr = getSection(section);
        if(!attr)
            return result;

        u32 idx = attr->findAttribute(key.c_str());
        if(idx >= 0)
            result = attr->getAttributeAsInt(idx);

        return result;
    }

    f32 TXMLConfig::getFloat(TString key, TString section, f32 def)
    {
        f32 result = def;

        IAttributes* attr;
        attr = getSection(section);
        if(!attr)
            return result;

        u32 idx = attr->findAttribute(key.c_str());
        if(idx >= 0)
            result = attr->getAttributeAsFloat(idx);

        return result;
    }

    //-----------------------------------------------------------------------
    //                          g e t V e c t o r 3
    //-----------------------------------------------------------------------
    TVector3 TXMLConfig::getVector3(TString key, TString section, TVector3 def)
    {
        TVector3 result = def;

        IAttributes* attr;
        attr = getSection(section);
        if(!attr)
            return result;

        u32 idx = attr->findAttribute(key.c_str());
        if(idx >= 0)
        {
            TString temp = attr->getAttributeAsString(idx);
            CNumbersAttribute na("temp",TVector3());
            na.setString(temp.c_str());
            result = na.getVector();
        }
        return result;

    }

    //-----------------------------------------------------------------------
    //                          g e t V e c t o r 2
    //-----------------------------------------------------------------------
    TVector2 TXMLConfig::getVector2(TString key, TString section, TVector2 def)
    {
        TVector2 result = def;

        IAttributes* attr;
        attr = getSection(section);
        if(!attr)
            return result;

        u32 idx = attr->findAttribute(key.c_str());
        if(idx >= 0)
        {
            TString temp = attr->getAttributeAsString(idx);
            CNumbersAttribute na("temp",TVector3());
            na.setString(temp.c_str());
            vector2df tv = na.getVector2d();
            result.X = tv.X;
            result.Y = tv.Y;
        }
        return result;

    }

    //-----------------------------------------------------------------------
    //                          g e t D i m e n s i o n
    //-----------------------------------------------------------------------
    TDimension TXMLConfig::getDimension(TString key, TString section, TDimension def)
    {
        TDimension result = def;

        IAttributes* attr;
        attr = getSection(section);
        if(!attr)
            return result;

        u32 idx = attr->findAttribute(key.c_str());
        if(idx >= 0)
        {
            TString temp = attr->getAttributeAsString(idx);
            CNumbersAttribute na("temp",position2di());
            na.setString(temp.c_str());
            position2di td = na.getPosition();
            result.Width = td.X;
            result.Height = td.Y;
        }
        return result;
    }

    //-----------------------------------------------------------------------
    //                          g e t C o l o u r
    //-----------------------------------------------------------------------
    TColour TXMLConfig::getColour(TString key, TString section, TColour def)
    {
        TColour result = def;

        IAttributes* attr;
        attr = getSection(section);
        if(!attr)
            return result;

        u32 idx = attr->findAttribute(key.c_str());
        if(idx >= 0)
        {
            TString temp = attr->getAttributeAsString(idx);
            CNumbersAttribute na("temp",TColour());
            na.setString(temp.c_str());
            result = na.getColor();
        }
        return result;
    }


}