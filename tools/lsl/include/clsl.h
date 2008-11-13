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

    //! Class representing an LSL script parser.
	/** This class may be used to load and parse a config,
    material, and/or material layer script.
	*/    class CLSL : public irr::IReferenceCounted
    {
    private:
        lua_State*                      L;
        irr::core::stringc              m_scriptName;

    protected:
        static irr::video::SColor       m_defColor;
        static irr::core::vector2di     m_defVector2di;
        static irr::core::vector3df     m_defVector3df;
        static irr::core::rect<irr::s32>m_defRects32;

        //! dumps the current lua stack to stdout
        void _dumpStack();

        //! dumps the global (_G) symbol table
        void _dumpGlobals();

        //! sets the package search path
        void _setPackagePath();

        //! splits a scoped/qualified name and stores the result in a string list
        /** given a name like "video.colors.background", the nameStack will 
        contain "video", "colors", and "background".
        \param name: name to split.
        \param nameStack: string list to populate.
        \return the stack item count.
        */
        int  _splitName(irr::core::stringc name, SSTACK& nameStack);

        //! extracts the directory from a file path
        irr::core::stringc _extractDir(irr::core::stringc filename);

        //! determines if a lua table indexes are all numeric.
        /**
        /param table: lua table at the top of the lua stack.
        */
        bool _tableKeysNumeric();

        //! prints the values of a lua table
        /**
        /param (lua) table: lua table at the top of the lua stack.
        */
        void _printTable();

        //! retrieves a lua table field as an integer.
        /**
        /param (lua) table: lua table at the top of the lua stack.
        /param fieldName: the table field name to retrieve.
        /return the field value. 0 if it doesn't exist.
        */
        irr::u32 _getFieldInt(char *fieldName);

        //! pushes the lua value onto the top of the lua stack for the given variable name.
        /**
        /param: varName: the scoped variable name.
        /return the lua TValue* that is at the top of the stack. 0 if not found.
        */
        void* _pushValue(const irr::core::stringc varName);

        const char* _getTableFieldString (const char* table, const char *key);
        bool _setTableFieldString (const char* table, const char *key, const char* value);

    public:
        //! CLSL Class constructor.
        CLSL();

        //! CLSL Class destructor.
        virtual ~CLSL();

        //! loads, parses, and executes the given script.
        /**
        /param fileName: the file name of the script to load.
        /param dumpST: dump the symbol table to stdout.
        /param dumpOI: dump the material, matrix, layer, and config objects to stdout.
        /param errorHandler: user specified error handler.
        /return CLSLStatus
        */
        CLSLStatus loadScript(const irr::core::stringc fileName, 
            const bool dumpST=false, const bool dumpOI=false,
            const CLSLErrorHandler& errorHandler=CLSLErrorHandler());

        //! deterimines if a given material contains texture layer matrix animation
        /**
        /param materialName: the material to check.
        /return true if the material has matrix animation. otherwise false.
        */
        bool isAnimatedMaterial(irr::core::stringc materialName);

        //! adds an animation reference to the global material layer animation class.
        void addAnimationRef(irr::core::stringc materialName, irr::video::SMaterial& ref);

        //! returns a string array for the given variable name.
        /**
        given var = {1, 'test', 2, 'test2'}, the returned string array for "var" will contain
        "1", "2", "test", & "test2".
        */
        irr::core::array<irr::core::stringc> getStringArray(const irr::core::stringc varName);

        //! returns a string map of key/value pairs for the given variable name.
        /**
        given test = {a=1, b=2, c=3, d='test'}, the returned string map for "test" will contain
        "a":"a", "b":"s", "c":"3", & "d":"test".
        */
        bool getStringMap(const irr::core::stringc varName, STRINGMAP& out, bool scopedID=true);

        //! returns the float value for the given variable name.
        irr::f32 getFloat(const irr::core::stringc varName, const irr::f32 defValue = 0);

        //! returns the integer value for the given variable name.
        int getInteger(const irr::core::stringc varName, const int defValue = 0);

        //! returns the booleant value for the given variable name.
        bool getBool(const irr::core::stringc varName, const bool defValue = false);

        //! returns the float string for the given variable name.
        irr::core::stringc getString(const irr::core::stringc varName, 
            const irr::core::stringc defValue="");

        //! returns the SMaterial value for the given variable name.
        const irr::video::SMaterial& getMaterial(irr::IrrlichtDevice* device, 
            const irr::core::stringc varName);

        //! returns the SMaterialLayer value for the given variable name.
        const irr::video::SMaterialLayer& getMaterialLayer(irr::IrrlichtDevice* device, 
            const irr::core::stringc varName);

        //! returns the IGUIElement value for the given variable name.
        irr::gui::IGUIElement* getGUIElement(irr::IrrlichtDevice* device, 
            const irr::core::stringc varName);

        //! returns the matrix4 value for the given variable name.
        const irr::core::matrix4& getMatrix(const irr::core::stringc varName);

        //! returns the SColor value for the given variable name.
        const irr::video::SColor& getColor(const irr::core::stringc varName,
            irr::video::SColor defValue = m_defColor);

        //! returns the vector2di value for the given variable name.
        irr::core::vector2di getVector2di(const irr::core::stringc varName,
            const irr::core::vector2di defValue=m_defVector2di);

        //! returns the vector3df value for the given variable name.
        irr::core::vector3df getVector3df(const irr::core::stringc varName,
            const irr::core::vector3df& defValue=m_defVector3df);

        //! returns the rect<s32> value for the given variable name.
        irr::core::rect<irr::s32> getRects32(const irr::core::stringc varName,
            const irr::core::rect<irr::s32> defValue=m_defRects32);

        //! returns the dimension2di value for the given variable name.
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
