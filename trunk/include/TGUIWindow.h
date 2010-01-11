//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TGUIWINDOW_H_
#define _TGUIWINDOW_H_

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                          T G U I W i n d o w
    //-----------------------------------------------------------------------
    class TGUIWindow : public IGUIWindow
    {
    protected:
		core::position2d<s32> DragStart;
		core::rect<s32> ClientRect;

        TGUIButton* CloseButton;
        IGUIButton* MinButton;
        IGUIButton* RestoreButton;
        IGUIElement* ModalScreen;
        bool    Dragging, IsDraggable;
        bool    DrawBackground;
        bool    DrawTitlebar;
        bool    Modal;

		void updateClientRect();

    public:
        TGUIWindow(IGUIEnvironment* environment, IGUIElement* parent,
            s32 id, core::rect<s32> rectangle,
            bool modal=false, bool centered=true, bool draggable=true);
        virtual ~TGUIWindow();

        //! called to determine if the window can close
        virtual bool canClose() {return true;}

        //! called if an event happened.
        virtual bool OnEvent(const SEvent& event);

        //! update absolute position
        virtual void updateAbsolutePosition();

        //! draws the element and its children
        virtual void draw();

        //! Returns pointer to the close button
        virtual IGUIButton* getCloseButton() const {return CloseButton;}

        //! Returns pointer to the minimize button
        virtual IGUIButton* getMinimizeButton() const {return MinButton;}

        //! Returns pointer to the maximize button
        virtual IGUIButton* getMaximizeButton() const {return RestoreButton;}

		//! Returns true if the window can be dragged with the mouse, false if not
        virtual bool isDraggable() const {return IsDraggable;}

		//! Sets whether the window can be dragged by the mouse
        virtual void setDraggable(bool draggable) {IsDraggable = draggable;}

        //! Set if the window background will be drawn
        virtual void setDrawBackground(bool draw) {DrawBackground = draw;}

        //! Get if the window background will be drawn
        virtual bool getDrawBackground() const {return DrawBackground;}

        //! Set if the window titlebar will be drawn
        //! Note: If the background is not drawn, then the titlebar is automatically also not drawn
        virtual void setDrawTitlebar(bool draw) {DrawTitlebar = draw;}

        //! Get if the window titlebar will be drawn
        virtual bool getDrawTitlebar() const {return DrawTitlebar;}

		//! Returns the rectangle of the drawable area (without border and without titlebar)
        virtual core::rect<s32> getClientRect() const {return ClientRect;}


    };

}

#endif
