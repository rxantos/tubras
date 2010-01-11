//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
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
        vector2di               m_savePos;
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
        void savePosition() 
        {
            m_savePos = m_pos;
        }

        void restorePosition()
        {
            if(m_savePos.X < 0 && m_savePos.Y < 0)
                centerCursor();
            else
            {
                setPosition(m_savePos);
            }
        }

        vector2di& getEffectivePosition()
        {
            m_effectivePos = m_pos - m_hotspot;
            return m_effectivePos;
        }

    };
}
#endif

