#-------------------------------------------------------------------------------
# This source file is part of the Blender to Irrlicht Exporter (irrb)
# url: http://code.google.com/p/tubras/wiki/irrb
#
# This is free and unencumbered software released into the public domain.
# For the full text of the Unlicense, see the file "docs/unlicense.html".
# Additional Unlicense information may be found at http://unlicense.org.
#-------------------------------------------------------------------------------


class IGUINull:

    def __init__(self):
        pass

    def setStatus(self, status):
        pass

    def updateStatus(self, status):
        pass

    def exportCancelled(self):
        pass


class IGUIPanel:

    def __init__(self):
        pass

    def setStatus(self, status):
        pass

    def updateStatus(self, status):
        pass

    def exportCancelled(self):
        pass

class IGUIFilePanel:

    def __init__(self):
        pass

    def setStatus(self, status):
        pass

    def updateStatus(self, status):
        pass

    def exportCancelled(self):
        pass



def getGUIInterface(itype):
    if type == 'null':
        return IGUINull()
    elif type == 'panel':
        return IGUIPanel()
    elif type == 'filepanel':
        return IGUIFilePanel()
    else:
        return IGUINull()

