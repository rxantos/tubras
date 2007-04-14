// Define the SIP wrapper for the Tubras engine.

%Module Tubras 0

%ExportedHeaderCode
	#include "tubras.h"
    using namespace Tubras;
%End

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

};


