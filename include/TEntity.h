//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TENTITY_H_
#define _TENTITY_H_

namespace Tubras
{
    class TEntity : public IReferenceCounted
    {
        friend class TEntityManager;

    private:
        TProperties         m_properties;
        TBehaviorMap        m_behaviors;
        TString             m_name;
        u32                 m_id;

    protected:
        TEntity(TString name, u32 id);
        virtual ~TEntity();

    public:
        TString getName() {return m_name;}
        u32 getID() {return m_id;}
        IBehavior* addBehavior(const TString type, TProperties& properties);
    };
}

#endif
