//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TTEXTOVERLAY_H_
#define _TTEXTOVERLAY_H_

namespace Tubras
{

    typedef IGUIStaticText          TTextElement;
    enum TTextAlignment
    {
        taLeft,
        taCenter,
        taRight
    };


    class TTextOverlay : public TOverlay
    {
    private:
        TString                     m_fontName;
        TColor                      m_fontColor;
        float                       m_fontSize;
        TArray<TTextElement*>       m_textItems;
        TDimension  				m_margins;


    public:
        TTextOverlay(const TString& name,TRect dims, 
            TColor overlayColor=TColor(255,255,255,128));
        virtual ~TTextOverlay();
        void addItem(const TString& text, TTextAlignment a=taLeft);
        void removeItem(s32 index);
        void updateItem(s32 index,const TString& text);
        u32 getItemCount() {return m_textItems.size();}
        void setFont(IGUIFont* value);
    };

}

#endif
