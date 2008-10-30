//-----------------------------------------------------------------------------
// Copyright (c) 2006-2008 Tubras Software, Ltd
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.txt" for detailed information.
//-----------------------------------------------------------------------------
#include "cisl.h"
#include "cislParser.h"
#include <errno.h>

namespace CISL
{
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
        const CISLErrorHandler& errorHandler)
    {
        CISLStatus result=E_OK;
        if(!m_parser)
            delete m_parser;

        m_parser = new CISLParser();

        result = m_parser->parseScript(fileName, errorHandler);

        return result;
    }

    //-------------------------------------------------------------------------
    //                           g e t M a t e r i a l
    //-------------------------------------------------------------------------
    irr::video::SMaterial* CISL::getMaterial(const irr::video::IVideoDriver* videoDriver, 
            const irr::core::stringc varName)
    {
        return m_parser->getMaterial(videoDriver, varName);
    }

    //-------------------------------------------------------------------------
    //                          g e t V e c t o r 2 d i   
    //-------------------------------------------------------------------------
    irr::core::vector2di CISL::getVector2di(const irr::core::stringc varName)
    {
        return m_parser->getVector2di(varName);
    }

    //-------------------------------------------------------------------------
    //                       g e t D i m e n s i o n 2 d i       
    //-------------------------------------------------------------------------
    irr::core::dimension2di CISL::getDimension2di(const irr::core::stringc varName, 
            irr::core::dimension2di defValue)
    {
        irr::core::dimension2di result;

        irr::core::vector2di iresult = m_parser->getVector2di(varName);
        result.Width = iresult.X;
        result.Height = iresult.Y;

        return result;
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
}
