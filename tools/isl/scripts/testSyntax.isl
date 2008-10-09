/*------------------------------------------
               test script
------------------------------------------*/

// assignment
a = 1;
b = 1.0;
c = 'testing';
d = "testing";
e = (1,2,3.0);
f = (a+1, 2, 3);

// using "namespace"
test.a = 1.0;
test.b = .1234;
test.c = 1;
test.d = 1234;
test.e = 'testing';
test.f = "testing";
test.g = (1,2,3);   // list assignment
test.h = test.g;

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

// object defs: "type name" {...}
color red {
    r = 1.0;
    a = 1.0;
}

// inheritence : "type name : parent name" {...}
color orange : red {
    g = 1.0;
}

material mat1 {
    stype = irr.solid;
    diffuse = red;
    pass 0 {
    }
}

material mat2 : mat1 {
    diffuse = orange;
}


