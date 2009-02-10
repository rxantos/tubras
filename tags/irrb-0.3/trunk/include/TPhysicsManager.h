//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
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
