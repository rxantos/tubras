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

#ifndef _TCONTROLLERFUNCTION_H_
#define _TCONTROLLERFUNCTION_H_

namespace Tubras
{
    /**
    TController Class.
    @remarks
    Controller class - a variation of Ogre::Controller.

    Creating a controller automatically registers it with the Controller Manager.  The manager 
    automatically deletes registered controllers when the manager itself is destroyed.

    If you would like to remove a controller that is no longer needed:
    1. Invoke TControllerManager::remove()
    2. Delete the controller manually

    */
	
    class TControllerFunction : public TObject
    {
    protected:
        float                   m_value;
    public:
        TControllerFunction();
        virtual ~TControllerFunction();

        virtual float calculate(float deltaTime) {return m_value;};
        float getValue() {return m_value;};
        virtual void setValue(float value) {m_value = value;};
    };

    class TFrameTimeFunction : public TControllerFunction
    {
    public:
        virtual float calculate(float deltaTime);
    };
}
#endif