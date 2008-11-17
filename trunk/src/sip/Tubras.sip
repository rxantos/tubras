//--------------------------------------------------------------------
//                         Tubras SIP Wrapper                         
//--------------------------------------------------------------------
%Copying
-----------------------------------------------------------------------------
This source file is part of the Tubras game engine.

Copyright (c) 2006-2008 Tubras Software, Ltd
Also see acknowledgements in docs/Readme.html

This software is licensed under the zlib/libpng license. See the file
"docs/license.html" for detailed information.
-----------------------------------------------------------------------------
%End
%ModuleHeaderCode
#include <tubras.h>
%End

%Module Tubras 0

%ExportedHeaderCode
#include "tubras.h"
using namespace Tubras;
extern int TVector3_FromPyTuple(TVector3& vec3,PyObject* tuple);
%End

%UnitCode
#include "tubras.h"
%End

%ModuleCode
int TVector3_FromPyTuple(TVector3& vec3,PyObject* tuple)
{
    if(!PyTuple_Check(tuple))
        return 0;

    float v[3]={0,0,0};
    int c = PyTuple_Size(tuple);
    for(int i=0;i<c;i++)
    {
        PyObject* o;
        o = PyTuple_GetItem(tuple,i);
        if(PyInt_Check(o))
        {
            v[i] = (float)PyInt_AsLong(o);
        }
        else if(PyFloat_Check(o))
        {
            v[i] = (float)PyFloat_AsDouble(o);
        }
        else return 0;
    }
    vec3 = TVector3(v[0],v[1],v[2]);
    return 1;
}
%End

TApplication* getApplication();

//--------------------------------------------------------------------
//                           T S t r i n g                            
//--------------------------------------------------------------------
%MappedType TString
{

%ConvertFromTypeCode
        const char *s = sipCpp->c_str();
    return PyString_FromString(s);
%End

%ConvertToTypeCode
        // Allow a Python string whenever a TString is expected.
    if (sipIsErr == NULL)
        return PyString_Check(sipPy);
    if (sipPy == Py_None) {
        *sipCppPtr = NULL;
        return 0;
    }
    if (PyString_Check(sipPy)) {
        *sipCppPtr = new TString(PyString_AS_STRING(sipPy));
        return 0;
    }
    *sipCppPtr = new TString("");
    return 1;
%End
};

//--------------------------------------------------------------------
//                           s i z e _ t
//--------------------------------------------------------------------
%MappedType size_t
{
%TypeHeaderCode
#include <stdlib.h>
%End

%ConvertFromTypeCode
        unsigned long l = (unsigned long) *sipCpp;
    return PyLong_FromUnsignedLong(l);
%End

%ConvertToTypeCode
    // Allow a Python string whenever a TString is expected.
    if (sipIsErr == NULL)
        return PyLong_Check(sipPy) | PyInt_Check(sipPy);

    if (sipPy == Py_None) {
        *sipCppPtr = 0;
        return 0;
    }
    if (PyLong_Check(sipPy)) {
        *sipCppPtr = new size_t(PyLong_AsUnsignedLong(sipPy));
        return 0;
    }
    if (PyInt_Check(sipPy)) {
        *sipCppPtr = new size_t(PyInt_AsSsize_t(sipPy));
        return 0;
    }
    *sipCppPtr = 0;
    return 1;
%End
};

//--------------------------------------------------------------------
//                           T C o l o u r                            
//--------------------------------------------------------------------
class TColour
{

public:
    TColour(long red=255, long green=255, long blue=255, long alpha=255);
};


//--------------------------------------------------------------------
//                           T V e c t o r 3                          
//--------------------------------------------------------------------
class TVector3 
{
public:
    float   X;
    float   Y;
    float   Z;
    static TVector3* UNIT_X;
%GetCode
    TVector3* sipVal = (TVector3 *)&TVector3::UNIT_X;
    sipPy = sipConvertFromInstance(sipVal,sipClass_TVector3,NULL);
%End
%SetCode

%End
    static TVector3* UNIT_Y;
%GetCode
    TVector3* sipVal = (TVector3 *)&TVector3::UNIT_Y;
    sipPy = sipConvertFromInstance(sipVal,sipClass_TVector3,NULL);
%End
%SetCode

%End
    static TVector3* UNIT_Z;
%GetCode
    TVector3* sipVal = (TVector3 *)&TVector3::UNIT_Z;
    sipPy = sipConvertFromInstance(sipVal,sipClass_TVector3,NULL);
%End
%SetCode

%End

public:
    TVector3(float nx=0.0, float ny=0.0, float nz=0.0);	
};

//--------------------------------------------------------------------
//                             T O b j e c t
//--------------------------------------------------------------------
class TObject
{
private:
    TObject();
    TObject(TObject&);

public:
    ~TObject();

    int acceptEvent(TString eventName, SIP_PYCALLABLE function);
%MethodCode 
    Py_INCREF(a1);
    sipRes = (int) sipCpp->acceptEventToScript(*a0,(void *)a1);
%End
    TSound* loadSound(TString fileName);

    IAnimatedMeshSceneNode* loadModel(const TString& fileName, 
        ISceneNode* parent=0, const TString& name="default");
};

//--------------------------------------------------------------------
//                             T E v e n t                            
//--------------------------------------------------------------------
class TEvent
{
public:
    TEvent(TString name);
};

/*
//--------------------------------------------------------------------
//                             C I S L
//--------------------------------------------------------------------
class CISL
{
private:
    CISL(CISL&);
public:
    CISL();
    TString getString(const TString& key, const TString& def="");
};
*/
//--------------------------------------------------------------------
//                             C L S L
//--------------------------------------------------------------------
class CLSL
{
private:
    CLSL(CLSL&);
public:
    CLSL();
    TString getString(const TString& key, const TString& def="");
};

//--------------------------------------------------------------------
//                        T A p p l i c a t i o n                     
//--------------------------------------------------------------------
class TApplication : TObject
{
private:
    TApplication(TApplication&);

public:
    TApplication(char* appName="Tubras App"); 
%MethodCode 
    TApplication* theApp = TApplication::getSingletonPtr();
    if(!theApp)
        sipCpp = new TApplication(a0);
%End
    ~TApplication();

    int initialize();
    void run();
    //void setGUICursorVisible(bool);
    //void setGUIEnabled(bool);
    CLSL*  getConfig();
    void stopRunning();

    void setControllerEnabled(TString controllerName, bool value);

    //TModelNode* loadModel(TString meshFileName, TString resourceGroup="General",TString name="default", TSceneNode* parent=NULL, bool isStatic=false);
    void setBGColour(const TColour& c);
    void toggleDebugOverlay();
    void toggleHelpOverlay();
    void cycleDebugData();
    void addHelpText(TString text);
    //
    // "Transfer" annotation transfers ownership back to C++
    //
    TRenderer* getRenderer() /Transfer/;
    //TParticleNode* createParticleNode(TString groupName, int maxParticles, TSceneNode* parent=NULL);
    ICameraSceneNode* getActiveCamera();
};

    enum TRenderMode
    {
        rmNormal,
        rmWire,
        rmNormalWire,
        rmPointCloud
    };

//--------------------------------------------------------------------
//                        T R e n d e r e r 
//--------------------------------------------------------------------
class TRenderer
{
private:
    TRenderer();
    TRenderer(TRenderer&);
    ~TRenderer();
public:
    void setRenderMode(TRenderMode value);
    TRenderMode getRenderMode();
};

//--------------------------------------------------------------------
//                   I C a m e r a S c e n e N o d e
//--------------------------------------------------------------------
class ICameraSceneNode
{
private:
    ICameraSceneNode();
    ICameraSceneNode(ICameraSceneNode&);

};

//--------------------------------------------------------------------
//                         I S c e n e N o d e                         
//--------------------------------------------------------------------
class ISceneNode
{
private:
    ISceneNode();
    ISceneNode(ISceneNode&);
public:
    TVector3*       pos;
%GetCode
    TVector3* sipVal = new TVector3(sipCpp->getPosition());
    sipPy = sipConvertFromInstance(sipVal,sipClass_TVector3,NULL);
%End
%SetCode
    TVector3* sipVal;
    TVector3  vec3;
    sipVal = reinterpret_cast<TVector3 *>(sipForceConvertToInstance(sipPy,sipClass_TVector3,NULL,0,NULL,&sipErr));

    if (sipErr)
    {
        if(TVector3_FromPyTuple(vec3,sipPy))
        {
            sipVal = &vec3;
        }
        else return NULL;
    }
    sipCpp->setPosition(*sipVal);

%End

public:
    void setPosition(TVector3 v);
    TVector3 getPosition();
};

//--------------------------------------------------------------------
//                   I A n i m a t e d S c e n e N o d e                         
//--------------------------------------------------------------------
class IAnimatedMeshSceneNode : ISceneNode
{
private:
    IAnimatedMeshSceneNode();
    IAnimatedMeshSceneNode(IAnimatedMeshSceneNode&);
public:
    void setCurrentFrame(float frame);
      
};

//--------------------------------------------------------------------
//                        T S c e n e N o d e                         
//--------------------------------------------------------------------
class TSceneNode
{
public:
    TVector3*       pos;
%GetCode
    TVector3* sipVal = new TVector3(sipCpp->getPosition());
    sipPy = sipConvertFromInstance(sipVal,sipClass_TVector3,NULL);
%End
%SetCode
    TVector3* sipVal;
    TVector3  vec3;
    sipVal = reinterpret_cast<TVector3 *>(sipForceConvertToInstance(sipPy,sipClass_TVector3,NULL,0,NULL,&sipErr));

    if (sipErr)
    {
        if(TVector3_FromPyTuple(vec3,sipPy))
        {
            sipVal = &vec3;
        }
        else return NULL;
    }
    sipCpp->setPosition(*sipVal);

%End

private:
    TSceneNode(TString name, TSceneNode *parent=NULL);
public:
    //void setPosition(float x, float y, float z);
    void setPosition(TVector3 v);
    //void lookAt (const TVector3& targetPoint);

};

//--------------------------------------------------------------------
//                        T C a m e r a N o d e                      
//--------------------------------------------------------------------
class TCameraNode : TSceneNode
{
private:
    TCameraNode();
};

/*
//--------------------------------------------------------------------
//                     T P a r t i c l e N o d e                      
//--------------------------------------------------------------------
class TParticleNode : TSceneNode
{
public:
TParticleNode(TString name, int maxParticles, TSceneNode* parent);
void addAction(TParticleAction* action);

void setColour(TColour colour);
void setColour(TParticleDomain& colorDomain);
void setColour(TParticleDomain& colorDomain, TParticleDomain& alphaDomain);

void setSize(TVector3 size);
void setSize(TParticleDomain& size);

void setMass(float mass);
void setRotVelocity(TParticleDomain& dom);
void setStartingAge(float age, float sigma);
void setUpVector(TVector3 vec);

void setVelocity(TVector3 vel);
void setVelocity(TParticleDomain& dom);

void setVertexB(TVector3 vec);
void setVertexB(TParticleDomain& dom);
void setVertexBTracks(bool value);
void setTimeStep(float dt);
float getTimeStep();

void setPointSize(float size);

void setMaterialName(TString name,TString resourceGroup="General");
void setSpriteImage(TString name, TString resourceGroup="General", bool alphaBlend=true);
size_t getMaxParticles();
void setMaxParticles(size_t value);

};

//--------------------------------------------------------------------
//                     T P a r t i c l e A c t i o n 
//--------------------------------------------------------------------
class TParticleAction
{
private:
TParticleAction();
TParticleAction(TParticleAction&);
};

//--------------------------------------------------------------------
//                     T P a r t i c l e D o m a i n
//--------------------------------------------------------------------
class TParticleDomain
{
public:
TParticleDomain();
};

//--------------------------------------------------------------------
//                        T L i n e D o m a i n
//--------------------------------------------------------------------
class TLineDomain : TParticleDomain
{
public:
TLineDomain(TVector3 p0, TVector3 p1);
};

//--------------------------------------------------------------------
//                        T D i s c D o m a i n
//--------------------------------------------------------------------
class TDiscDomain : TParticleDomain
{
public:
TDiscDomain(TVector3 center, TVector3 normal, float outerRadius, float innerRadius=0);
};

//--------------------------------------------------------------------
//                        T P l a n e D o m a i n
//--------------------------------------------------------------------
class TPlaneDomain : TParticleDomain
{
public:
TPlaneDomain(TVector3 center, TVector3 normal);
};

//--------------------------------------------------------------------
//                    T C y l i n d e r D o m a i n
//--------------------------------------------------------------------
class TCylinderDomain : TParticleDomain
{
public:
TCylinderDomain(TVector3 e0, TVector3 e1, float outerRadius, float innerRadius=0);
};

//--------------------------------------------------------------------
//                        T B o x D o m a i n
//--------------------------------------------------------------------
class TBoxDomain : TParticleDomain
{
public:
TBoxDomain(TVector3 e0, TVector3 e1);
};

//--------------------------------------------------------------------
//                        T S o u r c e A c t i o n
//--------------------------------------------------------------------
class TSourceAction : TParticleAction
{
public:
TSourceAction(float rate, TParticleDomain& dom);
void setRate(float rate);
};

//--------------------------------------------------------------------
//                      T G r a v i t y A c t i o n
//--------------------------------------------------------------------
class TGravityAction : TParticleAction
{
public:
TGravityAction(TVector3 direction);
};

//--------------------------------------------------------------------
//                        T B o u n c e A c t i o n
//--------------------------------------------------------------------
class TBounceAction : TParticleAction
{
public:
TBounceAction(float friction, float resilience, float cutoff, TParticleDomain& dom);
};

//--------------------------------------------------------------------
//                         T S i n k A c t i o n
//--------------------------------------------------------------------
class TSinkAction : TParticleAction
{
public:
TSinkAction(bool killInside, TParticleDomain& dom);
};
*/

//--------------------------------------------------------------------
//                             T S o u n d                            
//--------------------------------------------------------------------
class TSound
{
public:
    TSound(TString fileName);
%MethodCode 
    sipCpp = getApplication()->loadSound(*a0);
%End

    void play();
    void stop();
    void pause();
    void resume();
    void setLoop(bool loop=true);
    bool getLoop();

    // loop_count: 0 = forever; 1 = play once; n = play n times.
    // inits to 1.
    void setLoopCount(unsigned long loop_count=1);
    unsigned long getLoopCount();

private:
    TSound(TSound&);
};

//--------------------------------------------------------------------
//                     T R o t a t e C o n t r o l l e r              
//--------------------------------------------------------------------
class TRotateController
{
public:
    TRotateController(TString name, TSceneNode* node, float velocity=5.0,TVector3 axis=TVector3::UNIT_Y);
};

//--------------------------------------------------------------------
//                  T O s c i l l a t e C o n t r o l l e r           
//--------------------------------------------------------------------
class TOscillateController
{
public:
    TOscillateController(TString name, TSceneNode* node, float velocity=1.0,float amplitude=3.0, TVector3 axis=TVector3::UNIT_Y);
};

//--------------------------------------------------------------------
//                 T I n t e r v a l C o n t r o l l e r
//--------------------------------------------------------------------
class TIntervalController
{
private:
    ~TIntervalController();

public:
    TIntervalController(TString name,float start, float stop, float duration,
        SIP_PYCALLABLE function);    
%MethodCode 
    TScriptManager* sm = getApplication()->getScriptManager();
    TIntervalDelegate* d = sm->getIntervalDelegate();

    sipCpp = new TIntervalController(*a0,a1,a2,a3,d);
    sipReleaseMappedType(a0,sipMappedType_TString,a0State);
%End

};
