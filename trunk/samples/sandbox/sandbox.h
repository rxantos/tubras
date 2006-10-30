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
#ifndef _SANDBOX_H_
#define _SANDBOX_H_
#include "tubras.h"

using namespace Tubras;
class TSandbox : public TApplication
{
private:
	TSound*			m_fire;
    int             screenNumber;
    TModelNode*     m_cube;
	TModelNode*		m_ball;
	TOverlay*		m_crosshair;
    Ogre::Entity*   m_grid;    
	int				m_velocity;
	bool			m_deactivation;
	size_t			m_fireCount;

public:
    TSandbox(int argc,char **argv);
    virtual ~TSandbox();

    int quitApp(TSEvent event);
    int showConsole(Tubras::TSEvent event);
    int saveScreen(Tubras::TSEvent event);
    int showHelp(Tubras::TSEvent event);
    int toggleWire(Tubras::TSEvent event);
    int toggleDebug(Tubras::TSEvent event);
    int toggleBBox(Tubras::TSEvent event);
	int togglePhysicsDebug(Tubras::TSEvent event);
	int toggleGravity(Tubras::TSEvent event);
	int toggleDeactivation(Tubras::TSEvent event);
	int fire(Tubras::TSEvent event);
	int adjustFireVelocity(Tubras::TSEvent event);
    virtual int initialize();
};

#endif
