//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _COVERLAY_H_
#define _COVERLAY_H_

    class COverlay 
    {
    protected:
        stringc                     m_name;
        rectf                       m_dims;
        SColor                      m_colour;
        IGUIStaticText*             m_panel;

    public:
        COverlay(stringc name,rectf dims, SColor colour=SColor(128,255,255,255));
        void setVisible(bool value);
        bool getVisible();
        void setColour(SColor colour);
        void setAlpha(float alpha);
        void setRelativePosition(rectf dims);
    };


#endif

