//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"
#include "CAttributeImpl.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                          T X M L C o n f i g
    //-----------------------------------------------------------------------
    TXMLConfig::TXMLConfig(IrrlichtDevice* device) : m_device(device)
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
    bool TXMLConfig::load(const TString& filename)
    {

        IrrXMLReader* xml = createIrrXMLReader(filename.c_str());
        IAttributes* attr;

        if(!xml)
            return false;

        IrrlichtDevice* device = m_device;
        if(!device)
        {
            if(!getApplication())
                return false;
            device = getApplication()->getNullDevice();
            if(!device)
                return false;
        }

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

        delete xml;
        return true;
    }

    //-----------------------------------------------------------------------
    //                         g e t S e c t i o n
    //-----------------------------------------------------------------------
    IAttributes* TXMLConfig::getSection(const TString& name)
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
    TString TXMLConfig::getString(const TString& key, const TString& section, const TString& def)
    {
        TString result = def;

        IAttributes* attr;
        attr = getSection(section);
        if(!attr)
            return result;

        s32 idx = attr->findAttribute(key.c_str());
        if(idx >= 0)
            result = attr->getAttributeAsString(idx);

        return result;
    }

    //-----------------------------------------------------------------------
    //                            g e t B o o l
    //-----------------------------------------------------------------------
    bool TXMLConfig::getBool(const TString& key, const TString& section, const bool& def)
    {
        bool result = def;

        IAttributes* attr;
        attr = getSection(section);
        if(!attr)
            return result;

        s32 idx = attr->findAttribute(key.c_str());
        if(idx >= 0)
            result = attr->getAttributeAsBool(idx);

        return result;
    }

    //-----------------------------------------------------------------------
    //                             g e t I n t
    //-----------------------------------------------------------------------
    int TXMLConfig::getInt(const TString& key, const TString& section, const int& def)
    {
        int result = def;

        IAttributes* attr;
        attr = getSection(section);
        if(!attr)
            return result;

        s32 idx = attr->findAttribute(key.c_str());
        if(idx >= 0)
            result = attr->getAttributeAsInt(idx);

        return result;
    }

    //-----------------------------------------------------------------------
    //                             g e t F l o a t
    //-----------------------------------------------------------------------
    f32 TXMLConfig::getFloat(const TString& key, const TString& section, f32 def)
    {
        f32 result = def;

        IAttributes* attr;
        attr = getSection(section);
        if(!attr)
            return result;

        s32 idx = attr->findAttribute(key.c_str());
        if(idx >= 0)
            result = attr->getAttributeAsFloat(idx);

        return result;
    }

    //-----------------------------------------------------------------------
    //                          g e t V e c t o r 3
    //-----------------------------------------------------------------------
    TVector3 TXMLConfig::getVector3(const TString& key, const TString& section, const TVector3& def)
    {
        TVector3 result = def;

        IAttributes* attr;
        attr = getSection(section);
        if(!attr)
            return result;

        s32 idx = attr->findAttribute(key.c_str());
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
    TVector2 TXMLConfig::getVector2(const TString& key, const TString& section, const TVector2& def)
    {
        TVector2 result = def;

        IAttributes* attr;
        attr = getSection(section);
        if(!attr)
            return result;

        s32 idx = attr->findAttribute(key.c_str());
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
    TDimension TXMLConfig::getDimension(const TString& key, const TString& section, const TDimension& def)
    {
        TDimension result = def;

        IAttributes* attr;
        attr = getSection(section);
        if(!attr)
            return result;

        s32 idx = attr->findAttribute(key.c_str());
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
    //                           g e t R e c t d
    //-----------------------------------------------------------------------
    TRectd TXMLConfig::getRectd(const TString& key, const TString& section,const TRectd& def)
    {
        TRectd result = def;

        IAttributes* attr;
        attr = getSection(section);
        if(!attr)
            return result;

        s32 idx = attr->findAttribute(key.c_str());
        if(idx >= 0)
        {
            TString temp = attr->getAttributeAsString(idx);
            CNumbersAttribute na("temp",TRectd());
            na.setString(temp.c_str());
            result = na.getRect();
        }
        return result;
    }

    //-----------------------------------------------------------------------
    //                          g e t C o l o u r
    //-----------------------------------------------------------------------
    TColour TXMLConfig::getColour(const TString& key, const TString& section, const TColour& def)
    {
        TColour result = def;

        IAttributes* attr;
        attr = getSection(section);
        if(!attr)
            return result;

        s32 idx = attr->findAttribute(key.c_str());
        if(idx >= 0)
        {
            TString temp = attr->getAttributeAsString(idx);
            CNumbersAttribute na("temp",TColour());
            na.setString(temp.c_str());
            SColor c;
            c = na.getColor();
            result = c;
        }
        return result;
    }


}
