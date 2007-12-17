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
#ifndef _TCONTROLLERMANAGER_H_
#define _TCONTROLLERMANAGER_H_

namespace Tubras
{
    typedef TMap<TString, TController*> TControllerMap;
    typedef TMap<TString, TController*>::Iterator TControllerMapItr;
    /**
    TControllerManager Class.
    @remarks
    Controller Manager class.
    */
    class TControllerManager : public TSingleton<Tubras::TControllerManager>, public TObject
    {
    private:
        TControllerMap	    m_controllers;
        TControllerMap      m_activeControllers;
        TTimer*             m_clock;
    public:
        TControllerManager();
        virtual ~TControllerManager();

        static TControllerManager& getSingleton(void);
        static TControllerManager* getSingletonPtr(void);
        int initialize();
        void step();
        void setGlobalClock(TTimer* clock);

        int registerController(TController* controller);
        void setControllerEnabled(TString controllerName, bool value);
        void setNodeControllersEnabled(TString nodeName, bool value);
        TController* getController(TString controllerName);


        int start(TController* controller);
        int stop(TController* controller);

        int remove(TString controllerName);
        int remove(TController* controller);
        TController* get(TString controllerName) {return m_controllers[controllerName];};
    };
}

#endif