#include "irrlicht.isl"

matrix m1 {
    r = (45,0,0)
    t = (0,0,0)
    s = (1,1,1)
}

layer common {
    clampmode = ETC_REPEAT
    texture = 'data/tex/common.tga'
}

material test1 {
    type = EMT_SOLID
    ambient = BLACK
    diffuse = WHITE
    emissive = WHITE
    specular = WHITE
    shininess = 20.0
    parm1 = 0.0
    parm2 = 0.0
    thickness = 1.0
    gouraud = true
    lighting = true
    zwriteenable = true
    backfaceculling = true
    frontfaceculling = false
    fogenable = false
    normalizenormals = false
    zbuffer = 1

    // layer number identified in definition.  may be
    // referenced as 'layer1'
    layer 1 {  
        clampmode = ETC_CLAMP
        texture = 'data/tex/test.tga'
        bilinear = true
        trilinear = false
        anisotropic = false

        // transform as a matrix - "center" defaults to (0.5,0.5) but
        // may be overridden using "center" keyword.  rotation (degrees) is defined
        // in the X component of the rotational vector.
        transform = IDENTITY_MATRIX

        // or using keywords - overrides "transform" components
        scale = (1.0, 1.0)
        rotation = 0.0          // degrees
        center = (0.5, 0.5)     // for rotation
        offset = (0.0, 0.0)
    }

    warningvar = 1              // will generate warning
}

