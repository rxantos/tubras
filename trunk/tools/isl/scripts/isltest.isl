#include 'irrlicht.isl'

config options
{
    debug = 1
    rotateSpeed = 100.0
    moveSpeed = 50.0
    showCursor = false
}

config video
{
    driver = EDT_OPENGL
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
