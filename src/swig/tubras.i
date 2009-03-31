/*! \mainpage Tubras LUA API Documentation
 *
 * \section intro_sec Introduction
 *
 * This is the introduction.
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Opening the box
 *
 * \subsection global_sec Globals
 *  "tse" - TApplication*
 *  
 * etc...
 */
%module tubras
%{
#include "tubras.h"
using namespace Tubras;
%}
%include "lua_fnptr.i"
%include "typemaps.i"
%include "TEnums.h"
%include "TParticleDomain.h"
%include "TParticleAction.h"

%immutable;
extern long VERSION;
%mutable;
%constant int TESTCONST=42;

// converts a LUA number -> TBlendType
%typemap(in) TBlendType {
	$1 = (TBlendType) lua_tointeger(L,$input);
}

/*
%typemap(in) TVector3 {
    $1 = (int) lua_tonumber(L,$input);
}
*/

class TColor {
public:
    TColor();
    TColor(int r, int g, int b, int a=255);
    ~TColor();

};

class TVector2f
{
public:
    TVector2f();
    TVector2f(float x, float y);
    TVector2f(const TVector2f& other);
    float   X, Y;
};

class TVector2i
{
public:
    TVector2i();
    TVector2i(int x, int y);
    TVector2i(const TVector2i& other);
    int X, Y;
};

typedef TVector2f TVector2;

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

class TRecti
{
public:
    TRecti();
    TRecti(const TRecti& other);
    TRecti* operator=(const TRecti& other);
    vector2di UpperLeftCorner;
    vector2di LowerRightCorner;
};

class TRectf
{
public:
    TRectf();
    TRectf(const TRectf& other);
    TRectf* operator=(const TRectf& other);
    vector2df UpperLeftCorner;
    vector2df LowerRightCorner;
};

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

class TParticleNode : public ISceneNode {
private:
    TParticleNode();
    ~TParticleNode();
public:
    
    void setVelocity(TVector3 vel);
    void setVelocity(Tubras::TParticleDomain dom);

    void setColor(Tubras::TColor color);
    void setColor(Tubras::TParticleDomain colorDomain);
    void setColor(Tubras::TParticleDomain colorDomain, Tubras::TParticleDomain alphaDomain);

    void setSpriteImage(char* fileName, bool alphaBlend=true);
    void setPointSize(float size);
    void setSpeed(float speed);

    void addAction(Tubras::TParticleAction* action);
    
};

class TBackgroundNode: public ISceneNode 
{
private:
    TBackgroundNode();
    ~TBackgroundNode();
public:
};

enum TSLStatus {
	E_OK,
    E_NO_FILE,
    E_BAD_INPUT,
    E_OUT_OF_MEMORY,
    E_BAD_SYNTAX
    };

class TSL
{
public:
	TSL();
	~TSL();
	
    TSLStatus loadScript(char* fileName);
	
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

class TController
{
private:
    TController();
    ~TController();
public:
        void start();
        void stop();
        void setStartEvent(char *value);
        void setStopEvent(char *value);
};

class TRotateController : public TController {
private:
	~TRotateController();
public:
	TRotateController(char* name, ISceneNode* node, float velocity=5.0f,
            TVector3 axis=TVector3::UNIT_Y);
};

class TPlayerController
{
private:
    TPlayerController();
    ~TPlayerController();
public:
    void enableMovement(bool value);
    void enableMouseMovement(bool value);
};

//! The sound class is used to control a sound that has been previously
//! loaded via TApplication::loadSound() member function. 
class TSound {
private:
	TSound();
	~TSound();
public:
    //! Plays the loaded sound.
    //! If the sound is already playing, it is restarted from the beginning.
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

    void setFinishedEvent(char* event);

};


class IGUIElement
{
protected:
    IGUIElement();
    ~IGUIElement();
public:
    IGUIElement* getParent();
    void setVisible(bool value);
    TRecti getAbsolutePosition();
};

class TGUIImage : public IGUIElement
{
protected:
    TGUIImage();
    ~TGUIImage();
public:
    void setAlpha(float alpha);
    void setUseAlphaChannel(bool value);
};

%typemap(typecheck) SWIGLUA_FN = SWIGTYPE; 
%typemap(typecheck) TBlendType = SWIGTYPE; 

class TApplication
{
private:
    TApplication();

public:

	TSL* getConfig();
    
    %extend {
        int acceptEvent(char *eventName, SWIGLUA_FN luaFunc) {
            lua_pushvalue(luaFunc.L, luaFunc.idx);
            void *ref = (void *)luaL_ref(luaFunc.L, LUA_REGISTRYINDEX);
            return self->acceptEventToScript(eventName, ref);
        }
    }

    %extend {
        TController* addFunctionInterval(char* intervalName, SWIGLUA_FN luaFunc, float duration,
            TBlendType blendType) {
            lua_pushvalue(luaFunc.L, luaFunc.idx);
            void *ref = (void *)luaL_ref(luaFunc.L, LUA_REGISTRYINDEX);
            return self->addScriptFunctionInterval(intervalName, ref, duration, 
                blendType);
        }
    }
    
    IAnimatedMeshSceneNode* loadModel(char* fileName, ISceneNode* parent=0, char* name="default");
    TSound* loadSound(char* fileName, bool positional=false, char* finishedEvent="");

    TParticleNode* addParticleNode(char* name, const size_t maxParticles, 
            enum TParticlePrimitive primitive, ISceneNode* parent=0);

    TBackgroundNode* addBackgroundNode(char* imageFileName);

    TGUIImage* addGUIImage(char* fileName, float x=-1.f, float y=-1.f, 
        float width=-1.f, float height=-1.f, bool relative=true, IGUIElement* parent=0);

    void setCursorVisible(bool value);
    void centerGUICursor();
    void setGUICursorEnabled(bool value);

    void setBGColor(int r, int g, int b);
    void setWindowCaption(char* value);    

    int popState();
    int pushState(char* stateName);
    int changeState(char* stateName);

    TPlayerController* getPlayerController();
    void enableMovement(bool value);

    void stopRunning();
};

TApplication* getApplication();



