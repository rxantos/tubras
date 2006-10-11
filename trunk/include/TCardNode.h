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
#ifndef _TCARDNODE_H_
#define _TCARDNODE_H_

namespace Tubras
{
    enum TRenderPosition
    {
        rpBack,
        rpFront
    };

    class TCardNode : public TSceneNode
    {
    protected:
        Ogre::Rectangle2D*      m_rect;
        Ogre::Pass*             m_pass;
        Ogre::TextureUnitState* m_tus;
        Ogre::AxisAlignedBox    m_aab;
        TMaterial*              m_mat;
        TVector3                m_pos;
        TVector3                m_size;

        TRenderPosition         m_renderPos;
        bool                    m_fullScreen;
            
    public:
        TCardNode (string name, TSceneNode *parent,
            TVector3 pos=Ogre::Vector3::ZERO, TVector3 size=Ogre::Vector3::ZERO, 
            TRenderPosition rp=rpBack,bool fullScreen=true);
        virtual ~TCardNode();
        int setImage(string groupName, string imageName);

        // only x & y components used
        virtual void setPos(const TVector3& pos);
        virtual void setPos(TReal x, TReal y, TReal z=0);

        virtual void setSize(const TVector3& size);
        virtual void setSize(TReal x, TReal y, TReal z=0);

        void setScrollAnimation(float uSpeed, float vSpeed);
        void setRotateAnimation(float speed);

        void setAlpha(float value);

    };

}


#endif