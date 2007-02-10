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
    //                           T 1 P C a m e r a
    //-----------------------------------------------------------------------
    T1PCamera::T1PCamera(TString name, TSceneNode* parent) : TCameraNode(name,parent)
    {
        m_zoomInSound = NULL;
        m_zoomOutSound = NULL;
        m_normalFOV = getFOVy();
        m_zoomedFOV = m_normalFOV / 3;

        m_zoomDelegate = FUNCINT_DELEGATE(T1PCamera::procZoom);
        TString lerpName = m_name + "ZoomLerp";
        m_zoomLerp = new TLerpFunction(lerpName,m_normalFOV.valueRadians(),
            m_zoomedFOV.valueRadians(),0.53,m_zoomDelegate);

        m_cmdDelegate = EVENT_DELEGATE(T1PCamera::procCmd);

        m_zoomID = acceptEvent("zoom",m_cmdDelegate);

        setAutoAspectRatio(true);
        setFixedYawAxis(true);
    }

    //-----------------------------------------------------------------------
    //                           ~ T 1 P C a m e r a
    //-----------------------------------------------------------------------
    T1PCamera::~T1PCamera()
    {
    }

    //-----------------------------------------------------------------------
    //                        s e t Z o o m S o u n d s
    //-----------------------------------------------------------------------
    void T1PCamera::setZoomSounds(TSound* in, TSound* out)
    {
        m_zoomInSound = in;
        m_zoomOutSound = out;
    }


    //-----------------------------------------------------------------------
    //                           p r o c Z o o m
    //-----------------------------------------------------------------------
    void T1PCamera::procZoom(double T, void* userData)
    {
        setFOVy(Ogre::Radian(T));
    }


    //-----------------------------------------------------------------------
    //                            p r o c C m d
    //-----------------------------------------------------------------------
    int T1PCamera::procCmd(Tubras::TSEvent event)
    {
        int result = 1;
        int start = 0;
        float famount = 0.0f;

        if(event->getNumParameters() > 0)
        {
            if(event->getParameter(0)->isInt())
                start = event->getParameter(0)->getIntValue();
            else if (event->getParameter(0)->isDouble())
                famount = event->getParameter(0)->getDoubleValue();
        }
        int adjust = start ? 1 : -1;
        size_t eid = event->getID();
        if(eid == m_zoomID)
        {
            if(start)
            {
                m_zoomLerp->start(m_normalFOV.valueRadians(),m_zoomedFOV.valueRadians());
                if(m_zoomInSound)
                    m_zoomInSound->play();
            }
            else 
            {
                m_zoomLerp->start(getFOVy().valueRadians(),m_normalFOV.valueRadians());
                if(m_zoomOutSound)
                    m_zoomOutSound->play();
            }
        }
        return 1;
    }
}
