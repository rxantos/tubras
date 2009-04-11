#include "CApplication.h"
#include "CGUISceneNode.h"

#include <assert.h>


//-----------------------------------------------------------------------------
//                                 S a n d b o x
//-----------------------------------------------------------------------------
class Sandbox : public CApplication
{
public:
    Sandbox() : CApplication("isandbox") {}

    //-------------------------------------------------------------------------
    //                          c r e a t e S c e n e
    //-------------------------------------------------------------------------
    virtual void createScene()
    {
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


        IMeshSceneNode* n = m_sceneManager->addCubeSceneNode();
        n->setMaterialTexture(0, m_videoDriver->getTexture("tex/t351sml.jpg"));
        n->setMaterialFlag(video::EMF_LIGHTING, false);
        selector = m_sceneManager->createTriangleSelector(n->getMesh(), n);
        getWorld()->addTriangleSelector(selector);
        //n->addAnimator(getCollisionResponse());

        if (!n)
        {
            scene::ISceneNodeAnimator* anim =
                m_sceneManager->createFlyCircleAnimator(core::vector3df(0,0,0), 30.0f, 0.001f);
            if (anim)
            {
                n->addAnimator(anim);
                anim->drop();
            }
        }
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

    app.setArgs(argc, argv);

    if(app.init())
        return -1;

    app.run();

    return 0;
}

