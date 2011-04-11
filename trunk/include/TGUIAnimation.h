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
        TArray<IAnimatedMeshSceneNode*>     m_animatedNodes;
        IAnimatedMeshSceneNode* m_selected;
        IGUIComboBox*           m_cbNodes;
        IGUIComboBox*           m_cbAnimations;
        IGUIEditBox*            m_eStartFrame;
        IGUIEditBox*            m_eEndFrame;
        IGUIEditBox*            m_eCurrentFrame;
        IGUIEditBox*            m_eSpeed;
        IGUICheckBox*           m_cbLoop;
        IGUIScrollBar*          m_sbFrame;

        f32                     m_middle;

        void layout(u32 idx, IGUIStaticText* label, IGUIElement* control, f32 cwidth=1.f);
        void buildNodeList(ISceneManager* manager, ISceneNode* node=0);
        void updateSelectedNode();

    public:
        TGUIAnimation(stringw title="Animation", IGUIElement* parent=0, 
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
