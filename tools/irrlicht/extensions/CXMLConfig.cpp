//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "CXMLConfig.h"
#include "CAttributeImpl.h"
#include "IrrlichtDevice.h"
#include "irrlicht.h"

namespace irr {
    namespace io {
    //-----------------------------------------------------------------------
    //                          T X M L C o n f i g
    //-----------------------------------------------------------------------
    CXMLConfig::CXMLConfig()
    {
    }

    //-----------------------------------------------------------------------
    //                          T X M L C o n f i g
    //-----------------------------------------------------------------------
    CXMLConfig::~CXMLConfig()
    {
        TSectionMapItr sit;

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
    bool CXMLConfig::load(const core::stringc& filename)
    {
        IrrXMLReader* xml = createIrrXMLReader(filename.c_str());
        IAttributes* attr;

        if(!xml)
            return false;

        IrrlichtDevice* device = irr::createDevice(video::EDT_NULL);
        attr = device->getFileSystem()->createEmptyAttributes();


        core::stringc sectionName, nodeName, nodeValue;

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
                    TSectionMap::Node* node = m_sections.find(sectionName);
                    if(!node)
                    {
                        attr = device->getFileSystem()->createEmptyAttributes();
                        m_sections.insert(sectionName,attr);
                    }
                }
                break;
            default:
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
    IAttributes* CXMLConfig::getSection(const core::stringc& name)
    {
        TSectionMap::Node* node;

        node = m_sections.find(name);
        if(!node)
            return NULL;

        return node->getValue();
    }


    //-----------------------------------------------------------------------
    //                         g e t S t r i n g
    //-----------------------------------------------------------------------
    core::stringc CXMLConfig::getString(const core::stringc& key, const core::stringc& section, const core::stringc& def)
    {
        core::stringc result = def;

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
    bool CXMLConfig::getBool(const core::stringc& key, const core::stringc& section, const bool& def)
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
    int CXMLConfig::getInt(const core::stringc& key, const core::stringc& section, const int& def)
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
    f32 CXMLConfig::getFloat(const core::stringc& key, const core::stringc& section, f32 def)
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
    core::vector3df CXMLConfig::getVector3(const core::stringc& key, const core::stringc& section, const core::vector3df& def)
    {
        core::vector3df result = def;

        IAttributes* attr;
        attr = getSection(section);
        if(!attr)
            return result;

        s32 idx = attr->findAttribute(key.c_str());
        if(idx >= 0)
        {
            core::stringc temp = attr->getAttributeAsString(idx);
            CNumbersAttribute na("temp",core::vector3df());
            na.setString(temp.c_str());
            result = na.getVector();
        }
        return result;

    }

    //-----------------------------------------------------------------------
    //                          g e t V e c t o r 2
    //-----------------------------------------------------------------------
    core::vector2df CXMLConfig::getVector2(const core::stringc& key, const core::stringc& section, const core::vector2df& def)
    {
        core::vector2df result = def;

        IAttributes* attr;
        attr = getSection(section);
        if(!attr)
            return result;

        s32 idx = attr->findAttribute(key.c_str());
        if(idx >= 0)
        {
            core::stringc temp = attr->getAttributeAsString(idx);
            CNumbersAttribute na("temp",core::vector2df());
            na.setString(temp.c_str());
            core::vector2df tv = na.getVector2d();
            result.X = tv.X;
            result.Y = tv.Y;
        }
        return result;

    }

    //-----------------------------------------------------------------------
    //                          g e t D i m e n s i o n
    //-----------------------------------------------------------------------
    core::dimension2di CXMLConfig::getDimension(const core::stringc& key, const core::stringc& section, const core::dimension2di& def)
    {
        core::dimension2di result = def;

        IAttributes* attr;
        attr = getSection(section);
        if(!attr)
            return result;

        s32 idx = attr->findAttribute(key.c_str());
        if(idx >= 0)
        {
            core::stringc temp = attr->getAttributeAsString(idx);
            CNumbersAttribute na("temp",def);
            na.setString(temp.c_str());
            core::position2di td = na.getPosition();
            result.Width = td.X;
            result.Height = td.Y;
        }
        return result;
    }

    //-----------------------------------------------------------------------
    //                          g e t C o l o u r
    //-----------------------------------------------------------------------
    video::SColor CXMLConfig::getColor(const core::stringc& key, const core::stringc& section, const video::SColor& def)
    {
        video::SColor result = def;

        IAttributes* attr;
        attr = getSection(section);
        if(!attr)
            return result;

        s32 idx = attr->findAttribute(key.c_str());
        if(idx >= 0)
        {
            core::stringc temp = attr->getAttributeAsString(idx);
            CNumbersAttribute na("temp",video::SColor());
            na.setString(temp.c_str());
            result = na.getColor();
        }
        return result;
    }


}
}
