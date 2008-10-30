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
    CISLStatus CISL::parseScript(const irr::core::stringc fileName, const CISLErrorHandler& errorHandler)
    {
        CISLStatus result=E_OK;
        if(!m_parser)
            delete m_parser;

        m_parser = new CISLParser();

        result = m_parser->parseScript(fileName, errorHandler);

        return result;
    }

    irr::video::SMaterial* CISL::getMaterial(const irr::video::IVideoDriver* videoDriver, 
            const irr::core::stringc varName)
    {
        return m_parser->getMaterial(videoDriver, varName);
    }

    irr::core::vector2di CISL::getVector2di(const irr::core::stringc varName)
    {
        return m_parser->getVector2di(varName);
    }

    irr::core::dimension2di CISL::getDimension2di(const irr::core::stringc varName, 
            irr::core::dimension2di defValue)
    {
        irr::core::dimension2di result;

        irr::core::vector2di iresult = m_parser->getVector2di(varName);
        result.Width = iresult.X;
        result.Height = iresult.Y;

        return result;
    }


    int CISL::getInteger(const irr::core::stringc varName, const int defValue)
    {
        return m_parser->getInt(varName, defValue);
    }

    bool CISL::getBool(const irr::core::stringc varName, const bool defValue)
    {
        return m_parser->getInt(varName, defValue) ? true : false;
    }



}
