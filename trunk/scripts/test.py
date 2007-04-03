from Tubras import *

class TestApp(TApplication):
    def __init__(self,argv,argc):
        TApplication.__init__(self,argv,argc)

    def initialize(self):
        res = TApplication.initialize(self)
        if res:
            return res

        self.setGUICursorVisible(False)
        model = self.loadModel('Cube.mesh')

        print 'type(model)', type(model)

        vec3 = TVector3()

        print 'type(vec3)', type(vec3)

        model.setPos(vec3)


        return res

def createApplication(argc, argv):
    return TestApp(argc,argv)
