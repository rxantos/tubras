from Tubras import *

class TestApp(TApplication):
    def __init__(self,argv,argc):
        TApplication.__init__(self,argv,argc)

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

        '''
        print 'TestApp initialize() invoked'

        self.setGUICursorVisible(False)
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

    return TestApp(argc,argv)

