//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TOBJECT_H_
#define _TOBJECT_H_

namespace Tubras
{
    class TObject : public IReferenceCounted
    {
        friend class TEntityManager;
    private:
        TProperties         m_properties;
        TString             m_name;
        u32                 m_id;

    protected:
        TObject(TString name);
        ~TObject();

    public:
        TString getName() {return m_name;}
        u32 getID() {return m_id;}
    };
}

#endif
