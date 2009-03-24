//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
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
    class TControllerManager : public TSingleton<Tubras::TControllerManager>, public TDelegate
    {
        friend class TApplication;
    private:
        TControllerMap	    m_controllers;
        TControllerMap      m_activeControllers;
        TTimer*             m_clock;
    protected:
        TControllerManager();
        virtual ~TControllerManager();

    public:
        static TControllerManager& getSingleton(void);
        static TControllerManager* getSingletonPtr(void);
        int initialize();
        void step();
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

