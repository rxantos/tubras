//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to 
// deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
// sell copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                        T C o n t r o l l e r
    //-----------------------------------------------------------------------
    TController::TController(TString controllerName,ISceneNode* node,TControllerFunction* function) 
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
    void TController::setNode(TSceneNode* node)
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