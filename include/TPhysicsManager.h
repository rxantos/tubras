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

    class TPhysicsManager : public TDelegate
    {
        friend class TApplication;
    protected:
        TDynamicWorld*          m_world;
        TPhysicsMode            m_mode;
        TString					m_userDebugString;
        TPlayerController*      m_playerController;
    protected:
        TPhysicsManager();
        virtual ~TPhysicsManager();
        int initialize();

    public:

        void setUserDebugString(const TString& value);
        void toggleDebug() {m_world->toggleDebug();}

        void setPlayerController(TPlayerController* value) {m_playerController = value;}
        TPlayerController* getPlayerController() {return m_playerController;}

        TDynamicWorld* getWorld() {return m_world;};
        void update(const u32 delta);

    };
}


#endif
