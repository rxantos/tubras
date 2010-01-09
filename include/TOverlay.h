//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TOVERLAY_H_
#define _TOVERLAY_H_

namespace Tubras
{

    class TOverlay : public TDelegate
    {
    protected:
        TString                     m_name;
        TRectf                      m_dims;
        TColor                      m_color;
        IGUIStaticText*             m_panel;

    public:
        TOverlay(TString name, TRectf dims, TColor color=TColor(255,255,255,128));
        virtual ~TOverlay();
        void setVisible(bool value);
        bool getVisible();
        void setColor(TColor color);
        void setAlpha(float alpha);
        void setRelativePosition(TRectf dims);
    };

}

#endif

