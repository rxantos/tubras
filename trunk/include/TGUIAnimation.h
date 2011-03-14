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
        TArray<ISceneNode*>     m_animatedNodes;

        IGUIComboBox*           m_cbNodes;
        IGUIComboBox*           m_cbAnimations;
        IGUIEditBox*            m_eStartFrame;
        IGUIEditBox*            m_eEndFrame;
        IGUIEditBox*            m_eCurrentFrame;
        IGUIEditBox*            m_eSpeed;
        IGUIScrollBar*          m_sbFrame;

        bool                    m_autoGrow;
        f32                     m_middle;

        void layout(u32 idx, IGUIStaticText* label, IGUIElement* control);
        void buildNodeList(ISceneManager* manager, ISceneNode* node=0);
        void updateSelectedNode();

    public:
        TGUIAnimation(stringw title="Animation", IGUIElement* parent=0, 
            EGUI_ALIGNMENT ahorz=EGUIA_CENTER, 
            EGUI_ALIGNMENT avert=EGUIA_CENTER, 
            u32 width=225, u32 height=200,
            f32 middle=.35f,
            bool autoGrow=true,
            IGUIEnvironment* environment=0, s32 id=-1);

        bool canClose() 
        {
            this->setVisible(false);
            return false;
        }

        void loadAnimatedNodes(ISceneManager* manager);

        virtual bool OnEvent(const SEvent& event);

    };
}
#endif
