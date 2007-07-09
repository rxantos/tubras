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
#ifndef _ECORETEST_H_
#define _ECORETEST_H_
#include "tubras.h"

using namespace Tubras;
class TEcoreTest : public TApplication
{
private:
    int                 screenNumber;
    Ogre::Entity*       m_grid;    
    float			    m_velocity;
    bool			    m_deactivation;
    Ogre::TexturePtr ptex;
    Ogre::HardwarePixelBufferSharedPtr buffer;
    Ogre::TexturePtr optex;
    Ogre::HardwarePixelBufferSharedPtr obuffer;
    int                 canvas_bufSize;


public:
    TEcoreTest(int argc,char **argv);
    virtual ~TEcoreTest();

    int quitApp(TSEvent event);
    int showConsole(Tubras::TSEvent event);
    int saveScreen(Tubras::TSEvent event);
    int showHelp(Tubras::TSEvent event);
    int toggleWire(Tubras::TSEvent event);
    int toggleDebug(Tubras::TSEvent event);
    int toggleBBox(Tubras::TSEvent event);
    int mouseDown(Tubras::TSEvent event);
    int mouseUp(Tubras::TSEvent event);
    int mouseMove(Tubras::TSEvent event);
    virtual int initialize();

    virtual void preRender();

    void setUserDebugInfo(TStringVector& debugStrings);

};

#endif
