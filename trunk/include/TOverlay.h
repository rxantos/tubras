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

#ifndef _TOVERLAY_H_
#define _TOVERLAY_H_

namespace Tubras
{

    class TPosition
    {
    public:
        float	x;
        float	y;
        TPosition() {x=y=0;};
        TPosition(float ix, float iy)
        {
            x = ix;
            y = iy;
        }
    };
    class TSize
    {
    public:
        float	w;
        float	h;
        TSize() {w=h=0;};
        TSize(float iw, float ih)
        {
            w = iw;
            h = ih;
        }
    };

    class TDim
    {
    public:
        float	x;
        float	y;
        float	w;
        float	h;

        TDim()
        {
            x=y=w=h=0;
        }

        TDim(float ix, float iy, float iw, float ih)
        {
            x = ix;
            y = iy;
            w = iw;
            h = ih;
        }
    };

    class TOverlay : public TObject
    {
    protected:
        TString                     m_name;
        TString                     m_materialName;
        bool                        m_dynamic;
        TDim						m_dims;
        Ogre::MaterialPtr           m_material;
        TColor                      m_color;
        float                       m_alpha;
        Ogre::TextureUnitState*     m_textureUnit;

        Ogre::OverlayContainer*     m_panel;
        Ogre::Overlay*              m_overlay;

    public:
        TOverlay(TString name,TDim dims, TColor color=TColor::White,float alpha=1.0, TString materialName="", bool dynamic=false);
        virtual ~TOverlay();
        void setVisible(bool value);
        bool getVisible();
        void setColor(Ogre::ColourValue color);
        void setAlpha(float alpha);
        void setPos(float left, float top);
        void setSize(float width, float height);
    };

}

#endif