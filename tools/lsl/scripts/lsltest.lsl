require 'irrlicht'

-- control logic... 
if platform == 'win32' then
    a = 'win32'
else
    a = 'linux'
end

--
-- basic config
-- to retrieve values from c++:
--
-- CLSL *lsl = new CLSL()
-- lsl->parseScript("lsltest.lsl")
-- int debug = lsl->getInteger("options.debug");
-- stringc texture = lsl->getString("options.floorTexture");
-- dimension2di dims = lsl->getDimension2di("video.windowsize");
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
    windowsize = {1024, 728},
    bits = 32,
    vsync = true,
    stencilbuffer = false,
    antialias = false,
    caption = 'LSL Test',
    bgcolor = 0x557788AA,
    testcolor = {100, 100, 100, 255},
    testcolor2 = {green=100, 250, alpha=100}
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

-- GUI Elements
ID_TESTWINDOW = 100

testWindow = IWindow:new
{
    text = 'Test Window',
    id = ID_TESTWINDOW,
    size = {0.5, 0.25}    
}

