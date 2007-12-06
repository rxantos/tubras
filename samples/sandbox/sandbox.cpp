#include "sandbox.h"

//-----------------------------------------------------------------------
//                           T S a n d b o x
//-----------------------------------------------------------------------
TSandbox::TSandbox(int argc,char **argv) : TApplication(argc,argv,"sandbox")
{
}

//-----------------------------------------------------------------------
//                          ~ T S a n d b o x
//-----------------------------------------------------------------------
TSandbox::~TSandbox()
{
}

//-----------------------------------------------------------------------
//                           i n i t i a l i z e
//-----------------------------------------------------------------------
int TSandbox::initialize()
{
    if(TApplication::initialize())
        return 1;

    
    TEmptyNode* enode = (TEmptyNode *)addSceneNode("TEmptyNode",getRootSceneNode());  

    TPlaneNode* pnode = (TPlaneNode*)addSceneNode("TPlaneNode",getRootSceneNode());


    pnode->initialize(200.0,TVector3::UNIT_Y);
    pnode->setPosition(TVector3(0,-5,0));
    
    ITexture* tex = getTexture("data/tex/grid.tga");
    SMaterial& mat = pnode->getMaterial(0);
    mat.setTexture(0,tex);    
    mat.MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL;
    mat.setFlag(EMF_LIGHTING,false);

    //mat.setFlag(EMF_TRILINEAR_FILTER,true);
    //mat.setFlag(EMF_ANISOTROPIC_FILTER,true);

    mat.getTextureMatrix(0).setTextureScale(20.0,20.0);

    
    
    ISceneNode* node = getSceneManager()->addCubeSceneNode(10);
	node->setPosition(TVector3(0,-15,-25));
    node->getMaterial(0).setFlag(EMF_LIGHTING,false);
    

    /*
    IAnimatedMesh* mesh = getRenderer()->getSceneManager()->addArrowMesh("testArrow",
        SColor(255,255,0,0), SColor(255,255,255,0),16,256,10,8,1,3);
    node = getRenderer()->getSceneManager()->addMeshSceneNode(mesh->getMesh(0));
    node->getMaterial(0).setFlag(EMF_LIGHTING,false);
    node->getMaterial(1).setFlag(EMF_LIGHTING,false);
    */
    

    //getRenderer()->getSceneManager()->addCameraSceneNode(0, vector3df(0,20,-40), vector3df(0,5,0));

   
    scene::ICameraSceneNode* cam = getRenderer()->getSceneManager()->addCameraSceneNodeFPS(0, 100.0f, 100.0f);
	cam->setPosition(TVector3(0,5,100));
	cam->setTarget(TVector3(0,0,0));

    setCursorVisible(false);

    return 0;
}

//-----------------------------------------------------------------------
//                              m a i n
//-----------------------------------------------------------------------
#ifdef WIN32
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
{
    char    **argv=__argv;
    int     argc=__argc;
#else
extern "C" {
    int main(int argc, char **argv)
    {
#endif
        TSandbox app(argc,argv);

        if(!app.initialize())
            app.run();

        return 0;
    }