//--------------------------------------------------------------------
//                         Tubras SIP Wrapper                         
//--------------------------------------------------------------------
%Copying
-----------------------------------------------------------------------------
 This source file is part of the Tubras game engine
    
 For the latest info, see http://www.tubras.com

 Copyright (c) 2006-2007 Tubras Software, Ltd
 Also see acknowledgements in Readme.html

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Lesser General Public License as published by the Free Software
 Foundation; either version 2 of the License, or (at your option) any later
 version.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License along with
 this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 Place - Suite 330, Boston, MA 02111-1307, USA, or go to
 http://www.gnu.org/copyleft/lesser.txt.

 You may alternatively use this source under the terms of a specific version of
 the Tubras Unrestricted License provided you have obtained such a license from
 Tubras Software Ltd.  
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
            v[i] = PyInt_AsLong(o);
        }
        else if(PyFloat_Check(o))
        {
            v[i] = PyFloat_AsDouble(o);
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
%TypeHeaderCode
#include <string>
%End

%ConvertFromTypeCode
     const char *s = sipCpp->c_str();
     return PyString_FromString(s);
%End

%ConvertToTypeCode
         // Allow a Python string whenever a string is expected.
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
//                           T C o l o u r                            
//--------------------------------------------------------------------
class TColour
{
%TypeHeaderCode
#include <tubras.h>
%End
	    
	public:
		TColour(float red=1.0, float green=1.0, float blue=1.0, float alpha=1.0);
};


//--------------------------------------------------------------------
//                           T V e c t o r 3                          
//--------------------------------------------------------------------
class TVector3 
{
%TypeHeaderCode
#include <tubras.h>
%End
public:
    float   x;
    float   y;
    float   z;
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
//                             T E v e n t                            
//--------------------------------------------------------------------
class TEvent
{
%TypeHeaderCode
#include <tubras.h>
%End
    public:
        TEvent(TString name);
};

//--------------------------------------------------------------------
//                        T C o n f i g F i l e                       //
//--------------------------------------------------------------------
class TConfigFile
{
%TypeHeaderCode
#include <tubras.h>
%End
	    
	public:
		TConfigFile();
        TString getSetting(TString key, TString section = "") const;
};

//--------------------------------------------------------------------
//                        T A p p l i c a t i o n                     
//--------------------------------------------------------------------
class TApplication
{
%TypeHeaderCode
#include <tubras.h>
%End
public:

	public:
		TApplication(int argc,void* argv,char* appName="Tubras App") [(int, int , char*)];	
%MethodCode 
            sipCpp = new TApplication(a0,(char**)a1,a2);
%End

		int initialize();
		void run();
		void setGUICursorVisible(bool);
        void setGUIEnabled(bool);
        TConfigFile*  getConfigFile();
        void stopRunning();

        int acceptEvent(TString eventName, SIP_PYCALLABLE function);
%MethodCode 
            Py_INCREF(a1);
            sipRes = (int) sipCpp->acceptEventToScript(*a0,(void *)a1);
%End

        void setControllerEnabled(TString controllerName, bool value);

        TModelNode* loadModel(TString meshFileName, TString resourceGroup="General",TString name="default", TSceneNode* parent=NULL, bool isStatic=false);
        void setBackgroundColour(TColour c);
        void toggleDebugOverlay();
        void toggleHelpOverlay();
        void toggleWireFrame();
        void addHelpText(TString text);
        TSound* loadSound(TString fileName);
        TParticleNode* createParticleNode(TString groupName, int maxParticles, TSceneNode* parent=NULL);
        TCameraNode* getCamera(TString name);
        void captureScreen();
        void captureScreen(TString fileName);
};

//--------------------------------------------------------------------
//                        T S c e n e N o d e                         
//--------------------------------------------------------------------
class TSceneNode
{
public:
    TVector3*       pos;
%GetCode
        TVector3* sipVal = new TVector3(sipCpp->getPos());
        sipPy = sipConvertFromInstance(sipVal,sipClass_TVector3,NULL);
%End
%SetCode
    TVector3* sipVal;
    TVector3  vec3;
    sipVal = reinterpret_cast<TVector3 *>(sipForceConvertToInstance(sipPy,sipClass_TVector3,NULL,0,NULL,&sipIsErr));

    if (sipIsErr)
    {
        if(TVector3_FromPyTuple(vec3,sipPy))
        {
            sipVal = &vec3;
        }
        else return NULL;
    }
    sipCpp->setPos(*sipVal);

%End



public:
    TSceneNode(TString name, TSceneNode *parent=NULL);
    void setPos(float x, float y, float z);
    void setPos(TVector3 v);
    void lookAt (const TVector3& targetPoint);
    void lookAt (float x, float y, float z);

};

//--------------------------------------------------------------------
//                        T C a m e r a N o d e                      
//--------------------------------------------------------------------
class TCameraNode : TSceneNode
{
private:
    TCameraNode();
};


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

    void setPointSize(float size);
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

//--------------------------------------------------------------------
//                        T M o d e l N o d e                         
//--------------------------------------------------------------------
class TModelNode : TSceneNode
{
public:
    TModelNode(TString name, TString resourceGroup, TString filename, TSceneNode* parent=0,bool isStatic=true);
};


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
%TypeHeaderCode
#include <tubras.h>
%End
public:
    TRotateController(TString name, TSceneNode* node, float velocity=5.0,TVector3 axis=TVector3::UNIT_Y);
};

//--------------------------------------------------------------------
//                  T O s c i l l a t e C o n t r o l l e r           
//--------------------------------------------------------------------
class TOscillateController
{
%TypeHeaderCode
#include <tubras.h>
%End
public:
    TOscillateController(TString name, TSceneNode* node, float velocity=1.0,float amplitude=3.0, TVector3 axis=TVector3::UNIT_Y);
};

//--------------------------------------------------------------------
//                            T I n t e r v a l                       
//--------------------------------------------------------------------
class TInterval
{
%TypeHeaderCode
#include <tubras.h>
%End
private:
    TInterval(const TString &name, double duration, bool open_ended);
    TInterval(TInterval&);
    ~TInterval();

public:
        void start(double start_t = 0.0, double end_t = -1.0, double play_rate = 1.0);
        void setDoneEvent(const TString &event);


};

//--------------------------------------------------------------------
//                    T F u n c t i o n I n t e r v a l               
//--------------------------------------------------------------------
class TFunctionInterval : TInterval
{
%TypeHeaderCode
#include <tubras.h>
%End
private:
    ~TFunctionInterval();

public:
    TFunctionInterval(TString name,double duration,SIP_PYCALLABLE function);    
%MethodCode 
            TScriptManager* sm = getApplication()->getScriptManager();
            TFuncIntDelegate* d = sm->getFuncIntervalDelegate();

            sipCpp = new TFunctionInterval(*a0,a1, d, (void *)a2);
            sipReleaseMappedType(a0,sipMappedType_TString,a0State);
%End



};



