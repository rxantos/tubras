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

#ifndef _TRENDER_H_
#define _TRENDER_H_

namespace Tubras
{
    class TRender : public IReferenceCounted, public TObject
    {
    protected:
        IrrlichtDevice*         m_device;
        IVideoDriver*           m_driver;
        ISceneManager*          m_sceneManager;
        IGUIEnvironment*        m_guiManager;
        TCameraNode*            m_camera;
        TNodeFactory*           m_nodeFactory;


    public:
        TRender();
        virtual ~TRender();

        IrrlichtDevice* getDevice() {return m_device;}
        ISceneManager* getSceneManager() {return m_sceneManager;}
        IGUIEnvironment* getGUIManager() {return m_guiManager;}
        IVideoDriver* getVideoDriver() {return m_driver;}

        TCameraNode* getCamera() {return m_camera;}

        int initialize();
        bool renderFrame();

        ITimer* getTimer();
    };

}
#endif
