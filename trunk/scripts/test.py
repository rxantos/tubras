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

        self.setGUICursorVisible(False)

        #
        # we can pass either a function or a method
        #
        # self.acceptEvent('key.down.esc',self.escapeKeyHit);
        self.acceptEvent('key.down.esc',stopRunning);

        '''
        print 'TestApp initialize() invoked'

        self.model = self.loadModel('Cube.mesh')
        print 'type(model)', type(self.model)

        self.sound = self.loadSound('ambient.ogg')
        print 'type(sound)', type(self.sound)

        vec3 = TVector3()
        vec3.x = 2.5
        print 'type(vec3)', type(vec3)
        print 'vec3 valued (%f,%f,%f)' % (vec3.x,vec3.y,vec3.z)

        model.setPos(vec3)
        '''
        return res

    #
    # escape key event handler as a method
    #
    def escapeKeyHit(self,event):
        print 'escapeKeyHit()'
        print 'type(event', type(event)
        self.stopRunning()
        return 1


def createApplication(argc, argv):

    return TestApp(argc,argv,'Test Python')

