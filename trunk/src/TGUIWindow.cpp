//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{

    //-----------------------------------------------------------------------
    //                          T G U I W i n d o w
    //-----------------------------------------------------------------------
    TGUIWindow::TGUIWindow(IGUIEnvironment* environment, IGUIElement* parent, s32 id, 
        core::rect<s32> rectangle,bool modal,bool centered, bool draggable)
        : IGUIWindow(environment, parent, id, rectangle), Dragging(false),
        IsDraggable(draggable)
    {
#ifdef _DEBUG
        setDebugName("TGUIWindow");
#endif

        IGUISkin* skin = 0;
        if (environment)
            skin = environment->getSkin();

        IGUISpriteBank* sprites = 0;
        video::SColor color(255,255,255,255);

        s32 buttonw = 18;
        if (skin)
        {
            buttonw = skin->getSize(EGDS_WINDOW_BUTTON_WIDTH);
            sprites = skin->getSpriteBank();
            color = skin->getColor(EGDC_WINDOW_SYMBOL);
        }
        s32 posx = RelativeRect.getWidth() - buttonw - 18;

        CloseButton = getApplication()->getGUIFactory()->addButton(core::rect<s32>(posx, 5, posx + buttonw, 5 + buttonw), this, -1, 
            L"" );
        CloseButton->setSubElement(true);
        CloseButton->setTabStop(false);
        CloseButton->setAlignment(EGUIA_LOWERRIGHT, EGUIA_LOWERRIGHT, EGUIA_UPPERLEFT, EGUIA_UPPERLEFT);
        CloseButton->setType((EGUI_ELEMENT_TYPE)TGUI_BUTTON_CLOSE);
        /*
        if (sprites)
        {
            CloseButton->setSpriteBank(sprites);
            CloseButton->setSprite(EGBS_BUTTON_UP, skin->getIcon(EGDI_WINDOW_CLOSE), color);
            CloseButton->setSprite(EGBS_BUTTON_DOWN, skin->getIcon(EGDI_WINDOW_CLOSE), color);
        }
        */
        posx -= buttonw + 2;

        RestoreButton = Environment->addButton(core::rect<s32>(posx, 3, posx + buttonw, 3 + buttonw), this, -1, 
            L"", skin ? skin->getDefaultText(EGDT_WINDOW_RESTORE) : L"Restore" );
        RestoreButton->setVisible(false);
        RestoreButton->setSubElement(true);
        RestoreButton->setTabStop(false);
        RestoreButton->setAlignment(EGUIA_LOWERRIGHT, EGUIA_LOWERRIGHT, EGUIA_UPPERLEFT, EGUIA_UPPERLEFT);
        if (sprites)
        {
            RestoreButton->setSpriteBank(sprites);
            RestoreButton->setSprite(EGBS_BUTTON_UP, skin->getIcon(EGDI_WINDOW_RESTORE), color);
            RestoreButton->setSprite(EGBS_BUTTON_DOWN, skin->getIcon(EGDI_WINDOW_RESTORE), color);
        }
        posx -= buttonw + 2;

        MinButton = Environment->addButton(core::rect<s32>(posx, 3, posx + buttonw, 3 + buttonw), this, -1, 
            L"", skin ? skin->getDefaultText(EGDT_WINDOW_MINIMIZE) : L"Minimize" );
        MinButton->setVisible(false);
        MinButton->setSubElement(true);
        MinButton->setTabStop(false);
        MinButton->setAlignment(EGUIA_LOWERRIGHT, EGUIA_LOWERRIGHT, EGUIA_UPPERLEFT, EGUIA_UPPERLEFT);
        if (sprites)
        {
            MinButton->setSpriteBank(sprites);
            MinButton->setSprite(EGBS_BUTTON_UP, skin->getIcon(EGDI_WINDOW_MINIMIZE), color);
            MinButton->setSprite(EGBS_BUTTON_DOWN, skin->getIcon(EGDI_WINDOW_MINIMIZE), color);
        }

        MinButton->grab();
        RestoreButton->grab();
        CloseButton->grab();

        // this element is a tab group
        setTabGroup(true);
        setTabStop(true);
        setTabOrder(-1);
    }

    //-----------------------------------------------------------------------
    //                         ~ T G U I W i n d o w
    //-----------------------------------------------------------------------
    TGUIWindow::~TGUIWindow()
    {
        if (MinButton)
            MinButton->drop();

        if (RestoreButton)
            RestoreButton->drop();

        if (CloseButton)
            CloseButton->drop();
    }

    //! called if an event happened.
    bool TGUIWindow::OnEvent(const SEvent& event)
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
                    if ( Parent && ((event.GUIEvent.Caller == this) || isMyChild(event.GUIEvent.Caller)))
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
    void TGUIWindow::updateAbsolutePosition()
    {
        IGUIElement::updateAbsolutePosition();
    }


    //! draws the element and its children
    void TGUIWindow::draw()
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

}
