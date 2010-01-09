//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TCONTROLLERMANAGER_H_
#define _TCONTROLLERMANAGER_H_

namespace Tubras
{
    typedef TMap<TString, TController*> TControllerMap;
    typedef TControllerMap::Iterator TControllerMapItr;
    /**
    TControllerManager Class.
    @remarks
    Controller Manager class.
    */
    class TControllerManager : public TDelegate
    {
        friend class TApplication;
    private:
        TControllerMap	    m_controllers;
        TControllerMap      m_activeControllers;
        TStringVector       m_stoppedControllers;
        TTimer*             m_clock;
    protected:
        TControllerManager();
        virtual ~TControllerManager();
        int initialize();

    public:
        void update(const f32 deltaTime);
        void setGlobalClock(TTimer* clock);

        int registerController(TController* controller);
        void setNodeControllersEnabled(const TString& nodeName, const bool value);
        TController* getController(const TString& controllerName);


        int start(TController* controller);
        int stop(TController* controller);

        int remove(const TString& controllerName);
        int remove(TController* controller);
        TController* get(const TString& controllerName) {return m_controllers[controllerName];};
    };
}

#endif

