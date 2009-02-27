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

class TVector3
{
public:
	TVector3(float nx=0.f, float ny=0.f, float nz=0.f);
    TVector3 toRadians();
    TVector3 toDegrees();
    
	TVector3 operator+(const TVector3 other);

    float X,Y,Z;
};


enum CLSLStatus {
	E_OK,
    E_NO_FILE,
    E_BAD_INPUT,
    E_OUT_OF_MEMORY,
    E_BAD_SYNTAX
    };


class CLSL
{
public:
	CLSL();
	~CLSL();
	
    CLSLStatus loadScript(char* fileName);
	
	bool getBool(char* name, bool defValue=false);
	%extend {
		char* getString(char* name, char* defValue=0) {
		        static irr::core::stringc result;
		        result = self->getString(name, defValue);
				return (char *)result.c_str();
			}
		}
	int getInteger(char* name, int defValue=0);
	float getFloat(char* name, float defValue=0.f);
};

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

	CLSL* getConfig();
    
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

TApplication* getApplication();


