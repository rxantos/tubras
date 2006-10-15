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

#ifndef _TCONTROLLER_H_
#define _TCONTROLLER_H_

namespace Tubras
{
    /**
    TController Class.
    @remarks
    Controller class.

    Creating a controller automatically registers it with the Controller Manager.  The manager 
    automatically deletes registered controllers when the manager itself is destroyed.

    If you would like to remove a controller that is no longer needed:
    1. Invoke TControllerManager::remove()
    2. Delete the controller manually

    */
    class TController
    {
        friend class TControllerManager;
    private:
        string                  m_name;
        ULONG                   m_startTime;
        bool                    m_enabled;
    public:
        ULONG                   m_elapsedTime;
        ULONG                   m_deltaTime;
        ULONG                   m_lastTime;

    public:
        TController(string controllerName);
        virtual ~TController();

        string getName() {return m_name;};

        virtual void setEnabled(bool value);
        virtual bool getEnabled() {return m_enabled;};

        virtual void update(float delta);
    };

}

#endif