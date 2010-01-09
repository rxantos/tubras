#ifndef _CTEXTOVERLAY_H_
#define _CTEXTOVERLAY_H_
#include "irrString.h"
#include "rect.h"
#include "SColor.h"
#include "IGUIStaticText.h"
#include "IGUIEnvironment.h"

namespace irr {
    namespace gui {
        class CGUITextPanel 
        {
        private:
            IGUIEnvironment*                m_env;
            core::stringc                   m_name;
            core::rectf                     m_dims;
            video::SColor                   m_color;
            gui::IGUIStaticText*            m_panel;

            core::stringc                   m_fontName;
            video::SColor                   m_fontColor;
            f32                             m_fontSize;
            core::array<IGUIStaticText*>    m_textItems;
            core::dimension2di  			m_margins;


        public:
            CGUITextPanel(gui::IGUIEnvironment* env, const core::stringc& name, core::rectf dims, 
                video::SColor overlayColor=video::SColor(128,255,255,255));
            void addItem(const core::stringc& text, EGUI_ALIGNMENT a=EGUIA_UPPERLEFT);
            void removeItem(s32 index);
            void updateItem(s32 index,const core::stringc& text);
            u32 getItemCount() {return m_textItems.size();}
            void setFont(gui::IGUIFont* value);
            void setVisible(bool value);
            bool getVisible();
            void setColor(video::SColor color);
            void setAlpha(float alpha);
            void setRelativePosition(core::rectf dims);

        };
    }
}


#endif
