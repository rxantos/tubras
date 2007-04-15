from Tubras import *

print 'dir(TApplication)', dir(TApplication)

class TestApp(TApplication):
    def __init__(self,argc,argv,appname):
        print 'TestApp.__init__()'
        TApplication.__init__(self,argc,argv,appname)

    #
    # must call the inherited 'initialize' to start up
    # the sub-systems: renderer, physics, config, registry,
    # collision, etc.
    #
    def initialize(self):
        print 'test.py TApplication.initialize()'
        res = TApplication.initialize(self)
        if res:
            return res
        
        config = self.getConfigFile()
        s = config.getSetting('InitialState','Options')
        print 'InitialState=',s

        self.setGUICursorVisible(False)

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


def createApplication(argc, argv):

    print 'type(argc)', type(argc)
    print 'type(argv)', type(argv)
    return TestApp(argc,argv,'Test Python')

