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
    //                          T G U I D i a l o g
    //-----------------------------------------------------------------------
    TGUIDialog::TGUIDialog(IGUIEnvironment* environment, IGUIElement* parent,
        s32 id, core::rect<s32> rectangle,bool centered) : IGUIWindow(environment, parent,
        id, rectangle)
    {
        s32 x,y,w,h;
        TDimension dims = environment->getVideoDriver()->getScreenSize();

        Type = (EGUI_ELEMENT_TYPE)TGUI_GRAPHICSDLG;
        w = getAbsolutePosition().getWidth();
        h = getAbsolutePosition().getHeight();
        if(centered)
        {

            x = (dims.Width / 2) - (w / 2);
            y = (dims.Height / 2) - (h / 2);

            move(position2d<s32>(x,y));
        }

        s32 bwidth=60,bheight=24,pad=30,bx,by;
        bx = w-bwidth-pad;
        by = h-bheight-pad;

        IGUIButton* btn = getApplication()->getGUIFactory()->addButton(
            TRectd(bx,by,bx+bwidth,by+bheight),
            this, -1, L"Save");

        bx -= (bwidth + (pad/2));
        btn = getApplication()->getGUIFactory()->addButton(
            TRectd(bx,by,bx+bwidth,by+bheight),
            this, -1, L"Cancel");

        bx = pad;
        btn = getApplication()->getGUIFactory()->addButton(
            TRectd(bx,by,bx+bwidth,by+bheight),
            this, -1, L"Apply");

    }

    //-----------------------------------------------------------------------
    //                         ~ T G U I D i a l o g
    //-----------------------------------------------------------------------
    TGUIDialog::~TGUIDialog()
    {
    }

    //! called if an event happened.
    bool TGUIDialog::OnEvent(const SEvent& event)
    {
        switch(event.EventType)
        {
        case EET_GUI_EVENT:
            if (event.GUIEvent.EventType == EGET_ELEMENT_FOCUS_LOST)
            {
                Dragging = false;
            }
            else
                if (event.GUIEvent.EventType == EGET_ELEMENT_FOCUSED)
                {
                    if (isMyChild(event.GUIEvent.Caller) && Parent)
                        Parent->bringToFront(this);
                }
                else
                    if (event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
                    {
                        if (event.GUIEvent.Caller == CloseButton)
                        {
                            if (Parent)
                            {
                                // send close event to parent
                                SEvent e;
                                e.EventType = EET_GUI_EVENT;
                                e.GUIEvent.Caller = this;
                                e.GUIEvent.Element = 0;
                                e.GUIEvent.EventType = EGET_ELEMENT_CLOSED;

                                // if the event was not absorbed
                                if (!Parent->OnEvent(e))
                                    remove();

                                return true;

                            }
                            else
                            {
                                remove();
                                return true;
                            }
                        }
                    }
                    break;
        case EET_MOUSE_INPUT_EVENT:
            switch(event.MouseInput.Event)
            {
            case EMIE_LMOUSE_PRESSED_DOWN:
                DragStart.X = event.MouseInput.X;
                DragStart.Y = event.MouseInput.Y;
                Dragging = true;
                if (!Environment->hasFocus(this))
                {
                    Environment->setFocus(this);
                    if (Parent)
                        Parent->bringToFront(this);
                }
                return true;
            case EMIE_LMOUSE_LEFT_UP:
                Dragging = false;
                return true;
            case EMIE_MOUSE_MOVED:
                if (Dragging)
                {
                    // gui window should not be dragged outside its parent
                    if (Parent)
                        if (event.MouseInput.X < Parent->getAbsolutePosition().UpperLeftCorner.X +1 ||
                            event.MouseInput.Y < Parent->getAbsolutePosition().UpperLeftCorner.Y +1 ||
                            event.MouseInput.X > Parent->getAbsolutePosition().LowerRightCorner.X -1 ||
                            event.MouseInput.Y > Parent->getAbsolutePosition().LowerRightCorner.Y -1)

                            return true;


                    move(core::position2d<s32>(event.MouseInput.X - DragStart.X, event.MouseInput.Y - DragStart.Y));
                    DragStart.X = event.MouseInput.X;
                    DragStart.Y = event.MouseInput.Y;
                    return true;
                }
                break;
            default:
                break;
            }
        default:
            break;
        }

        return IGUIElement::OnEvent(event);
    }


    //! Updates the absolute position.
    void TGUIDialog::updateAbsolutePosition()
    {
        IGUIElement::updateAbsolutePosition();
    }


    //! draws the element and its children
    void TGUIDialog::draw()
    {
        if (!IsVisible)
            return;

        IGUISkin* skin = Environment->getSkin();

        core::rect<s32> rect = AbsoluteRect;
        core::rect<s32> *cl = &AbsoluteClippingRect;

        // draw body fast
        rect = skin->draw3DWindowBackground(this, true, skin->getColor(EGDC_ACTIVE_BORDER),
            AbsoluteRect, &AbsoluteClippingRect);

        if (Text.size())
        {
            rect.UpperLeftCorner.X += skin->getSize(EGDS_TEXT_DISTANCE_X);
            rect.UpperLeftCorner.Y += skin->getSize(EGDS_TEXT_DISTANCE_Y);
            rect.LowerRightCorner.X -= skin->getSize(EGDS_WINDOW_BUTTON_WIDTH) + 5;

            IGUIFont* font = skin->getFont(EGDF_WINDOW);
            if (font)
                font->draw(Text.c_str(), rect, skin->getColor(EGDC_ACTIVE_CAPTION), false, true, cl);
        }

        IGUIElement::draw();
    }



    //-----------------------------------------------------------------------
    //                        T G r a p h i c s D l g
    //-----------------------------------------------------------------------
    TGraphicsDlg::TGraphicsDlg(IGUIEnvironment* environment, IGUIElement* parent,
        s32 id) : TGUIDialog(environment, parent,
        id, TRectd(0,0,400,400))
    {
        setText(L"Graphic Settings");
        environment->addCheckBox(false,TRectd(20,40,140,60),this,-1,L"Test Checkbox");
        IGUIListBox* lb = environment->addListBox(TRectd(20,70,160,200),this,-1,true);
        lb->addItem(L"Item 1");
        lb->addItem(L"This is a really long item...");
        lb->addItem(L"Item 2");
        lb->addItem(L"Item 3");
        lb->addItem(L"Item 4");
        lb->addItem(L"Item 5");
        lb->addItem(L"Item 6");
        lb->addItem(L"Item 7");
        lb->addItem(L"Item 8");
        lb->addItem(L"Item 9");

    }

    TGraphicsDlg::~TGraphicsDlg()
    {
    }

}
