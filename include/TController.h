//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
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
    Controller class. Inspired by both the Ogre & Panda3D controller classes.

    Creating a controller automatically registers it with the Controller Manager.  The manager 
    automatically deletes registered controllers when the manager itself is destroyed.

    If you would like to remove a controller that is no longer needed:
    1. Invoke TControllerManager::remove()
    2. Delete the controller manually

    A controller must be "started" (start()) in order for it to be executed by the 
    controller manager.

    */

    class TController : public TDelegate
    {
        friend class TControllerManager;
    protected:
        TControllerManager*     m_manager;
        TString                 m_name;
        TString                 m_startedEvent;
        TString                 m_stoppedEvent;
        ISceneNode*             m_node;
        TControllerFunction*    m_function;
        bool                    m_active;
    public:
        u32                     m_startTime;
        u32                     m_elapsedTime;
        float                   m_deltaTime;
        u32                     m_lastTime;

    public:
        TController(const TString& controllerName, TControllerFunction* function=NULL, ISceneNode* node=0,
            const TString& startedEvent="", const TString& stoppedEvent="");
        virtual ~TController();

        TString getName() {return m_name;}

        virtual bool getActive() {return m_active;}

        virtual void start();
        virtual void stop();
        virtual void reset() {}

        virtual void setFunction(TControllerFunction* function) {m_function = function;}
        virtual TControllerFunction* getFunction() {return m_function;}

        void setNode(ISceneNode* node);
        ISceneNode* getNode();

        virtual void update(float value) {}
    };

}

#endif

