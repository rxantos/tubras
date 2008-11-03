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
        arotation = 5.0;
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
        center = (0,0)
        //rotation = 0
        //ascroll = (-2.5, 0)     // scroll animation
        //ascale = (-0.1, 0.1)    // scale animation
        arotation = -angle        // rotation animation (deg/sec)
    }
}

/* todo gui & particles
guielement Element {
    id = -1
    pos = (0,0)
    size = (1,1)
}

guielement Window : Element {
    type = EGUIET_WINDOW
}

guielement Button : Element {  
    type = EGUIET_BUTTON
}

guielement testWindow : Window {
    title = 'Test Window'config options
{
    debug = 1
    rotateSpeed = 100.0
    moveSpeed = 50.0
    showCursor = false
    floorTexture = 'tex/grid.tga'
}

// functionally equivalent to the above "config options" block 
// in that both definitions allow access via the "options" scope:
//      int debug = m_isl->getInteger("options.debug");

options.debug = 1
options.rotateSpeed = 100.0
options.moveSpeed = 50.0
options.showCursor = false
options.floorTexture = 'text/grid.tga'
    pos = (0, 0)
    size = (0.5, 0.5)

    guielement okButton : Button {
        text = 'OK'
        id = 1
        pos = (0.1, 0.2)        
    }

}
*/
