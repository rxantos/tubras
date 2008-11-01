//-----------------------------------------------------------------------------
// Copyright (c) 2006-2008 Tubras Software, Ltd
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.txt" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _CISL_H_
#define _CISL_H_
#include "irrlicht.h"

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

        CISLStatus parseScript(const irr::core::stringc fileName, 
            const bool dumpAST=false, const bool dumpST=false, const bool dumpOI=false,
            const CISLErrorHandler& errorHandler=CISLErrorHandler());

        const irr::video::SMaterial& getMaterial(irr::video::IVideoDriver* videoDriver, 
            const irr::core::stringc varName);

        const irr::video::SMaterialLayer& getMaterialLayer(irr::video::IVideoDriver* videoDriver, 
            const irr::core::stringc varName);

        const irr::core::matrix4& getMatrix(const irr::core::stringc varName);

        const irr::video::SColor& getColor(const irr::core::stringc varName,
            irr::video::SColor& defValue = irr::video::SColor());

        irr::core::vector2di getVector2di(const irr::core::stringc varName);

        irr::core::dimension2di getDimension2di(const irr::core::stringc varName, 
            irr::core::dimension2di defValue=irr::core::dimension2di());

        irr::f32 getFloat(const irr::core::stringc varName, const irr::f32 defValue);

        int getInteger(const irr::core::stringc varName, const int defValue = 0);

        bool getBool(const irr::core::stringc varName, const bool defValue = false);

        irr::core::stringc getString(const irr::core::stringc varName, 
            const irr::core::stringc defValue="");

        void* getList(const irr::core::stringc varName);

    };

}

#endif
