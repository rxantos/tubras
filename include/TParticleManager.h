//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TPARTICLEMANAGER_H_
#define _TPARTICLEMANAGER_H_

namespace Tubras
{
    typedef TMap<TString, TParticleNode*> TParticleNodeMap;
    typedef TParticleNodeMap::Iterator TParticleNodeMapItr;

    class TParticleManager : public Tubras::TSingleton<Tubras::TParticleManager>, public TDObject
    {
    protected:
        TParticleNodeMap        m_nodes;

    public:
        TParticleManager();
        virtual ~TParticleManager();
        static TParticleManager& getSingleton(void);
        static TParticleManager* getSingletonPtr(void);
        TParticleNode* createParticleNode(TString name,const size_t maxParticles, 
            TParticlePrimitive primitive=PP_BILLBOARD, ISceneNode* parent=0);
        TParticleNode* findNode(TString name);
        TParticleNode* removeParticleNode(TString name);
        void destroyParticleNode(TString name);
        int initialize();
        void step();

    };
}
#endif
