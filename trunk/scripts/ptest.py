from Tubras import *
#
# escape key event handler as a function
#
def stopRunning(event):
    print 'stopRunning()'
    getApplication().stopRunning()
    return 1

def captureScreen(event):
    print 'captureScreen()'
    getApplication().captureScreen()
    return 1


class TestApp(TApplication):
    #
    # must call the inherited constructor
    #
    def __init__(self,argc,argv,appname):
        global theApp
        TApplication.__init__(self,argc,argv,appname)

    #
    # must call the inherited TApplication 'initialize' to start up
    # the sub-systems: renderer, physics, config, registry,
    # collision, etc.
    #
    # note that "tse" calls "initialize" immediately after
    # "createTubrasApp".
    #
    def initialize(self):
        res = TApplication.initialize(self)
        if res:
            return res
        
        self.p1 = 0
        
        #
        # turn off the GUI 
        #
        self.setGUICursorVisible(False)
        self.setGUIEnabled(False)


        #
        # enable default camera movement
        #
        self.setControllerEnabled("DefaultPlayerController",True)

        #
        # we can pass either a function or a class method as a
        # target to accept events.
        #
        self.acceptEvent('key.down.esc',stopRunning)
        self.acceptEvent('key.down.sysrq',captureScreen)
        self.acceptEvent('key.down.p',self.test)
        self.acceptEvent('key.down.m',self.test2)

        #self.cube = self.loadModel('Cube.mesh')
        #self.cube.setPos(5,0,0)

        self.maxParticles = 5
        
        #
        # test particle system (Particle2)
        #
        # create a particle node maxParticles=19000
        #
        self.pnode = self.createParticleNode('test',19000)
        self.pnode.setTimeStep(1)
        self.pnode.setPointSize(10)
        #
        # use an ogre material script
        #
        #self.pnode.setMaterialName('ptest/circle')
        #
        # or, specify an image directly
        #
        self.pnode.setSpriteImage('star2.png')
        self.pnode.setPointSize(42)

        #self.osc = TOscillateController('pnode::oscillator::y',self.pnode,0.45,1.5,TVector3.UNIT_Y);
        #self.yrot = TRotateController('pnode::rotater::y',self.pnode,200.0,TVector3.UNIT_Y)
        
        #
        # set up initial particle states
        #
        self.pnode.setVelocity(TCylinderDomain(TVector3(0.0, 0.25, -0.01),TVector3(0.0, 0.27, -0.01), 0.021, 0.019))
        self.pnode.setColour(TLineDomain(TVector3(0.8, 0.9,1.0),TVector3(0.0, 0.0, 1.0)))
        
        #
        # create/add some particle actions
        #

        self.action1 = TSourceAction(5,TLineDomain(TVector3(0,0,0),TVector3(0,0.4,0)))
        self.pnode.addAction(self.action1)

        self.action2 = TGravityAction(TVector3(0,-0.01,0))
        self.pnode.addAction(self.action2)

        self.action3 = TBounceAction(-0.05, 0.35, 0, TDiscDomain(TVector3(0,0,0),TVector3(0,1,0),5))
        self.pnode.addAction(self.action3)
        
        self.action4 = TSinkAction(False,TPlaneDomain(TVector3(0,-3,0), TVector3(0,1,0)))
        self.pnode.addAction(self.action4)


        camera = self.getCamera('Camera::Default')
        camera.setPos(0,7.17,15.7)
        camera.lookAt(TVector3(0,-2.4,-0.9))


        self.toggleDebugOverlay()

    def test(self,event):
        print 'test() invoked:',self.pnode.getMaxParticles()
        if self.p1 == 0:
            self.action1.setRate(1)
            self.p1 = 1
            self.pnode.setMaterialName('ptest/circle')
        else:
            self.action1.setRate(120)            
            self.p1 = 0
            self.pnode.setMaterialName('star.png')
        return 1

    def test2(self,event):
        self.pnode.setMaxParticles(self.maxParticles)
        self.maxParticles += 5
        return 1

#
# this function is required by "tse" applications.
# return an instance of a derived TApplication class
#
def createTubrasApp(argc, argv):

    return TestApp(argc,argv,'Tubras Python Particles')

