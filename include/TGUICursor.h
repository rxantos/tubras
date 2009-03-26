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
        dimension2du            m_screenSize;
    public:
        //! constructor
        TGUICursor(IGUIEnvironment* environment);

        //! destructor
        virtual ~TGUICursor();

	    //! Let the renderer decide whether to draw us or not.
        virtual void setVisible(bool visible) {}

        void mouseMoved(const vector2di& relPos);
        const vector2di& getPosition() {return m_pos;}
        void setPosition(const vector2di& value);
        void centerCursor();

    };
}
#endif

