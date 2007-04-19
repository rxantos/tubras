from Tubras import *

theApp = 0

print 'dir(TApplication)', dir(TApplication)

#
# escape key event handler as a function
#
def stopRunning(event):
    print 'stopRunning()'
    getApplication().stopRunning()
    return 1

#
# function interval target.  this function will be repeatedly called 
# by the engine. "elapsedTime" will contain the amount of time (float
# seconds) that has elapsed since the interval was started.
#
def funcInterval(elapsedTime):
    print 'funcInterval:', elapsedTime
    return 1

class TestApp(TApplication):
    #
    # must call the inherited constructor
    #
    def __init__(self,argc,argv,appname):
        global theApp
        TApplication.__init__(self,argc,argv,appname)
        #
        # save off a reference to ourself for use by standalone
        # functions.  alternately "getApplication()" may be invoked
        # to retrieve the TApplication instance.
        #
        theApp = self

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
        # pull the Engine's config file - by default this is "tse.cfg".
        # we could optionally create our TConfigFile and call
        # .load('filename')...
        #
        config = self.getConfigFile()        
        s = config.getSetting('InitialState','Options')
        print 'InitialState=',s

        #
        # turn off the GUI cursor and set the background colour
        # to a dark red
        #
        self.setBackgroundColour(TColour(0.0,0.0,0.2))
        self.setGUICursorVisible(False)
        self.setGUIEnabled(False)

        #
        # setup a test function interval.  "funcInterval" will be repeatedly
        # called for a duration of 2 seconds.  After 2 seconds, the 
        # specified event will be fired.
        #
        self.funcInt = TFunctionInterval('testFuncInterval',2.0,funcInterval)
        self.funcInt.setDoneEvent('* Interval Done *')
        self.funcInt.start()

        #
        # enable default camera movement
        #
        self.setControllerEnabled("DefaultPlayerController",True)

        #
        # we can pass either a function or a class method as a
        # target to accept events.
        #
        self.acceptEvent('key.down.esc',stopRunning)
        self.acceptEvent('key.down.f1',self.toggleHelp)
        self.acceptEvent('key.down.f2',self.toggleWire)
        self.acceptEvent('key.down.f3',self.toggleDebug)

        #
        # add text to the "Help" box
        #
        self.addHelpText('wasd - Camera movement')
        self.addHelpText('ec   - Elevate camera')
        self.addHelpText('m    - Toggle mouse control')
        self.addHelpText('i    - Invert mouse')
        self.addHelpText('F1   - Toggle help')
        self.addHelpText('F2   - Toggle wire')
        self.addHelpText('F3   - Toggle debug')

        #
        # load a model (returns TModelNode)
        #
        self.cube = self.loadModel('Cube.mesh')
        self.ball = self.loadModel('Ball.mesh')

        #
        # set model position 
        #
        self.cube.setPos(0,0,-15)

        # or
        
        v = TVector3()
        v.x = 0.5
        v.y = 1.5
        v.z = -20.0        
        self.cube.setPos(v)

        # or TVector3 assignment
        self.cube.pos = TVector3(0,0,-10)
        # or tuple assignment
        self.cube.pos = (0,0,-20.5)

        self.ball.pos = (3,0,-15)
       
        #
        # attach a "rotator" to the cube node
        #
        self.xrot = TRotateController('cube::rotater::x',self.cube,100.0,TVector3.UNIT_X)
        self.yrot = TRotateController('cube::rotater::y',self.cube,200.0,TVector3.UNIT_Y)

        self.ball.yrot = TRotateController('ball::rotater::y',self.ball,200.0,TVector3.UNIT_Y)

        #
        # attach an "oscillator" to the cybe node
        self.osc = TOscillateController('cube::oscillator::y',self.cube,0.45,1.5,TVector3.UNIT_Y);
        self.ball.osc = TOscillateController('ball::oscillator::z',self.ball,1.0,2.5,TVector3.UNIT_Z);
        
        #
        # load a sound
        #
        self.sound = self.loadSound('ambient.ogg')
        self.sound.setLoop(True)
        self.sound.play()

        return res
    #
    # toggle wire frame
    #
    def toggleWire(self,event):
        self.toggleWireFrame()

    #
    # toggle debug overlay
    #
    def toggleDebug(self,event):
        self.toggleDebugOverlay()

    #
    # toggle help overlay
    #
    def toggleHelp(self,event):
        self.toggleHelpOverlay()

    #
    # escape key event handler as a method
    #
    def escapeKeyHit(self,event):
        print 'escapeKeyHit()'
        print 'type(event)', type(event)
        self.stopRunning()
        return 1

#
# this function is required by "tse" applications.
# return an instance of a derived TApplication class
#
def createTubrasApp(argc, argv):

    return TestApp(argc,argv,'Test Python')

