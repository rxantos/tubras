from Tubras import *
import sys

#
# 'standard' (default) or 'stackless'
#
tseMode='standard'

class Test(TApplication):
    #
    # must call the inherited constructor
    #
    def __init__(self,appname):
        TApplication.__init__(self,appname)
        

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
        # set the background to familiar color
        # 
        self.setBGColor(TColor(100,101,140))

        #
        # we can pass either a function or a class method as a
        # target to accept events.
        #
        self.acceptEvent('quit',self.handleEscape)
        self.acceptEvent('key.down.f3',self.cycleRenderMode)
        
        #
        # add help text
        #
        self.addHelpText('     F3 - Cycle Wire')
        self.addHelpText(' Escape - quit')

        #
        # load something to look at
        #
        cube = self.loadModel('mdl/Cube.irrmesh')

        #
        # get/set position
        #
        cube.setPosition(TVector3(0.0,0.0,-50.0))
        # or
        cube.pos = TVector3(0.0,5.0,-80.0)

        position = cube.getPosition()
        # or
        position = cube.pos

        #
        # save off renderer
        #
        self.renderer = self.getRenderer()

        return res

    #
    # escape key event handler as a method
    #
    def handleEscape(self,event):
        print 'escapeKeyHit()'
        self.stopRunning()
        return 1

    #
    # cycle render modes
    #
    def cycleRenderMode(self,event):
        mode = self.renderer.getRenderMode()

        if mode == rmNormal:
            self.renderer.setRenderMode(rmWire)
        elif mode == rmWire:
            self.renderer.setRenderMode(rmPointCloud)
        else:
            self.renderer.setRenderMode(rmNormal)

        return 1

#
# this function is required by "tse" applications.
# return an instance of a derived TApplication class
#
def createTubrasApp():

    return Test('Test Tubras Python App')

