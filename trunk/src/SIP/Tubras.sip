//--------------------------------------------------------------------//
//                         Tubras SIP Wrapper                         //
//--------------------------------------------------------------------//

%Module Tubras 0

%ExportedHeaderCode
	#include "tubras.h"
    using namespace Tubras;
%End

%UnitCode
	#include "tubras.h"
%End

TApplication* getApplication();

//--------------------------------------------------------------------//
//                           T S t r i n g                            //
//--------------------------------------------------------------------//
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

//--------------------------------------------------------------------//
//                           T C o l o u r                            //
//--------------------------------------------------------------------//
class TColour
{
%TypeHeaderCode
#include <tubras.h>
%End
	    
	public:
		TColour(float red=1.0, float green=1.0, float blue=1.0, float alpha=1.0);
};

//--------------------------------------------------------------------//
//                           T V e c t o r 3                          //
//--------------------------------------------------------------------//
class TVector3 
{
%TypeHeaderCode
#include <tubras.h>
%End
	    
	public:
		TVector3();
		TVector3(float nx, float ny, float nz);	
};

//--------------------------------------------------------------------//
//                             T E v e n t                            //
//--------------------------------------------------------------------//
class TEvent
{
%TypeHeaderCode
#include <tubras.h>
%End
    public:
        TEvent(TString name);
};

//--------------------------------------------------------------------//
//                        T C o n f i g F i l e                       //
//--------------------------------------------------------------------//
class TConfigFile
{
%TypeHeaderCode
#include <tubras.h>
%End
	    
	public:
		TConfigFile();
        TString getSetting(TString key, TString section = "") const;
};

//--------------------------------------------------------------------//
//                        T A p p l i c a t i o n                     //
//--------------------------------------------------------------------//
class TApplication
{
%TypeHeaderCode
#include <tubras.h>
%End

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

};

//--------------------------------------------------------------------//
//                        T S c e n e N o d e                         //
//--------------------------------------------------------------------//
class TSceneNode
{
public:
    TSceneNode(TString name, TSceneNode *parent=NULL);
    void setPos(float x, float y, float z);
};

//--------------------------------------------------------------------//
//                        T M o d e l N o d e                         //
//--------------------------------------------------------------------//
class TModelNode : TSceneNode
{
public:
    TModelNode(TString name, TString resourceGroup, TString filename, TSceneNode* parent,bool isStatic=true);
};


