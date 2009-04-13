#include "CApplication.h"
#include "CGUISceneNode.h"

#include <assert.h>

#define GID_GUISCENENODE 200
#define GID_GRAVITY 201

//-----------------------------------------------------------------------------
//                                 S a n d b o x
//-----------------------------------------------------------------------------
class Sandbox : public CApplication
{
private:
    bool                m_guiNodeActivated;
    array<CGUISceneNode*> m_guiNodes;
    IGUIImage*          m_crossHair;

public:
    Sandbox() : CApplication("isandbox"),
        m_guiNodeActivated(false) {}

    virtual ~Sandbox()
    {
        for(u32 i=0;i<m_guiNodes.size(); i++)
            m_guiNodes[i]->drop();
    }

    //-----------------------------------------------------------------------
    //                            O n E v e n t
    //-----------------------------------------------------------------------
    bool OnEvent(const SEvent &  event)
    {
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
    //                          c r e a t e S c e n e
    //-------------------------------------------------------------------------
    virtual void createScene()
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

