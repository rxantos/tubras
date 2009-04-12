//-----------------------------------------------------------------------------
// Copyright (c) 2006-2009 Tubras Software, Ltd
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.txt" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TSL_H_
#define _TSL_H_
struct lua_State;

namespace Tubras {    

    #define ITYPE_MATERIAL          1
    #define ITYPE_MATERIAL_LAYER    2
    #define ITYPE_GUIELEMENT        3
    #define ITYPE_PARTICLE          4

    enum TSLStatus {
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

    class TSLErrorHandler 
    {
    public:
        virtual int handleError(irr::core::stringc fileName, int line, int code, irr::core::stringc errMessage)
        {
            printf("TSL Error (%d), line: %d, message: %s\n",code, line, errMessage.c_str());
            return 0;
        }
    };

    //! Class representing a TSL script parser.
	/** This class may be used to load and parse a config,
    material, and/or material layer script.
	*/    
    class TSL : public irr::IReferenceCounted
    {
    protected:
        enum SYMTYPE {stUnknown, stMaterial, stMaterialLayer, stGUIElement, stParticle};
        typedef struct _SYMDATA_
        {
            irr::core::stringc  name;
            SYMTYPE             type;
            void*               typeData;
            irr::IReferenceCounted* userData;

            _SYMDATA_() : name(""),
                type(stUnknown),
                typeData(0),
                userData(0)
            {}
        } SYMDATA;
        typedef irr::core::map<irr::core::stringc, SYMDATA*> SYMMAP;        

    protected:
        lua_State*                      L;
        irr::core::stringc              m_scriptName;

        SYMMAP                          m_matDefs;
        SYMMAP                          m_layDefs;
        SYMMAP                          m_guiDefs;

    protected:

        static irr::video::SColor       m_defColor;
        static irr::core::vector2di     m_defVector2di;
        static irr::core::vector2df     m_defVector2df;
        static irr::core::vector3df     m_defVector3df;
        static irr::core::rect<irr::s32>m_defRects32;

        TSceneNodeAnimatorMaterialLayer* m_animator;
        irr::scene::ISceneNode*         m_emptyNode;

        //! dumps the current lua stack to stdout
        void _dumpStack();

        //! dumps the table at the top of the lua stack to stdout
        void _dumpTable();

        //! sets the package search path
        void _setPackagePath();

        SYMDATA* _getLayerData(irr::core::stringc materialName, irr::u32 layerNum);

        //! splits a scoped/qualified name and stores the result in a string list
        /** given a name like "video.colors.background", the nameStack will 
        contain "video", "colors", and "background".
        \param name: name to split.
        \param nameStack: string list to populate.
        \return the stack item count.
        */
        int  _splitName(irr::core::stringc name, SSTACK& nameStack);

        //! pushes the lua value onto the top of the lua stack for the given variable name.
        /**
        /param: varName: the scoped variable name.
        /return the lua TValue* that is at the top of the stack. 0 if not found.
        */
        void* _pushValue(const irr::core::stringc varName);

        //! extracts the directory from a file path.
        irr::core::stringc _extractDir(irr::core::stringc filename);

        //! opens the required lua libraries.
        void _openLuaLibs();

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
        bool _getIntegerValue(const char *fieldName, irr::u32& result);

        //! retrieves a lua table field as a float.
        /**
        /param (lua) table: lua table at the top of the lua stack.
        /param fieldName: the table field name to retrieve.
        /return the field value. 0 if it doesn't exist.
        */
        bool _getFloatValue(const char *fieldName, irr::f32& result);

        //! retrieves a lua table field as a string.
        /**
        /param (lua) table: lua table at the top of the lua stack.
        /param fieldName: the table field name to retrieve.
        /return the field value. 0 if it doesn't exist.
        */
        bool _getStringValue(const char* fieldName, irr::core::stringc& result);

        //! retrieves a lua table field as a color.
        /**
        /param (lua) table: lua table at the top of the lua stack.
        /param fieldName: the table field name to retrieve.
        /return the field value. 0 if it doesn't exist.
        */
        bool _getColorValue(const char* fieldName, irr::video::SColor& result);
        irr::video::SColor _getColorValue();

        //! retrieves a lua table field as a matrix.
        /**
        /param (lua) table: lua table at the top of the lua stack.
        /param fieldName: the table field name to retrieve.
        /return the field value. 0 if it doesn't exist.
        */
        irr::core::matrix4 _getMatrixValue(const char* fieldName);
        irr::core::matrix4 _getMatrixValue();

        bool _getBoolValue(const char *fieldName, bool& result);

        //! retrieves the rect<f32> value for the lua table positioned at the top of 
        //! the lua stack.
        /**
        /param (lua) table: lua table at the top of the lua stack (numeric indexes only)
                            UpperLeft x,y LowerRight x,y.
        */
        irr::core::rect<irr::f32> _getRectf32Value();

        bool _getRectf32Value(const char*varName, irr::core::rect<irr::f32>& result);

        //! retrieves the vector value for the lua table positioned at the top of 
        //! the lua stack.
        /**
        /param (lua) table: lua table at the top of the lua stack (numeric indexes only)
                            indexes 1-rotation, 2-translation, 3-scale.
        */
        irr::core::vector3df _getVector3dfValue();

        //! retrieves the vector value for the given variable name.
        /**
        /param (lua) table: lua table at the top of the lua stack.                            
        */
        bool _getVector3dfValue(const char *varName, irr::core::vector3df& result);

        //! retrieves the vector value for the given variable name.
        /**
        /param (lua) table: lua table at the top of the lua stack.                            
        */
        bool _getVector2dfValue(const char *varName, irr::core::vector2df& result);

        //! retrieves the material layer value for the given variable name.
        /**
        /param (lua) table: lua table at the top of the lua stack.
        */
        irr::video::SMaterialLayer* _getMaterialLayerValue(irr::IrrlichtDevice* device, 
            irr::core::stringc varName);

        //! retrieves the material value for the given variable name.
        /**
        /param (lua) table: lua table at the top of the lua stack.
        */
        irr::video::SMaterial* _getMaterialValue(irr::IrrlichtDevice* device, irr::core::stringc varName);

        //! retrieves the GUI Element value for the given variable name.
        /**
        /param (lua) table: lua table at the top of the lua stack.
        */
        irr::gui::IGUIElement* _getGUIElementValue(irr::IrrlichtDevice* device, 
            irr::core::stringc varName, irr::gui::IGUIElement* parent=0);

        int _addGUIElementChildren(irr::IrrlichtDevice* device, 
            irr::core::stringc varName, irr::gui::IGUIElement* parent=0);

        void _getStringMap(const irr::core::stringc varName, STRINGMAP& out, bool scopedID);
        void _getStringArray(irr::core::array<irr::core::stringc>& out);
        void _setGELCommonAttributes(irr::gui::IGUIElement* pel);
        const char* _getTableFieldString (const char* table, const char *key);
        bool _setTableFieldString (const char* table, const char *key, const char* value);
        void _parseLUAError(const irr::core::stringc& lmsg, irr::core::stringc& fileName, int& line, 
                    irr::core::stringc& emsg);

    public:
        //! TSL Class constructor.
        TSL();

        //! TSL Class destructor.
        virtual ~TSL();

        //! loads, parses, and executes the given script.
        /**
        /param fileName: the file name of the script to load.
        /param dumpST: dump the symbol table to stdout.
        /param dumpOI: dump the material, matrix, layer, and config objects to stdout.
        /param errorHandler: user specified error handler.
        /return TSLStatus
        */
        TSLStatus loadScript(const irr::core::stringc fileName, 
            const bool dumpST=false, const bool dumpOI=false,
            TSLErrorHandler* errorHandler=0);

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
        bool getStringArray(const irr::core::stringc varName, irr::core::array<irr::core::stringc>& out);

        //! returns a string map of key/value pairs for the given variable name.
        /**
        given test = {a=1, b=2, c=3, d='test'}, the returned string map for "test" will contain
        "a":"a", "b":"s", "c":"3", & "d":"test".
        */
        bool getStringMap(const irr::core::stringc varName, STRINGMAP& out, bool scopedID=false);

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
        bool getMaterial(irr::IrrlichtDevice* device, 
            const irr::core::stringc varName, irr::video::SMaterial& result);

        //! returns the SMaterialLayer value for the given variable name.
        const irr::video::SMaterialLayer& getMaterialLayer(irr::IrrlichtDevice* device, 
            const irr::core::stringc varName);

        //! returns the IGUIElement value for the given variable name.
        irr::gui::IGUIElement* getGUIElement(irr::IrrlichtDevice* device, 
            const irr::core::stringc varName);

        //! returns the matrix4 value for the given variable name.
        const irr::core::matrix4 getMatrix(const irr::core::stringc varName);

        //! returns the SColor value for the given variable name.
        const irr::video::SColor getColor(const irr::core::stringc varName,
            irr::video::SColor defValue = m_defColor);

        //! returns the vector2di value for the given variable name.
        irr::core::vector2di getVector2di(const irr::core::stringc varName,
            const irr::core::vector2di defValue=m_defVector2di);

        //! returns the vector2di value for the given variable name.
        irr::core::vector2df getVector2df(const irr::core::stringc varName,
            const irr::core::vector2df defValue=m_defVector2df);

        //! returns the vector3df value for the given variable name.
        irr::core::vector3df getVector3df(const irr::core::stringc varName,
            const irr::core::vector3df& defValue=m_defVector3df);

        //! returns the rect<s32> value for the given variable name.
        irr::core::rect<irr::s32> getRects32(const irr::core::stringc varName,
            const irr::core::rect<irr::s32> defValue=m_defRects32);

        //! returns the dimension2di value for the given variable name.
        irr::core::dimension2di getDimension2di(const irr::core::stringc varName, 
            const irr::core::dimension2di defValue=irr::core::dimension2di());

        //! returns the dimension2du value for the given variable name.
        irr::core::dimension2du getDimension2du(const irr::core::stringc varName, 
            const irr::core::dimension2du defValue=irr::core::dimension2du());

    };

}
#endif