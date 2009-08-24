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
    enum TMessageDialogType
    {
        mdtError,
        mdtOK,
        mdtYesNo
    };

    enum TPhysicsBodyType
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

    enum TPlayerControllerMode
    {
        pcmFirstPerson,
        pcmThirdPerson,
        pcmGod,
        pcsUnreal
    };

    enum TParticlePrimitive
    {
        PP_POINT=0,
        PP_BILLBOARD,
        PP_POINTSPRITE
    };

    enum TPropertyType 
    {
        ptEmpty,
        ptBool,
        ptNumber,
        ptString,
        ptWideString,
        ptPointer,
        ptEntity
    };

    enum TEntityNotification
    {
        enBehaviorAdded,
        enBehaviorRemoved,
        enBehaviorUpdated
    };

    enum TInputMode
    {
        imDisabled = 0,         // input disabled
        imApp = 1,              // input sent to application
        imGUI = 2,              // input sent to registered gui environments
        imAll = 3               // input sent to both gui and app
    };
}
#endif
