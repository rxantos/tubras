//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TENUMS_H_
#define _TENUMS_H_

namespace Tubras
{
    enum TBodyType
    {
        btDynamic,
        btStatic,
        btKinematic
    };

    enum TRenderMode
    {
        rmNormal,
        rmWire,
        rmNormalWire,
        rmPointCloud
    };

    enum TBlendType 
    {
        btNoBlend,
        btEaseIn,
        btEaseOut,
        btEaseInOut,
        BTInvalid
    };

    enum TPlayerControllerStyle 
    {
        pcsFirstPerson,
        pcsThirdPerson,
        pcsUnrealEditor
    };


}
#endif
