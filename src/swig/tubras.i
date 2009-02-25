%module tubras
%{
#include "tubras.h"
using namespace Tubras;
%}
%include "lua_fnptr.i"

%immutable;
extern long VERSION;
%mutable;
%constant int TESTCONST=42;

class TEventParameter
{
private:
    TEventParameter();
    ~TEventParameter();
public:

    bool isEmpty();

    bool isInt();
    int getIntValue();

    bool isString();
    char* getStringValue();

    bool isDouble();
    double getDoubleValue();

};

class TEvent
{
private:
    TEvent();
    ~TEvent();
public:
    const char* getName();
    int getID();
    int getNumParameters();
    TEventParameter* getParameter(int n);    
};

class TApplication
{
private:
    TApplication();

public:
    
    %extend {
        int acceptEvent(char *eventName, SWIGLUA_FN luaFunc) {
            lua_pushvalue(luaFunc.L, luaFunc.idx);
            void *ref = (void *)luaL_ref(luaFunc.L, LUA_REGISTRYINDEX);
            return self->acceptEventToScript(eventName, ref);
        }
    }

    void setBGColor(int r, int g, int b);
    void setWindowCaption(char* value);    

    void stopRunning();
};


class TVector3
{
public:
    TVector3();
    TVector3 toRadians();
    TVector3 toDegrees();

    float X,Y,Z;
};

TApplication* getApplication();


