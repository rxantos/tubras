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
    
    const ElementInfo TGUIFactory::types[]= {
        {"TGUIButton", TGUI_BUTTON},
        {"TGUISlider", TGUI_SLIDER},
        {"TGraphicsDlg", TGUI_GRAPHICSDLG},
        {"TGUIWindow", TGUI_WINDOW},
        {"TGUIScreen", TGUI_SCREEN},
        {"TGUIImage", TGUI_IMAGE},
        {"TGUINULL",0}
    };

    const u32 TGUIFactory::typeCount=4;

    //-----------------------------------------------------------------------
    //                        T G U I F a c t o r y
    //-----------------------------------------------------------------------
    TGUIFactory::TGUIFactory(IGUIEnvironment* environment) : IGUIElementFactory(),
        m_environment(environment)
    {
    }

    //-----------------------------------------------------------------------
    //                       ~ T G U I F a c t o r y
    //-----------------------------------------------------------------------
    TGUIFactory::~TGUIFactory()
    {
    }

    //-----------------------------------------------------------------------
    //                         i n i t i a l i z e
    //-----------------------------------------------------------------------
    int TGUIFactory::initialize()
    {
        int result = 0;
        getApplication()->getGUIManager()->registerGUIElementFactory(this);

        return result;
    }

    //-----------------------------------------------------------------------
    //                           a d d B u t t o n
    //-----------------------------------------------------------------------
    TGUIButton* TGUIFactory::addButton(const core::rect<s32>& rectangle,
        IGUIElement* parent, s32 id, const wchar_t* text, 
        const wchar_t* tooltiptext)
    {
        TGUIButton* result=0;

        result = new TGUIButton(getApplication()->getGUIManager(),parent,id,rectangle);
        result->setText(text);
        result->setToolTipText(tooltiptext);
        result->drop();
        return result;
    }

    //-----------------------------------------------------------------------
    //                           a d d I m a g e
    //-----------------------------------------------------------------------
    TGUIImage* TGUIFactory::addImage(const core::rect<s32>& rectangle, 
        IGUIElement* parent, s32 id)
    {
        TGUIImage* result;
        IGUIEnvironment* env = getApplication()->getGUIManager();
        result = new TGUIImage(env, parent ? parent : env->getRootGUIElement(), id, rectangle);
        result->drop();
        return result;
    }

    //-----------------------------------------------------------------------
    //                            a d d S l i d e r
    //-----------------------------------------------------------------------
    TGUISlider* TGUIFactory::addSlider(bool horizontal, IGUIEnvironment* environment,
			IGUIElement* parent, s32 id, core::rect<s32> rectangle,
			bool noclip)
    {
        TGUISlider* result=0;

        return result;
    }

    //-----------------------------------------------------------------------
    //                       a d d G r a p h i c s D l g
    //-----------------------------------------------------------------------
    TGraphicsDlg* TGUIFactory::addGraphicsDlg(IGUIElement* parent, s32 id)
    {
        TGraphicsDlg* result=0;

        result = new TGraphicsDlg(getApplication()->getGUIManager(),parent,id);

        result->drop();

        return result;
    }

    //-----------------------------------------------------------------------
    //                           a d d W i n d o w
    //-----------------------------------------------------------------------
    TGUIWindow* TGUIFactory::addWindow(const core::rect<s32>& rectangle, bool modal, 
		    const wchar_t* text, IGUIElement* parent, s32 id, bool centered)
    {
        TGUIWindow* result=0;
        result = new TGUIWindow(getApplication()->getGUIManager(),parent,id,rectangle,modal,centered);
        result->setText(text);
        result->drop();
        return result;
    }


    //-----------------------------------------------------------------------
    //                       a d d G U I E l e m e n t
    //-----------------------------------------------------------------------
    IGUIElement* TGUIFactory::addGUIElement(EGUI_ELEMENT_TYPE type, IGUIElement* parent)
    {
        IGUIElement* result=0;

        switch(type)
        {
        case TGUI_BUTTON:
            {
            TGUIButton* b = new TGUIButton(m_environment,parent,-1,TRecti(0,0,100,80));
            b->drop();
            result = b;
            }
            break;
        default:
            break;
        }

        return result;
    }

    //-----------------------------------------------------------------------
    //                         a d d G U I E l e m e n t
    //-----------------------------------------------------------------------
    IGUIElement* TGUIFactory::addGUIElement(const c8* typeName, IGUIElement* parent)
    {
        IGUIElement* result=0;

        result = addGUIElement(getTypeFromName(typeName),parent);

        return result;
    }

    //-----------------------------------------------------------------------
    //     g e t C r e a t a b l e G U I E l e m e n t T y p e C o u n t
    //-----------------------------------------------------------------------
    s32 TGUIFactory::getCreatableGUIElementTypeCount() const
    {
        return typeCount;
    }

    //-----------------------------------------------------------------------
    //           g e t C r e a t a b l e G U I E l e m e n t T y p e
    //-----------------------------------------------------------------------
    EGUI_ELEMENT_TYPE TGUIFactory::getCreateableGUIElementType(s32 idx) const
    {
        EGUI_ELEMENT_TYPE result=EGUIET_ELEMENT;

        if( (idx>=0) && (idx<<typeCount))
            result = (EGUI_ELEMENT_TYPE)types[idx].type;

        return result;
    }

    //-----------------------------------------------------------------------
    //       g e t C r e a t a b l e G U I E l e m e n t T y p e N a m e
    //-----------------------------------------------------------------------
    const c8* TGUIFactory::getCreateableGUIElementTypeName(s32 idx) const
    {
        const c8* result=0;
        if( (idx>=0) && (idx<<typeCount))
            result = types[idx].name.c_str();
        return result;
    }

    //-----------------------------------------------------------------------
    //       g e t C r e a t a b l e G U I E l e m e n t T y p e N a m e
    //-----------------------------------------------------------------------
    const c8* TGUIFactory::getCreateableGUIElementTypeName(EGUI_ELEMENT_TYPE type) const
    {
        const c8* result=0;

        for(u32 i=0;i<typeCount;i++)
        {
            if(types[i].type == (u32)type)
                return types[i].name.c_str();
        }

        return result;
    }

    //-----------------------------------------------------------------------
    //                     g e t T y p e F r o m N a m e
    //-----------------------------------------------------------------------
    EGUI_ELEMENT_TYPE TGUIFactory::getTypeFromName(const c8* name) const
    {
        for ( u32 i=0; GUIElementTypeNames[i]; ++i)
            if (!strcmp(name, types[i].name.c_str()) )
                return (EGUI_ELEMENT_TYPE)types[i].type;

        return EGUIET_ELEMENT;
    }
}
