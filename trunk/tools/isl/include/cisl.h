//-----------------------------------------------------------------------------
// Copyright (c) 2006-2008 Tubras Software, Ltd
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.txt" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _CISL_H_
#define _CISL_H_
#include "irrlicht.h"
#include "CSceneNodeAnimatorMaterialLayer.h"

namespace isl {    

    enum CISLStatus {
        E_OK,
        E_NO_FILE,
        E_BAD_INPUT,
        E_OUT_OF_MEMORY,
        E_BAD_SYNTAX
    };

    typedef irr::core::array<irr::core::stringc>  ARRAY;
    typedef irr::core::map<irr::core::stringc, irr::core::stringc> STRINGMAP;
    typedef irr::core::map<irr::core::stringc, irr::core::stringc>::Iterator STRINGMAPITR;

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

    class CISL : public irr::IReferenceCounted
    {
    protected:
        CISLParser*             m_parser;
        static irr::video::SColor       m_defColor;
        static irr::core::vector2di     m_defVector2di;
        static irr::core::vector3df     m_defVector3df;
        static irr::core::rect<irr::s32>m_defRects32;



    public:
        CISL();
        virtual ~CISL();

        CISLStatus parseScript(const irr::core::stringc fileName, 
            const bool dumpAST=false, const bool dumpST=false, const bool dumpOI=false,
            const CISLErrorHandler& errorHandler=CISLErrorHandler());

        const irr::video::SMaterial& getMaterial(irr::IrrlichtDevice* device, 
            const irr::core::stringc varName);

        const irr::video::SMaterialLayer& getMaterialLayer(irr::IrrlichtDevice* device, 
            const irr::core::stringc varName);

        irr::gui::IGUIElement* getGUIElement(irr::IrrlichtDevice* device, 
            const irr::core::stringc varName);

        const irr::core::matrix4& getMatrix(const irr::core::stringc varName);

        const irr::video::SColor& getColor(const irr::core::stringc varName,
            irr::video::SColor& defValue = m_defColor);

        irr::core::vector2di getVector2di(const irr::core::stringc varName,
            const irr::core::vector2di=m_defVector2di);

        irr::core::vector3df getVector3df(const irr::core::stringc varName,
            const irr::core::vector3df& defValue=m_defVector3df);

        irr::core::rect<irr::s32> getRects32(const irr::core::stringc varName,
            const irr::core::rect<irr::s32> defValue=m_defRects32);

        irr::core::dimension2di getDimension2di(const irr::core::stringc varName, 
            const irr::core::dimension2di defValue=irr::core::dimension2di());

        irr::f32 getFloat(const irr::core::stringc varName, const irr::f32 defValue);

        int getInteger(const irr::core::stringc varName, const int defValue = 0);

        bool getBool(const irr::core::stringc varName, const bool defValue = false);

        irr::core::stringc getString(const irr::core::stringc varName, 
            const irr::core::stringc defValue="");

        isl::CSceneNodeAnimatorMaterialLayer* getAnimator();

        bool isAnimatedMaterial(irr::core::stringc materialName);

        void addAnimationRef(irr::core::stringc materialName, irr::video::SMaterial& ref);

        irr::core::array<irr::core::stringc> getStringArray(const irr::core::stringc varName);
        bool getStringMap(const irr::core::stringc varName, STRINGMAP& out, bool scopedID=true);

    };

#ifdef _DEBUG
#pragma comment(lib, "libCISL_d.lib")

#pragma warning( push )
#pragma warning( disable : 4068 )
#pragma library("libCISL_d.lib")
#pragma warning( pop )
#else
#pragma comment(lib, "libCISL.lib")

#pragma warning( push )
#pragma warning( disable : 4068 )
#pragma library("libCISL.lib")
#pragma warning( pop )
#endif


}
#endif
