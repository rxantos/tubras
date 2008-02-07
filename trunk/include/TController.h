//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
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
        u32                     m_startTime;
        bool                    m_enabled;
    public:
        u32                     m_elapsedTime;
        float                   m_deltaTime;
        u32                     m_lastTime;

    public:
        TController(const TString& controllerName,ISceneNode* node, TControllerFunction* function=NULL);
        virtual ~TController();

        TString getName() {return m_name;};

        virtual void setEnabled(bool value);
        virtual bool getEnabled() {return m_enabled;};

        virtual void start(u32 startTime) {}
        virtual void stop() {}

        virtual void setFunction(TControllerFunction* function) {m_function = function;};
        virtual TControllerFunction* getFunction() {return m_function;};

        void setNode(ISceneNode* node);
        ISceneNode* getNode();

        virtual void update(float value) {};
    };

}

#endif

