//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ios>
#include "irrlicht.h"

// define one of the following
#define USE_BULLET
// #define USE_IRRPHYSX
// #define USE_IRR         // collision/triggers only - no dynamics.

using namespace irr;
using namespace irr::io;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::gui;
using namespace video;

#define TRIGGER_ENTER       0xFFCE0001
#define TRIGGER_EXIT        0xFFCE0000

enum EBodyType {btStatic, btDynamic, btKinematic, btSoft};
enum EShapeType {stBox, stPlane, stSphere, stCone, stCylinder, stConvexMesh, stConcaveMesh};
struct PhysicsAttributes
{
    EBodyType       BodyType;
    EShapeType      Shapetype;
    f32             mass;
    f32             radius;
    f32             friction;
    f32             restitution;
    bool            visible;
    bool            ghost;
    bool            trigger;
};

void _setPhysicsAttributes(irr::io::IAttributes* userData, struct PhysicsAttributes& attr);
void _updateDebugText(u32 idx, core::stringc text);
void _addHelpText(core::stringc text);

// library specific functions
int _initPhysicsLibrary();
void _setGravity(f32 value);
void _addPhysicsObject(irr::scene::ISceneNode* node, irr::io::IAttributes* userData);
void _enablePhysicsDebug(bool value);
void _jump();
void _warp(vector3df pos);
void _stepSimulation(irr::u32 deltaMS);
bool _handleEvent(const SEvent& event);

// custom scene node class for drawing physics debug info
class CDebugNode : public scene::ISceneNode
{
private:
    S3DVertex*      m_vertices;
    u32             m_vcount;
    u32             m_vmax;

    u32*            m_indices;
    u32             m_icount;

    video::IVideoDriver* m_driver;
    core::aabbox3d<f32>  m_aabb;
    SMaterial       m_material;

public:

    CDebugNode(scene::ISceneManager* mgr) : ISceneNode(mgr->getRootSceneNode(), mgr),
        m_vertices(0), m_vcount(0), m_vmax(1000), m_indices(0), m_icount(0)
    {
        m_material.Wireframe = false;
        m_material.Lighting = false;
        m_material.DiffuseColor.set(255, 255, 255,255);
        m_material.AmbientColor.set(255, 255, 255,255);
        m_driver = mgr->getVideoDriver();

        m_vertices = (S3DVertex*)malloc(sizeof(S3DVertex)*m_vmax);
        m_indices = (u32*)malloc(sizeof(m_indices)*m_vmax);
        m_aabb.reset(0.f,0.f,0.f);
    }

    virtual ~CDebugNode() 
    {
        if(m_vertices)
            free(m_vertices);
        if(m_indices)
            free(m_indices);
    }

    void addLine(const S3DVertex& v1, const S3DVertex& v2)
    {
        if((m_vcount+2) >= m_vmax)
        {
            m_vmax += 1000;
            m_vertices = (S3DVertex*)realloc(m_vertices,sizeof(S3DVertex)*m_vmax);
            m_indices = (u32*)realloc(m_indices,sizeof(m_indices)*m_vmax);
        }

        m_vertices[m_vcount++] = v1;
        m_vertices[m_vcount++] = v2;
        m_indices[m_icount] = m_icount++;
        m_indices[m_icount] = m_icount++;

        m_aabb.addInternalPoint(v1.Pos);
        m_aabb.addInternalPoint(v2.Pos);

    }

    void reset()
    {
        m_vcount = 0;
        m_icount = 0;
        m_aabb.reset(0.f,0.f,0.f);
    }

    const core::aabbox3d<f32>& getBoundingBox() const {return m_aabb;} 
    virtual u32 getMaterialCount() const {return 1;}
    SMaterial& getMaterial(u32 i) {return m_material;}
    void OnRegisterSceneNode()
    {
        if (IsVisible)
            SceneManager->registerNodeForRendering(this);

        ISceneNode::OnRegisterSceneNode();        
    }

    void render()
    {
		m_driver->setMaterial(m_material);
		m_driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
        m_driver->drawVertexPrimitiveList(m_vertices,m_vcount,m_indices,
            m_icount/2,EVT_STANDARD,EPT_LINES,EIT_32BIT);
    }

};

