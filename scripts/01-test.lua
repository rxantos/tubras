-- tubras module is named "tubras" and is automatically added 
-- by tse. 
--
tse = tubras

tubras.testFunc(2)

vec = tubras.TVector3()
vec2 = tse.TVector3()

vec.X = 1.2
vec2.Y = vec.X

rvec = vec:toRadians()

print('hello tubras', tubras, tubras.VERSION, tubras.TESTCONST)
