// color object value assignments other than (r,g,b,a,value) are 
// ignored with warnings.
color black {
    r = .0;         // default
    g = .0;         // default
    b = .0;         // default
    a = 1.0;        // default
}

// inherits g, b, & a from black
color red : black {
    r = 1.0;
}

// value may be a "list" type (r,g,b,a) or "hex" type.  
//    < 4 entries -> components default to 0
//    > 4 entries -> extra components ignored
color blue {
    value = (0,0,1.0,1.0);
}

color green {
    value = 0x00FF00FF;  // r=0, g=255, b= 0, a=255
}

// color object using both inheritance and "value" ignore the parent
// values.
color yellow : red {
    value = (1, 1, 0, 0);   // overrides red.r component
    testwarn = 1.0;
}

// although syntactically legal, the internal def is ignored and will
// generate a symantic warning.
color blah {
   color imignored {
       r = 1.0;
       g = 1.0;
   }
}

// r,g,b,a components must be of type integer or float.  this will 
// generate a symantic warning and default the component to 0.
color bad {
    r = color {
        r = 1.0;
    };
}
