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
    //                           T L i n e N o d e
    //-----------------------------------------------------------------------
    TLineNode::TLineNode(TString name, TSceneNode* parent,
        TVector3 pt1,TVector3 pt2,TColor color) : TSceneNode(name,parent)
    {
        m_pt1 = pt1;
        m_pt2 = pt2;
        m_color = color;
        m_lineObject = NULL;

        Ogre::SceneManager* sm = getRenderEngine()->getSceneManager();
        m_lineObject =  sm->createManualObject(name + "::lineObject"); 
        m_mat = new TMaterial(name+"::mat","General");
        m_mat->setColor(m_color);

        m_lineObject->begin(m_mat->getName(), Ogre::RenderOperation::OT_LINE_LIST);
        m_lineObject->position(pt1);
        m_lineObject->position(pt2);
        m_lineObject->end(); 
        getNode()->attachObject(m_lineObject);
    }

    //-----------------------------------------------------------------------
    //                          ~ T L i n e N o d e
    //-----------------------------------------------------------------------
    TLineNode::~TLineNode()
    {
    }


}