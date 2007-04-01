%module Tubras
//
// copied directly to swig output wrapper
//
%{
#include "Tubras.h"
using namespace Tubras;

PyObject* toCharPP(char** v)
{
    return SWIG_NewPointerObj(v,SWIGTYPE_p_p_char,0);
}
%}
%include std_string.i
%include std_vector.i
%include TString.i
%include TSingleton.i
%include TState.i
%include TApplication.i
%include TSceneNode.i
%include TModelNode.i
