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

/*
%typemap(in) TVector3 {
    $1 = (int) lua_tonumber(L,$input);
}
*/


class ISceneNode {
private:
	ISceneNode();
public:
	bool isVisible();
	void setVisible(bool value);
	
	void setPosition(const TVector3& newpos);
	%extend {
	TVector3 Pos;
	}
};

%{
const TVector3* ISceneNode_Pos_get(ISceneNode* node) {

	static TVector3 result;
	result = node->getPosition();
	return &result;
}
void ISceneNode_Pos_set(ISceneNode* node, TVector3* pos) {
	node->setPosition(*pos);
}
%}

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

class IAnimatedMeshSceneNode : public ISceneNode {
private:
	IAnimatedMeshSceneNode();
public:
};

class TVector3
{
public:
	TVector3(float nx=0.f, float ny=0.f, float nz=0.f);
	~TVector3();
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

class TController {
private:
	TController();
public:
};

class TRotateController : public TController {
private:
	~TRotateController();
public:
	TRotateController(char* name, ISceneNode* node, float velocity=5.0f,
            TVector3 axis=TVector3::UNIT_Y);
};

class TSound {
private:
	TSound();
	~TSound();
public:
	void play();
    void stop();
    void pause();
    void resume();

    bool isPlaying();

    // loop: false = play once; true = play forever.
    // inits to false.
    void setLoop(bool loop=true);
    bool getLoop();

    // loop_count: 0 = forever; 1 = play once; n = play n times.
    // inits to 1.
    void setLoopCount(unsigned long loop_count=1);
    unsigned long getLoopCount();
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
    
    IAnimatedMeshSceneNode* loadModel(char* fileName, ISceneNode* parent=0, char* name="default");
    TSound* loadSound(char* fileName, bool positional=false);

    void setBGColor(int r, int g, int b);
    void setWindowCaption(char* value);    

    void stopRunning();
};

TApplication* getApplication();


