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

#ifndef _TPLANENODE_H_
#define _TPLANENODE_H_

namespace Tubras
{
    class TPlaneNode : public TSceneNode
    {
        friend class TNodeFactory;
    private:
        f32             m_size;
        TVector3        m_normal;
        TAABBox         m_aabb;

        TVertex         m_vertices[4];
        SMaterial       m_material;

    private:
        TPlaneNode(ISceneNode* parent);

    public:
        ~TPlaneNode();

        int initialize(f32 size, TVector3 normal=TVector3::UNIT_Y, TColour colour=TColour(255,255,255));

        void render();
        const core::aabbox3d<f32>& getBoundingBox() const {return m_aabb;} 
        void OnRegisterSceneNode();
	    virtual u32 getMaterialCount() const;
        SMaterial& getMaterial(u32 i);

    };
} 
#endif
