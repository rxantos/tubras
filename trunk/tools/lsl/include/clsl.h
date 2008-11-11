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
    typedef irr::core::list<irr::core::stringc> SSTACK;
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

        void _dumpStack();
        void _dumpGlobals();
        void _setPackagePath();
        int  _splitName(irr::core::stringc name, SSTACK& nameStack);
        irr::core::stringc _extractDir(irr::core::stringc filename);

        const char* _getTableFieldString (const char* table, const char *key);
        bool _setTableFieldString (const char* table, const char *key, const char* value);

    public:
        CLSL();
        virtual ~CLSL();

        CLSLStatus parseScript(const irr::core::stringc fileName, 
            const bool dumpST=false, const bool dumpOI=false,
            const CLSLErrorHandler& errorHandler=CLSLErrorHandler());

        bool isAnimatedMaterial(irr::core::stringc materialName);

        void addAnimationRef(irr::core::stringc materialName, irr::video::SMaterial& ref);

        irr::core::array<irr::core::stringc> getStringArray(const irr::core::stringc varName);
        bool getStringMap(const irr::core::stringc varName, STRINGMAP& out, bool scopedID=true);


        // basic types
        irr::f32 getFloat(const irr::core::stringc varName, const irr::f32 defValue = 0);

        int getInteger(const irr::core::stringc varName, const int defValue = 0);

        bool getBool(const irr::core::stringc varName, const bool defValue = false);

        irr::core::stringc getString(const irr::core::stringc varName, 
            const irr::core::stringc defValue="");

        // complex types
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
            const irr::core::vector2di defValue=m_defVector2di);

        irr::core::vector3df getVector3df(const irr::core::stringc varName,
            const irr::core::vector3df& defValue=m_defVector3df);

        irr::core::rect<irr::s32> getRects32(const irr::core::stringc varName,
            const irr::core::rect<irr::s32> defValue=m_defRects32);

        irr::core::dimension2di getDimension2di(const irr::core::stringc varName, 
            const irr::core::dimension2di defValue=irr::core::dimension2di());

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
