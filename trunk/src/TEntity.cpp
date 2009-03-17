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
    //                            T E n t i t y 
    //-----------------------------------------------------------------------
    TEntity::TEntity(TString name, u32 id) : m_name(name), m_id(id)
    {
    }

    //-----------------------------------------------------------------------
    //                           ~ T E n t i t y 
    //-----------------------------------------------------------------------
    TEntity::~TEntity()
    {
    }

    //-----------------------------------------------------------------------
    //                         a d d B e h a v i o r
    //-----------------------------------------------------------------------
    IBehavior* TEntity::addBehavior(const TString type, TProperties& properties)
    {
        IBehavior* result = getApplication()->getEntityManager()->createBehavior(type, properties, this);

        if(result)
            m_behaviors[result->getName()] = result;

        return result;
    }
}
