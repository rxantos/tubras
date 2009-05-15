//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                     T P a r t i c l e M a n a g e r
    //-----------------------------------------------------------------------
    TParticleManager::TParticleManager() : TDelegate()
    {
    }

    //-----------------------------------------------------------------------
    //                    ~ T P a r t i c l e M a n a g e r
    //-----------------------------------------------------------------------
    TParticleManager::~TParticleManager()
    {
        TParticleNodeMapItr itr;
        while(m_nodes.size() > 0)
        {
            itr = m_nodes.getIterator();
            TParticleNode* node = itr->getValue();
            m_nodes.remove(itr->getKey());
            node->drop();
        }

        m_nodes.clear();
    }

    //-----------------------------------------------------------------------
    //                          i n i t i a l i z e 
    //-----------------------------------------------------------------------
    int TParticleManager::initialize()
    {
        int result=0;
        return result;
    }

    //-----------------------------------------------------------------------
    //                   c r e a t e P a r t i c l e N o d e
    //-----------------------------------------------------------------------
    TParticleNode* TParticleManager::createParticleNode(TString name,   
        const size_t maxParticles, TParticlePrimitive primitive, ISceneNode* parent)
    {
        TParticleNode* pg;
        if(!parent)
            parent = getApplication()->getRenderer()->getSceneManager()->getRootSceneNode();

        pg = new TParticleNode(parent, maxParticles, primitive);
        m_nodes[name] = pg;
        return pg;
    }

    //-----------------------------------------------------------------------
    //                           f i n d N o d e
    //-----------------------------------------------------------------------
    TParticleNode* TParticleManager::findNode(TString name)
    {
        TParticleNode* pg=0;

        return pg;
    }

    //-----------------------------------------------------------------------
    //                  r e m o v e P a r t i c l e N o d e
    //-----------------------------------------------------------------------
    TParticleNode* TParticleManager::removeParticleNode(TString name)
    {
        TParticleNode* pg=0;

        return pg;
    }

    //-----------------------------------------------------------------------
    //                 d e s t r o y P a r t i c l e N o d e
    //-----------------------------------------------------------------------
    void TParticleManager::destroyParticleNode(TString name)
    {

    }

    //-----------------------------------------------------------------------
    //                            u p d a t e
    //-----------------------------------------------------------------------
    void TParticleManager::update(const u32 deltaTime)
    {
        for ( TParticleNodeMapItr it = m_nodes.getIterator(); !it.atEnd(); it++)
        {
            TParticleNode*  node = it->getValue();
            node->step(deltaTime);
        }        
    }
}
