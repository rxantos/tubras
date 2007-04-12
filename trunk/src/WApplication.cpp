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

#include "tubras.h"

namespace Tubras
{
    
    //-----------------------------------------------------------------------
    //                          W A p p l i c a t i o n
    //-----------------------------------------------------------------------
    WApplication::WApplication() : Py::PythonExtension<WApplication>()
    {
    }

    //-----------------------------------------------------------------------
    //                         ~ W A p p l i c a t i o n
    //-----------------------------------------------------------------------
    WApplication::~WApplication() 
    {
    }

    //-----------------------------------------------------------------------
    //                           i n i t _ t y p e
    //-----------------------------------------------------------------------
    void WApplication::init_type(Py::ExtensionModuleBase* module)
    {
        behaviors().name("TApplication");
        behaviors().doc("TApplication: Application Class");
        behaviors().supportRepr();
        behaviors().supportGetattr();

        add_varargs_method("__init__", &WApplication::__init__);
        add_varargs_method("initialize", &WApplication::initialize);
        add_varargs_method("logMessage", &WApplication::logMessage);

        //
        // allow the class to be a base type
        //
        PyTypeObject* pt = behaviors().type_object();
        pt->tp_flags |= Py_TPFLAGS_BASETYPE;
        pt->tp_new = &PyType_GenericNew;
        Py::Dict dict = module->moduleDictionary();
        PyModule_AddObject(module->module().ptr(),"TApplication",(PyObject *)pt);

    }

    //-----------------------------------------------------------------------
    //                           l o g M e s s a g e
    //-----------------------------------------------------------------------
    Py::Object WApplication::logMessage (const Py::Tuple& args)
    {
        return Py::None();
    }

    Py::Object WApplication::__init__ (const Py::Tuple& args)
    {

        return Py::None();
    }


    Py::Object WApplication::initialize(const Py::Tuple& args)
    {

        return Py::None();
    }





}