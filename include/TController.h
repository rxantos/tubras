//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
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
        TString                 m_startEvent;
        TString                 m_stopEvent;
        ISceneNode*             m_node;
        TControllerFunction*    m_function;
        bool                    m_active;

    public:
        TController(const TString& controllerName, TControllerFunction* function=NULL, ISceneNode* node=0,
            const TString& startEvent="", const TString& stopEvent="");
        virtual ~TController();

        TString& getName() {return m_name;}

        virtual bool getActive() {return m_active;}

        virtual void start();
        virtual void stop();
        virtual void reset() {}

        virtual void setFunction(TControllerFunction* function) {m_function = function;}
        virtual TControllerFunction* getFunction() {return m_function;}

        void setNode(ISceneNode* node);
        ISceneNode* getNode();

        void setStartEvent(TString value) {m_startEvent = value;}
        void setStopEvent(TString value) {m_stopEvent = value;}
        TString getStartEvent() {return m_startEvent;}
        TString getStopEvent() {return m_stopEvent;}

        virtual void update(float value) = 0;
    };

}

#endif

