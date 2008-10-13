z = 1 + 2 * 6 / 3;
bb = 3 * 2.5;
bbb = bb * .5;
a = 2 * 2;
aa = 5;
aaa = 5 - 2;
test.a.b = 12 + z;
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

