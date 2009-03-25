//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TGUIFACTORY_H_
#define _TGUIFACTORY_H_

namespace Tubras
{
    struct ElementInfo
    {
        TString name;
        u32     type;
    };

    enum TGUI_ELEMENT_TYPE
    {
        TGUI_BUTTON=(int)EGUIET_ELEMENT+1,
        TGUI_BUTTON_CLOSE,
        TGUI_SLIDER,
        TGUI_GRAPHICSDLG,
        TGUI_WINDOW,
        TGUI_SCREEN,
        TGUI_NULL
    };


    class TGUIFactory : public IGUIElementFactory
    {
    protected:
        IGUIEnvironment*            m_environment;

    public: 
        TGUIFactory(IGUIEnvironment* environment);
        ~TGUIFactory();
        int initialize();


        TGUIButton* addButton(const core::rect<s32>& rectangle,IGUIElement* parent=0, s32 id=-1, 
            const wchar_t* text=0, const wchar_t* tooltiptext = 0);

        TGUISlider* addSlider(bool horizontal, IGUIEnvironment* environment,
			IGUIElement* parent, s32 id, core::rect<s32> rectangle,
			bool noclip=false);

        TGUIWindow* addWindow(const core::rect<s32>& rectangle, bool modal = false, 
		    const wchar_t* text=0, IGUIElement* parent=0, s32 id=-1, bool centered=false);

        TGraphicsDlg* addGraphicsDlg(IGUIElement* parent, s32 id=-1);

        //! adds an element to the gui environment based on its type id
        /** \param type: Type of the element to add.
        \param parent: Parent scene node of the new element, can be null to add to the root.
        \return Returns pointer to the new element or null if not successful. */
        IGUIElement* addGUIElement(EGUI_ELEMENT_TYPE type, IGUIElement* parent=0);

        //! adds a GUI element to the GUI Environment based on its type name
        /** \param typeName: Type name of the element to add.
        \param parent: Parent scene node of the new element, can be null to add it to the root.
        \return Returns pointer to the new element or null if not successful. */
        IGUIElement* addGUIElement(const c8* typeName, IGUIElement* parent=0);

        //! returns amount of GUI element types this factory is able to create
        s32 getCreatableGUIElementTypeCount() const;

        //! returns type of a createable element type
        /** \param idx: Index of the element type in this factory. Must be a value between 0 and
        getCreatableGUIElementTypeCount() */
        EGUI_ELEMENT_TYPE getCreateableGUIElementType(s32 idx) const;

        //! returns type name of a createable GUI element type by index
        /** \param idx: Index of the type in this factory. Must be a value between 0 and
        getCreatableGUIElementTypeCount() */
        const c8* getCreateableGUIElementTypeName(s32 idx) const;

        //! returns type name of a createable GUI element
        /** \param type: Type of GUI element. 
        \return: Returns name of the type if this factory can create the type, otherwise 0. */
        const c8* getCreateableGUIElementTypeName(EGUI_ELEMENT_TYPE type) const;

        EGUI_ELEMENT_TYPE getTypeFromName(const c8* name) const;


        static const ElementInfo types[];
        static const u32 typeCount;

    };
}
#endif
