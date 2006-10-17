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

#ifndef _TUBRAS_H_
#define _TUBRAS_H_

//
// Bullet
//
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"

#undef UNICODE

#include "config.h"

#include "ogre.h"
#include "ogresingleton.h"
#include "ogrescenenode.h"
#include "ogrescenemanager.h"
#include "ogretextareaoverlayelement.h"

//
// OIS
//
#include "ois/ois.h"

//
// CEGUI
//
#include <CEGUI/CEGUIImageset.h>
#include <CEGUI/CEGUISystem.h>
#include <CEGUI/CEGUILogger.h>
#include <CEGUI/CEGUISchemeManager.h>
#include <CEGUI/CEGUIWindowManager.h>
#include "cegui/ceguifontmanager.h"
#include <CEGUI/CEGUIWindow.h>
#include <CEGUI/CEGUIPropertyHelper.h>
#include <CEGUI/elements/CEGUICombobox.h>
#include <CEGUI/elements/CEGUIListbox.h>
#include <CEGUI/elements/CEGUIListboxTextItem.h>
#include <CEGUI/elements/CEGUIPushButton.h>
#include <CEGUI/elements/CEGUIScrollbar.h>
#include "cegui/elements/ceguiframewindow.h"
#include "cegui/elements/ceguicheckbox.h"
#include "cegui/elements/ceguislider.h"
#include "cegui/elements/ceguispinner.h"
#include "cegui/elements/ceguieditbox.h"

#include "OgreCEGUIRenderer.h"
#include "OgreCEGUIResourceProvider.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

typedef std::vector<std::string> TStringVector;
typedef Ogre::StringUtil::StrStreamType TStrStream;
typedef Ogre::Vector2 TVector2;
typedef Ogre::Vector3 TVector3;
typedef Ogre::Vector4 TVector4;
typedef Ogre::Quaternion TQuaternion;
typedef Ogre::Matrix3 TMatrix3;
typedef Ogre::Matrix4 TMatrix4;
typedef Ogre::Real TReal;
typedef Ogre::ColourValue TColor;
typedef Ogre::FloatRect TFloatRect;
typedef Ogre::Radian TRadian;

#ifndef ULONG
typedef unsigned long ULONG;
#endif

using namespace std;

#include "tfile.h"
#include "delegate.h"
#include "trandom.h"
#include "ttimer.h"
#include "tsingleton.h"
#include "teventparameter.h"
#include "tevent.h"
#include "teventqueue.h"
#include "teventmanager.h"
#include "tobject.h"
#include "tinterval.h"
#include "tfunctioninterval.h"
#include "tlerpinterval.h"
#include "tlerpfunction.h"
#include "tlerpscenenodeinterval.h"
#include "tintervalmanager.h"
#include "tconfigfile.h"
#include "tinputbinder.h"
#include "tinputhandler.h"
#include "tinputmanager.h"
#include "tscenenode.h"
#include "tentitynode.h"
#include "tcameranode.h"
#include "tcardnode.h"
#include "tcollisionnode.h"
#include "tviewport.h"
#include "toverlay.h"
#include "ttextoverlay.h"
#include "tmaterial.h"
#include "trenderengine.h"
#include "ttask.h"
#include "ttaskmanager.h"
#include "tcontroller.h"
#include "tcontrollermanager.h"
#include "tcameranode.h"
#include "t1pcamera.h"
#include "t3pcamera.h"
#include "tstate.h"
#include "tsound.h"
#include "tnullsound.h"
#include "tsoundmanager.h"
#include "tfmsound.h"
#include "tfmsoundmanager.h"
#include "tnullsoundmanager.h"
#include "ttheme.h"
#include "tthememanager.h"
#include "tconnection.h"
#include "tconnectionmanager.h"
#include "tapplication.h"
#include "twindow.h"
#include "tframewindow.h"
#include "tguilogger.h"
#include "tguimanager.h"
#include "timagebutton.h"
#include "tbutton.h"
#include "tstatictext.h"
#include "tstaticimage.h"
#include "tcheckbox.h"
#include "tlistbox.h"
#include "teditbox.h"
#include "tcombobox.h"
#include "tspinner.h"
#include "tconsole.h"

#include "tcollisionworld.h"
#include "tdynamicworld.h"
#include "tcollidershape.h"
#include "tcolliderbox.h"
#include "tcollidersphere.h"
#include "tcollidercylinder.h"
#include "tcollidercone.h"
#include "tphysicsmanager.h"

#endif

