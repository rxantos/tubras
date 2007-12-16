import Blender
from Blender import sys as bsys
from Blender import Mathutils
import iGUI

GModules = [iGUI]


#-----------------------------------------------------------------------------
#                            G l o b a l  V a r i a b l e s
#-----------------------------------------------------------------------------
GRegKey = 'irrexport'

# config options:
GExportDir = ''
GObjects = None
GErrorMsg = None
GConfirmOverWrite = True
GVerbose = True

#-----------------------------------------------------------------------------
#                                l o a d C o n f i g
#-----------------------------------------------------------------------------
def loadConfig():
    # Looking for a saved key in Blender's Registry
    RegDict = Blender.Registry.GetKey(GRegKey, True)

    if RegDict:
        try:
            GExportDir = RegDict['GExportDir']
            GConfirmOverWrite = RegDict['GConfirmOverWrite']
            GVerbose = RegDict['GVerbose']
        except: 
            print 'Error Loading Default Config Values'

#-----------------------------------------------------------------------------
#                                c r e a t e G U I 
#-----------------------------------------------------------------------------
def createGUI():
    pass

def selectFile():

    GObjects = Blender.Object.GetSelected()
    if len(GObjects) == 0:
	    GObjects = Blender.Scene.GetCurrent().getChildren()
    print "GObjects = ", GObjects

    if not GObjects:
    	Blender.Draw.PupMenu('ERROR: No objects to export.')
    else:
	    fname = bsys.makename(ext=".irr")
	    if GExportDir:
		    fname = bsys.join(GExportDir, bsys.basename(fname))
            
    Blender.Window.FileSelector(fsCallback, "Export Irrlicht", fname)


#-----------------------------------------------------------------------------
#                                    M a i n
#-----------------------------------------------------------------------------
def Main():
    global GModules

    # Show the wait cursor in blender
    Blender.Window.WaitCursor(1)
    print 'istart.Main()'

    # reload modules
    for module in GModules:		  
        try:
            reload(module)
        except NameError:
            print 'Unable reload module %s' % (module)

    # Load the default/saved configuration values
    loadConfig()
    Blender.Draw.Register(iGUI.gui, iGUI.event, iGUI.buttonEvent)
    Blender.Window.WaitCursor(0)
    
