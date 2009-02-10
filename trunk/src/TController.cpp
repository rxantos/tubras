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
    //                        T C o n t r o l l e r
    //-----------------------------------------------------------------------
    TController::TController(const TString& controllerName,ISceneNode* node,TControllerFunction* function) 
        : TObject()
    {
        m_name = controllerName;        
        m_node = node;
        m_function = function;
        m_startTime = 0;
        m_lastTime = 0;
        m_manager = TControllerManager::getSingletonPtr();
        if(!m_function)
            m_function = new TPassThroughControllerFunction();
        m_enabled = true;
        m_manager->registerController(this);
    }

    //-----------------------------------------------------------------------
    //                       ~ T C o n t r o l l e r
    //-----------------------------------------------------------------------
    TController::~TController()
    {
        if(m_function)
            delete m_function;

    }

    //-----------------------------------------------------------------------
    //                         s e t E n a b l e d
    //-----------------------------------------------------------------------
    void TController::setEnabled(bool value)
    {
        m_enabled = value;
    }

    //-----------------------------------------------------------------------
    //                           s e t N o d e
    //-----------------------------------------------------------------------
    void TController::setNode(ISceneNode* node)
    {
        m_node = node;
    }

    //-----------------------------------------------------------------------
    //                           g e t N o d e
    //-----------------------------------------------------------------------
    ISceneNode* TController::getNode() 
    {
        return m_node;
    }
}

