#include "irrlicht.isl"

matrix m1 {
    t = (0,0,0)
    r = (0,90,0)
    s = (1,1,1)
}

layer common {
    clampmode = ETC_REPEAT
    texture = '/data/tex/common.tga'
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
        transform = IDENTITY_MATRIX
    }

    layer2 = common
    layer2.transform = m1
    
    warningvar = 1         // will generate warning
}

