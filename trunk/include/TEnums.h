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

    enum TCharacterControllerMode
    {
        ccmFirstPerson,
        ccmThirdPerson,
        ccmGod,
        ccmUnreal
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

    enum TPhysicsBodyType
    {
        btStatic,
        btDynamic,
        btKinematic
    };

    enum TPhysicsBodyShape
    {
        stBox,
        stPlane,
        stSphere,
        stCone,
        stCylinder,
        stConvexMesh,
        stConcaveMesh
    };

    enum TPhysicsDebugMode
    {
        PDM_NoDebug=0,
        PDM_DrawWireframe = 1,
        PDM_DrawAabb=2,
        PDM_DrawFeaturesText=4,
        PDM_DrawContactPoints=8,
        PDM_NoDeactivation=16,
        PDM_NoHelpText = 32,
        PDM_DrawText=64,
        PDM_ProfileTimings = 128,
        PDM_EnableSatComparison = 256,
        PDM_DisableBulletLCP = 512,
        PDM_EnableCCD = 1024,
        PDM_MAX_DEBUG_DRAW_MODE
    };

    enum TPhysicsMode
    {
        pmNone,
        pmCollisionMode,
        pmDynamicsMode,
    };

    enum TCollisionSystemType
    {
        cstIrrlicht,
        cstBullet
    };
}
#endif
