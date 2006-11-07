//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006 Tubras Software Ltd
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
#ifndef _TTASKDELEGATE_H_
#define _TTASKDELEGATE_H_

namespace Tubras
{
    class TTask;
    class TObject;


    typedef int (TObject::*TTaskDelegateFunction)(TTask* Param);

    class TTaskDelegate : public TDelegate
    {
    protected:
        TTaskDelegateFunction  pFunction;

    public:
        TTaskDelegate() : TDelegate(0)  
        {
            pFunction = 0;
        }

        TTaskDelegate(TObject* instance,
            TTaskDelegateFunction pFunctionPointer) : TDelegate(instance)
        {
            pFunction = pFunctionPointer;
        }

        virtual int Execute(TTask* Param) const;

        void SetCallback (TObject  *instance,
            TTaskDelegateFunction   pFunctionPointer)
        {
            m_instance  = instance;
            pFunction = pFunctionPointer;
        }

    };

}
#endif