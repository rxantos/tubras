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

#ifndef _TSCRIPT_H_
#define _TSCRIPT_H_

namespace Tubras
{
    typedef std::map< TString,PyObject *> MAP_SCRIPTFUNCS;
    typedef PyObject    TModule;

	typedef MAP_SCRIPTFUNCS::iterator MAP_SCRIPTFUNCS_ITR;

    class TScript 
    {
        friend class TScriptManager;
	private:
        TString             m_modName;
		PyObject*			m_module;
		PyObject*			m_application;
		MAP_SCRIPTFUNCS	    m_functions;

    protected:
	    void printPyErr();
	    int checkError();
        PyObject* classToPyObject(void *klass, std::string type);
	    int	unRef(PyObject *pobj);
        PyObject *getFunction(PyObject *pObj, std::string funcname);
        TScript(TString modName);
        virtual ~TScript();
        int initialize();

    public:
        void logMessage(TString msg) {}
        PyObject* callFunction(std::string function,char *fmt, ...);
        PyObject* callFunction(TModule* baseptr, std::string function,char *fmt, ...);
        bool inheritedFrom(PyObject* obj, std::string cname);
        TModule* getModule() {return m_module;}
        TString getModName() {return m_modName;}
    };
}

#endif