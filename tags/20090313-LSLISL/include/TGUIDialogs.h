//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TGUIDIALOGS_H_
#define _TGUIDIALOGS_H_

namespace Tubras
{
    #define TID_DLG_SAVE    1000
    #define TID_DLG_CANCEL  1001
    #define TID_DLG_APPLY   1002

    enum TDialogButtons 
    {
        dbApply     = 1,
        dbSave      = 1 << 2,
        dbCancel    = 1 << 3
    };
    //-----------------------------------------------------------------------
    //                          T G U I D i a l o g
    //-----------------------------------------------------------------------
    class TGUIDialog : public IGUIWindow
    {
    protected:
		core::position2d<s32> DragStart;

        IGUIButton* CloseButton;
        IGUIButton* MinButton;
        IGUIButton* RestoreButton;
        IGUIElement* ModalScreen;
        bool    Dragging;
        bool    Modal;
        bool    m_draggable;

    public:
        TGUIDialog(IGUIEnvironment* environment, IGUIElement* parent,
            s32 id, core::rect<s32> rectangle,TDialogButtons buttons=(TDialogButtons)(dbApply + dbSave + dbCancel),
            bool modal=false, bool centered=true, bool draggable=true);
        virtual ~TGUIDialog();

        //! called if an event happened.
        virtual bool OnEvent(const SEvent& event);

        //! update absolute position
        virtual void updateAbsolutePosition();

        //! draws the element and its children
        virtual void draw();

        //! Returns pointer to the close button
        virtual IGUIButton* getCloseButton() const {return 0;}

        //! Returns pointer to the minimize button
        virtual IGUIButton* getMinimizeButton() const {return 0;}

        //! Returns pointer to the maximize button
        virtual IGUIButton* getMaximizeButton() const {return 0;}

        virtual void closeDialog();

        virtual int onSave() const {return 0;}
        virtual int onApply() const {return 0;}
        virtual int onCancel() const {return 1;}

		//! Returns true if the window can be dragged with the mouse, false if not
        virtual bool isDraggable() const {return m_draggable;}

		//! Sets whether the window can be dragged by the mouse
        virtual void setDraggable(bool draggable) {m_draggable = draggable;}


    };

    //-----------------------------------------------------------------------
    //                        T G r a p h i c s D l g
    //-----------------------------------------------------------------------
    class TGraphicsDlg : public TGUIDialog
    {
    public:
        TGraphicsDlg(IGUIEnvironment* environment, IGUIElement* parent,
            s32 id);
        virtual ~TGraphicsDlg();
    };
}

#endif
