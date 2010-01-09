//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
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
