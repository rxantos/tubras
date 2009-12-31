#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ios>
#include "irrlicht.h"

// define one of the following
// #define USE_BULLET
// #define USE_IRRPHYSX
#define USE_IRR         // collision/triggers only - no dynamics.

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


int _initPhysicsLibrary();
void _addPhysicsObject(irr::scene::ISceneNode* node, irr::io::IAttributes* userData);
void _displayPhysicsDebug();
void _jump();
void _stepSimulation(irr::u32 deltaMS);
