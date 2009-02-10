/*------------------------------------------
               test script
------------------------------------------*/
#include "irrlicht.isl"

// assignment
a = 1
b = 1234
c = 1.0
d = .1234
e = 1234.1234
f = 'testing'
g = "testing"
h = (1,2,3.0)           // tuple assignment
i = (a+1, 2, 3)

// using "scope"
test.a = 1
test.b = 1234
test.c = 1.0
test.d = .1234
test.e = 1234.1234
test.f = 'testing'
test.g = "testing"
test.h = (1,2,3.0)      // tuple assignment
test.i = (a+1, 2, 3)

// to an un-named object
mat = material {
    diffuse = BLACK;
};

// math expressions
a = 1 + 1
a = 1 - 1
a = 1 * 1
a = 1 / 1

a = 1 + 1 * 1
a = (1 + 1) * 1
a = 1 + 1 / 1
a = (1 + 1) / 1
a = (1 + 1) / ( (1 + 1) * 1 )


// generic "config' object
config video {
    bgcolor = (0.25, 0.25, 0.25, 1.0)
    fsaa = true
    colordepth = 32
    fullscreen = false
    resolution = (800,600)
    vsync = true
    guiskin = "data/gui/tubras.xml"
}

red = (1,0,0,1)

material mat1 {
    type = EMT_SOLID
    diffuse = red
    specular = (1,1,1,1)
}

material mat2 : mat1 {
    diffuse = WHITE
    layer 1 {
        clampmode = ETC_CLAMP
        texture = 'data/text/test.tga'        
    }
}


