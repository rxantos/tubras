#-----------------------------------------------------------------------------
# Blender to Irrlicht Exporter
# url: http://www.tubras.com
#
# Copyright (C) 2008 Keith Murray -- <pc0de@tubras.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
# this export script is assumed to be used with the latest blender version.
#-----------------------------------------------------------------------------
import Blender
from Blender import Draw, BGL, Window
import iExporter,iMesh,iMeshBuffer,iMaterials,iUtils

GModules = [iExporter,iMesh,iMeshBuffer,iMaterials,iUtils]
GRegKey = 'irrexport'

# config options:
gExportDir = 'c:\\temp'
gTextureLoc = 'tex\\'
gHomeyVal = 1
gDebug = 1
GObjects = None
GErrorMsg = None
GConfirmOverWrite = True
GVerbose = True

scriptsLocation = Blender.Get('scriptsdir')+Blender.sys.sep+'bpymodules'+Blender.sys.sep+'irrlicht'+Blender.sys.sep
fileButton = None
toggleCreateSceneFile = None
gCreateScene = 0
gCreateWorld = 0
toggleSelectedOnly = None
gSelectedOnly = 0
toggleCopyTex = None
gCopyTextures = 0
gTGAOutput = 1
gPNGOutput = 0
gBMPOutput = 0

togglePNG = None
toggleTGA = None
toggleBMP = None
toggleWorld = None

ID_SELECTDIR    = 2
ID_EXPORT       = 3
ID_CANCEL       = 4
ID_SCENEFILE    = 5
ID_SELECTEDONLY = 6
ID_COPYTEX      = 7
ID_PNG          = 8
ID_TGA          = 9
ID_BMP          = 10
ID_WORLD        = 11

#-----------------------------------------------------------------------------
#                              i n i t i a l i z e
#-----------------------------------------------------------------------------
def initialize():
    pass

#-----------------------------------------------------------------------------
#                                   g u i 
#-----------------------------------------------------------------------------
def gui():
    global mystring, mymsg, toggle, scriptsLocation, fileButton, gExportDir
    global toggleCreateSceneFile, gCreateScene, toggleSelectedOnly
    global gSelectedOnly, gHomeyVal, gCopyTextures, toggleCopyTex
    global gTextureLoc, gPNGOutput, togglePNG, gTGAOutput, toggleTGA
    global gBMPOutput, toggleBMP, toggleWorld, gCreateWorld


    if gHomeyVal == 0:
        BGL.glClearColor(0.69,0.69,0.69,1) 
    else: 
        BGL.glClearColor(0.392,0.396,0.549,1) 
    
    BGL.glClear(Blender.BGL.GL_COLOR_BUFFER_BIT)
    size = Blender.Window.GetAreaSize()
    try:
        bheight=10
        boffset = 8
        logoImage = Blender.Image.Load(scriptsLocation + 'irrblend.png')
        isize = logoImage.getSize()
        BGL.glColor3f(0.8,0.8,0.8) 

        BGL.glRectd(11+isize[0],size[1]-bheight-boffset,size[0]-5,size[1]-boffset)

        Blender.BGL.glEnable(Blender.BGL.GL_BLEND ) 
        Blender.BGL.glBlendFunc(Blender.BGL.GL_SRC_ALPHA, Blender.BGL.GL_ONE_MINUS_SRC_ALPHA)	  
        Blender.Draw.Image(logoImage, 6, size[1]-isize[1]-5)
        Blender.BGL.glDisable(Blender.BGL.GL_BLEND)

    except IOError: 
        BGL.glColor3f(1.0,1.0,1.0)
        Blender.BGL.glRasterPos2i(45, size[1]-30)
        Blender.Draw.Text('Irrlicht Plugin for Blender', 'large')
        isize = [256,75]



	# Create File path input
    if gHomeyVal == 0:
        BGL.glColor3f(0.0, 0.0, 0.0)
    else:
        BGL.glColor3f(1.0,1.0,1.0)
    yval = size[1]-isize[1] - 40
    Blender.BGL.glRasterPos2i(8, yval)
    Blender.Draw.Text('Export Directory:','normal')
    fileWidth = size[0] - (105 + 35)
    fileButton = Blender.Draw.String('', 5, 105, yval-6, fileWidth, 20, gExportDir, 255) 
    Blender.Draw.PushButton('...', ID_SELECTDIR, 105 + fileWidth, yval-6, 30,20,'Select Directory')

    yval = yval - 50
    toggleCreateSceneFile = Blender.Draw.Toggle('Create Scene File', \
            ID_SCENEFILE,105, yval, 150, 20, gCreateScene, 'Create Irrlicht Scene File (.irr)')
    
    yval = yval - 40    
    toggleSelectedOnly = Blender.Draw.Toggle('Selected Meshes Only', \
            ID_SELECTEDONLY,105, yval, 150, 20, gSelectedOnly, 'Export Select Meshes Only')

    yval = yval - 40    
    toggleCopyTex = Blender.Draw.Toggle('Copy Textures', \
            ID_COPYTEX,105, yval, 150, 20, gCopyTextures, 'Copy Textures To Export Directory')

    if gCopyTextures:
        Blender.BGL.glRasterPos2i(265, yval+4)
        Blender.Draw.Text('Relative Loc:','normal')
        fileWidth = size[0] - (345)
        texPrefix = Blender.Draw.String('', 5, 340, yval-1, fileWidth, 20, gTextureLoc, 255) 

        toggleTGA = Blender.Draw.Toggle('TGA', ID_TGA,340, yval-23, 40, 20, gTGAOutput, 'Generate .TGA Textures')
        togglePNG = Blender.Draw.Toggle('PNG', ID_PNG,382, yval-23, 40, 20, gPNGOutput, 'Generate .PNG Textures')
        toggleBMP = Blender.Draw.Toggle('BMP', ID_BMP,424, yval-23, 40, 20, gBMPOutput, 'Generate .BMP Textures')

    yval = yval - 60
    toggleWorld = Blender.Draw.Toggle('Create World File', \
            ID_WORLD,105, yval, 150, 20, gCreateWorld, 'Create Compressed .wld File (experimental)')


    Blender.Draw.PushButton('Export', ID_EXPORT, 105, 10, 100, 20, 'Export')
    Blender.Draw.PushButton('Exit', ID_CANCEL, size[0]-105, 10, 100, 20,'Exit the Exporter')
    
    
#-----------------------------------------------------------------------------
#                                  e v e n t
#-----------------------------------------------------------------------------
def event(evt, val):
    global mystring, mymsg

    if not val:  # val = 0: it's a key/mbutton release
        return

    if evt == Draw.ESCKEY:
        Draw.Exit()                 # exit when user presses ESC
        return

    else: return # no need to redraw if nothing changed

    Draw.Redraw(1)


#-----------------------------------------------------------------------------
#                             d i r S e l e c t e d
#-----------------------------------------------------------------------------
def dirSelected(fileName):
    global fileButton,gExportDir

    gExportDir = Blender.sys.dirname(fileName)
    fileButton.val = gExportDir

    
#-----------------------------------------------------------------------------
#                             b u t t o n E v e n t
#-----------------------------------------------------------------------------
def buttonEvent(evt):
    global mymsg, toggle, gHomeyVal, gSelectedOnly
    global toggleSelectedOnly, toggleCreateSceneFile, gCreateScene
    global gExportDir, gDebug, toggleCopyTex, gCopyTextures
    global gTGAOutput, gPNGOutput, gBMPOutput

    if evt == ID_SELECTDIR:
        Window.FileSelector(dirSelected,'Select Export Directory',gExportDir)
        Draw.Redraw(1)        
    elif evt == ID_CANCEL:
        saveConfig()
        Draw.Exit()
    elif evt == ID_SELECTEDONLY:
        gSelectedOnly = toggleSelectedOnly.val
        Draw.Redraw(1)
    elif evt == ID_COPYTEX:
        gCopyTextures = toggleCopyTex.val
        Draw.Redraw(1)
    elif evt == ID_SCENEFILE:
        gCreateScene = toggleCreateSceneFile.val
        Draw.Redraw(1)
    elif evt == ID_EXPORT:
        saveConfig()
        exporter = iExporter.Exporter(gExportDir, gCreateScene, gSelectedOnly, \
                gCopyTextures, gDebug)
        exporter.doExport()
        exporter = None
    elif evt == ID_TGA:
        if not gTGAOutput:
            gBMPOutput = 0
            gTGAOutput = 1
            gPNGOutput = 0
        Draw.Redraw(1)
    elif evt == ID_PNG:
        if not gPNGOutput:
            gBMPOutput = 0
            gTGAOutput = 0
            gPNGOutput = 1
        Draw.Redraw(1)
    elif evt == ID_BMP:
        if not gBMPOutput:
            gBMPOutput = 1
            gTGAOutput = 0
            gPNGOutput = 0
        Draw.Redraw(1)



#-----------------------------------------------------------------------------
#                            s a v e C o n f i g 
#-----------------------------------------------------------------------------
def saveConfig():
    global gExportDir, GConfirmOverWrite, GVerbose 
    global gCreateScene, gSelectedOnly, gCopyTextures
    
    d = {}
    d['gExportDir'] = gExportDir
    d['gCreateScene'] = gCreateScene
    d['gSelectedOnly'] = gSelectedOnly
    d['GConfirmOverWrite'] = GConfirmOverWrite
    d['GVerbose'] = GVerbose
    d['gCopyTextures'] = gCopyTextures
    Blender.Registry.SetKey(GRegKey, d, True)
        
    
#-----------------------------------------------------------------------------
#                            l o a d C o n f i g
#-----------------------------------------------------------------------------
def loadConfig():
    global gExportDir, GConfirmOverWrite, GVerbose 
    global gCreateScene, gSelectedOnly, gCopyTextures

    # Looking for a saved key in Blender's Registry
    RegDict = Blender.Registry.GetKey(GRegKey, True)

    if RegDict:
        try:
            gExportDir = RegDict['gExportDir']
            gCreateScene = RegDict['gCreateScene']
            gSelectedOnly = RegDict['gSelectedOnly']
            GConfirmOverWrite = RegDict['GConfirmOverWrite']
            GVerbose = RegDict['GVerbose']
            gCopyTextures = RegDict['gCopyTextures']
        except: 
            print 'Error Loading Default Config Values'

#-----------------------------------------------------------------------------
#                                M a i n
#-----------------------------------------------------------------------------
def Main():
    global gModules
    
    # Show the wait cursor in blender
    Window.WaitCursor(1)
    print 'iGUI.Main()'
    
    # reload modules
    for module in GModules:		  
        try:
            reload(module)
        except NameError:
            print 'Unable reload module %s' % (module)

    # Load the default/saved configuration values
    loadConfig()
    Blender.Draw.Register(gui, event, buttonEvent)
    Blender.Window.WaitCursor(0)
    





