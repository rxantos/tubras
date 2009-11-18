#include "CApplication.h"
#include "CGUISceneNode.h"

#include <assert.h>

#define GID_GUISCENENODE 200
#define GID_GRAVITY 201

//-----------------------------------------------------------------------------
//                                 S a n d b o x
//-----------------------------------------------------------------------------
class Sandbox : public CApplication, public ISceneUserDataSerializer
{
private:
    bool                m_guiNodeActivated;
    array<CGUISceneNode*> m_guiNodes;
    IGUIImage*          m_crossHair;
    CPhysicsManager     m_physicsManager;
#ifdef USE_BULLET
    btDiscreteDynamicsWorld* m_world;
#elif USE_IRRPHYSX
    IPhysxManager*      m_physxManager;
#else
    irr::scene::IMetaTriangleSelector* m_world;
    irr::scene::IMetaTriangleSelector* m_triggers;
    irr::scene::ISceneCollisionManager* m_irrCollisionManager;
    irr::scene::ISceneNodeAnimatorCollisionResponse* m_character;
#endif

public:
    Sandbox() : CApplication("isandbox"),
        m_guiNodeActivated(false) {}

    virtual ~Sandbox()
    {
        for(u32 i=0;i<m_guiNodes.size(); i++)
            m_guiNodes[i]->drop();
    }

    virtual io::IAttributes* createUserData(ISceneNode* forSceneNode) {return 0;}

    virtual void OnCreateNode(ISceneNode* node) {}

    //-----------------------------------------------------------------------
    //                            O n E v e n t
    //-----------------------------------------------------------------------
    bool OnEvent(const SEvent &  event)
    {
        if(m_physicsManager.processEvent(event))
            return true;

        // post event to all gui nodes we created.
        for(u32 i=0;i<m_guiNodes.size(); i++)
            m_guiNodes[i]->postEventFromUser(event);

        if(event.EventType == EET_USER_EVENT)
        {
            if(event.UserEvent.UserData1 == GID_GUISCENENODE)
            {
                SGUISceneNodeEvent* nevent = (SGUISceneNodeEvent*)event.UserEvent.UserData2;
                // if a gui node has been activiated, hide the crosshair image.
                if(nevent->EventType == EGNET_ACTIVATED)
                {
                    m_guiNodeActivated = nevent->UserData == 0 ? false : true;
                    /*
                    if(m_guiNodeActivated)
                    m_guiEnterSound->play();
                    else m_guiExitSound->play();
                    */
                    m_crossHair->setVisible(!m_guiNodeActivated);
                }
                return true;
            }
        }
        else if(event.EventType == EET_GUI_EVENT)
        {
            if(event.GUIEvent.Caller->getID() == GID_GRAVITY)
            {
                if(event.GUIEvent.EventType == EGET_CHECKBOX_CHANGED)
                {
                    /*
                    if(((IGUICheckBox*)event.GUIEvent.Caller)->isChecked())
                    getPhysicsManager()->getWorld()->setGravity(TVector3(0.f,-10.f,0.f));
                    else
                    getPhysicsManager()->getWorld()->setGravity(TVector3(0.f,0.f,0.f));
                    */
                    return true;
                }
            }
        }

        return CApplication::OnEvent(event);
    }

    //-------------------------------------------------------------------------
    //                           t e s t S c e n e 1
    //-------------------------------------------------------------------------
    void testScene1()
    {
        // floor plane
        SMaterial* mat = new SMaterial();
        ITexture* tex = getVideoDriver()->getTexture("tex/floor.png");
        mat->setTexture(0,tex);
        // causes static text background to disappear.
        mat->MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL;

        mat->setFlag(EMF_LIGHTING,false);
        mat->setFlag(EMF_BACK_FACE_CULLING, false);
        mat->getTextureMatrix(0).setTextureScale(50.0,50.0);

        dimension2d<f32> tileSize(50,50);
        dimension2d<u32> tileCount(6,6);
        IAnimatedMesh* pmesh = getSceneManager()->addHillPlaneMesh("testHillPlane"
            ,tileSize,tileCount,mat);
        IAnimatedMeshSceneNode* pnode;
        pnode = m_sceneManager->addAnimatedMeshSceneNode(pmesh);
        ITriangleSelector* selector = m_sceneManager->createTriangleSelector(pmesh, pnode);
        getWorld()->addTriangleSelector(selector);


        // rotating cube
        IMeshSceneNode* n = m_sceneManager->addCubeSceneNode();
        n->setMaterialTexture(0, m_videoDriver->getTexture("tex/t351sml.jpg"));
        n->setMaterialFlag(video::EMF_LIGHTING, false);
        selector = m_sceneManager->createTriangleSelector(n->getMesh(), n);
        getWorld()->addTriangleSelector(selector);
        n->setPosition(vector3df(0,5,0));
        if (n)
        {
            scene::ISceneNodeAnimator* anim =
                m_sceneManager->createRotationAnimator(core::vector3df(0,0.5f,0));
            if (anim)
            {
                n->addAnimator(anim);
                anim->drop();
            }
        }


        // gui crosshair
        tex = getVideoDriver()->getTexture("tex/sandbox/crosshair.png");
        s32 x,y;
        dimension2d<u32> size = getVideoDriver()->getCurrentRenderTargetSize();
        x = (size.Width/2) - 64;
        y = (size.Height/2) - 64;
        m_crossHair = getGUIEnvironment()->addImage(tex,position2d<s32>(x,y));

        // gui scene node
        CGUISceneNode* guiNode = new CGUISceneNode(getSceneManager()->getRootSceneNode(), getSceneManager(), 
            GID_GUISCENENODE, 
            "tex/altcursor.png",
            GSNAM_3D,
            this,
            10.f,               // activation distance
            SColor(255,200,200,200),
            dimension2du(512,512),
            vector2df(6,6),     // size
            vector3df(0,3,-10),   // position
            vector3df(0,0,0));  // rotation

        //m_guiNode->setScale(TVector3(3,1,1));
        //m_guiNode->setRotation(vector3df(0,0,0));
        //m_guiNode->setPosition(vector3df(0,0,0));

        guiNode->addStaticText(L"Transparent Control:", rect<s32>(5,20,200,40), true);

        //m_guiNodeRot = new Tubras::TRotateController("guinode::rotatory",m_guiNode,
        //    45.f,vector3df);




        IGUIScrollBar* bar = guiNode->addScrollBar(true, rect<s32>(210, 20, 410, 40));
        bar->setMin(0);
        bar->setMax(255);

        guiNode->addButton(rect<s32>(5, 50, 98, 70),0,777,L"Test Button");
        guiNode->addButton(rect<s32>(102, 50, 200, 70),0,-1,L"Test Button 2");
        guiNode->addCheckBox(true,rect<s32>(5,80,200,100),0,GID_GRAVITY,L"Gravity Enabled");

        IGUIComboBox* combo = guiNode->addComboBox(rect<s32>(5,120,200,140));
        combo->addItem(L"Test Item 1");
        combo->addItem(L"Test Item 2");
        combo->addItem(L"Test Item 3");
        combo->setSelected(1);

        IGUIListBox* lb = guiNode->addListBox(rect<s32>(5,160,200,300),0,-1,true);
        lb->addItem(L"lb item 1");
        lb->addItem(L"lb item 2");
        lb->addItem(L"lb item 3");
        lb->addItem(L"lb item 4");
        lb->addItem(L"lb item 5");
        lb->addItem(L"lb item 6");
        lb->addItem(L"lb item 7");
        lb->addItem(L"lb item 8");
        lb->addItem(L"lb item 9");

        IImage* image = getVideoDriver()->createImageFromFile("tex/t351sml.jpg");
        ITexture* texture = getVideoDriver()->addTexture("tex/t351sml.jpg", image);    
        guiNode->addImage(texture, vector2d<s32>(210, 60));
        guiNode->addImage(texture, vector2d<s32>(210+135, 60));

        m_guiNodes.push_back(guiNode);
    }


    //-----------------------------------------------------------------------
    //                      O n R e a d U s e r D a t a
    //-----------------------------------------------------------------------
    void OnReadUserData(ISceneNode* forSceneNode, io::IAttributes* userData)
    {
        stringc sname = forSceneNode->getName();
        static bool physicsEnabled = false;

        // save the root (scene) attributes.
        if(sname == "root")
        {
            physicsEnabled = userData->getAttributeAsBool("Physics.Enabled");
            //
            // turn gravity on
            //
            if(physicsEnabled)
            {
                f32 gravity=-9.8f;
                if(userData->existsAttribute("Gravity"))
                    gravity = userData->getAttributeAsFloat("Gravity");
                m_physicsManager.setGravity(gravity);
            }

            return;
        }

        ESCENE_NODE_TYPE type = forSceneNode->getType();
        if(type == ESNT_MESH)
        {
            IMeshSceneNode* mnode = reinterpret_cast<IMeshSceneNode*>(forSceneNode);
            if(physicsEnabled)
            {
                m_physicsManager.addPhysicsObject(mnode, userData);
            }

            if(mnode && userData->existsAttribute("HWMappingHint") &&
                !userData->getAttributeAsBool("Physics.Ghost"))
            {
                E_HARDWARE_MAPPING  mapping=EHM_NEVER;
                E_BUFFER_TYPE buffertype=EBT_NONE;

                IMesh* mesh = mnode->getMesh();

                stringc smapping = userData->getAttributeAsString("HWMappingHint");
                if(smapping == "static")
                    mapping = EHM_STATIC;
                else if(smapping == "dynamic")
                    mapping = EHM_DYNAMIC;
                else if(smapping == "stream")
                    mapping = EHM_STREAM;

                stringc sbuffertype = userData->getAttributeAsString("HWMappingBufferType");
                if(sbuffertype == "vertex")
                    buffertype = EBT_VERTEX;
                else if(sbuffertype == "index")
                    buffertype = EBT_INDEX;
                else if(sbuffertype == "vertexindex")
                    buffertype = EBT_VERTEX_AND_INDEX;

                mesh->setHardwareMappingHint(mapping, buffertype);
            }
        }
        else if(type == ESNT_CAMERA)
        {
            /*
            PCamCharInfo    pci = new CamCharInfo;
            pci->camera = reinterpret_cast<ICameraSceneNode*>(forSceneNode);
            pci->width = getConfig()->getFloat("physics.characterWidth", 1.f);
            pci->height = getConfig()->getFloat("physics.characterHeight", 2.f);
            pci->stepHeight = getConfig()->getFloat("physics.characterStepHeight", 0.35f);
            pci->jumpSpeed = getConfig()->getFloat("physics.characterJumpSpeed", 0.3f);

            if(userData->existsAttribute("Character.Width"))
                pci->width = userData->getAttributeAsFloat("Character.Width");
            if(userData->existsAttribute("Character.Height"))
                pci->height = userData->getAttributeAsFloat("Character.Height");
            if(userData->existsAttribute("Character.JumpSpeed"))
                pci->jumpSpeed = userData->getAttributeAsFloat("Character.JumpSpeed");
            if(userData->existsAttribute("Character.StepHeight"))
                pci->stepHeight = userData->getAttributeAsFloat("Character.StepHeight");
            m_cameras.push_back(pci);
            */

        }
    }


    //-------------------------------------------------------------------------
    //                           t e s t P h y s i c s
    //-------------------------------------------------------------------------
    void testPhysics()
    {

        stringc sceneDirectory, saveDir;
        irr::io::path sceneFileName;

        // physics library initialization
#ifdef USE_BULLET
        btVector3 worldAabbMin(-1000,-1000,-1000);
        btVector3 worldAabbMax(1000,1000,1000);

        btDefaultCollisionConfiguration* collisionConfig = new btDefaultCollisionConfiguration();
        btCollisionDispatcher* dispatcher = new	btCollisionDispatcher(collisionConfig);
        btAxisSweep3* broadPhase = new btAxisSweep3(worldAabbMin,worldAabbMax);
        btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

        m_bulletWorld = new btDiscreteDynamicsWorld(dispatcher,broadPhase,solver,collisionConfig);

#elif USE_PHYSX
	    SSceneDesc sceneDesc;
	    m_physxManager = createPhysxManager(getDevice(), sceneDesc);

#else // Irrlicht - (only performs collision response)
        m_irrCollisionManager = getSceneManager()->getSceneCollisionManager();

        m_world = getSceneManager()->createMetaTriangleSelector();
        m_triggers = getSceneManager()->createMetaTriangleSelector();
        m_character = getSceneManager()->createCollisionResponseAnimator(m_world, 0);

        // set default "character" size
        m_character->setEllipsoidRadius(vector3df(1.f, 2.f, 1.f));
        m_character->setGravity(vector3df(0.f, -9.8f, 0.f));

        m_physicsManager.setIrrlichtVars(getSceneManager(), getDevice()->getTimer(),
            m_irrCollisionManager, m_world, m_triggers, m_character);
#endif

        // load a scene with collision/physics data

        if(m_argc < 2)
        {
            printf("Error: Scene file not specified as a parameter\n");
            return;
        }

        sceneFileName = m_argv[1];   
        sceneDirectory = getFileSystem()->getFileDir(sceneFileName);

        saveDir = getFileSystem()->getWorkingDirectory();
        getFileSystem()->changeWorkingDirectoryTo(sceneDirectory);

        getSceneManager()->loadScene(sceneFileName.c_str(), this);

        getFileSystem()->changeWorkingDirectoryTo(saveDir);
    }

    //-------------------------------------------------------------------------
    //                           c r e a t e S c e n e
    //-------------------------------------------------------------------------
    // invoked by CApplication::initialize() 
    virtual void createScene()
    {
        // testScene1();

        testPhysics();

    }

    //-------------------------------------------------------------------------
    //                           p r e R e n d e r
    //-------------------------------------------------------------------------
    // invoked by CApplication "run" loop for every frame.
    virtual void preRender(u32 delta)
    {
        m_physicsManager.stepSimulation(delta);
    }

};

//-----------------------------------------------------------------------------
//                                 m a i n
//-----------------------------------------------------------------------------
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib") 
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup") 
#endif
int main(int argc, const char* argv[])
{

    Sandbox app;

    printf("app.setArgs\n");
    app.setArgs(argc, argv);

    if(app.init())
    {
        app.logMessage("isandbox.init() returned non-zero value.");
        return -1;
    }

    app.logMessage("entering run()");
    app.run();
    app.logMessage("exiting run()");

    return 0;
}

