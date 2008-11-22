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
        center = (0.5,0.5)
        trilinear = true
        //arotation = 5.0;
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

scale4x4 = (4.0, 4.0)
angle = 20.5

material testPlane1
{
    type = EMT_SOLID
    lighting = false
    backfaceculling = false

    layer 1 
    {
        clampmode = ETC_REPEAT
        texture = 'tex/t351sml.jpg'        
        scale = scale4x4
        //center = (0.5,0.5)
        //rotation = 0
        //ascroll = (-2.5, 0)     // scroll animation
        //ascale = (-0.1, 0.1)    // scale animation
        acenter = (0.5, 0.5)
        arotation = angle        // rotation animation (deg/sec)
    }
}

guielement Element {
    id = -1
    pos = (0, 0)            // relative position
    size  = (0.1, 0.1)          // relative size
}

guielement Window : Element {
    type = EGUIET_WINDOW
}

guielement Button : Element {  
    type = EGUIET_BUTTON
}

ID_TESTWINDOW = 100

guielement testWindow : Window {
    text = 'Test Window'
    id = ID_TESTWINDOW
    size = (0.5, 0.25)         // relative size
}

