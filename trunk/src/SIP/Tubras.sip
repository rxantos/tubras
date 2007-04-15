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
        TConfigFile*  getConfigFile();


};


