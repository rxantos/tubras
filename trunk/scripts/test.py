from Tubras import *

class TestApp(TApplication):
    def __init__(self,argv,argc):
        TApplication.__init__(self,argv,argc)


    def initialize(self):
        res = TApplication.initialize(self)

        self.setGUICursorVisible(False)

        self.loadModel('Cube.mesh')

        return res

def createApplication(argc, argv):
    return TestApp(argc,argv)
