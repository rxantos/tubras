#ifndef _CTEXTOVERLAY_H_
#define _CTEXTOVERLAY_H_

class CTextOverlay : public COverlay
{
private:
    stringc                     m_fontName;
    SColor                      m_fontColor;
    float                       m_fontSize;
    array<IGUIStaticText*>      m_textItems;
    dimension2di  				m_margins;


public:
    CTextOverlay(const stringc& name,rectf dims, 
        SColor overlayColor=SColor(128,255,255,255));
    void addItem(const stringc& text, EGUI_ALIGNMENT a=EGUIA_UPPERLEFT);
    void removeItem(s32 index);
    void updateItem(s32 index,const stringc& text);
    u32 getItemCount() {return m_textItems.size();}
    void setFont(IGUIFont* value);
};


#endif
