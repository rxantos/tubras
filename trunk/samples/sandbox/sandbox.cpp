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


    pnode->initialize(300.0,TVector3::UNIT_Y);
    pnode->setPosition(TVector3(0,-5,0));
    SMaterial& mat = pnode->getMaterial(0);
    ITexture* tex = getTexture("data/tex/grid.tga");
    mat.setTexture(0,tex);    
    mat.MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL;
    mat.setFlag(EMF_LIGHTING,false);
    mat.getTextureMatrix(0).setTextureScale(20.0,20.0);

    
    
    ISceneNode* node = getSceneManager()->addCubeSceneNode(10);
	node->setPosition(TVector3(0,-15,-25));
    node->getMaterial(0).setFlag(EMF_LIGHTING,false);
    new TRotateController("testRot",node,180.0);
    new TOscillateController("testOsc",node,1.0,20.0);
    
    IAnimatedMesh* mesh = getSceneManager()->addArrowMesh("testArrow",
        SColor(255,255,0,0), SColor(255,255,255,0),16,256,10,8,1,3);
    node = getSceneManager()->addMeshSceneNode(mesh->getMesh(0));
    node->getMaterial(0).setFlag(EMF_LIGHTING,false);
    node->getMaterial(1).setFlag(EMF_LIGHTING,false);

    new TRotateController("testRot2",node,250.0,TVector3::UNIT_Z);
    new TOscillateController("testOsc2",node,1.0,10.0,TVector3::UNIT_Z);    

    TSound* sound = loadSound("data/snd/ambient.ogg");
    sound->setLoop(true);
    //sound->play();

    //setCursorVisible(false);
    
  

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