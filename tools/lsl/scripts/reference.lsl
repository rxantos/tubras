-- ----------------------------------------------------------------------------
--                            O v e r v i e w
--[[
This file documents the "lsl" language semantics as well as the related
c++ interface when appropriate.  

The "lsl" syntax is pure Lua with one exception - a modification has been
made to the Lua core (llex.c) which treats identifiers as case-insensitive.

Currently, the "lsl" parser (CLSL) only includes/opens Lua's base & package 
libraries.  Therefore, none of the other Lua standard libraries are available 
(io, os, string, etc.) to configuration scripts.

Before parsing, CLSL adds the following variables to Lua's global name space:

    "platform" - Valid String values include:
                 'win32' - Windows 
                 'linux' - Linux

    "irrVersion" - A String value indicating the Irrlicht version the CLSL 
                   library was compiled against.

In addition to the expected Lua syntax parsing, CLSL also provides additional 
semantic parsing which allows an application to define and access the following 
Irrlicht data structures:

    SColor, matrix4 (f32) , vectors (2df, 3df, 2di, 3di), SMaterial, 
    SMaterialLayer, and IGUIElement derivatives (Window, Button, etc.).

CLSL also provides for definitions and accessibility to generic configuration 
data.

Example C++ application code using the CLSL library:

    // --------------------------------------------------------------
    CLSL *lsl = new CLSL()
    if(lsl->loadScript("lsltest.lsl") == lsl::E_OK)
    {
        int debug = lsl->getInteger("options.debug");
        stringc texture = lsl->getString("options.floorTexture");
        dimension2di dims = lsl->getDimension2di("video.windowsize");
    }
    // --------------------------------------------------------------
--]]

--[[
Additional "lsl" scripts may be "included" via the "require" keyword. The 
syntax is:
    require 'module'
where 'module':
    Does NOT include the filename extension.

The file search logic will look for filenames that have extensions of either 
".lsl" or ".lua". The search path will be the directory in which the calling 
script  was loaded from and any additional directories previously setup by 
the user application using CLSL::addIncludePath(char *path). 
--]]
require 'irrlicht'

-------------------------------------------------------------------------------
--                       B a s i c    C o n f i g u r a t i o n
--                         
-- Integer, float, string, boolean values may be accessed via the following 
-- CLSL methods:
--      getInteger(variable name, default value)
--      getFloat(variable name, default value)
--      getString(variable name, default value)
--      getBool(variablej name, default value)
-------------------------------------------------------------------------------

-- getInteger("ival") => 1
-- getFloat("ival") => 1.5
-- getString("ival") => "1.5"
-- getBool("ival") => true
ival = 1.5

-------------------------------------------------------------------------------
-- getInteger("sval") => default value
-- getFloat("sval") => default value
-- getString("sval") => 'test string'
-- getBool("sval") => true
sval = 'test string'

-------------------------------------------------------------------------------
-- Using "scope" 
-- getInteger("values.ival") => 1
-- getFloat("values.ival") => 1.5
-- getString("values.sval") => 'test string'
-- getBool("values.ival") => true
values = 
{
    ival = 1.5,
    sval = 'test string',
}
-- Functional equivalent:
values = {}
values.ival = 1.5
values.sval = 'test string'

-------------------------------------------------------------------------------
-- Using nested "scope"
-- getInteger("values.integers.val1") => 1
-- getString("values.strings.val2") => 'test string 2'
-- getBool("values.bools.val2") => false
values = 
{
    integers = 
    {
        val1 = 1,
        val2 = 2,
    },
    strings = 
    {
        val1 = 'test string 1',
        val2 = 'test string 2',
    },
    bools =
    {
        val1 = true,
        val2 = false,
    }
}
-- Functional equivalent:
values = 
{
    ['integers.val1'] = 1,
    ['integers.val2'] = 2,
    ['strings.val1'] = 'test string 1',
    ['strings.val2'] = 'test string 2',
    ['bools.val1'] = true,
    ['bools.val2'] = false,
}

-- Example use for an Irrlicht application
options =                           -- Generic application options
{
    debug = 1,
    rotateSpeed = 100.0,
    moveSpeed = 50.0,
    showCursor = true,
    floorTexture = 'tex/grid.tga',
}

device =                            -- Irrlicht device options
{
    driver = EDT_OPENGL,            -- EDT_OPENGL defined in 'irrlicht.lsl'
    -- driver = EDT_DIRECT3D9,
    windowsize = {1024, 768},
    bits = 32,
    vsync = false,
    stencilbuffer = false,
    antialias = false,
    bgcolor = 0x557788AA,
}

-------------------------------------------------------------------------------
--                       C o l o r   D e f i n i t i o n s
--
-- Colors values may be created using either Lua numbers or tables.  Note that
-- the color specification "order" is "rgba".

-- Color as integer
-- getColor("red") => SColor(255, 0, 0, 255)
-- getColor("green") => SColor(0, 255, 0, 255)
red   = 0xFF0000FF    -- rrggbbaa
green = 0x00FF00FF
blue  = 0x0000FFFF
black = 255           -- equivalent to 0x000000FF

-- Color as table {red/r, green/g, blue/b, alpha/a}
red = {255, 0, 0, 255}
-- or
red = {255}           -- g & b default to 0, alpha defaults to 255

green = {0, 255, 0, 255}
-- or
green = {0, 0xFF}     -- b defaults to 0, alpha defaults to 255
-- or
green = {green=255}   -- using named parameter
-- or
green = {g=255}       -- using "short" named parameter

black = {}            -- all values default

-------------------------------------------------------------------------------
--                      V e c t o r   D e f i n i t i o n s
--
-- 2d/3d Vector values may be created using Lua tables.  Note that
-- the vector specification "order" is "x, y, [z]".  Un-specified component
-- values are set to 0.
--
-- vector3df vec = getVector("position");

-- Vector as a table {x, y, z}
position = {0, 0, 0}  -- x=0.0, y=0.0, z=0.0
position = {0, 1.5}   -- x=0.0, y=1.5, z defaults to 0.0
size = {1024, 728}    -- x=1024.0, y = 728.0, z defaults to 0.0

offset = {z=2.0}      -- using named parameter, x & y default to 0.0
offset =              -- using names parameters
{
    y = 1.0,
    z = 2.0,
    x = 3.0,
}

-- if a definition uses a named parameter (regardless if it's valid), 
-- positional values are ignored.
pos = {1.5, z=2.5}    -- This def will return (x=0.0, y=0.0, z=2.5)

-------------------------------------------------------------------------------
--                     M a t r i x   D e f i n i t i o n s
--
-- Matrices may be created using Lua tables.  Matrices are defined as a table 
-- of "Vectors".
--
-- The matrix specification "order" is "translation/t, rotation/r, scale/s".  
-- Un-specified "translation" and "rotation" component values are set to
-- {0, 0, 0}.  An unspecified "scale" component value is set to {1, 1, 1}
--
-- Rotations are specified in degrees.
--

identityMatrix = 
{
    {0, 0, 0},   -- translation vector (xyz defaults)
    {0, 0, 0},   -- rotation vector (xyz defaults)
    {1, 1, 1}    -- scale vector (xyz defaults)
}

transMatrix =    -- rotation & scale default
{
    {0, 1, -5}
}
-- or
transMatrix
{
    t = {y=1, z=-1}
}

scaleMatrix =    -- rotation & translation default
{
    scale = {2, 0, 2}
}
-- or
scaleMatrix = 
{
    s = {x=2, z=2}
}

rotMatrix = 
{
    rotation = {0, 0, 45.5}
}
-- or
rotMatrix = 
{
    r = {z=45.5}
}

-------------------------------------------------------------------------------
--              G e n e r al   C l a s s   D e f i n i t i o n s
--  
--  The remaining Irrlicht variable types: MaterialLayer, Material,
--  IGUIElement, and Particle, may all be defined as generic Lua tables.  
--  However, for convenience, special Lua "classes" have been defined in
--  "irrlicht.isl" which allow these types of variables to easily inherit 
--  properties from other variables that have been previously defined.
--
--  Irrlicht Type               LSL Type
--
--  MaterialLayer               IMaterialLayer
--  Material                    IMaterial
--  IGUIElement                 IGUIElement & derivatives (IWindow, ...)
--
--  A definition using inheritance would like:
--
--  varName = <LSL Type>:new
--  {
--      overridden parameter definitions
--  }
--
--  Each LSL base class defines a type parameter named "_type" which is
--  optionally used by the LSL semantic parser.
--
--  Empty class definitions will have their parameters set to the Irrlicht
--  C++ class defaults.
--
--  Note that the definitions are only instantiated at the time they are 
--  accessed by the user application ( "CLSL::getMaterial(...)" ), not when
--  they are initially loaded via "CLSL::loadScript(...)".
--
-------------------------------------------------------------------------------
--              M a t e r i a l L a y e r   D e f i n i t i o n s
--
-- Material Layers are typically used by Material definitions.  Valid 
-- parameters are identical matches to the variable names defined by
-- "SMaterialLayer" with the following additions:
--
-- "transform"   -> layer matrix (translation, rotation, scale)
-- "translation" -> initial layer translation 
-- "rotation"    -> initial layer rotation (float in degrees)
-- "scale"       -> initial layer scale 
--
-- CLSL contains a Material Layer Matrix Animation class which also allows
-- parameters to be defined which control texture matrix animation for
-- scrolling, rotation, and scaling. The additional parameters for
-- controlling matrix animation include:
--
-- "acenter"     -> center used for rotational animation
-- "ascroll"     -> (x, y) speed/direction
-- "arotation"   -> speed in degrees/second
-- "ascale"      -> (x, y) speed/direction
--
testLayer1 = IMaterialLayer:new
{
    clampMode = ETC_REPEAT,             -- from 'irrlicht.lsl'
    lighting = false,
    trilinear = true,
    texture = 'tex/test.tga'
    transform =IDENTITY_MATRIX          -- from 'irrlicht.lsl'
}

-- inherits from "testLayer1" and overrides the texture parm and rotation 
-- parameter of the identity matrix.
testLayer2 = testLayer1:new
{
    texture = 'tex/test2.tga'
    rotation = 45.0                     -- override transform rotation
}
-- or
testLayer2 = testLayer1:new()
testLayer2.texture = 'tex/test2.tga'

-------------------------------------------------------------------------------
--              M a t e r i a l    D e f i n i t i o n s
--
-- A Material definition is used to generate an Irrlicht SMaterial type. As
-- with a Material Layer, valid parameters are identical mataches to
-- variable names defined by "SMaterial" with the following addition:
--
-- "layer?"      -> identifies a specific layer definition ?=1-4
--
floorMat = IMaterial:new
{
    type = EMT_SOLID,                   -- from 'irrlicht.isl'
    lighting = false,
    ambient = {255, 255, 255, 255},
    layer1 = IMaterialLayer:new
    {
        clampmode = ETC_CLAMP,
        texture = 'tex/test2.tga',
    }
}
-- or using inheritence 
ceilingMat = floorMat:new
{
    layer1 = testLayer1
}

billboard1 = IMaterial:new
{
    -- bug using non REF alpha with floor as the background.
    -- need to research...
    type = EMT_TRANSPARENT_ALPHA_CHANNEL_REF,
    lighting = false,

    layer1 = 
    {
        clampmode = ETC_CLAMP,
        texture = 'tex/leaf.tga',
        trilinear = true,
        arotation = 45.0,
    }
}

scale4x4 = {4,4}

testPlane1 = IMaterial:new
{
    type = EMT_TRANSPARENT_ALPHA_CHANNEL,
    lighting = false,
    backfaceculling = false,

    layer1 =
    {
        clampmode = ETC_CLAMP,
        texture = 'tex/test.png',
        trilinear = true,
        -- scale = scale4x4,
        -- center = {0.0,0.0},
        -- rotation = 20.5,
        -- ascroll = {-.5, 0},     -- scroll animation
        -- ascale = {-0.1, -0.1},    -- scale animation
        -- acenter = {0.5, 0.1},
        arotation = -180.5,        -- rotation animation (deg/sec)
    }
}

testPlane2 = IMaterial:new
{
    type = EMT_SOLID,
    lighting = false,
    backfaceculling = false,

    layer1 =
    {
        clampmode = ETC_CLAMP,
        texture = 'tex/test2.tga',
        trilinear = true,
    }
}

testPlane3 = IMaterial:new
{
    type = EMT_TRANSPARENT_ALPHA_CHANNEL,
    lighting = false,
    backfaceculling = false,

    layer1 =
    {
        clampmode = ETC_REPEAT,
        texture = 'tex/test3.tga',
        trilinear = true,
        ascroll = {0, 0.5},
    }
}

-- inherit from testPlane3 & override texture & ascroll props
testPlane4 = testPlane3:new()
testPlane4.layer1.texture = 'tex/test3.tga'
testPlane4.layer1.ascroll = {0, -1.5}

-- inherit from testPlane2 & override layer props
testPlane5 = testPlane2:new()
testPlane5.layer1.clampmode = ETC_REPEAT
testPlane5.layer1.texture = 'tex/test2.tga'
testPlane5.layer1.rotation = 270

testPlane6 = IMaterial:new
{
    type = EMT_SOLID,
    lighting = false,
    backfaceculling = false,

    layer1 =
    {
        clampmode = ETC_REPEAT,
        texture = 'tex/test4.tga',
        trilinear = true,
        center = {0.5,0.5},
        ascale = {-0.1, -0.1},    -- scale animation
        acenter = {0.5, 0.5},     -- rotation animation center
        arotation = 18.5,         -- rotation animation (deg/sec)
    }
}

-- GUI Elements
ID_TESTWINDOW = 100
ID_OK         = 101

testWindow = IWindow:new
{
    text = 'Test Window',
    id = ID_TESTWINDOW,
    bounds = {0, 0, 0.5, 0.24},
    visible = false,

    okButton = IButton:new
    {
        text = 'OK',
        bounds = {0.2, 0.2, 0.4, 0.4}
    }
}


--[[
The following definitions are identical in that 
CLSL::getStringMap("bindings", scopedID=false) will return:

'key.down.w' : 'frwd'
'key.down.a' : 'left'
'key.down.s' : 'back'
'key.down.d' : 'right'
'key.up.w' : 'frwd up'
'key.up.a' : 'left up'
'key.up.s' : 'back up'
'key.up.d' : 'rght up'

if "scopedID" = true, then the map keys are prefixed with 
"bindings.".

and 

CLSL::getString('bindings.key.down.w') => 'frwd'

--]]

bindings =
{
    key =
    {
        down = 
        {
            w = 'frwd',
            a = 'left',
            s = 'back',
            d = 'rght',
        },

        up = 
        {
            w = 'frwd up',
            a = 'left up',
            s = 'back up',
            d = 'rght up',
        }
    }
}

bindings = 
{
    ['key.down.w'] = 'frwd',
    ['key.down.a'] = 'left',
    ['key.down.s'] = 'back',
    ['key.down.d'] = 'right',
    ['key.up.w'] = 'frwd up',
    ['key.up.a'] = 'left up',
    ['key.up.s'] = 'back up',
    ['key.up.d'] = 'rght up',
}


