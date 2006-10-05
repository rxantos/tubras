#include "tubras.h"
#include "test.h"

TTestTheme::TTestTheme(string baseDir) : Tubras::TTheme(baseDir)
{


}

//-----------------------------------------------------------------------
//                             l o a d
//-----------------------------------------------------------------------
int TTestTheme::load()
{
    if(TTheme::load())
        return 1;

    return 0;
}

//-----------------------------------------------------------------------
//                            u n l o a d
//-----------------------------------------------------------------------
int TTestTheme::unload()
{
    if(TTheme::unload())
        return 1;

    return 0;
}

