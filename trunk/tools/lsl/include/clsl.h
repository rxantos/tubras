//-----------------------------------------------------------------------------
// Copyright (c) 2006-2008 Tubras Software, Ltd
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.txt" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _CLSL_H_
#define _CLSL_H_
#include "irrlicht.h"
//#include "CSceneNodeAnimatorMaterialLayer.h"
struct lua_State;

namespace lsl {    

    enum CLSLStatus {
        E_OK,
        E_NO_FILE,
        E_BAD_INPUT,
        E_OUT_OF_MEMORY,
        E_BAD_SYNTAX
    };

    typedef irr::core::array<irr::core::stringc>  ARRAY;
    typedef irr::core::map<irr::core::stringc, irr::core::stringc> STRINGMAP;
    typedef irr::core::map<irr::core::stringc, irr::core::stringc>::Iterator STRINGMAPITR;

    class CLSLErrorHandler 
    {
    public:
        virtual int handleError(int line, int code, irr::core::stringc errMessage)
        {
            printf("CISL Error (%d), line: %d, message: %s\n",code, line, errMessage.c_str());
            return 0;
        }
    };

    class CLSL : public irr::IReferenceCounted
    {
    private:
        lua_State*                      L;
        irr::core::stringc              m_scriptName;

    protected:
        static irr::video::SColor       m_defColor;
        static irr::core::vector2di     m_defVector2di;
        static irr::core::vector3df     m_defVector3df;
        static irr::core::rect<irr::s32>m_defRects32;


    public:
        CLSL();
        virtual ~CLSL();

        CLSLStatus parseScript(const irr::core::stringc fileName, 
            const bool dumpST=false, const bool dumpOI=false,
            const CLSLErrorHandler& errorHandler=CLSLErrorHandler());

        static void dumpStack(lua_State* L);

    };

#ifdef _DEBUG
#pragma comment(lib, "libCLSL_d.lib")

#pragma warning( push )
#pragma warning( disable : 4068 )
#pragma library("libCLSL_d.lib")
#pragma warning( pop )
#else
#pragma comment(lib, "libCLSL.lib")

#pragma warning( push )
#pragma warning( disable : 4068 )
#pragma library("libCLSL.lib")
#pragma warning( pop )
#endif


}
#endif
