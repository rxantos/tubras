#include "irrlicht.isl"

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
    
    warningvar = 1         // will generate warning
}
