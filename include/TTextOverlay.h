//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
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
        TTextOverlay(const TString& name,TRectf dims, 
            TColor overlayColor=TColor(255,255,255,128));
        virtual ~TTextOverlay();
        u32 addItem(const TString& text, TTextAlignment a=taLeft, TColor color=TColor::White,
            TColor bgColor=TColor::Transparent);
        void removeItem(s32 index);
        void updateItem(s32 index,const TString& text, TColor color=TColor::White,
            TColor bgColor=TColor::Transparent);
        u32 getItemCount() {return m_textItems.size();}
        void setFont(IGUIFont* value);
    };

}

#endif
