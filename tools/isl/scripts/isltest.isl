#include 'irrlicht.isl'

config options
{
    debug = 1
    rotateSpeed = 100.0
    moveSpeed = 50.0
    showCursor = false
    floorTexture = 'tex/grid.tga'
}

config video
{
    driver = EDT_OPENGL
    windowsize = (640, 480)
    bits = 32
    fullscreen = false
    vsync = true
    stencilbuffer = false
    antialias = false
    caption = 'ISL Test'
}

config filesystems
{
    folders = ('c:\\scenes\\')
    zips = ('')
}

config keymap
{
    forward = KEY_KEY_W
    left = KEY_KEY_A
    backward = KEY_KEY_S
    right = KEY_KEY_D
}

material floor
{
    type = EMT_TRANSPARENT_ALPHA_CHANNEL
    lighting = false

    layer 1 
    {
        clampmode = ETC_REPEAT
        texture = 'tex/grid.tga'        
        scale = (10,10)
        trilinear = true
    }
}

material test1
{
    type = EMT_SOLID
    lighting = false

    layer 1 
    {
        clampmode = ETC_REPEAT
        texture = 'tex/t351sml.jpg'
        scale = (2,2)
        center = (0.5,0.5)
        rotation = 20.5
    }
}

