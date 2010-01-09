#include "CGUITextPanel.h"
#include "IGUIEnvironment.h"
#include "IGUIFont.h"

namespace irr {
    namespace gui {
        //-----------------------------------------------------------------------
        //                        C G U I T e x t P a n e l
        //-----------------------------------------------------------------------
        CGUITextPanel::CGUITextPanel(gui::IGUIEnvironment* env, const core::stringc& name, 
            core::rectf dims, video::SColor color)
        {
            m_env = env;
            m_name = name;
            m_dims = dims;
            m_panel = m_env->addStaticText(L"",core::rect<s32>(0,0,0,0));
            setColor(color);

            m_panel->setRelativePositionProportional(dims);

            m_margins.Width = 5;
            m_margins.Height = 5;
        }

        //-----------------------------------------------------------------------
        //                         s e t V i s i b l e
        //-----------------------------------------------------------------------
        void CGUITextPanel::setVisible(bool value)
        {
            m_panel->setVisible(value);
        }

        //-----------------------------------------------------------------------
        //                         g e t V i s i b l e
        //-----------------------------------------------------------------------
        bool CGUITextPanel::getVisible()
        {
            return m_panel->isVisible();
        }

        //-----------------------------------------------------------------------
        //                          s e t C o l o r
        //-----------------------------------------------------------------------
        void CGUITextPanel::setColor(video::SColor color)
        {
            m_color = color;
            m_panel->setBackgroundColor(color);
        }

        //-----------------------------------------------------------------------
        //                          s e t A l p h a 
        //-----------------------------------------------------------------------
        void CGUITextPanel::setAlpha(float alpha)
        {
            video::SColor c = m_color;
            c.setAlpha((u32)(255.f * alpha));
            setColor(c);
        }

        //-----------------------------------------------------------------------
        //                   s e t R e l a t i v e P o s i t i o n 
        //-----------------------------------------------------------------------
        void CGUITextPanel::setRelativePosition(core::rectf dims)
        {
            m_panel->setRelativePositionProportional(dims);
        }

        //-----------------------------------------------------------------------
        //                              a d d I t e m
        //-----------------------------------------------------------------------
        void CGUITextPanel::addItem(const core::stringc& text, gui::EGUI_ALIGNMENT a)
        {

            s32 offset = 0;
            int idx;
            IGUIFont* font=m_panel->getOverrideFont();
            if(!font)
                font = m_env->getSkin()->getFont();

            core::recti apos = m_panel->getAbsolutePosition();

            idx = (int)m_textItems.size();
            core::stringc name;		
            name = m_name;
            name += "-item";
            name += (idx+1);

            core::stringw wstr = text.c_str();

            s32 cheight = font->getDimension(L"Ay").Height;
            cheight += font->getKerningHeight();

            core::recti tdim(0,0,apos.getWidth(),cheight);

            gui::IGUIStaticText* textArea = m_env->addStaticText(wstr.c_str(),tdim,false,false,0);
            textArea->move(core::position2di(0,cheight*idx));
            //textArea->setOverrideFont(font);
            textArea->setOverrideColor(video::SColor(255,255,255,255));


            offset = idx * (cheight);
            s32 theight = ((idx+1) * cheight) + (m_margins.Height * 2);

            textArea->setTextAlignment(a,EGUIA_UPPERLEFT);

            m_panel->addChild(textArea);
            m_textItems.push_back(textArea);

            if(apos.getHeight() < theight)     
            {
                m_panel->setMinSize(core::dimension2du(0,theight));
            }
        }

        //-----------------------------------------------------------------------
        //                          u p d a t e I t e m
        //-----------------------------------------------------------------------
        void CGUITextPanel::updateItem(s32 index, const core::stringc& text)
        {
            if( (index < 0) || ((u32)index >= m_textItems.size()))
                return;

            core::stringw wstr = text.c_str();
            m_textItems[index]->setText(wstr.c_str());
        }

        //-----------------------------------------------------------------------
        //                            s e t F o n t
        //-----------------------------------------------------------------------
        void CGUITextPanel::setFont(gui::IGUIFont* value)
        {
            m_panel->setOverrideFont(value);
        }
    }
}
