//-----------------------------------------------------------------------------
// Copyright (c) 2006-2008 Tubras Software, Ltd
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.txt" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _CISL_H_
#define _CISL_H_

#include "islLexer.h"
#include "islParser.h"
#include "irrlicht.h"
#include "cst.h"

namespace CISL {

    class CISL;

    enum CISLStatus {
        E_OK,
        E_NO_FILE,
        E_BAD_INPUT,
        E_OUT_OF_MEMORY,
        E_BAD_SYNTAX
    };

    typedef irr::core::array<irr::core::stringc>  ARRAY;

    class CISLErrorHandler 
    {
    public:
        virtual int handleError(int line, int code, irr::core::stringc errMessage)
        {
            printf("CISL Error (%d), line: %d, message: %s\n",code, line, errMessage.c_str());
            return 0;
        }
    };

    class CISLParser;

    class CISL 
    {
    protected:
        CISLParser*             m_parser;

    public:
        CISL();
        virtual ~CISL();

        CISLStatus parseScript(const irr::core::stringc fileName, const CISLErrorHandler& errorHandler=CISLErrorHandler());

        const irr::video::SMaterial* getMaterial(const irr::video::IVideoDriver* videoDriver, 
            const irr::core::stringc varName);
        const irr::video::SMaterialLayer* getMaterialLayer(const irr::video::IVideoDriver* videoDriver, 
            const irr::core::stringc varName);

        const irr::core::matrix4& getMatrix(const irr::core::stringc varName);
        const irr::video::SColor* getColor(const irr::core::stringc varName);

        float getFloat(const irr::core::stringc varName);
        int getInt(const irr::core::stringc varName);
        const irr::core::stringc getString(const irr::core::stringc varName);
        const void* getList(const irr::core::stringc varName);

    };

}

#endif
