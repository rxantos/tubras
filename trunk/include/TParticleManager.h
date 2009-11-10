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
    class TParticleNode : public IReferenceCounted // dummy class for now
    {
    };

    typedef TMap<TString, TParticleNode*> TParticleNodeMap;
    typedef TParticleNodeMap::Iterator TParticleNodeMapItr;

    class TParticleManager : public TDelegate
    {
        friend class TApplication;
    private:
        TParticleNodeMap        m_nodes;

    protected:
        TParticleManager();
        virtual ~TParticleManager();
        int initialize();

    public:
        TParticleNode* createParticleNode(TString name,const size_t maxParticles, 
            TParticlePrimitive primitive=PP_BILLBOARD, ISceneNode* parent=0);
        TParticleNode* findNode(TString name);
        TParticleNode* removeParticleNode(TString name);
        void destroyParticleNode(TString name);
        void update(const f32 deltaTime);

    };
}
#endif
