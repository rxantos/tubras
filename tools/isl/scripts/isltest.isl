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
    //driver = EDT_DIRECT3D9
    windowsize = (1024, 728)
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
        scale = (20,20)
        trilinear = true
    }
}

material billboard1
{
    // bug using non REF alpha with floor as the background.
    // need to research...
    type = EMT_TRANSPARENT_ALPHA_CHANNEL_REF
    lighting = false

    layer 1 
    {
        clampmode = ETC_CLAMP
        texture = 'tex/leaf.tga'        
        trilinear = true
    }
}

material testPlane1
{
    type = EMT_SOLID
    lighting = false
    backfaceculling = false

    layer 1 
    {
        clampmode = ETC_REPEAT
        texture = 'tex/t351sml.jpg'        
        scale = (4,4)
        center = (0,0)
        //rotation = 20.5
        //ascroll = (2.5, 0)    // scroll animation
        ascale = (0.5, 0.5)     // scale animation
        //arotation = 90.0         // rotation animation (deg/sec)
    }
}

