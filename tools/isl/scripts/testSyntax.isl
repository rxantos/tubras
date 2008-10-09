/*------------------------------------------
               test script
------------------------------------------*/

// assignment
a = 1;
b = 1234;
c = 1.0;
d = .1234;
e = 1234.1234;
f = 'testing';
g = "testing";
h = (1,2,3.0);      // list assignment
i = (a+1, 2, 3);

// using "namespace"
test.a = 1;
test.b = 1234;
test.c = 1.0;
test.d = .1234;
test.e = 1234.1234;
test.f = 'testing';
test.g = "testing";
test.h = (1,2,3.0);      // list assignment
test.i = (a+1, 2, 3);

// to an un-named object
a = color {r=0;g=0;b=0;};
mat = material {
    diffuse = color{r=1;};
};

// math expressions
a = 1 + 1;
a = 1 - 1;
a = 1 * 1;
a = 1 / 1;

a = 1 + 1 * 1;
a = (1 + 1) * 1;
a = 1 + 1 / 1;
a = (1 + 1) / 1;
a = (1 + 1) / ( (1 + 1) * 1 );

// object defs: "objectType name" {...}
color red {
    r = 1.0;
    a = 1.0;
}

// inheritence : "objectType name : parentName" {...}
color yellow : red {
    g = 1.0;
}

material mat1 {
    stype = irr.solid;
    diffuse = red;

    specular = color {r=1;g=1;b=1;a=1};  
    // or
    specular = (1,1,1,1);

    pass 0 {
    }
}

material mat2 : mat1 {
    diffuse = orange;
}


