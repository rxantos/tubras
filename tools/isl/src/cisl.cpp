//-----------------------------------------------------------------------------
// Copyright (c) 2006-2008 Tubras Software, Ltd
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.txt" for detailed information.
//-----------------------------------------------------------------------------
#include "cisl.h"
#include "cislParser.h"
#include <errno.h>

namespace isl
{
    irr::core::vector2di CISL::m_defVector2di=irr::core::vector2di();
    irr::video::SColor   CISL::m_defColor=irr::video::SColor();
    irr::core::vector3df CISL::m_defVector3df=irr::core::vector3df();
    irr::core::rect<irr::s32> CISL::m_defRects32=irr::core::rect<irr::s32>();

    //-------------------------------------------------------------------------
    //                                  C I S L
    //-------------------------------------------------------------------------
    CISL::CISL() : m_parser(0)
    {
    }

    //-------------------------------------------------------------------------
    //                                 ~ C I S L
    //-------------------------------------------------------------------------
    CISL::~CISL()
    {
        if(m_parser)
            delete m_parser;
    }

    //-------------------------------------------------------------------------
    //                           p a r s e S c r i p t
    //-------------------------------------------------------------------------
    CISLStatus CISL::parseScript(const irr::core::stringc fileName, 
        const bool dumpAST, const bool dumpST, const bool dumpOI,
        const CISLErrorHandler& errorHandler)
    {
        CISLStatus result=E_OK;
        if(m_parser)
            delete m_parser;

        m_parser = new CISLParser();

        result = m_parser->parseScript(fileName, dumpAST, dumpST, dumpOI, errorHandler);

        return result;
    }

    //-------------------------------------------------------------------------
    //                           g e t M a t e r i a l
    //-------------------------------------------------------------------------
    const irr::video::SMaterial& CISL::getMaterial(irr::IrrlichtDevice* device,  
        const irr::core::stringc varName)
    {
        return *(m_parser->getMaterial(device, varName));
    }

    //-------------------------------------------------------------------------
    //                             g e t C o l o r
    //-------------------------------------------------------------------------
    const irr::video::SColor& CISL::getColor(const irr::core::stringc varName,
        irr::video::SColor& defValue)
    {
        return m_parser->getColor(varName, defValue);
    }

    //-------------------------------------------------------------------------
    //                          g e t V e c t o r 2 d i   
    //-------------------------------------------------------------------------
    irr::core::vector2di CISL::getVector2di(const irr::core::stringc varName,
        const irr::core::vector2di defValue)
    {
        return m_parser->getVector2di(varName, defValue);
    }

    //-------------------------------------------------------------------------
    //                          g e t V e c t o r 3 d f
    //-------------------------------------------------------------------------
    irr::core::vector3df CISL::getVector3df(const irr::core::stringc varName,
        const irr::core::vector3df& defValue)
    {
        return m_parser->getVector3df(varName, defValue);
    }

    //-------------------------------------------------------------------------
    //                       g e t D i m e n s i o n 2 d i       
    //-------------------------------------------------------------------------
    irr::core::dimension2di CISL::getDimension2di(const irr::core::stringc varName, 
        const irr::core::dimension2di defValue)
    {
        irr::core::dimension2di result;
        irr::core::vector2di defValue2(defValue.Width, defValue.Height);

        irr::core::vector2di iresult = m_parser->getVector2di(varName, defValue2);
        result.Width = iresult.X;
        result.Height = iresult.Y;

        return result;
    }

    //-------------------------------------------------------------------------
    //                           g e t R e c t s 3 2
    //-------------------------------------------------------------------------
    irr::core::rect<irr::s32> CISL::getRects32(const irr::core::stringc varName,
        irr::core::rect<irr::s32> defValue)
    {
        return m_parser->getRects32(varName, defValue);
    }

    //-------------------------------------------------------------------------
    //                       g e t S t r i n g A r r a y
    //-------------------------------------------------------------------------
    irr::core::array<irr::core::stringc> CISL::getStringArray(const irr::core::stringc varName)
    {
        return m_parser->getStringArray(varName);
    }

    //-------------------------------------------------------------------------
    //                       g e t S t r i n g M a p
    //-------------------------------------------------------------------------
    bool CISL::getStringMap(const irr::core::stringc varName, STRINGMAP& out, bool scopedID)
    {
        return m_parser->getStringMap(varName, out, scopedID);
    }

    //-------------------------------------------------------------------------
    //                           g e t I n t e g e r    
    //-------------------------------------------------------------------------
    int CISL::getInteger(const irr::core::stringc varName, const int defValue)
    {
        return m_parser->getInt(varName, defValue);
    }

    //-------------------------------------------------------------------------
    //                           g e t F l o a t
    //-------------------------------------------------------------------------
    irr::f32 CISL::getFloat(const irr::core::stringc varName, const irr::f32 defValue)
    {
        return m_parser->getFloat(varName, defValue);
    }


    //-------------------------------------------------------------------------
    //                            g e t B o o l 
    //-------------------------------------------------------------------------
    bool CISL::getBool(const irr::core::stringc varName, const bool defValue)
    {
        return m_parser->getInt(varName, defValue) ? true : false;
    }

    //-------------------------------------------------------------------------
    //                          g e t S t r i n g 
    //-------------------------------------------------------------------------
    irr::core::stringc CISL::getString(const irr::core::stringc varName, 
        const irr::core::stringc defValue)
    {
        return m_parser->getString(varName, defValue);
    }

    //-------------------------------------------------------------------------
    //                          g e t A n i m a t o r
    //-------------------------------------------------------------------------
    isl::CSceneNodeAnimatorMaterialLayer* CISL::getAnimator()
    {
        return m_parser->getAnimator();
    }

    //-------------------------------------------------------------------------
    //                    i s A n i m a t e d M a t e r i a l
    //-------------------------------------------------------------------------
    bool CISL::isAnimatedMaterial(irr::core::stringc materialName)
    {
        return m_parser->isAnimatedMaterial(materialName);
    }

    //-------------------------------------------------------------------------
    //                       a d d A n i m a t i o n R e f
    //-------------------------------------------------------------------------
    void CISL::addAnimationRef(irr::core::stringc materialName, irr::video::SMaterial& ref)
    {
        m_parser->addAnimationRef(materialName, ref);
    }

    //-------------------------------------------------------------------------
    //                        g e t G U I E l e m e n t
    //-------------------------------------------------------------------------
    irr::gui::IGUIElement* CISL::getGUIElement(irr::IrrlichtDevice* device, 
        const irr::core::stringc varName)
    {
        return m_parser->getGUIElement(device, varName);
    }
}
