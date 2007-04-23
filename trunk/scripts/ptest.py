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
        self.acceptEvent("key.down.sysrq",captureScreen)

        #self.cube = self.loadModel('Cube.mesh')
        #self.cube.setPos(5,0,0)

        #
        # test particle system (Particle2)
        #
        # create a particle node maxParticles=19000
        #
        self.pnode = self.createParticleNode('test',19000)
        self.pnode.setTimeStep(1)

        #self.osc = TOscillateController('pnode::oscillator::y',self.pnode,0.45,1.5,TVector3.UNIT_Y);
        #self.yrot = TRotateController('pnode::rotater::y',self.pnode,200.0,TVector3.UNIT_X)
        
        #
        # set up initial particle states
        #
        self.pnode.setVelocity(TCylinderDomain(TVector3(0.0, 0.25, -0.01),TVector3(0.0, 0.27, -0.01), 0.021, 0.019))
        self.pnode.setColour(TLineDomain(TVector3(0.8, 0.9,
            1.0),TVector3(0.0, 0.0, 1.0)))
        
        #
        # create/add some particle actions
        #

        self.action1 = TSourceAction(120,TLineDomain(TVector3(0,0,0),TVector3(0,0.4,0)))
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

#
# this function is required by "tse" applications.
# return an instance of a derived TApplication class
#
def createTubrasApp(argc, argv):

    return TestApp(argc,argv,'Tubras Python Particles')

