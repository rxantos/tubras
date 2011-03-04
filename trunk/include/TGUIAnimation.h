//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TGUIANIMATION_H_
#define _TGUIANIMATION_H_

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                       T G U I A n i m a t i o n
    //-----------------------------------------------------------------------
    class TGUIAnimation : public TGUIWindow
    {
    protected:
        TArray<IGUIStaticText*> m_labelItems;
        TArray<IGUIStaticText*> m_valueItems;
        bool                    m_autoGrow;
        f32                     m_middle;

    public:
        TGUIAnimation(stringw title="TGUIAnimation", IGUIElement* parent=0, 
            EGUI_ALIGNMENT ahorz=EGUIA_CENTER, 
            EGUI_ALIGNMENT avert=EGUIA_CENTER, 
            u32 width=225, u32 height=200,
            f32 middle=.5f,
            bool autoGrow=true,
            IGUIEnvironment* environment=0, s32 id=-1);

        bool canClose() 
        {
            this->setVisible(false);
            return false;
        }

        u32 addItem(core::stringc text, 
            TColor lcolor=TColor(0, 255, 255),
            TColor lbgColor=TColor::Transparent,
            TColor vcolor=TColor::White,
            TColor vbgColor=TColor::Transparent);

        u32 addItem(core::stringc text, core::stringc value,
            TColor lcolor=TColor(0, 255, 255),
            TColor lbgColor=TColor::Transparent,
            TColor vcolor=TColor::White,
            TColor vbgColor=TColor::Transparent);

        void removeItem(s32 index);

        void updateItem(u32 index, const TString& text, TColor color=TColor::White,
            TColor bgColor=TColor::Transparent);

        void updateValue(u32 index, const TString& text, TColor color=TColor::White,
            TColor bgColor=TColor::Transparent);  

        u32 getItemCount() {return m_labelItems.size();}

        void setFont(IGUIFont* value);


    };
}
#endif
