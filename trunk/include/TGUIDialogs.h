//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TGUIDIALOGS_H_
#define _TGUIDIALOGS_H_

namespace Tubras
{
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

    public:
        TGUIDialog(IGUIEnvironment* environment, IGUIElement* parent,
            s32 id, core::rect<s32> rectangle,bool modal=false, bool centered=true);
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
