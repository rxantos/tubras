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

        TXMLConfig* config = new TXMLConfig();
        if(!config->load(m_skinName))
            return 1;

        m_baseName = config->getString("base","textures");
        m_baseNames = config->getString("bases","textures");
        m_hilightName = config->getString("hilight","textures");

        m_sc.winLeft = config->getRectd("winLeft","layout");
        m_sc.winRight = config->getRectd("winRight","layout");
        m_sc.winTopMid = config->getRectd("winTopMid","layout");
        m_sc.winTopLeft = config->getRectd("winTopLeft","layout");
        m_sc.winTopRight = config->getRectd("winTopRight","layout");
        m_sc.winBotLeft = config->getRectd("winBotLeft","layout");
        m_sc.winBotRight = config->getRectd("winBotRight","layout");
        m_sc.winBotMid = config->getRectd("winBotMid","layout");
        m_sc.buttonLeft = config->getRectd("buttonLeft","layout");
        m_sc.buttonMid = config->getRectd("buttonMid","layout");
        m_sc.buttonRight = config->getRectd("buttonRight","layout");
        m_sc.menuBar = config->getRectd("menuBar","layout");

        m_sc.checkBox = config->getRectd("checkBox","layout");
        m_sc.checkBoxChecked = config->getRectd("checkBoxChecked","layout");

        IrrlichtDevice* dev = getApplication()->getRenderer()->getDevice();
        m_driver = dev->getVideoDriver();
        m_baseTex = m_driver->getTexture(m_baseName.c_str());
        if(!m_baseTex)
        {
            config->drop();
            return 1;
        }

        m_baseTexs = m_driver->getTexture(m_baseNames.c_str());
        if(!m_baseTexs)
        {
            config->drop();
            return 1;
        }

        m_hilightTex = m_driver->getTexture(m_hilightName.c_str());
        if(!m_hilightTex)
        {
            config->drop();
            return 1;
        }

        m_defSkin = getApplication()->getRenderer()->getGUIManager()->getSkin();
        m_defSkin->grab();

        
        //
        // load default colours
        //

        SColor col;
        col = config->getColour("egdc_3d_face","colours");
        setColor(EGDC_3D_FACE,col);

        col = config->getColour("egdc_window","colours");
        setColor(EGDC_WINDOW,col);

        m_sc.dialogWindowColour = config->getColour("tgdc_dialog_window","colours");

        config->drop();

        return result;
    }

    //-----------------------------------------------------------------------
    //                           g e t C o l o r
    //-----------------------------------------------------------------------
    video::SColor TGUISkin::getColor(gui::EGUI_DEFAULT_COLOR color) const
    {
        SColor colour;
        if(color == EGDC_BUTTON_TEXT)
        {
            colour = SColor(255,0,0,0);
        }
        else if(color == EGDC_ACTIVE_CAPTION)
        {
            colour = SColor(255,0,0,0);
        }
        else
        {
            colour = m_defSkin->getColor(color);
        }
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
        SColor col = getColor(EGDC_3D_FACE);
        SColor vcol[4]={col,col,col,col};
        TRectd dstRect,srcRect;
        ITexture* tex=m_baseTex;

        srcRect = m_sc.buttonLeft;
        dstRect = rect;

        s32 bheight = rect.getHeight();
        if(bheight == 32)
        {
            tex = m_baseTexs;
            srcRect.UpperLeftCorner.Y /= 2;
            srcRect.LowerRightCorner.X /= 2;
            srcRect.LowerRightCorner.Y /= 2;
        }
        
        
        dstRect.LowerRightCorner.X = dstRect.UpperLeftCorner.X + bheight;
        m_driver->draw2DImage(tex,dstRect,srcRect,clip,vcol,true);

        srcRect = m_sc.buttonRight;
        if(bheight == 32)
        {
            tex = m_baseTexs;
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
                tex = m_baseTexs;
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
        f32 ipl=0.8f;
        col.setRed((s32)(col.getRed() * ipl));
        col.setGreen((s32)(col.getGreen() * ipl));
        col.setBlue((s32)(col.getBlue() * ipl));
        SColor vcol[4]={col,col,col,col};
        TRectd dstRect,srcRect;
        ITexture* tex=m_baseTex;

        srcRect = m_sc.buttonLeft;
        dstRect = rect;

        s32 bheight = rect.getHeight();
        if(bheight == 32)
        {
            tex = m_baseTexs;
            srcRect.UpperLeftCorner.Y /= 2;
            srcRect.LowerRightCorner.X /= 2;
            srcRect.LowerRightCorner.Y /= 2;
        }
        
        
        dstRect.LowerRightCorner.X = dstRect.UpperLeftCorner.X + bheight;
        m_driver->draw2DImage(tex,dstRect,srcRect,clip,vcol,true);

        srcRect = m_sc.buttonRight;
        if(bheight == 32)
        {
            tex = m_baseTexs;
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
                tex = m_baseTexs;
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
        case EGUIET_CHECK_BOX:
            {
            IGUICheckBox* cb = (IGUICheckBox*) element;
            if(cb->isChecked())
            {
                m_driver->draw2DImage(m_baseTex,rect,m_sc.checkBoxChecked,clip,vcol,true);
            }
            else
            {
                m_driver->draw2DImage(m_baseTex,rect,m_sc.checkBox,clip,vcol,true);
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
            col2 = m_sc.dialogWindowColour;
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
        m_defSkin->draw2DRectangle(element,color,pos,clip);
    }

}
