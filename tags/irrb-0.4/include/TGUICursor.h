//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TGUICURSOR_H_
#define _TGUICURSOR_H_

namespace Tubras
{
    class TGUICursor : public TGUIImage
    {
    private:
        IImage*                 m_defaultImage;
        ITexture*               m_defaultTexture;
        vector2di               m_pos;
        vector2di               m_effectivePos;
        vector2di               m_hotspot;
        dimension2du            m_screenSize;
        dimension2du            m_cursorSize;
    public:
        //! constructor
        TGUICursor(IGUIEnvironment* environment);

        //! destructor
        virtual ~TGUICursor();

        virtual void setImage(video::ITexture* image);

	    //! Let the renderer decide whether to draw us or not.
        virtual void setVisible(bool visible) {}

        void setHotSpot(vector2di value) {m_hotspot = value;}
        vector2di getHotSpot() {return m_hotspot;}

        void mouseMoved(const vector2di& relPos);
        const vector2di& getPosition() {return m_pos;}
        void setPosition(const vector2di& value);
        void centerCursor();

        vector2di& getEffectivePosition()
        {
            m_effectivePos = m_pos - m_hotspot;
            return m_effectivePos;
        }

    };
}
#endif

