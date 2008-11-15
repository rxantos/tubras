require 'irrlicht'

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
    windowsize = {1024, 728},
    bits = 32,
    vsync = true,
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
        arotation = 5.0
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
        trilinear = true
    }
}

testPlane1 = IMaterial:new
{
    type = EMT_SOLID,
    lighting = false,
    backfaceculling = false,

    layer1 =
    {
        clampmode = ETC_REPEAT,
        texture = 'tex/t351sml.jpg',
        trilinear = true,
        -- scale = scale4x4,
        -- center = (0.5,0.5),
        -- rotation = 0,
        -- ascroll = (-2.5, 0),     -- scroll animation
        -- ascale = (-0.1, 0.1),    -- scale animation
        -- acenter = (0.5, 0.5),
        arotation = 5.0,        -- rotation animation (deg/sec)
    }
}


-- GUI Elements
ID_TESTWINDOW = 100

testWindow = IWindow:new
{
    text = 'Test Window',
    id = ID_TESTWINDOW,
    size = {0.5, 0.25}    
}

