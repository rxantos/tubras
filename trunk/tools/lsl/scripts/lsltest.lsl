require 'irrlicht'

AbCdEF = 1


-- control logic... 
if platform == 'win32' then
    a = 'win32'
else
    a = 'linux'
end

matrix1 =
{
    {0, 0, 0},   -- rotation vector (xyz defaults)
    {0, 0, 0},   -- translation vector (xyz defaults)
    {1, 1, 1}    -- scale vector (xyz defaults)
}

matrix2 = 
{
    rotation = {y=90},  -- by name, "translation" defaults
    scale = {x=2.0, z=1.5} 
}

vector1 = {0, 0, 0} -- XYZ defaults
vector2 = {y=12.5}  -- Y, X&Z default

color1 = {0, 0, 0, 255} -- rgba defaults
color2 = 0xFF00FFFF     -- as hex integer (rgba)
color3 =                -- by name
{
    red = 128,
    green = 128,
    blue = 128,
    alpha = 128
}

--
-- basic config
-- to retrieve values from c++:
--
-- CLSL *lsl = new CLSL()
-- if(lsl->loadScript("lsltest.lsl") == lsl::E_OK)
-- {
--     int debug = lsl->getInteger("options.debug");
--     stringc texture = lsl->getString("options.floorTexture");
--     dimension2di dims = lsl->getDimension2di("video.windowsize");
-- }
--
options = 
{
    debug = 1,
    rotateSpeed = 100.0,
    moveSpeed = 50.0,
    showCursor = true,
    floorTexture = 'tex/grid.tga'
}

video = 
{
    driver = EDT_OPENGL,
    -- driver = EDT_DIRECT3D9,
    windowsize = {1024, 768},
    bits = 32,
    vsync = false,
    stencilbuffer = false,
    antialias = false,
    caption = 'LSL Test',
    bgcolor = 0x557788AA,
    testcolor = {100, 100, 100, 255},
    testcolor2 = {green=100, 250, red=1, alpha=100, 350}
}

keymap = 
{
    forward = KEY_KEY_W,
    left = KEY_KEY_A,
    backward = KEY_KEY_S,
    right = KEY_KEY_D
}

-- material definition
floor = IMaterial:new
{
    type = EMT_TRANSPARENT_ALPHA_CHANNEL,
    lighting = false,
    ambient = {255, 255, 255, 255},

    layer1 = 
    {
        clampmode = ETC_REPEAT,
        texture = 'tex/grid.tga',
        scale = {20, 20},
        center = {0.5, 0.5},
        trilinear = true,
        --arotation = 5.0
    }
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

