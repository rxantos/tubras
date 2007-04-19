from Tubras import *

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
        #self.setControllerEnabled("DefaultPlayerController",True)

        #
        # we can pass either a function or a class method as a
        # target to accept events.
        #
        self.acceptEvent('key.down.esc',stopRunning)


        #
        # test particle system (Particle2)
        #
        self.createParticleGroup('test',10000)

#
# this function is required by "tse" applications.
# return an instance of a derived TApplication class
#
def createTubrasApp(argc, argv):

    return TestApp(argc,argv,'Test Python')

