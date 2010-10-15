//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _WALKTEST_H_
#define _WALKTEST_H_
#include "tubras.h"

using namespace Tubras;

// byte-align structures
#if defined(_MSC_VER) ||  defined(__BORLANDC__) || defined (__BCPLUSPLUS__) 
#	pragma pack( push, packing )
#	pragma pack( 1 )
#	define PACK_STRUCT
#elif defined( __GNUC__ )
#	define PACK_STRUCT	__attribute__((packed))
#else
#	define PACK_STRUCT
#endif

#define RT_ARCHIVE  1
#define RT_CONFIG   2
struct SigStruct
{
    u32     sig1;
    u32     offset;
    u32     count;
    u32     crc;
    u32     sig2;
} PACK_STRUCT;

struct DatStruct
{
    u32     sig;
    u32     type;
    char    id[256];
    u32     length;
    u32     crc;
} PACK_STRUCT;


#if defined(_MSC_VER) ||  defined(__BORLANDC__) || defined (__BCPLUSPLUS__) 
#	pragma pack( pop, packing )
#endif

#undef PACK_STRUCT

typedef struct 
{
    ISceneNode*     node;
    E_MATERIAL_TYPE orgType;
    u32             idx;
} LMInfo, *PLMInfo;

typedef struct
{
    ICameraSceneNode*   camera;
    f32                 width;
    f32                 height;
    f32                 jumpSpeed;
    f32                 stepHeight;
} CamCharInfo, *PCamCharInfo;

class TWalktest : public TApplication
{
protected:
    Tubras::TString                 m_sceneFileName;
    TArray<PCamCharInfo>            m_cameras;
    TArray<IBillboardSceneNode*>    m_lights;
    TArray<PLMInfo>                 m_lightMaps;
    bool                            m_lightsVisible;
    bool                            m_lightMapsVisible;
    bool                            m_useIrrlichtCollision;
    bool                            m_havePayload;
    io::IAttributes*                m_sceneAttributes;
    u32                             m_dbgSensorIndex;
public:
    TWalktest();
    ~TWalktest();
    int initialize();
    int toggleDebug(const TEvent* event);
    int toggleDebugLights(const TEvent* event);
    int toggleLightMaps(const TEvent* event);
    int togglePhysicsDebug(const TEvent* event);
    int toggleHelp(const TEvent* event);
    int toggleWire(const TEvent* event);
    int cycleDebug(const TEvent* event);
    int cycleCamera(const TEvent* event);
    int toggleGod(const TEvent* event);
    int captureScreen(const TEvent* event);
    int quit(const TEvent* event);
    int handleSensor(const TEvent* event);
    int initConfig();
    int postRenderInit();
    void testInterval(double T, void* userData);
    stringc getSceneFromManifest(stringc fileName);
    int checkPayload();

    void buildLightList(ISceneNode* node);
    void buildLMList(ISceneNode* node);

    PCamCharInfo getCamCharInfo(ICameraSceneNode* node);

    void createPhysicsObject(IMeshSceneNode* mnode, io::IAttributes* userData);

	void OnReadUserData(ISceneNode* forSceneNode, io::IAttributes* userData);

    int testTask(TTask* task);

    io::IAttributes* createUserData(ISceneNode* forSceneNode) {return 0;}

};
#endif

