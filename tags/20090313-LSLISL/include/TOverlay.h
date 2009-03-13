//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TOVERLAY_H_
#define _TOVERLAY_H_

namespace Tubras
{

    class TOverlay : public TObject
    {
    protected:
        TString                     m_name;
        TRect                       m_dims;
        TColor                      m_color;
        IGUIStaticText*             m_panel;

    public:
        TOverlay(TString name,TRect dims, TColor color=TColor(255,255,255,128));
        virtual ~TOverlay();
        void setVisible(bool value);
        bool getVisible();
        void setColor(TColor color);
        void setAlpha(float alpha);
        void setRelativePosition(TRect dims);
    };

}

#endif

