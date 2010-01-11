//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                            T G U I I n f o
    //-----------------------------------------------------------------------
    TGUIInfo::TGUIInfo(stringw title, IGUIElement* parent, 
        EGUI_ALIGNMENT ahorz, EGUI_ALIGNMENT avert, 
        u32 width, u32 height, f32 middle, bool autoGrow,
        IGUIEnvironment* environment, s32 id) : TGUIWindow(environment ? environment : getApplication()->getGUIManager(), 
        parent, id,  core::rect<s32>(0, 0, width, height), false, false, true)
    {
        m_autoGrow = autoGrow;
        m_middle = middle;
        setText(title.c_str());
        TRecti screen = getApplication()->getRenderer()->getScreenRect();

        // horizontal alignment
        switch(ahorz)
        {
        case EGUIA_LOWERRIGHT:
            setRelativePosition(core::position2di(screen.getWidth() - AbsoluteRect.getWidth() + 9, 1));
            break;
        case EGUIA_UPPERLEFT:
            setRelativePosition(core::position2di(-9, 1));
            break;
        };
    }

    //-----------------------------------------------------------------------
    //                             a d d I t e m 
    //-----------------------------------------------------------------------
    u32 TGUIInfo::addItem(core::stringc text, TColor lcolor, TColor lbgColor,
        TColor vcolor, TColor vbgColor)
    {
        IGUIEnvironment* mgr = getApplication()->getGUIManager();
        int starty = 26; // fix this... use ClientRect

        int idx = (int)m_labelItems.size();
        TStrStream lname, vname;		
        lname << "label" << idx+1;
        vname << "value" << idx+1;

        TStringW wtext = text.c_str();

        IGUIFont* font=mgr->getSkin()->getFont();
        s32 cheight = font->getDimension(L"Ay").Height;
        cheight += font->getKerningHeight();

        f32 fwidth = (f32) AbsoluteRect.getWidth();
        u32 middle = (u32) (fwidth * m_middle);
        TRecti tdim(0, 0, middle, cheight);

        TTextElement* textArea = mgr->addStaticText(wtext.c_str(),tdim,false,false,this);
        textArea->move(position2di(0,starty+(cheight*idx)));
        textArea->setOverrideFont(font);
        textArea->setOverrideColor(lcolor);
        textArea->setBackgroundColor(lbgColor);
        textArea->setTextAlignment(EGUIA_LOWERRIGHT, EGUIA_UPPERLEFT);
        m_labelItems.push_back(textArea);

        if(textArea->getAbsolutePosition().LowerRightCorner.Y > (this->AbsoluteRect.LowerRightCorner.Y - 30))
        {
            AbsoluteRect.LowerRightCorner.Y = textArea->getAbsolutePosition().LowerRightCorner.Y + 30;
            this->setRelativePosition(AbsoluteRect);
            this->updateAbsolutePosition();
        }

        tdim.UpperLeftCorner.X = tdim.LowerRightCorner.X + 5;
        tdim.LowerRightCorner.X = AbsoluteRect.getWidth() - 20;
        textArea = mgr->addStaticText(L"",tdim,false,false,this);
        textArea->move(position2di(0,starty+(cheight*idx)));
        textArea->setOverrideFont(font);
        textArea->setOverrideColor(vcolor);
        textArea->setBackgroundColor(vbgColor);
        textArea->setTextAlignment(EGUIA_UPPERLEFT, EGUIA_UPPERLEFT);
        m_valueItems.push_back(textArea);

        return m_labelItems.size()-1;
    }

    //-----------------------------------------------------------------------
    //                             a d d I t e m 
    //-----------------------------------------------------------------------
    u32 TGUIInfo::addItem(core::stringc text, core::stringc value, 
        TColor lcolor, TColor lbgColor, TColor vcolor, TColor vbgColor)
    {
        u32 idx = addItem(text, lcolor, lbgColor);
        updateValue(idx, value, vcolor, vbgColor);
        return idx;
    }

    //-----------------------------------------------------------------------
    //                           r e m o v e I t e m 
    //-----------------------------------------------------------------------
    void TGUIInfo::removeItem(s32 index)
    {
    }

    //-----------------------------------------------------------------------
    //                          u p d a t e I t e m 
    //-----------------------------------------------------------------------
    void TGUIInfo::updateItem(u32 index, const TString& text, TColor color, 
        TColor bgColor)
    {
        if( (index < 0) || ((u32)index >= m_labelItems.size()))
            return;

        TStringW wstr = text.c_str();
        m_labelItems[index]->setText(wstr.c_str());
        m_labelItems[index]->setOverrideColor(color);
        m_labelItems[index]->setBackgroundColor(bgColor);
    }

    //-----------------------------------------------------------------------
    //                         u p d a t e V a l u e
    //-----------------------------------------------------------------------
    void TGUIInfo::updateValue(u32 index, const TString& text, TColor color, 
        TColor bgColor)
    {
        if( (index < 0) || ((u32)index >= m_valueItems.size()))
            return;

        TStringW wstr = text.c_str();
        m_valueItems[index]->setText(wstr.c_str());
        m_valueItems[index]->setOverrideColor(color);
        m_valueItems[index]->setBackgroundColor(bgColor);
    }

    //-----------------------------------------------------------------------
    //                            s e t F o n t
    //-----------------------------------------------------------------------
    void TGUIInfo::setFont(IGUIFont* value)
    {
    }
}
