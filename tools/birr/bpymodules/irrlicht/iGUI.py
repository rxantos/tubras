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
import iExporter,iMesh,iMeshBuffer,iMaterials,iUtils,iFilename

GModules = [iExporter,iMesh,iMeshBuffer,iMaterials,iUtils,iFilename]
GRegKey = 'irrexport'

# config options:
gMeshDir = 'c:\\temp'
gMeshPath = ''
gTexDir = 'c:\\temp'
gTexPath = ''
gCreateScene = 0
gCreateWorld = 0
gHomeyVal = 1
gDebug = 1
gObjects = None
gCopyTextures = 0
gTGAOutput = 1
gPNGOutput = 0
gBMPOutput = 0
gSelectedOnly = 0
GErrorMsg = None
GConfirmOverWrite = True
GVerbose = True

# buttons
bMeshDir = None
bMeshPath = None
bTextureDir = None
bTexPath = None
bCreateScene = None
bSelectedOnly = None
bCopyTex = None
bPNG = None
bTGA = None
bBMP = None
bWorld = None

# button id's
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
ID_SELECTDIR2   = 12
ID_MESHPATH     = 13
ID_TEXPATH      = 14

scriptsLocation = Blender.Get('scriptsdir')+Blender.sys.sep+'bpymodules'+Blender.sys.sep+'irrlicht'+Blender.sys.sep

#-----------------------------------------------------------------------------
#                              i n i t i a l i z e
#-----------------------------------------------------------------------------
def initialize():
    pass

#-----------------------------------------------------------------------------
#                                   g u i 
#-----------------------------------------------------------------------------
def gui():
    global mystring, mymsg, toggle, scriptsLocation, bMeshDir, gMeshDir
    global bCreateScene, gCreateScene, bSelectedOnly
    global gSelectedOnly, gHomeyVal, gCopyTextures, bCopyTex
    global gTexDir, gPNGOutput, bPNG, gTGAOutput, bTGA
    global gBMPOutput, bBMP, bWorld, gCreateWorld, bTextureDir
    global bTexPath, gTexPath, bMeshPath, gMeshPath


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
    Blender.BGL.glRasterPos2i(17, yval)
    Blender.Draw.Text('Mesh Directory','normal')
    fileWidth = size[0] - (105 + 35)
    bMeshDir = Blender.Draw.String('', 5, 105, yval-6, fileWidth, 20, gMeshDir, 255) 
    Blender.Draw.PushButton('...', ID_SELECTDIR, 105 + fileWidth, yval-6, \
            30,20,'Select Mesh Directory')


    yval = yval - 50    
    bSelectedOnly = Blender.Draw.Toggle('Selected Meshes Only', \
            ID_SELECTEDONLY,105, yval, 150, 20, gSelectedOnly, 'Export Select Meshes Only')

    yval = yval - 40
    bCreateScene = Blender.Draw.Toggle('Create Scene File', \
            ID_SCENEFILE,105, yval, 150, 20, gCreateScene, 'Create Irrlicht Scene File (.irr)')
    if gCreateScene:
        yval = yval - 18
        Blender.BGL.glRasterPos2i(40, yval)
        Blender.Draw.Text('Mesh Path','normal')
        fileWidth = size[0] - (105 + 35)
        bMeshPath = Blender.Draw.String('', ID_MESHPATH, 105, yval-6, fileWidth, 20, gMeshPath, 255)         
    
    yval = yval - 40    
    bCopyTex = Blender.Draw.Toggle('Copy Textures', \
            ID_COPYTEX,105, yval, 150, 20, gCopyTextures, 'Copy Textures To Export Directory')
    

    if gCopyTextures:
        bx = 265
        bTGA = Blender.Draw.Toggle('TGA', ID_TGA,bx, yval, 40, 20, gTGAOutput, 'Generate .TGA Textures')
        bPNG = Blender.Draw.Toggle('PNG', ID_PNG,bx+42, yval, 40, 20, gPNGOutput, 'Generate .PNG Textures')
        bBMP = Blender.Draw.Toggle('BMP', ID_BMP,bx+84, yval, 40, 20, gBMPOutput, 'Generate .BMP Textures')
        yval = yval - 23
        
        Blender.BGL.glRasterPos2i(5, yval+4)
        Blender.Draw.Text('Texture Directory','normal')
        fileWidth = size[0] - (105 + 35)
        bTextureDir = Blender.Draw.String('', 5, 105, yval-1, fileWidth, 20, gTexDir, 255) 
        Blender.Draw.PushButton('...', ID_SELECTDIR2, 105 + fileWidth, \
                yval-1, 30,20,'Select Texture Directory')
        yval = yval - 18
        Blender.BGL.glRasterPos2i(30, yval)
        Blender.Draw.Text('Texture Path','normal')
        fileWidth = size[0] - (105 + 35)
        bTexPath = Blender.Draw.String('', ID_TEXPATH, 105, yval-6, fileWidth, 20, gTexPath, 255)         


    yval = yval - 40
    bWorld = Blender.Draw.Toggle('Create World File', \
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
    global bMeshDir,gMeshDir

    gMeshDir = Blender.sys.dirname(fileName)
    bMeshDir.val = gMeshDir

#-----------------------------------------------------------------------------
#                             d i r S e l e c t e d 2
#-----------------------------------------------------------------------------
def dirSelected2(fileName):
    global gTexDir,bTextureDir

    gTexDir = Blender.sys.dirname(fileName)
    bTextureDir.val = gTexDir

    
#-----------------------------------------------------------------------------
#                             b u t t o n E v e n t
#-----------------------------------------------------------------------------
def buttonEvent(evt):
    global mymsg, toggle, gHomeyVal, gSelectedOnly
    global bSelectedOnly, bCreateScene, gCreateScene
    global gMeshDir, gDebug, bCopyTex, gCopyTextures
    global gTGAOutput, gPNGOutput, gBMPOutput, gTexDir
    global bWorld, gCreateWorld, bMeshPath, gMeshPath
    global bTexPath,gTexPath


    if evt == ID_SELECTDIR:
        Window.FileSelector(dirSelected,'Select Directory',gMeshDir)
        Draw.Redraw(1)        
    if evt == ID_SELECTDIR2:
        Window.FileSelector(dirSelected2,'Select Directory',gTexDir)
        Draw.Redraw(1)        
    elif evt == ID_CANCEL:
        saveConfig()
        Draw.Exit()
    elif evt == ID_SELECTEDONLY:
        gSelectedOnly = bSelectedOnly.val
        Draw.Redraw(1)
    elif evt == ID_COPYTEX:
        gCopyTextures = bCopyTex.val
        Draw.Redraw(1)
    elif evt == ID_SCENEFILE:
        gCreateScene = bCreateScene.val
        Draw.Redraw(1)
    elif evt == ID_WORLD:
        gCreateWorld = bWorld.val
        Draw.Redraw(1)
    elif evt == ID_MESHPATH:
        gMeshPath = bMeshPath.val
        if len(gMeshPath):
            if gMeshPath[len(gMeshPath)-1] != '/':
                gMeshPath += '/'
        Draw.Redraw(1)
    elif evt == ID_TEXPATH:
        gTexPath = bTexPath.val
        if len(gTexPath):
            if gTexPath[len(gTexPath)-1] != '/':
                gTexPath += '/'
        Draw.Redraw(1)
    elif evt == ID_EXPORT:
        saveConfig()
        exporter = iExporter.Exporter(gMeshDir, gMeshPath, gTexDir, \
                gTexPath, gCreateScene, gSelectedOnly, \
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
    global gMeshDir, GConfirmOverWrite, GVerbose, gTexDir
    global gCreateScene, gSelectedOnly, gCopyTextures 
    global gTGAOutput, gPNGOutput, gBMPOutput, gCreateWorld
    global gMeshPath, gTexPath

    otype = 0
    if gPNGOutput:
        otype = 1
    elif gBMPOutput:
        otype = 2

    
    d = {}
    d['gMeshDir'] = gMeshDir
    d['gTexDir'] = gTexDir
    d['gCreateScene'] = gCreateScene
    d['gSelectedOnly'] = gSelectedOnly
    d['GConfirmOverWrite'] = GConfirmOverWrite
    d['GVerbose'] = GVerbose
    d['gCopyTextures'] = gCopyTextures
    d['gTexType'] = otype
    d['gCreateWorld'] = gCreateWorld
    d['gMeshPath'] = gMeshPath
    d['gTexPath'] = gTexPath

    
    Blender.Registry.SetKey(GRegKey, d, True)
        
    
#-----------------------------------------------------------------------------
#                            l o a d C o n f i g
#-----------------------------------------------------------------------------
def loadConfig():
    global gMeshDir, GConfirmOverWrite, GVerbose, gTexDir
    global gCreateScene, gSelectedOnly, gCopyTextures 
    global gTGAOutput, gPNGOutput, gBMPOutput, gCreateWorld
    global gMeshPath, gTexPath

    # Looking for a saved key in Blender's Registry
    RegDict = Blender.Registry.GetKey(GRegKey, True)

    if RegDict:
        try:
            gMeshDir = RegDict['gMeshDir']
        except: 
            gMeshDir = 'c:\\temp'
        try:
            gMeshPath = RegDict['gMeshPath']
        except: 
            gMeshPath = ''
        try:
            gTexPath = RegDict['gTexPath']
        except: 
            gTexPath = ''
        try:
            gCreateScene = RegDict['gCreateScene']
        except:
            gCreateScene = 0
        try:
            gCreateWorld = RegDict['gCreateWorld']
        except:
            gCreateWorld = 0
        try:
            gSelectedOnly = RegDict['gSelectedOnly']
        except:
            gSelectedONly = 0
        try:
            GConfirmOverWrite = RegDict['GConfirmOverWrite']
        except:
            GConfirmOverWrite = 1
        try:
            GVerbose = RegDict['GVerbose']
        except:
            GVerbose = 0
        try:
            gCopyTextures = RegDict['gCopyTextures']
        except:
            gCopyTextures = 0
        try:
            gTexDir = RegDict['gTexDir']
        except: 
            gTexDir = gMeshDir
        try:
            otype = RegDict['gTexType']
        except:
            otype = 0

        if otype == 0:
            gTGAOutput = 1
            gPNGOutput = 0
            gBMPOutput = 0
        elif otype == 1:
            gTGAOutput = 0
            gPNGOutput = 1
            gBMPOutput = 0
        else:
            gTGAOutput = 0
            gPNGOutput = 0
            gBMPOutput = 1



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
    





