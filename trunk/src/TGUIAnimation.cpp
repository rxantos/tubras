//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

#define GID_NODES           1000
#define GID_ANIMATIONS      1001
#define GID_FRAMES          1002

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                       T G U I A n i m a t i o n
    //-----------------------------------------------------------------------
    TGUIAnimation::TGUIAnimation(stringw title, IGUIElement* parent, 
        IGUIEnvironment* environment, s32 id) : TGUIWindow(environment ? environment : getApplication()->getGUIManager(), 
        parent, id,  core::rect<s32>(0, 0, 0, 0), false, false, true),
        m_selected(0)
    {
        u32 width=225, height=300;
        f32 middle = .35f;

        m_middle = middle;
        setText(title.c_str());
        TRecti screen = getApplication()->getRenderer()->getScreenRect();

        // set dialog position
        s32 xpos = screen.getWidth() - width + 9;
        s32 ypos = screen.getHeight() - height;
        setRelativePosition(TRecti(xpos, 
            ypos,
            xpos + width,
            ypos + height)
            );

        // create controls
        IGUIEnvironment* env = getApplication()->getGUIManager();

        u32 idx=0;
        TRecti rect;
        IGUIStaticText* label;

        label = env->addStaticText(L"Node", rect, false, true, this);
        m_cbNodes = env->addComboBox(rect, this, GID_NODES);
        layout(idx, label, m_cbNodes);
        ++idx;
        
        label = env->addStaticText(L"Animation", rect, false, true, this);
        m_cbAnimations = env->addComboBox(rect, this, GID_ANIMATIONS);

        layout(idx, label, m_cbAnimations);
        ++idx;

        label = env->addStaticText(L"Start", rect, false, true, this);
        m_eStartFrame = env->addEditBox(L"1", rect, true, this);
        m_eStartFrame->setEnabled(false);
        m_eStartFrame->setOverrideColor(SColor(0xFFFFFFFF));

        layout(idx, label, m_eStartFrame, .5f);
        ++idx;

        label = env->addStaticText(L"End", rect, false, true, this);
        m_eEndFrame = env->addEditBox(L"", rect, true, this);
        m_eEndFrame->setEnabled(false);
        m_eEndFrame->setOverrideColor(SColor(0xFFFFFFFF));
        layout(idx, label, m_eEndFrame, .5f);
        ++idx;

        label = env->addStaticText(L"Current", rect, false, true, this);
        m_eCurrentFrame = env->addEditBox(L"0", rect, true, this);
        layout(idx, label, m_eCurrentFrame, .5f);
        ++idx;

        label = env->addStaticText(L"Speed", rect, false, true, this);
        m_eSpeed = env->addEditBox(L"100", rect, true, this);
        layout(idx, label, m_eSpeed, .5f);
        ++idx;

        label = env->addStaticText(L"Loop", rect, false, true, this);
        m_cbLoop = env->addCheckBox(false, rect, this);
        layout(idx, label, m_cbLoop, .5f);
        ++idx;
        
        label = env->addStaticText(L"Frame", rect, false, true, this);
        m_sbFrame = env->addScrollBar(true, rect, this, GID_FRAMES);
        layout(idx, label, m_sbFrame);
        ++idx;


        
    }

    //-----------------------------------------------------------------------
    //                             l a y o u t
    //-----------------------------------------------------------------------
    void TGUIAnimation::layout(u32 idx, IGUIStaticText* label,
        IGUIElement* control, f32 cwidth)
    {
        IGUIEnvironment* mgr = getApplication()->getGUIManager();
        int startx = 0;
        int starty = 26; 
        int eheight = 5;
        int spacing = 8;

        IGUIFont* font=mgr->getSkin()->getFont();
        s32 cheight = font->getDimension(L"Ay").Height;
        cheight += (font->getKerningHeight() + eheight);

        f32 fwidth = (f32) AbsoluteRect.getWidth();
        u32 middle = (u32) (fwidth * m_middle);
        s32 ypos = starty + ((cheight + spacing) * idx);
        TRecti tdim(startx, ypos, middle, ypos+cheight);

        if(label)
        {
            label->setRelativePosition(tdim);

            label->setOverrideFont(font);
            label->setOverrideColor(SColor(255, 0, 255, 255));
            label->setBackgroundColor(SColor(0));
            label->setTextAlignment(EGUIA_LOWERRIGHT, EGUIA_UPPERLEFT);
            startx = tdim.LowerRightCorner.X + 5;
        }

        if(control)
        {
            tdim.UpperLeftCorner.X = middle + 5;
            tdim.LowerRightCorner.X = AbsoluteRect.getWidth() - 20;

            f32 awidth = (f32)(tdim.LowerRightCorner.X - tdim.UpperLeftCorner.X) * cwidth;
            tdim.LowerRightCorner.X = tdim.UpperLeftCorner.X + (s32)awidth;

            control->setRelativePosition(tdim);
        }
    }

    //-----------------------------------------------------------------------
    //                     b u i l d N o d e L i s t
    //-----------------------------------------------------------------------
    void TGUIAnimation::buildNodeList(ISceneManager* manager, ISceneNode* node)
    {
        if(!node)
            return;

        ESCENE_NODE_TYPE type = node->getType();
        if(type == ESNT_ANIMATED_MESH)
        {
            m_animatedNodes.push_back(static_cast<scene::IAnimatedMeshSceneNode*>(node));
            stringw name = node->getName();
            m_cbNodes->addItem(name.c_str(), m_animatedNodes.size()-1);
        }

        if(node->getChildren().size())
        {
            list<ISceneNode*> children = node->getChildren();
            list<ISceneNode*>::Iterator itr = children.begin();
            while(itr != children.end())
            {
                ISceneNode* child = *itr;
                buildNodeList(manager, child);
                itr++;
            }
        }
    }

    //-----------------------------------------------------------------------
    //                     l o a d A n i m a t e d N o d e s
    //-----------------------------------------------------------------------
    void TGUIAnimation::loadAnimatedNodes(ISceneManager* manager)
    {
        m_cbNodes->clear();
        m_animatedNodes.clear();
        if(!manager->getRootSceneNode())
            return;

        buildNodeList(manager, manager->getRootSceneNode());
        if(m_animatedNodes.size())
        {
            m_cbNodes->setSelected(0);
            updateSelectedNode();
        }
    }

    //-----------------------------------------------------------------------
    //               u p d a t e S e l e c t e d A n i m a t i o n
    //-----------------------------------------------------------------------
    void TGUIAnimation::updateSelectedAnimation()
    {
        const wchar_t* wname = m_cbAnimations->getText();
        stringc name = wname;

        IAnimatedMesh* mesh = m_selected->getMesh();

        s32 idx = mesh->getAnimationIndex(name.c_str());
        if(idx < 0)
            return;

        io::IAttributes* attr;

        mesh->getAnimation(idx, &attr);

        s32 start = attr->getAttributeAsInt("startFrame");
        s32 end = attr->getAttributeAsInt("endFrame");

        char     buf[64];
        stringw  wbuf;

        sprintf(buf, "%d", start);
        wbuf = buf;
        m_eStartFrame->setText(wbuf.c_str());

        sprintf(buf, "%d", end);
        wbuf = buf;
        m_eEndFrame->setText(wbuf.c_str());

        sprintf(buf, "%d", (int) start);
        wbuf = buf;
        m_eCurrentFrame->setText(wbuf.c_str());

        m_selected->setAnimation(name.c_str());
        m_selected->setCurrentFrame(start);

        m_sbFrame->setMin(start);
        m_sbFrame->setMax(end);
        m_sbFrame->setPos(start);
        m_sbFrame->setSmallStep(1);
        m_sbFrame->setLargeStep(5);

    }

    //-----------------------------------------------------------------------
    //                  u p d a t e S e l e c t e d N o d e
    //-----------------------------------------------------------------------
    void TGUIAnimation::updateSelectedNode()
    {
        s32 idx = m_cbNodes->getSelected();
        if(idx < 0)
            return;

        IAnimatedMeshSceneNode* node = m_animatedNodes[idx];
        m_selected = node;

        s32 start = node->getStartFrame();
        s32 end = node->getEndFrame();

        f32 cur = node->getFrameNr();
        f32 speed = node->getAnimationSpeed();
        
        char     buf[64];
        stringw  wbuf;

        sprintf(buf, "%d", start);
        wbuf = buf;
        m_eStartFrame->setText(wbuf.c_str());

        sprintf(buf, "%d", end);
        wbuf = buf;
        m_eEndFrame->setText(wbuf.c_str());

        sprintf(buf, "%d", (int) cur);
        wbuf = buf;
        m_eCurrentFrame->setText(wbuf.c_str());

        sprintf(buf, "%d", (int) speed);
        wbuf = buf;
        m_eSpeed->setText(wbuf.c_str());

        m_sbFrame->setMin(start);
        m_sbFrame->setMax(end);
        m_sbFrame->setPos(s32(cur));
        m_sbFrame->setSmallStep(1);
        m_sbFrame->setLargeStep(5);

        // enumerate named animations
        IAnimatedMesh* mesh = node->getMesh();
        u32 count = mesh->getAnimationCount();
        io::IAttributes* attr=0;
        m_cbAnimations->clear();
        for(u32 i=0; i < count; i++)
        {
            if(mesh->getAnimation((s32)i, &attr))
            {
                stringw name = attr->getAttributeAsStringW("animationName");
                m_cbAnimations->addItem(name.c_str());
            }
        }
        if(m_cbAnimations->getItemCount())
        {
            m_cbAnimations->setSelected(0);
            updateSelectedAnimation();
        }
    }

    //-----------------------------------------------------------------------
    //                          O n E v e n t
    //-----------------------------------------------------------------------
    bool TGUIAnimation::OnEvent(const SEvent& event)
    {
        bool result = false;

        if(event.EventType == EET_GUI_EVENT)
        {
            s32 id = event.GUIEvent.Caller->getID();
            switch(id)
            {
            case GID_NODES:
                if(event.GUIEvent.EventType == EGET_COMBO_BOX_CHANGED)
                {
                    updateSelectedNode();
                    result = true;
                }
                break;
            case GID_ANIMATIONS:
                if(event.GUIEvent.EventType == EGET_COMBO_BOX_CHANGED)
                {
                    updateSelectedAnimation();
                    result = true;
                }
                break;

            case GID_FRAMES:
                if(event.GUIEvent.EventType == EGET_SCROLL_BAR_CHANGED)
                {
                    if(m_selected)
                    {
                        m_selected->setCurrentFrame(m_sbFrame->getPos());
                        char buf[64];
                        sprintf(buf, "%d", (int) m_selected->getFrameNr());
                        stringw wbuf = buf;
                        m_eCurrentFrame->setText(wbuf.c_str());
                    }
                    result = true;
                }
                break;
            }
        }

        return TGUIWindow::OnEvent(event) | result;
    }

}
