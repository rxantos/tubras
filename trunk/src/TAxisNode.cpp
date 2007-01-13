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
    //                           T A x i s N o d e
    //-----------------------------------------------------------------------
    TAxisNode::TAxisNode(TString name, TSceneNode* parent, int size)
        : TSceneNode(name,parent)
    {
        m_size = size;
        m_xLine = new TLineNode(name+"axis-x",this,TVector3(-m_size,0,0),TVector3(m_size,0,0),TColor(1,0,0,0));
        m_yLine = new TLineNode(name+"axis-y",this,TVector3(0,-m_size,0),TVector3(0,m_size,0),TColor(0,1,0,0));
        m_zLine = new TLineNode(name+"axis-z",this,TVector3(0,0,-m_size),TVector3(0,0,m_size),TColor(0,0,1,0));
    }

    //-----------------------------------------------------------------------
    //                          ~ T A x i s N o d e
    //-----------------------------------------------------------------------
    TAxisNode::~TAxisNode()
    {
    }


}