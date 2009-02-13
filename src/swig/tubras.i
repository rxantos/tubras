%module tubras
%{
#include "tubras.h"
using namespace Tubras;
%}
%immutable;
extern long VERSION;
%mutable;
%constant int TESTCONST=42;

int testFunc(int v);

class TApplication
{
public:

};

class TVector3
{
public:
    TVector3();
    TVector3 toRadians();
    TVector3 toDegrees();

    float X,Y,Z;
};


