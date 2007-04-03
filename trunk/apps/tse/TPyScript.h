//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006-2007 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 59 Temple
// Place - Suite 330, Boston, MA 02111-1307, USA, or go to
// http://www.gnu.org/copyleft/lesser.txt.
//
// You may alternatively use this source under the terms of a specific version of
// the Tubras Unrestricted License provided you have obtained such a license from
// Tubras Software Ltd.
//-----------------------------------------------------------------------------

#ifndef _TPYSCRIPT_H_
#define _TPYSCRIPT_H_
#include "python.h"

namespace Tubras
{
    typedef std::map< TString,PyObject *> MAP_PYFUNCS;

	typedef MAP_PYFUNCS::iterator MAP_PYFUNCS_ITR;

    class TPyScript : public TScript
    {
	private:
		PyObject*			m_module;
		PyObject*			m_application;
		MAP_PYFUNCS			m_functions;

    protected:
	    void printPyErr();
	    int checkError();
	    PyObject* classToPyObject(void *klass, string type);
	    int	unRef(PyObject *pobj);
	    int inheritedFrom(PyObject* obj,string cname);
	    PyObject *getFunction(PyObject *pObj,string funcname);
	    PyObject* callFunction(string function, char *fmt, ...);
	    PyObject* callFunction(PyObject* baseptr, string function,char *fmt, ...);

    public:
        TPyScript(TString scriptPath, TString scriptName);
        virtual ~TPyScript();
        virtual int initialize(int argc,char** argv);
    };
}

#endif