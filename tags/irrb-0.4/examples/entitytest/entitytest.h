//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _ENTITYTEST_H_
#define _ENTITYTEST_H_
#include "tubras.h"

using namespace Tubras;

class TEntityTest : public TApplication
{
protected:
    TSL*            m_tsl;
protected:
    void _createScene();
    int quit(const TEvent* event);

public:
    TEntityTest() {}
    ~TEntityTest() {}
    int initialize();

};

#endif
