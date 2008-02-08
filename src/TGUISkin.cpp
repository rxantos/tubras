//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                          T G U I S k i n
    //-----------------------------------------------------------------------
    TGUISkin::TGUISkin() : IGUISkin(),
        m_defSkin(0)
    {
    }

    //-----------------------------------------------------------------------
    //                         ~ T G U I S k i n
    //-----------------------------------------------------------------------
    TGUISkin::~TGUISkin()
    {
        if(m_defSkin)
            m_defSkin->drop();
    }

    //-----------------------------------------------------------------------
    //                           i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TGUISkin::initialize()
    {
        int result=0;

        m_defSkin = getApplication()->getRenderer()->getGUIManager()->getSkin();
        m_defSkin->grab();

        return result;
    }

    //-----------------------------------------------------------------------
    //                           g e t C o l o r
    //-----------------------------------------------------------------------
    video::SColor TGUISkin::getColor(gui::EGUI_DEFAULT_COLOR color) const
    {
        SColor colour;
        colour = m_defSkin->getColor(color);
        return colour;
    }

    //-----------------------------------------------------------------------
    //                           s e t C o l o r
    //-----------------------------------------------------------------------
    void TGUISkin::setColor(EGUI_DEFAULT_COLOR which, video::SColor newColor)
    {
        m_defSkin->setColor(which, newColor);
    }

    //-----------------------------------------------------------------------
    //                           g e t S i z e
    //-----------------------------------------------------------------------
    s32 TGUISkin::getSize(EGUI_DEFAULT_SIZE size) const
    { 
        s32 result=0;
        result = m_defSkin->getSize(size);
        return result;
    }

    //-----------------------------------------------------------------------
    //                      g e t D e f a u l t T e x t
    //-----------------------------------------------------------------------
    const wchar_t* TGUISkin::getDefaultText(EGUI_DEFAULT_TEXT text) const
    {
        const wchar_t* result;
        result = m_defSkin->getDefaultText(text);
        return result;
    }

    //-----------------------------------------------------------------------
    //                      s e t D e f a u l t T e x t
    //-----------------------------------------------------------------------
    void TGUISkin::setDefaultText(EGUI_DEFAULT_TEXT which, const wchar_t* newText)
    {
        m_defSkin->setDefaultText(which, newText);
    }

    //-----------------------------------------------------------------------
    //                             s e t S i z e
    //-----------------------------------------------------------------------
    void TGUISkin::setSize(EGUI_DEFAULT_SIZE which, s32 size)
    {
        m_defSkin->setSize(which, size);
    }

    //-----------------------------------------------------------------------
    //                             g e t F o n t
    //-----------------------------------------------------------------------
    IGUIFont* TGUISkin::getFont(EGUI_DEFAULT_FONT which) const
    {
        IGUIFont* result;
        result = m_defSkin->getFont(which);
        return result;
    }

    //-----------------------------------------------------------------------
    //                             s e t F o n t
    //-----------------------------------------------------------------------
    void TGUISkin::setFont(IGUIFont* font, EGUI_DEFAULT_FONT which)
    {
        m_defSkin->setFont(font, which);
    }

    //-----------------------------------------------------------------------
    //                        g e t S p r i t e B a n k
    //-----------------------------------------------------------------------
    IGUISpriteBank* TGUISkin::getSpriteBank() const
    {
        IGUISpriteBank* result;
        result = m_defSkin->getSpriteBank();
        return result;
    }

    //-----------------------------------------------------------------------
    //                        s e t S p r i t e B a n k
    //-----------------------------------------------------------------------
    void TGUISkin::setSpriteBank(IGUISpriteBank* bank)
    {
        m_defSkin->setSpriteBank(bank);
    }

    //-----------------------------------------------------------------------
    //                            g e t I c o n
    //-----------------------------------------------------------------------
    u32 TGUISkin::getIcon(EGUI_DEFAULT_ICON icon) const
    {
        u32 result;
        result = m_defSkin->getIcon(icon);
        return result;
    }

    //-----------------------------------------------------------------------
    //                            s e t I c o n
    //-----------------------------------------------------------------------
    void TGUISkin::setIcon(EGUI_DEFAULT_ICON icon, u32 index)
    {
        m_defSkin->setIcon(icon,index);
    }

    //-----------------------------------------------------------------------
    //            d r a w 3 D B u t t o n P a n e S t a n d a r d
    //-----------------------------------------------------------------------
    void TGUISkin::draw3DButtonPaneStandard(IGUIElement* element,
        const core::rect<s32>& rect,
        const core::rect<s32>* clip)
    {
        IrrlichtDevice* dev = getApplication()->getRenderer()->getDevice();
        IVideoDriver* driver = dev->getVideoDriver();
        ITexture* tex = driver->getTexture("data/tex/gui.tga");
    

        driver->draw2DImage(tex,rect,irr::core::rect<s32>(0,0,256,70),clip,0,true);
        //m_defSkin->draw3DButtonPaneStandard(element,rect,clip);
    }

    //-----------------------------------------------------------------------
    //            d r a w 3 D B u t t o n P a n e P r e s s e d 
    //-----------------------------------------------------------------------
    void TGUISkin::draw3DButtonPanePressed(IGUIElement* element, 
        const core::rect<s32>& rect,
        const core::rect<s32>* clip)
    {
        IrrlichtDevice* dev = getApplication()->getRenderer()->getDevice();
        IVideoDriver* driver = dev->getVideoDriver();
        ITexture* tex = driver->getTexture("data/tex/gui.tga");
        core::rect<s32> drect = rect;
        drect.UpperLeftCorner.X += 5;
        drect.UpperLeftCorner.Y += 5;
        drect.LowerRightCorner.X += 5;
        drect.LowerRightCorner.Y += 5;

        driver->draw2DImage(tex,drect,irr::core::rect<s32>(0,0,256,70),clip,0,true);
        //m_defSkin->draw3DButtonPanePressed(element,rect,clip);
    }

    //-----------------------------------------------------------------------
    //                    d r a w 3 D S u n k e n P a n e
    //-----------------------------------------------------------------------
    void TGUISkin::draw3DSunkenPane(IGUIElement* element,
        video::SColor bgcolor, bool flat, bool fillBackGround,
        const core::rect<s32>& rect,
        const core::rect<s32>* clip)
    {
        m_defSkin->draw3DSunkenPane(element,bgcolor,flat,fillBackGround,rect,clip);
    }

    //-----------------------------------------------------------------------
    //              d r a w 3 D W i n d o w B a c k g r o u n d
    //-----------------------------------------------------------------------
    core::rect<s32> TGUISkin::draw3DWindowBackground(IGUIElement* element,
        bool drawTitleBar, video::SColor titleBarColor,
        const core::rect<s32>& rect,
        const core::rect<s32>* clip)
    {
        core::rect<s32> r;

        r = m_defSkin->draw3DWindowBackground(element,drawTitleBar,titleBarColor,rect,clip);

        return r;
    }

    //-----------------------------------------------------------------------
    //                      d r a w 3 D M e n u P a n e
    //-----------------------------------------------------------------------
    void TGUISkin::draw3DMenuPane(IGUIElement* element,
        const core::rect<s32>& rect,
        const core::rect<s32>* clip)
    {
        m_defSkin->draw3DMenuPane(element,rect,clip);
    }

    //-----------------------------------------------------------------------
    //                      d r a w 3 D T o o l B a r
    //-----------------------------------------------------------------------
    void TGUISkin::draw3DToolBar(IGUIElement* element,
        const core::rect<s32>& rect,
        const core::rect<s32>* clip)
    {
        m_defSkin->draw3DToolBar(element, rect, clip);
    }

    //-----------------------------------------------------------------------
    //                     d r a w 3 D T a b B u t t o n
    //-----------------------------------------------------------------------
    void TGUISkin::draw3DTabButton(IGUIElement* element, bool active,
        const core::rect<s32>& rect, const core::rect<s32>* clip, gui::EGUI_ALIGNMENT alignment)
    {
        m_defSkin->draw3DTabButton(element, active, rect, clip, alignment);
    }

    //-----------------------------------------------------------------------
    //                      d r a w 3 D T a b B o d y 
    //-----------------------------------------------------------------------
    void TGUISkin::draw3DTabBody(IGUIElement* element, bool border, bool background,
        const core::rect<s32>& rect, const core::rect<s32>* clip, s32 tabHeight, gui::EGUI_ALIGNMENT alignment )
    {
        m_defSkin->draw3DTabBody(element, border, background, rect, clip, tabHeight, alignment);
    }

    //-----------------------------------------------------------------------
    //                           d r a w I c o n
    //-----------------------------------------------------------------------
    void TGUISkin::drawIcon(IGUIElement* element, EGUI_DEFAULT_ICON icon,
        const core::position2di position, u32 starttime, u32 currenttime, 
        bool loop, const core::rect<s32>* clip)
    {
        m_defSkin->drawIcon(element, icon, position, starttime, currenttime, loop, clip);
    }

    //-----------------------------------------------------------------------
    //                     d r a w 2 D R e c t a n g l e
    //-----------------------------------------------------------------------
    void TGUISkin::draw2DRectangle(IGUIElement* element, const video::SColor &color, 
        const core::rect<s32>& pos, const core::rect<s32>* clip)
    {
        m_defSkin->draw2DRectangle(element,color,pos,clip);
    }

}
