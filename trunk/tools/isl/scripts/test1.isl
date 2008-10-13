test.a.b = 12;
a = 1;
b = a + 2;
c = (1,'test',1.5,(1,2));

color black {
    r = 0;
    g = 0;
    b = 0;
    a = 1;
}

color red : black {
    r = 1;
}

config video {
    resolution = (800,300+300);
    bgcolor = color {r=1;};
}


b2 = black;

v = false;

