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
#ifndef _TCONTROLLER_H_
#define _TCONTROLLER_H_

namespace Tubras
{
    /**
    TController Class.
    @remarks
    Controller class.

    Creating a controller automatically registers it with the Controller Manager.  The manager 
    automatically deletes registered controllers when the manager itself is destroyed.

    If you would like to remove a controller that is no longer needed:
    1. Invoke TControllerManager::remove()
    2. Delete the controller manually

    */

    class TController : public TObject
    {
        friend class TControllerManager;
    protected:
        TControllerManager*     m_manager;
        TString                 m_name;
        ISceneNode*             m_node;
        TControllerFunction*    m_function;
        ULONG                   m_startTime;
        bool                    m_enabled;
    public:
        ULONG                   m_elapsedTime;
        float                   m_deltaTime;
        ULONG                   m_lastTime;

    public:
        TController(TString controllerName,ISceneNode* node, TControllerFunction* function=NULL);
        virtual ~TController();

        TString getName() {return m_name;};

        virtual void setEnabled(bool value);
        virtual bool getEnabled() {return m_enabled;};

        virtual void setFunction(TControllerFunction* function) {m_function = function;};
        virtual TControllerFunction* getFunction() {return m_function;};

        void setNode(TSceneNode* node);
        ISceneNode* getNode();

        virtual void update(float value) {};
    };

}

#endif