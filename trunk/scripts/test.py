from Tubras import *

print 'dir(TApplication)', dir(TApplication)

#
# escape key event handler as a function
#
def stopRunning(event):
    print 'stopRunning()'
    getApplication().stopRunning()
    return 1

class TestApp(TApplication):
    #
    # must call the inherited constructor
    #
    def __init__(self,argc,argv,appname):
        TApplication.__init__(self,argc,argv,appname)

    #
    # must call the inherited TApplication 'initialize' to start up
    # the sub-systems: renderer, physics, config, registry,
    # collision, etc.
    #
    def initialize(self):
        res = TApplication.initialize(self)
        if res:
            return res
        
        config = self.getConfigFile()
        s = config.getSetting('InitialState','Options')
        print 'InitialState=',s


        #
        # turn off the GUI cursor and set the background colour
        # to a dark red
        #
        self.setGUICursorVisible(False)
        self.setGUIEnabled(False)
        self.setBackgroundColour(TColour(0.2,0.0,0.0))

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
        # load a model
        #
        self.cube = self.loadModel('Cube.mesh')
        self.cube.setPos(0,0,-15)

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


def createApplication(argc, argv):

    return TestApp(argc,argv,'Test Python')

