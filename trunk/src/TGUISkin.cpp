//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
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
    TGUISkin::TGUISkin(TString skinName) : IGUISkin(),
        m_defSkin(0),
        m_skinName(skinName)
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
        TString cfgName;

        int result=0;

        //
        // load skin config
        //
        
        if(!m_skinName.size())
        {
            getApplication()->logMessage("Error: Missing GUI Skin Configuration");
            return 1;
        }

        CLSL* config = new CLSL();
        if(config->loadScript(m_skinName) != E_OK)        
        {
            delete config;
            return 1;
        }

        TString baseName = config->getString("textures.base512");
        TString baseName2 = config->getString("textures.base256");
        TString hilightName = config->getString("textures.hilight512");
        TString hilightName2 = config->getString("textures.hilight256");

        m_sc.winLeft = config->getRects32("layout.winLeft");
        m_sc.winRight = config->getRects32("layout.winRight");
        m_sc.winTopMid = config->getRects32("layout.winTopMid");
        m_sc.winTopLeft = config->getRects32("layout.winTopLeft");
        m_sc.winTopRight = config->getRects32("layout.winTopRight");
        m_sc.winBotLeft = config->getRects32("layout.winBotLeft");
        m_sc.winBotRight = config->getRects32("layout.winBotRight");
        m_sc.winBotMid = config->getRects32("layout.winBotMid");
        m_sc.buttonLeft = config->getRects32("layout.buttonLeft");
        m_sc.buttonMid = config->getRects32("layout.buttonMid");
        m_sc.buttonRight = config->getRects32("layout.buttonRight");
        m_sc.menuBar = config->getRects32("layout.menuBar");
        m_sc.horzScrollBar = config->getRects32("layout.horzScrollBar");

        m_sc.checkBox = config->getRects32("layout.checkBox");
        m_sc.checkBoxChecked = config->getRects32("layout.checkBoxChecked");

        IrrlichtDevice* dev = getApplication()->getRenderer()->getDevice();
        m_driver = dev->getVideoDriver();
        m_baseTex = m_driver->getTexture(baseName.c_str());
        if(!m_baseTex)
        {
            config->drop();
            return 1;
        }

        m_baseTex2 = m_driver->getTexture(baseName2.c_str());
        if(!m_baseTex2)
        {
            config->drop();
            return 1;
        }

        m_hilightTex = m_driver->getTexture(hilightName.c_str());
        if(!m_hilightTex)
        {
            config->drop();
            return 1;
        }

        m_hilightTex2 = m_driver->getTexture(hilightName2.c_str());
        if(!m_hilightTex2)
        {
            config->drop();
            return 1;
        }

        m_defSkin = getApplication()->getRenderer()->getGUIManager()->getSkin();
        m_defSkin->grab();

        
        //
        // load default colors
        //

        SColor col;
        col = config->getColor("colors.egdc_3d_face");
        setColor(EGDC_3D_FACE,col);

        col = config->getColor("colors.egdc_window");
        setColor(EGDC_WINDOW,col);

        m_sc.dialogWindowColor = config->getColor("colors.tgdc_dialog_window");
        m_sc.buttonDefaultColor = config->getColor("colors.tgdc_button_default");

        config->drop();

        return result;
    }

    //-----------------------------------------------------------------------
    //                           g e t C o l o r
    //-----------------------------------------------------------------------
    video::SColor TGUISkin::getColor(gui::EGUI_DEFAULT_COLOR color) const
    {
        SColor scolor;
        if(color == EGDC_BUTTON_TEXT)
        {
            scolor = SColor(255,0,0,0);
        }
        else if(color == EGDC_ACTIVE_CAPTION)
        {
            scolor = SColor(255,255,255,255);
        }
        else
        {
            scolor = m_defSkin->getColor(color);
        }
        return scolor;
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
        if(size == EGDS_WINDOW_BUTTON_WIDTH)
            return 18;

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
        SColor col = getColor(EGDC_3D_FACE);
        ITexture* tex=m_baseTex;
        ITexture* tex2=m_hilightTex;

        TRectd dstRect,srcRect;
        dstRect = rect;


        if(element->getType() == (EGUI_ELEMENT_TYPE)TGUI_BUTTON_CLOSE)
        {
            col = SColor(255,255,0,0);
            SColor vcol[4]={col,col,col,col};
            srcRect = TRectd(96/2,1,160/2,64/2);
            m_driver->draw2DImage(m_baseTex2,dstRect,srcRect,clip,vcol,true);
            //m_driver->draw2DImage(m_hilightTex2,dstRect,srcRect,clip,vcol,true);
            return;
        }
        else if(element->getType() == (EGUI_ELEMENT_TYPE)TGUI_BUTTON)
        {
            TGUIButton* btn = (TGUIButton*)element;
            if(btn->isDefault())
            {
                col = m_sc.buttonDefaultColor;
            }
        }

        IGUIElement* parent = element->getParent();
        if(element->getType() == EGUIET_SCROLL_BAR ||
            (parent && (parent->getType() == EGUIET_SCROLL_BAR)))
        {
            SColor vcol[4]={col,col,col,col};            
            srcRect = m_sc.horzScrollBar;
            m_driver->draw2DImage(m_baseTex,dstRect,m_sc.checkBox,clip,vcol,true);
            m_driver->draw2DImage(m_hilightTex,rect,m_sc.checkBox,clip,vcol,true);
            return;
        }

        SColor vcol[4]={col,col,col,col};
        srcRect = m_sc.buttonLeft;

        s32 bheight = rect.getHeight();
        if(bheight == 32)
        {
            tex = m_baseTex2;
            tex2 = m_hilightTex2;
            srcRect.UpperLeftCorner.Y /= 2;
            srcRect.LowerRightCorner.X /= 2;
            srcRect.LowerRightCorner.Y /= 2;
        }
        
        
        dstRect.LowerRightCorner.X = dstRect.UpperLeftCorner.X + bheight;
        m_driver->draw2DImage(tex,dstRect,srcRect,clip,vcol,true);
        m_driver->draw2DImage(tex2,dstRect,srcRect,clip,vcol,true);

        srcRect = m_sc.buttonRight;
        if(bheight == 32)
        {
            tex = m_baseTex2;
            srcRect.UpperLeftCorner.X /= 2;
            srcRect.UpperLeftCorner.Y /= 2;
            srcRect.LowerRightCorner.X /= 2;
            srcRect.LowerRightCorner.Y /= 2;
        }
        dstRect = rect;
        dstRect.UpperLeftCorner.X = dstRect.LowerRightCorner.X - bheight;
        m_driver->draw2DImage(tex,dstRect,srcRect,clip,vcol,true);
        m_driver->draw2DImage(tex2,dstRect,srcRect,clip,vcol,true);

        if(bheight < rect.getWidth())
        {
            srcRect = m_sc.buttonMid;
            if(bheight == 32)
            {
                tex = m_baseTex2;
                srcRect.UpperLeftCorner.X /= 2;
                srcRect.UpperLeftCorner.Y /= 2;
                srcRect.LowerRightCorner.X /= 2;
                srcRect.LowerRightCorner.Y /= 2;
            }
            dstRect = rect;
            dstRect.UpperLeftCorner.X = dstRect.UpperLeftCorner.X + bheight;
            dstRect.LowerRightCorner.X = dstRect.LowerRightCorner.X - bheight;
            m_driver->draw2DImage(tex,dstRect,srcRect,clip,vcol,true);
            m_driver->draw2DImage(tex2,dstRect,srcRect,clip,vcol,true);
        }

        //m_driver->draw2DImage(m_hilightTex,rect,irr::core::rect<s32>(0,288,256,352),clip,vcol,true);
   }

    //-----------------------------------------------------------------------
    //           d r a w 3 D B u t t o n P a n e H i g h l i g h t
    //-----------------------------------------------------------------------
    void TGUISkin::draw3DButtonPaneHighlight(IGUIElement* element,
            const core::rect<s32>& rect,
            const core::rect<s32>* clip)
    {
        SColor col = getColor(EGDC_3D_FACE);
        SColor vcol[4]={col,col,col,col};

        m_driver->draw2DImage(m_hilightTex,rect,irr::core::rect<s32>(0,288,256,352),clip,vcol,true);
    }



    //-----------------------------------------------------------------------
    //            d r a w 3 D B u t t o n P a n e P r e s s e d 
    //-----------------------------------------------------------------------
    void TGUISkin::draw3DButtonPanePressed(IGUIElement* element, 
        const core::rect<s32>& rect,
        const core::rect<s32>* clip)
    {
        SColor col = getColor(EGDC_3D_FACE);
        TRectd dstRect,srcRect;

        if(element->getType() == (EGUI_ELEMENT_TYPE)TGUI_BUTTON_CLOSE)
        {
            col = SColor(255,154,0,0);
            SColor vcol[4]={col,col,col,col};
            dstRect = rect;
            srcRect = TRectd(96/2,1,160/2,64/2);
            m_driver->draw2DImage(m_baseTex2,dstRect,srcRect,clip,vcol,true);
            //m_driver->draw2DImage(m_hilightTex2,dstRect,srcRect,clip,vcol,true);
            return;
        }
        if(element->getType() == (EGUI_ELEMENT_TYPE)TGUI_BUTTON)
        {
            TGUIButton* btn = (TGUIButton*)element;
            if(btn->isDefault())
            {
                col = m_sc.buttonDefaultColor;
            }
        }

        f32 ipl=0.8f;
        col.setRed((s32)(col.getRed() * ipl));
        col.setGreen((s32)(col.getGreen() * ipl));
        col.setBlue((s32)(col.getBlue() * ipl));
        SColor vcol[4]={col,col,col,col};
        ITexture* tex=m_baseTex;

        IGUIElement* parent = element->getParent();
        if(element->getType() == EGUIET_SCROLL_BAR ||
            (parent && (parent->getType() == EGUIET_SCROLL_BAR)))
        {
            SColor vcol[4]={col,col,col,col};            
            srcRect = m_sc.horzScrollBar;
            m_driver->draw2DImage(m_baseTex,dstRect,m_sc.checkBox,clip,vcol,true);
            return;
        }


        srcRect = m_sc.buttonLeft;
        dstRect = rect;

        s32 bheight = rect.getHeight();
        if(bheight == 32)
        {
            tex = m_baseTex2;
            srcRect.UpperLeftCorner.Y /= 2;
            srcRect.LowerRightCorner.X /= 2;
            srcRect.LowerRightCorner.Y /= 2;
        }
        
        
        dstRect.LowerRightCorner.X = dstRect.UpperLeftCorner.X + bheight;
        m_driver->draw2DImage(tex,dstRect,srcRect,clip,vcol,true);

        srcRect = m_sc.buttonRight;
        if(bheight == 32)
        {
            tex = m_baseTex2;
            srcRect.UpperLeftCorner.X /= 2;
            srcRect.UpperLeftCorner.Y /= 2;
            srcRect.LowerRightCorner.X /= 2;
            srcRect.LowerRightCorner.Y /= 2;
        }
        dstRect = rect;
        dstRect.UpperLeftCorner.X = dstRect.LowerRightCorner.X - bheight;
        m_driver->draw2DImage(tex,dstRect,srcRect,clip,vcol,true);

        if(bheight < rect.getWidth())
        {
            srcRect = m_sc.buttonMid;
            if(bheight == 32)
            {
                tex = m_baseTex2;
                srcRect.UpperLeftCorner.X /= 2;
                srcRect.UpperLeftCorner.Y /= 2;
                srcRect.LowerRightCorner.X /= 2;
                srcRect.LowerRightCorner.Y /= 2;
            }
            dstRect = rect;
            dstRect.UpperLeftCorner.X = dstRect.UpperLeftCorner.X + bheight;
            dstRect.LowerRightCorner.X = dstRect.LowerRightCorner.X - bheight;
            m_driver->draw2DImage(tex,dstRect,srcRect,clip,vcol,true);

        }

    }

    //-----------------------------------------------------------------------
    //                    d r a w 3 D S u n k e n P a n e
    //-----------------------------------------------------------------------
    void TGUISkin::draw3DSunkenPane(IGUIElement* element,
        video::SColor bgcolor, bool flat, bool fillBackGround,
        const core::rect<s32>& rect,
        const core::rect<s32>* clip)
    {
        SColor col = getColor(EGDC_3D_FACE);
        SColor vcol[4]={col,col,col,col};
        TRectd dstRect=rect;

        switch(element->getType())
        {
        case EGUIET_LIST_BOX:
            {
                dstRect = rect;
                dstRect.UpperLeftCorner.X -= 2;
                dstRect.UpperLeftCorner.Y -= 2;
                dstRect.LowerRightCorner.X += 2;
                dstRect.LowerRightCorner.Y += 2;
                SColor col(255,0,0,0);
                m_driver->draw2DRectangle(col,dstRect);
                col = m_sc.dialogWindowColor;
                dstRect.UpperLeftCorner.X++;
                dstRect.UpperLeftCorner.Y++;
                dstRect.LowerRightCorner.X--;
                dstRect.LowerRightCorner.Y--;
                m_driver->draw2DRectangle(col,rect);

                m_defSkin->draw3DSunkenPane(element,bgcolor,flat,fillBackGround,rect,clip);
            }
            break;
        case EGUIET_CHECK_BOX:
            {
            IGUICheckBox* cb = (IGUICheckBox*) element;
            if(cb->isChecked())
            {
                SColor col = m_sc.buttonDefaultColor;
                SColor vcol2[4]={col,col,col,col};
                m_driver->draw2DImage(m_baseTex,rect,m_sc.checkBoxChecked,clip,vcol2,true);
                m_driver->draw2DImage(m_hilightTex,rect,m_sc.checkBoxChecked,clip,vcol2,true);
            }
            else
            {
                m_driver->draw2DImage(m_baseTex,rect,m_sc.checkBox,clip,vcol,true);
                m_driver->draw2DImage(m_hilightTex,rect,m_sc.checkBoxChecked,clip,vcol,true);
            }
            break;
            }
        case EGUIET_MENU:
            dstRect.LowerRightCorner.Y--;
            m_defSkin->draw2DRectangle(element,bgcolor,dstRect,clip);
            break;
        default:
            m_defSkin->draw3DSunkenPane(element,bgcolor,flat,fillBackGround,dstRect,clip);
        }
    }

    //-----------------------------------------------------------------------
    //              d r a w 3 D W i n d o w B a c k g r o u n d
    //-----------------------------------------------------------------------
    core::rect<s32> TGUISkin::draw3DWindowBackground(IGUIElement* element,
        bool drawTitleBar, video::SColor titleBarColor,
        const core::rect<s32>& rect,
        const core::rect<s32>* clip)
    {
        core::rect<s32> r=rect;
        TRectd dstRect,srcRect,capRect;

        SColor col(255,170,170,170);
        SColor vcol[4]={col,col,col,col};


        //
        // top left side
        //
        srcRect = m_sc.winTopLeft;
        dstRect = rect;
        
        dstRect.LowerRightCorner.X = dstRect.UpperLeftCorner.X + srcRect.getWidth();
        dstRect.LowerRightCorner.Y = dstRect.UpperLeftCorner.Y + srcRect.getHeight();
        m_driver->draw2DImage(m_baseTex,dstRect,srcRect,clip,vcol,true);

        //
        // top middle
        //
        srcRect = m_sc.winTopMid;
        dstRect = rect;
        dstRect.UpperLeftCorner.X = rect.UpperLeftCorner.X + m_sc.winTopLeft.getWidth();
        dstRect.LowerRightCorner.X = rect.LowerRightCorner.X - m_sc.winTopRight.getWidth();
        dstRect.LowerRightCorner.Y = rect.UpperLeftCorner.Y + srcRect.getHeight();
        m_driver->draw2DImage(m_baseTex,dstRect,srcRect,clip,vcol,true);

        //
        // top right
        //
        srcRect = m_sc.winTopRight;
        dstRect = rect;
        dstRect.UpperLeftCorner.X = rect.LowerRightCorner.X - srcRect.getWidth();
        dstRect.LowerRightCorner.Y = rect.UpperLeftCorner.Y + srcRect.getHeight();
        m_driver->draw2DImage(m_baseTex,dstRect,srcRect,clip,vcol,true);


        //
        // left side
        //
        srcRect = m_sc.winLeft;
        dstRect = rect;
        dstRect.UpperLeftCorner.Y  = dstRect.UpperLeftCorner.Y + m_sc.winTopLeft.getHeight();
        dstRect.LowerRightCorner.X = dstRect.UpperLeftCorner.X + srcRect.getWidth();
        dstRect.LowerRightCorner.Y = dstRect.LowerRightCorner.Y - m_sc.winBotLeft.getHeight();
        m_driver->draw2DImage(m_baseTex,dstRect,srcRect,clip,vcol,true);

        //
        // right side
        //
        srcRect = m_sc.winRight;
        dstRect = rect;
        dstRect.UpperLeftCorner.X = dstRect.LowerRightCorner.X - srcRect.getWidth();
        dstRect.UpperLeftCorner.Y = dstRect.UpperLeftCorner.Y + m_sc.winTopRight.getHeight();
        dstRect.LowerRightCorner.Y = dstRect.LowerRightCorner.Y - m_sc.winBotLeft.getHeight();
        m_driver->draw2DImage(m_baseTex,dstRect,srcRect,clip,vcol,true);


        //
        // bottom left
        //
        srcRect = m_sc.winBotLeft;
        dstRect = rect;
        dstRect.UpperLeftCorner.Y = dstRect.LowerRightCorner.Y - srcRect.getHeight();
        dstRect.LowerRightCorner.X = dstRect.UpperLeftCorner.X + srcRect.getWidth();
        m_driver->draw2DImage(m_baseTex,dstRect,srcRect,clip,vcol,true);

        //
        // bottom right
        //
        srcRect = m_sc.winBotRight;
        dstRect = rect;
        dstRect.UpperLeftCorner.Y = dstRect.LowerRightCorner.Y - srcRect.getHeight();
        dstRect.UpperLeftCorner.X = dstRect.LowerRightCorner.X - srcRect.getWidth();
        m_driver->draw2DImage(m_baseTex,dstRect,srcRect,clip,vcol,true);

        //
        // bottom middle
        //
        srcRect = m_sc.winBotMid;
        dstRect = rect;
        dstRect.UpperLeftCorner.Y = dstRect.LowerRightCorner.Y - srcRect.getHeight();
        dstRect.UpperLeftCorner.X = dstRect.UpperLeftCorner.X + m_sc.winBotLeft.getWidth();
        dstRect.LowerRightCorner.X = dstRect.LowerRightCorner.X - m_sc.winBotRight.getWidth();
        m_driver->draw2DImage(m_baseTex,dstRect,srcRect,clip,vcol,true);

        //
        // client rect 
        //
        SColor col2 = getColor(EGDC_WINDOW);
        switch(element->getType())
        {
        case TGUI_GRAPHICSDLG:
            col2 = m_sc.dialogWindowColor;
            break;
        default:
            break;
        }

        dstRect = rect;
        dstRect.UpperLeftCorner.X += m_sc.winLeft.getWidth();
        dstRect.UpperLeftCorner.Y += m_sc.winTopMid.getHeight();
        dstRect.LowerRightCorner.X -= m_sc.winRight.getWidth();
        dstRect.LowerRightCorner.Y -= m_sc.winBotMid.getHeight();
        m_driver->draw2DRectangle(col2,dstRect);


        capRect = rect;
        capRect.UpperLeftCorner.X += m_sc.winLeft.getWidth()+4;
        capRect.UpperLeftCorner.Y += 4;
        capRect.LowerRightCorner.Y = rect.UpperLeftCorner.Y + m_sc.winTopMid.getHeight();
        return capRect;
    }

    //-----------------------------------------------------------------------
    //                      d r a w 3 D M e n u P a n e
    //-----------------------------------------------------------------------
    void TGUISkin::draw3DMenuPane(IGUIElement* element,
        const core::rect<s32>& rect,
        const core::rect<s32>* clip)
    {
        SColor col(255,250,250,250);
        SColor vcol[4]={col,col,col,col};
        TRectd dstRect = rect;
        TRectd srcRect = m_sc.menuBar;
        --srcRect.LowerRightCorner.Y;
        m_driver->draw2DRectangle(SColor(255,0,0,0),dstRect);
        dstRect.UpperLeftCorner.X++;
        dstRect.LowerRightCorner.X--;
        dstRect.LowerRightCorner.Y--;

        m_driver->draw2DImage(m_baseTex,dstRect,srcRect,clip,vcol,true);
        //m_defSkin->draw3DMenuPane(element,rect,clip);
    }

    //-----------------------------------------------------------------------
    //                      d r a w 3 D T o o l B a r
    //-----------------------------------------------------------------------
    void TGUISkin::draw3DToolBar(IGUIElement* element,
        const core::rect<s32>& rect,
        const core::rect<s32>* clip)
    {
        SColor col(255,250,250,250);
        SColor vcol[4]={col,col,col,col};
        if(element->getType() == EGUIET_MENU)
        {
            TRectd srcRect = m_sc.menuBar;
            m_driver->draw2DImage(m_baseTex,rect,srcRect,clip,vcol,true);
        }
        else
        {
            m_defSkin->draw3DToolBar(element, rect, clip);
        }
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

        switch(element->getType())
        {
        case EGUIET_CHECK_BOX:
            break;
        default:
            m_defSkin->drawIcon(element, icon, position, starttime, currenttime, loop, clip);
        }
    }

    //-----------------------------------------------------------------------
    //                     d r a w 2 D R e c t a n g l e
    //-----------------------------------------------------------------------
    void TGUISkin::draw2DRectangle(IGUIElement* element, const video::SColor &color, 
        const core::rect<s32>& pos, const core::rect<s32>* clip)
    {
        SColor vcol[4]={color,color,color,color};
        TRectd dstRect = pos;
        TRectd srcRect = m_sc.horzScrollBar;
        if(element->getType() == EGUIET_SCROLL_BAR)
        {
            srcRect = m_sc.horzScrollBar;
            m_driver->draw2DImage(m_baseTex,dstRect,srcRect,clip,vcol,true);
            return;
        }

        m_defSkin->draw2DRectangle(element,color,pos,clip);
    }

}
