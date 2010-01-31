#-------------------------------------------------------------------------------
# This source file is part of the Blender to Irrlicht Exporter (irrb)
# url: http://code.google.com/p/tubras/wiki/irrb
#
# This is free and unencumbered software released into the public domain.
# For the full text of the Unlicense, see the file "docs/unlicense.html".
# Additional Unlicense information may be found at http://unlicense.org.
#-------------------------------------------------------------------------------
import traceback

class IGUIDebug:

    def __init__(self):
        self.cancelled = False


    def setStatus(self, status):
        print('GUI.setStatus()', status)

    def updateStatus(self, status):
        print('GUI.updateStatus()', status)

    def isExportCancelled(self):
        print('GUI.isExportCancelled()')
        return self.cancelled


class IGUIPanel(IGUIDebug):

    def __init__(self):
        pass


class IGUIFilePanel(IGUIDebug):

    def __init__(self):
        pass


def getGUIInterface(itype):
    if type == 'debug':
        return IGUIDebug()
    elif type == 'panel':
        return IGUIPanel()
    elif type == 'filepanel':
        return IGUIFilePanel()
    else:
        return IGUIDebug()

