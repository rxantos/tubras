//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                          T G U I D i a l o g
    //-----------------------------------------------------------------------
    TGUIDialog::TGUIDialog(IGUIEnvironment* environment, IGUIElement* parent,
        s32 id, core::rect<s32> rectangle,TDialogButtons buttons, bool modal, 
        bool centered, bool draggable) : IGUIWindow(environment, parent,
        id, rectangle), ModalScreen(0), Dragging(false), Modal(modal), 
        IsDraggable(draggable), IsActive(false)
    {
        s32 x,y,w,h;
        TDimension dims = environment->getVideoDriver()->getScreenSize();

	    if (modal)
	    {
            parent->removeChild(this);
            parent = environment->addModalScreen(parent);
            parent->addChild(this);
            
	    }

        Type = (EGUI_ELEMENT_TYPE)TGUI_GRAPHICSDLG;
        w = getAbsolutePosition().getWidth();
        h = getAbsolutePosition().getHeight();
        if(centered)
        {

            x = (dims.Width / 2) - (w / 2);
            y = (dims.Height / 2) - (h / 2);

            move(position2d<s32>(x,y));
        }

        s32 bwidth=82,bheight=24,pad=30,bx,by;
        bx = w-bwidth-pad;
        by = h-bheight-pad;

        if(buttons && dbSave)
        {
            TGUIButton* btn = getApplication()->getGUIFactory()->addButton(
                TRecti(bx,by,bx+bwidth,by+bheight),
                this, TID_DLG_SAVE, L"Save");
            btn->setIsDefault(true);
        }

        if(buttons && dbCancel)
        {
            bx -= (bwidth + (pad/2));
            getApplication()->getGUIFactory()->addButton(
                TRecti(bx,by,bx+bwidth,by+bheight),
                this, TID_DLG_CANCEL, L"Cancel");
        }

        if(buttons && dbApply)
        {
            bx = pad;
            getApplication()->getGUIFactory()->addButton(
                TRecti(bx,by,bx+bwidth,by+bheight),
                this, TID_DLG_APPLY, L"Apply");
        }

        updateClientRect();

    }

    //-----------------------------------------------------------------------
    //                         ~ T G U I D i a l o g
    //-----------------------------------------------------------------------
    TGUIDialog::~TGUIDialog()
    {
    }

    //-----------------------------------------------------------------------
    //                         c l o s e D i a l o g
    //-----------------------------------------------------------------------
    void TGUIDialog::closeDialog()
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
                IsActive = false;
            }
            else
                if (event.GUIEvent.EventType == EGET_ELEMENT_FOCUSED)
                {
                    if ( Parent && ((event.GUIEvent.Caller == this) || isMyChild(event.GUIEvent.Caller)))
                    {
                        Parent->bringToFront(this);
                        IsActive = true;
                    }
                    else
                    {
                        IsActive = false;
                    }
                }
                else
                    if (event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
                    {
                        if (event.GUIEvent.Caller == CloseButton)
                        {
                            if (Parent)
                            {
                                closeDialog();

                                return true;

                            }
                            else
                            {
                                remove();
                                return true;
                            }
                        }
                        else if (event.GUIEvent.Caller->getID() == TID_DLG_SAVE)
                        {
                            if(onSave())
                            {
                                closeDialog();
                                return true;
                            }
                        }
                        else if (event.GUIEvent.Caller->getID() == TID_DLG_CANCEL)
                        {
                            if(onCancel())
                            {
                                closeDialog();
                                return true;
                            }
                        }
                        else if (event.GUIEvent.Caller->getID() == TID_DLG_APPLY)
                        {
                            if(onApply())
                            {
                                closeDialog();
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

    void TGUIDialog::updateClientRect()
    {
        if (! DrawBackground )
        {
            ClientRect = core::rect<s32>(0,0, AbsoluteRect.getWidth(), AbsoluteRect.getHeight());
            return;
        }
        IGUISkin* skin = Environment->getSkin();
        skin->draw3DWindowBackground(this,
            DrawTitlebar,
            skin->getColor(IsActive ? EGDC_ACTIVE_BORDER : EGDC_INACTIVE_BORDER),
            AbsoluteRect, &AbsoluteClippingRect, &ClientRect);
        ClientRect -= AbsoluteRect.UpperLeftCorner;
    }



    //! draws the element and its children
    void TGUIDialog::draw()
    {
        if (!IsVisible)
            return;

        IGUISkin* skin = Environment->getSkin();

        updateClientRect();

        core::rect<s32> rect = AbsoluteRect;
        core::rect<s32> *cl = &AbsoluteClippingRect;

        // draw body fast
        rect = skin->draw3DWindowBackground(this, true, 
            skin->getColor(IsActive ? EGDC_ACTIVE_BORDER : EGDC_INACTIVE_BORDER),
            AbsoluteRect, &AbsoluteClippingRect);

        if (Text.size())
        {
            rect.UpperLeftCorner.X += skin->getSize(EGDS_TEXT_DISTANCE_X);
            rect.UpperLeftCorner.Y += skin->getSize(EGDS_TEXT_DISTANCE_Y);
            rect.LowerRightCorner.X -= skin->getSize(EGDS_WINDOW_BUTTON_WIDTH) + 5;

            IGUIFont* font = skin->getFont(EGDF_WINDOW);
            if (font)
                font->draw(Text.c_str(), rect, 
                skin->getColor(IsActive ? EGDC_ACTIVE_CAPTION:EGDC_INACTIVE_CAPTION), 
                false, true, cl);
        }

        IGUIElement::draw();
    }



    //-----------------------------------------------------------------------
    //                        T G r a p h i c s D l g
    //-----------------------------------------------------------------------
    TGraphicsDlg::TGraphicsDlg(IGUIEnvironment* environment, IGUIElement* parent,
        s32 id) : TGUIDialog(environment, parent,
        id, TRecti(0,0,500,400))
    {
        s32 leftX=30;

        setText(L"Graphic Settings");
        environment->addStaticText(L"Resolution:",TRecti(leftX,40,140,60),false,false,this,-1);
        IGUIListBox* lb = environment->addListBox(TRecti(leftX,70,160,200),this,-1,true);

        TApplication* app = getApplication();

        IrrlichtDevice* dev = app->getRenderer()->getDevice();

        //
        // screen resolution
        //
        IVideoModeList* ml = dev->getVideoModeList();
        s32 count = ml->getVideoModeCount();
        u32 lwidth=0, lheight=0;
        for(s32 i=0;i<count;i++)
        {
            char buf[100];

            dimension2d<u32> res = ml->getVideoModeResolution(i);
            if( (lwidth != res.Width) && (lheight != res.Height) )
            {
                TStrStream str;
                sprintf(buf,"%dx%d",res.Width, res.Height);
                stringw val = buf;
                lb->addItem(val.c_str());
                lwidth = res.Width;
                lheight = res.Height;
            }
        }

        environment->addCheckBox(false,TRecti(leftX,220,140,240),this,-1,L"Full Screen");
        environment->addCheckBox(false,TRecti(leftX,245,140,265),this,-1,L"Vertical Sync");
        environment->addComboBox(TRecti(leftX,270,140,290),this,-1);

    }

    TGraphicsDlg::~TGraphicsDlg()
    {
    }

}
