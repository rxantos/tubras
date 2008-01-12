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
#ifndef __TPHYSICSMANAGER_H_
#define __TPHYSICSMANAGER_H_

namespace Tubras
{
    enum TPhysicsMode
    {
        pmNone,
        pmCollisionMode,
        pmDynamicsMode,
    };

    class TPhysicsManager : public TSingleton<Tubras::TPhysicsManager>, public TObject
    {
    protected:
        TDynamicWorld*          m_world;
        TPhysicsMode            m_mode;
        TString					m_userDebugString;
        //TTextOverlay*           m_debugOverlay;
        //TTask*                  m_debugTask;
    protected:
        //virtual int showDebugInfo(TTask* task);

    public:
        TPhysicsManager();
        virtual ~TPhysicsManager();

        static TPhysicsManager& getSingleton(void);
        static TPhysicsManager* getSingletonPtr(void);

        int initialize();

        void setUserDebugString(const TString& value);
        void toggleDebugOverlay();
        void toggleDebug() {m_world->toggleDebug();}

        TDynamicWorld* getWorld() {return m_world;};
        void step(u32 delta) {m_world->step(delta);};

    };
}


#endif
