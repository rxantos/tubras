from Tubras import *


class Minimal(TApplication):
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
    # note that "tse" calls "initialize" immediately after
    # "createTubrasApp".
    #
    def initialize(self):
        res = TApplication.initialize(self)
        if res:
            return res
        
        #
        # turn off the GUI cursor and set the background colour
        # to black
        #
        self.setBackgroundColour(TColour(0.0,0.0,0.0))
        self.setGUICursorVisible(False)
        self.setGUIEnabled(False)

        #
        # we can pass either a function or a class method as a
        # target to accept events.
        #
        self.acceptEvent('key.down.esc',self.handleEscape)
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
def createTubrasApp(argc, argv):

    return Minimal(argc,argv,'Minimal Tubras Python App')

