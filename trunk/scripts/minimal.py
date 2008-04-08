from Tubras import *
import sys

#
# 'standard' (default) or 'stackless'
#
tseMode='standard'

class Minimal(TApplication):
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
        # set the background to familiar colour
        # 
        self.setBGColour(TColour(100,101,140))

        #
        # we can pass either a function or a class method as a
        # target to accept events.
        #
        self.acceptEvent('quit',self.handleEscape)

        #
        # load something to look at
        #
        cube = self.loadModel('data/mdl/Cube.irrbmesh')

        return res

    #
    # escape key event handler as a method
    #
    def handleEscape(self,event):
        print 'escapeKeyHit()'
        self.stopRunning()
        return 1

#
# this function is required by "tse" applications.
# return an instance of a derived TApplication class
#
def createTubrasApp():

    print 'len(sys.argv)', len(sys.argv)
    for arg in sys.argv:
        print 'arg: %s' % (arg)
            
    return Minimal('Minimal Tubras Python App')

