require 'irrlicht'

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

-- application config
options = 
{
    debug = 1,
    rotateSpeed = 100.0,
    moveSpeed = 0.1,
    showCursor = false,
}

-- video config
video = 
{
    driver = EDT_OPENGL,
    -- driver = EDT_DIRECT3D9,
    windowsize = {800, 600},
    bits = 32,
    vsync = true,
    stencilbuffer = false,
    -- antialias 0, 2, 4, 8, 16
    antialias = 0,
    caption = 'LSL Test',
    bgcolor = 0x111144AA,
}

-- key mapping config
keymap = 
{
    forward = KEY_KEY_W,
    left = KEY_KEY_A,
    backward = KEY_KEY_S,
    right = KEY_KEY_D
}

--
-- material definitions
--
floor = IMaterial:new
{
    type = EMT_TRANSPARENT_ALPHA_CHANNEL,
    lighting = false,
    backFaceCulling = false,

    layer1 = 
    {
        clampmode = ETC_REPEAT,
        texture = 'tex/floor.png',
        scale = {20, 20},
        center = {0.5, 0.5},
        trilinear = true,
    }
}

leafBillBoard = IMaterial:new
{
    -- bug using non REF alpha with floor as the background.
    -- need to research...
    type = EMT_TRANSPARENT_ALPHA_CHANNEL_REF,
    lighting = false,

    layer1 = 
    {
        clampmode = ETC_CLAMP,
        texture = 'tex/leaf.png',
        trilinear = true,
        arotation = 45.0,
    }
}

redPattern = IMaterial:new
{
    type = EMT_TRANSPARENT_ALPHA_CHANNEL,
    lighting = false,
    backfaceculling = false,

    layer1 =
    {
        clampmode = ETC_CLAMP,
        texture = 'tex/redpattern.png',
        trilinear = true,
        arotation = -180.5,        -- rotation animation (deg/sec)
    }
}

panelBGLayer = IMaterialLayer:new
{
    clampmode = ETC_REPEAT,
    texture = 'tex/panelbg.png',
    trilinear = true,
}

leftPanelBG = IMaterial:new
{
    type = EMT_SOLID,
    lighting = false,
    backfaceculling = false,

    -- assign "reference".  changing testPlane2.layer1 attributes will
    -- change the originals.
    layer1 = panelBGLayer:new()
}

-- inherit from leftPanelBG & override layer props
rightPanelBG = leftPanelBG:new
{
    -- assign new "instance", attribute changes override the original
    -- values
    layer1 = panelBGLayer:new
    {
        rotation = 270,
    }
}


leftPanelFG = IMaterial:new
{
    type = EMT_TRANSPARENT_ALPHA_CHANNEL,
    lighting = false,
    backfaceculling = false,

    layer1 = IMaterialLayer:new
    {
        clampmode = ETC_REPEAT,
        texture = 'tex/panelfg.png',
        trilinear = true,
        ascroll = {0, 0.5},
    }
}

-- inherit from testPlane3 & override texture & ascroll props

rightPanelFG = leftPanelFG:new
{
    layer1 = leftPanelFG.layer1:new
    {
        ascroll = {0, -1.5}
    }
}

cubeMat = IMaterial:new
{
    type = EMT_SOLID,
    lighting = false,
    backfaceculling = false,

    layer1 =
    {
        clampmode = ETC_REPEAT,
        texture = 'tex/cube.png',
        trilinear = true,
        center = {0.5,0.5},
        ascale = {-0.1, -0.1},    -- scale animation
        acenter = {0.5, 0.5},     -- rotation animation center
        arotation = 18.5,         -- rotation animation (deg/sec)
    }
}

twimbg = IMaterial:new
{
    type = EMT_SOLID,
    lighting = false,
    backfaceculling = false,
    layer1 =
    {
        clampmode = ETC_CLAMP,
        texture = 'tex/twimbg.png',
        trilinear = true,
    }
}

twimfg = IMaterial:new
{
    type = EMT_TRANSPARENT_ALPHA_CHANNEL,
    lighting = false,
    backfaceculling = false,
    layer1 =
    {
        clampmode = ETC_REPEAT,
        texture = 'tex/twimfg.png',
        trilinear = true,
        ascroll = {0.2, 0},
    }
}

leftSphere = IMaterial:new
{
    type = EMT_SOLID,
    lighting = false,
    layer1 = IMaterialLayer:new
    {
        clampmode = ETC_REPEAT,
        texture = 'tex/sphere.png',
        scale = {2, 2},
        ascroll = {-0.3, 0},
    }
}

rightSphere = leftSphere:new
{
    layer1 = leftSphere.layer1:new
    {
        scale = {4, 4},
        ascroll = {0.0, 2.0},
    }
}

-- GUI Elements
ID_TESTWINDOW = 100
ID_OK         = 101

helpText = IStaticText:new
{
    text = 'F3 - Toggle Wire',
    bounds = {0.01, 0.005, 0.1, 0.1},
    fgcolor = 0xFFFFFFFF,
}

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

