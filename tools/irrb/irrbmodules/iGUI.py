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
import Blender,types,os,sys,subprocess
from Blender import Draw, BGL, Window
import iExporter,iScene,iMesh,iMeshBuffer
import iMaterials,iUtils,iFilename,iTGAWriter

GModules = [iExporter,iScene,iMesh,iMeshBuffer,iMaterials,
        iUtils,iFilename,iTGAWriter]
GRegKey = 'irrbexport'

gTexExtensions = ('.???','.tga')


# config options:
gMeshDir = 'c:\\temp'
gTexDir = 'c:\\temp'
gSceneDir = 'c:\\temp'
gBaseDir = 'c:\\temp'
if sys.platform != 'win32':
    gMeshDir = '/tmp'
    gTexDir = '/tmp'
    gSceneDir = '/tmp'
    gBaseDir = '/tmp'

gWarnings = []
gDisplayWarnings = False
gCreateScene = 1
gTexExt = 0
gLastSceneExported = None
gCreateWorld = 0
gHomeyVal = 1
gDebug = 1
gObjects = None
gSavePackedTextures = 0
gORGOutput = 1
gTGAOutput = 0
gSelectedOnly = 0
gExportLights = 1
gExportCameras = 1
gLastYVal = 0
gBinary = 0
GErrorMsg = None
GConfirmOverWrite = True
GVerbose = True
gWalkTest = 0
gExportCancelled = False
gStatus = ['None']

gWorldLogic = False

gHaveWalkTest = False
gWalkTestPath = ''
if 'IWALKTEST' in os.environ.keys():
    gWalkTestPath = os.environ['IWALKTEST']
    gHaveWalkTest = True

gHaveMeshCvt = False
gMeshCvtPath = ''
if 'IMESHCVT' in os.environ.keys():
    gMeshCvtPath = os.environ['IMESHCVT']
    gHaveMeshCvt = True

# buttons
bCreateScene = None
bBaseDir = None
bMeshDir = None
bTextureDir = None
bSceneDir = None
bSelectedOnly = None
bExportLights = None
bExportCameras = None
bCopyTex = None
bORG = None
bTGA = None
bWorld = None
bWalkTest = None
bReWalkTest = None
bBinary = None

# button id's
ID_SELECTDIR    = 2
ID_SELECTDIR2   = 3
ID_SELECTDIR3   = 4
ID_SELECTDIR4   = 5
ID_EXPORT       = 6
ID_CANCEL       = 7
ID_CREATESCENE  = 8
ID_SELECTEDONLY = 9
ID_COPYTEX      = 10
ID_ORG          = 11
ID_TGA          = 12
ID_WORLD        = 13
ID_EXPLIGHTS    = 14
ID_MESHDIR      = 15
ID_SCENEDIR     = 16
ID_TEXDIR       = 17
ID_WALKTEST     = 18
ID_EXPCAMERAS   = 19
ID_REWALKTEST   = 20
ID_BINARY       = 21
ID_BACK         = 22
ID_SHOWWARNINGS = 23
ID_BASEDIR      = 25

scriptsLocation = (Blender.Get('scriptsdir')+Blender.sys.sep+
        'irrbmodules'+Blender.sys.sep)
if not Blender.sys.exists(scriptsLocation):
    scriptsLocation = (Blender.Get('uscriptsdir')+Blender.sys.sep+
            'irrbmodules'+Blender.sys.sep)

#-----------------------------------------------------------------------------
#                              i n i t i a l i z e
#-----------------------------------------------------------------------------
def initialize():
    pass

#-----------------------------------------------------------------------------
#                             u p d a t e S t a t u s
#-----------------------------------------------------------------------------
def updateStatus(status):
    global gStatus

    gStatus = status
    if gHomeyVal == 0:
        BGL.glClearColor(0.69,0.69,0.69,1) 
    else: 
        BGL.glClearColor(0.392,0.396,0.549,1) 
    
    BGL.glClear(Blender.BGL.GL_COLOR_BUFFER_BIT)
    size = Blender.Window.GetAreaSize()

    isize = drawHeader(size)

    BGL.glColor3f(1.0,1.0,1.0)
    yval = size[1]-isize[1] - 40
    
    Blender.BGL.glRasterPos2i(60, yval)
    Blender.Draw.Text('Status:','normal')

    if type(gStatus) == types.ListType:
        for s in gStatus:
            Blender.BGL.glRasterPos2i(105, yval)
            Blender.Draw.Text(s,'normal')
            yval = yval - 18
    else:
        Blender.BGL.glRasterPos2i(105, yval)
        Blender.Draw.Text(gStatus,'normal')
        yval = yval - 18

    Blender.Redraw()

#-----------------------------------------------------------------------------
#                               s e t S t a t u s 
#-----------------------------------------------------------------------------
def setStatus(status):
    global gStatus
    gStatus = status

#-----------------------------------------------------------------------------
#                            d r a w H e a d e r 
#-----------------------------------------------------------------------------
def drawHeader(size):
    sver = 'v' + iUtils.iversion

    try:
        bheight=10
        boffset = 8
        logoImage = Blender.Image.Load(scriptsLocation + 'irrblend.png')
        isize = logoImage.getSize()
        BGL.glColor3f(0.8,0.8,0.8) 

        BGL.glRectd(11+isize[0],size[1]-bheight-boffset,size[0]-5,
                size[1]-boffset)

        Blender.BGL.glEnable(Blender.BGL.GL_BLEND ) 
        Blender.BGL.glBlendFunc(Blender.BGL.GL_SRC_ALPHA, 
                Blender.BGL.GL_ONE_MINUS_SRC_ALPHA)	  
        Blender.Draw.Image(logoImage, 6, size[1]-isize[1]-5)
        Blender.BGL.glDisable(Blender.BGL.GL_BLEND)

        Blender.BGL.glRasterPos2i(183, size[1]-33)
        Blender.Draw.Text(sver,'normal')        

    except IOError: 
        BGL.glColor3f(1.0,1.0,1.0)
        Blender.BGL.glRasterPos2i(45, size[1]-30)
        Blender.Draw.Text('Irrlicht Plugin for Blender - ' + sver, 'large')
        isize = [256,75]

    return isize

#-----------------------------------------------------------------------------
#                               a d d W a r n i n g
#-----------------------------------------------------------------------------
def addWarning(msg):
    gWarnings.append(msg)

#-----------------------------------------------------------------------------
#                           d i s p l a y W a r n i n g s
#-----------------------------------------------------------------------------
def displayWarnings():
    if gHomeyVal == 0:
        BGL.glClearColor(0.69,0.69,0.69,1) 
    else: 
        BGL.glClearColor(0.392,0.396,0.549,1) 
    
    BGL.glClear(Blender.BGL.GL_COLOR_BUFFER_BIT)
    size = Blender.Window.GetAreaSize()

    isize = drawHeader(size)

    BGL.glColor3f(1.0,1.0,0.0)
    yval = size[1]-isize[1] - 40
    
    Blender.BGL.glRasterPos2i(50, yval)
    Blender.Draw.Text('Warnings:','normal')

    BGL.glColor3f(1.0,1.0,1.0)
    for s in gWarnings:
        Blender.BGL.glRasterPos2i(115, yval)
        Blender.Draw.Text(s,'normal')
        yval = yval - 18

    Blender.Draw.PushButton('Back', ID_BACK, 105, 10, 100, 20, 'Back To Exporter')

#-----------------------------------------------------------------------------
#                                   g u i 
#-----------------------------------------------------------------------------
def gui():
    global mystring, mymsg, toggle, scriptsLocation, bMeshDir, gMeshDir
    global bSelectedOnly, bBaseDir, gBaseDir, bMeshDir
    global gSelectedOnly, gHomeyVal, gSavePackedTextures, bCopyTex
    global gTexDir, gTGAOutput, bTGA
    global gORGOutput, bORG, bWorld, gCreateWorld, bTextureDir
    global bSceneDir, gSceneDir, gExportLights, bExportLights, gLastYVal
    global bWalkTest, gWalkTest, gExportCameras, bExportCameras, bReWalkTest
    global gLastSceneExported, bBinary, gBinary
    global gCreateScene, bCreateScene


    if gDisplayWarnings:
        displayWarnings()
        return

    if gHomeyVal == 0:
        BGL.glClearColor(0.69,0.69,0.69,1) 
    else: 
        BGL.glClearColor(0.392,0.396,0.549,1) 
    
    BGL.glClear(Blender.BGL.GL_COLOR_BUFFER_BIT)
    size = Blender.Window.GetAreaSize()

    isize = drawHeader(size)

    maxWidth = 440

	# Create File path input
    if gHomeyVal == 0:
        BGL.glColor3f(0.0, 0.0, 0.0)
    else:
        BGL.glColor3f(1.0,1.0,1.0)

    # starting x&y position values
    xval = 10
    yval = size[1]-isize[1] - 40

    fileWidth = size[0] - (xval+130)

    if fileWidth > maxWidth:
        fileWidth = maxWidth

    
    bCreateScene = Blender.Draw.Toggle('Create Scene File', 
        ID_CREATESCENE,xval+95, yval, 150, 20, gCreateScene, 'Create Scene File (.irr)')

    bSelectedOnly = Blender.Draw.Toggle('Selected Meshes Only',
            ID_SELECTEDONLY,xval+255, yval, 150, 20, gSelectedOnly, 
            'Export Select Meshes Only')

    if gHaveMeshCvt:
        bBinary = Blender.Draw.Toggle('Create Binary Meshes',
                ID_BINARY,xval+415, yval, 150, 20, gBinary, 
                'Export Binary Mesh Format (.irrbmesh)')

    yval = yval - 40

    Blender.BGL.glRasterPos2i(xval+14, yval+5)
    Blender.Draw.Text('Relative Base','normal')
    bBaseDir = Blender.Draw.String('', ID_BASEDIR, xval+95, 
            yval, fileWidth, 20, gBaseDir, 255) 
    Blender.Draw.PushButton('...', ID_SELECTDIR4, xval+95 + fileWidth, 
            yval, 30,20,'Select Relative Base Directory')

    if gCreateScene:
        yval = yval - 40

        Blender.BGL.glRasterPos2i(xval, yval+5)
        Blender.Draw.Text('Scene Directory','normal')
        bSceneDir = Blender.Draw.String('', ID_SCENEDIR, xval+95, 
            yval, fileWidth, 20, gSceneDir, 255) 

        Blender.Draw.PushButton('...', ID_SELECTDIR3, xval+95 + fileWidth, 
            yval, 30,20,'Select Scene Output Directory')

        yval = yval - 23

        bExportCameras = Blender.Draw.Toggle('Export Camera(s)', 
            ID_EXPCAMERAS,xval+95, yval, 150, 20, gExportCameras, 'Export Scene Camera(s)')

        bExportLights = Blender.Draw.Toggle('Export Light(s)', 
            ID_EXPLIGHTS, xval+255, yval, 150, 20, gExportLights, 'Export Scene Light(s)')


    yval = yval - 40    

    Blender.BGL.glRasterPos2i(xval+4, yval+5)
    Blender.Draw.Text('Mesh Directory','normal')
    
    bMeshDir = Blender.Draw.String('', ID_MESHDIR, xval+95, yval, 
            fileWidth, 20, gMeshDir, 255) 
    Blender.Draw.PushButton('...', ID_SELECTDIR, xval+95 + fileWidth, 
            yval, 30,20,'Select Mesh Output Directory')

    yval = yval - 40

    bCopyTex = Blender.Draw.Toggle('Save Packed Textures', ID_COPYTEX,xval+95, yval, 
            150, 20, gSavePackedTextures, 'Save Packed Textures To Disk')
    

    if gSavePackedTextures:
        bx = xval + 255
        bTGA = Blender.Draw.Toggle('ORG', ID_ORG,bx, yval, 55, 20, 
                gORGOutput, 'Use Original Texture Format')
        bPNG = Blender.Draw.Toggle('TGA', ID_TGA,bx+60, yval, 55, 20, 
                gTGAOutput, 'Generate .TGA Textures')
        yval = yval - 23
        
        Blender.BGL.glRasterPos2i(xval-5, yval+4)
        Blender.Draw.Text('Texture Directory','normal')
        bTextureDir = Blender.Draw.String('', ID_TEXDIR, xval+95, yval-1, 
                fileWidth, 20, gTexDir, 255) 
        Blender.Draw.PushButton('...', ID_SELECTDIR2, xval+95 + fileWidth, 
                yval-1, 30,20,'Select Texture Output Directory')

    if gCreateScene and gHaveWalkTest:
        yval = yval - 40
        bWalkTest = Blender.Draw.Toggle('Walk Test', ID_WALKTEST,xval+95, 
                yval, 150, 20, gWalkTest, 'Run Walk Test After Export')    

        if gLastSceneExported != None:
            bReWalkTest = Blender.Draw.PushButton('Re-Test', ID_REWALKTEST,
                    xval + 255, yval, 75, 20, 
                    'Run Walk Test With Last Exported Scene')    
        

    if gWorldLogic:
        yval = yval - 40
        bWorld = Blender.Draw.Toggle('Create World File', ID_WORLD, xval+95, 
                yval, 150, 20, gCreateWorld, 
                'Create Compressed .wld File (experimental)')

    Blender.Draw.PushButton('Export', ID_EXPORT, xval+95, 10, 100, 20, 'Export')
    Blender.Draw.PushButton('Exit', ID_CANCEL, fileWidth+35, 10, 100, 
            20,'Exit the Exporter')

    yval = yval - 40
    Blender.BGL.glRasterPos2i(xval+50, yval)
    Blender.Draw.Text('Status:','normal')

    gLastYVal = yval
    
    if type(gStatus) == types.ListType:
        for s in gStatus:
            Blender.BGL.glRasterPos2i(xval+95, yval)
            Blender.Draw.Text(s,'normal')
            yval = yval - 18
        if len(gWarnings) > 0 :
            BGL.glColor3f(1.0,1.0,0.0)
            Blender.BGL.glRasterPos2i(xval+95, yval)
            Blender.Draw.Text('%d Warnings' % len(gWarnings),'normal')
            Blender.Draw.PushButton('Warnings', ID_SHOWWARNINGS,
                    xval+255, yval-3, 75, 20, 
                    'Display Warnings From Last Export')

    else:
        Blender.BGL.glRasterPos2i(xval+95, yval)
        Blender.Draw.Text(gStatus,'normal')
        yval = yval - 18
        
    
#-----------------------------------------------------------------------------
#                             d i r S e l e c t e d
#-----------------------------------------------------------------------------
def dirSelected(fileName):
    global bMeshDir,gMeshDir

    gMeshDir = iUtils.filterDirPath(Blender.sys.dirname(fileName))
    bMeshDir.val = gMeshDir

#-----------------------------------------------------------------------------
#                             d i r S e l e c t e d 2
#-----------------------------------------------------------------------------
def dirSelected2(fileName):
    global gTexDir,bTextureDir

    gTexDir = iUtils.filterDirPath(Blender.sys.dirname(fileName))
    bTextureDir.val = gTexDir

#-----------------------------------------------------------------------------
#                             d i r S e l e c t e d 3
#-----------------------------------------------------------------------------
def dirSelected3(fileName):
    global gSceneDir,bSceneDir

    gSceneDir = iUtils.filterDirPath(Blender.sys.dirname(fileName))
    bSceneDir.val = gSceneDir

#-----------------------------------------------------------------------------
#                             d i r S e l e c t e d 4
#-----------------------------------------------------------------------------
def dirSelected4(fileName):
    global gBaseDir, bBaseDir

    gBaseDir = iUtils.filterDirPath(Blender.sys.dirname(fileName))
    bBaseDir.val = gBaseDir

#-----------------------------------------------------------------------------
#                             r u n W a l k T e s t
#-----------------------------------------------------------------------------
def runWalkTest(sceneFileName):


    directory = Blender.sys.dirname(gWalkTestPath)
    bcwd = os.getcwd()

    if gWalkTestPath.find('%s') < 0:
        cmdline =  gWalkTestPath + ' ' + sceneFileName
    else:
        cmdline = gWalkTestPath % sceneFileName
    p  = subprocess.Popen(cmdline, shell=True, cwd=directory)

#-----------------------------------------------------------------------------
#                         e x p o r t C a n c e l l e d
#-----------------------------------------------------------------------------
def exportCancelled():
    global gExportCancelled
    

    while Window.QTest():
        evt, val = Window.QRead()
        if evt == Draw.ESCKEY:
            gExportCancelled = True
            break;

    return gExportCancelled

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
#                             b u t t o n E v e n t
#-----------------------------------------------------------------------------
def buttonEvent(evt):
    global mymsg, toggle, gHomeyVal, gSelectedOnly
    global bSelectedOnly, bCreateScene, gCreateScene
    global gMeshDir, gDebug, bCopyTex, gSavePackedTextures
    global gTGAOutput, gORGOutput, gTexDir, gBaseDir
    global bWorld, gCreateWorld, gTexExt, gTexExtensions
    global gSceneDir, gExportLights, bExportLights
    global gMeshDir, gSceneDir, gTexDir, bWalkTest, gWalkTest
    global gExportCameras, bExportCameras, gLastSceneExported
    global gBinary, bBinary, gWarnings, gDisplayWarnings
    global gExportCancelled, gStatus


    if evt == ID_SELECTDIR:
        Window.FileSelector(dirSelected,'Select Directory',gMeshDir)
        Draw.Redraw(1)        
    elif evt == ID_SELECTDIR2:
        Window.FileSelector(dirSelected2,'Select Directory',gTexDir)
        Draw.Redraw(1)        
    elif evt == ID_SELECTDIR3:
        Window.FileSelector(dirSelected3,'Select Directory',gSceneDir)
        Draw.Redraw(1)        
    elif evt == ID_SELECTDIR4:
        Window.FileSelector(dirSelected4,'Select Directory',gBaseDir)
        Draw.Redraw(1)        
    elif evt == ID_CANCEL:
        saveConfig()
        Draw.Exit()
    elif evt == ID_SELECTEDONLY:
        gSelectedOnly = bSelectedOnly.val
        Draw.Redraw(1)
    elif evt == ID_BINARY:
        gBinary = bBinary.val
        Draw.Redraw(1)
    elif evt == ID_CREATESCENE:
        gCreateScene = bCreateScene.val
        Draw.Redraw(1)
    elif evt == ID_COPYTEX:
        gSavePackedTextures = bCopyTex.val
        Draw.Redraw(1)        
    elif evt == ID_EXPLIGHTS:
        gExportLights = bExportLights.val
        Draw.Redraw(1)
    elif evt == ID_EXPCAMERAS:
        gExportCameras = bExportCameras.val
        Draw.Redraw(1)
    elif evt == ID_WORLD:
        gCreateWorld = bWorld.val
        Draw.Redraw(1)
    elif evt == ID_WALKTEST:
        gWalkTest = bWalkTest.val
        Draw.Redraw(1)
    elif evt == ID_MESHDIR:
        gMeshDir = iUtils.filterDirPath(bMeshDir.val)
        Draw.Redraw(1)
    elif evt == ID_TEXDIR:
        gTexDir = iUtils.filterDirPath(bTextureDir.val);
        Draw.Redraw(1)
    elif evt == ID_SCENEDIR:
        gSceneDir = iUtils.filterDirPath(bSceneDir.val)
        Draw.Redraw(1)
    elif evt == ID_BASEDIR:
        gBaseDir = iUtils.filterDirPath(bBaseDir.val)
        Draw.Redraw(1)
    elif evt == ID_EXPORT:
        saveConfig()
        gWarnings = []
        gExportCancelled = False
        exporter = iExporter.Exporter(gCreateScene, gBaseDir, gSceneDir, gMeshDir, 
                gTexDir, gTexExtensions[gTexExt], gSelectedOnly,
                gExportLights, gExportCameras, gSavePackedTextures, gBinary, gDebug)
        Window.WaitCursor(1)
        exporter.doExport()
        
        if gExportCancelled:
            gStatus = 'Export Cancelled'
        elif exporter.gFatalError == None:
            if (gCreateScene and gWalkTest and gHaveWalkTest and 
                    (exporter.gSceneFileName !=None)):
                runWalkTest(exporter.gSceneFileName)
            gLastSceneExported = exporter.gSceneFileName

        Window.WaitCursor(0)
        exporter = None
        if len(gWarnings) > 0:
            gDisplayWarnings = True
        Draw.Redraw(1)
    elif evt == ID_BACK:
        gDisplayWarnings = False
        Draw.Redraw(1)
    elif evt == ID_SHOWWARNINGS:
        if len(gWarnings) > 0:
            gDisplayWarnings = True
        Draw.Redraw(1)
    elif evt == ID_REWALKTEST:
        if gHaveWalkTest and (gLastSceneExported != None):
            runWalkTest(gLastSceneExported)
    elif evt == ID_TGA:
        if not gTGAOutput:
            gORGOutput = 0
            gTGAOutput = 1
            gTexExt = 1
        Draw.Redraw(1)
    elif evt == ID_ORG:
        if not gORGOutput:
            gTGAOutput = 0
            gORGOutput = 1
            gTexExt = 0
        Draw.Redraw(1)



#-----------------------------------------------------------------------------
#                            s a v e C o n f i g 
#-----------------------------------------------------------------------------
def saveConfig():
    global gMeshDir, GConfirmOverWrite, GVerbose, gTexDir
    global gSelectedOnly, gSavePackedTextures, gCreateScene 
    global gTGAOutput, gORGOutput, gCreateWorld
    global gTexExt, gSceneDir, gExportLights, gBaseDir
    global gWalkTest, gExportCameras, gBinary
    
    d = {}
    d['gBaseDir'] = gBaseDir
    d['gMeshDir'] = gMeshDir
    d['gTexDir'] = gTexDir
    d['gSelectedOnly'] = gSelectedOnly
    d['gBinary'] = gBinary
    d['GConfirmOverWrite'] = GConfirmOverWrite
    d['GVerbose'] = GVerbose
    d['gSavePackedTextures'] = gSavePackedTextures
    d['gTexExt'] = gTexExt
    d['gCreateWorld'] = gCreateWorld
    d['gSceneDir'] = gSceneDir
    d['gExportLights'] = gExportLights
    d['gExportCameras'] = gExportCameras
    d['gWalkTest'] = gWalkTest
    d['gCreateScene'] = gCreateScene

    Blender.Registry.SetKey(GRegKey, d, True)
        
    
#-----------------------------------------------------------------------------
#                            l o a d C o n f i g
#-----------------------------------------------------------------------------
def loadConfig():
    global gMeshDir, GConfirmOverWrite, GVerbose, gTexDir
    global gSelectedOnly, gSavePackedTextures, gBaseDir
    global gTGAOutput, gORGOutput, gCreateScene
    global gTexExt, gSceneDir, gExportLights
    global gWalkTest, gExportCameras, gBinary

    # Looking for a saved key in Blender's Registry
    RegDict = Blender.Registry.GetKey(GRegKey, True)

    if RegDict:
        try:
            gBaseDir = RegDict['gBaseDir']
        except:
            pass
        try:
            gCreateScene = RegDict['gCreateScene']
        except:
            gCreateScene = 1
        try:
            gMeshDir = RegDict['gMeshDir']
        except: 
            gMeshDir = gBaseDir
        try:
            gExportLights = RegDict['gExportLights']
        except:
            gExportLights = 0
        try:
            gExportCameras = RegDict['gExportCameras']
        except:
            gExportCameras = 0
        try:
            gCreateWorld = RegDict['gCreateWorld']
        except:
            gCreateWorld = 0
        try:
            gSelectedOnly = RegDict['gSelectedOnly']
        except:
            gSelectedOnly = 0
        try:
            gBinary = RegDict['gBinary']
        except:
            gBinary = 0
        try:
            GConfirmOverWrite = RegDict['GConfirmOverWrite']
        except:
            GConfirmOverWrite = 1
        try:
            GVerbose = RegDict['GVerbose']
        except:
            GVerbose = 0
        try:
            gSavePackedTextures = RegDict['gSavePackedTextures']
        except:
            gSavePackedTextures = 0
        try:
            gTexDir = RegDict['gTexDir']
        except: 
            gTexDir = gMeshDir
        try:
            gSceneDir = RegDict['gSceneDir']
        except:
            gSceneDir = gBaseDir
        try:
            gTexExt = RegDict['gTexExt']
        except:
            gTexExt = 0

        try:
            gWalkTest = RegDict['gWalkTest']
        except:
            gWalkTest = 0

        if gTexExt == 0:
            gORGOutput = 1
            gTGAOutput = 0
        else:
            gORGOutput = 0
            gTGAOutput = 1



#-----------------------------------------------------------------------------
#                                M a i n
#-----------------------------------------------------------------------------
def Main():
    
    # Show the wait cursor in blender
    Window.WaitCursor(1)
    
    # reload modules
    for module in GModules:		  
        try:
            reload(module)
        except NameError:
            print 'irrb unable to reload module %s' % (module)

    # Load the default/saved configuration values
    loadConfig()
    
    Blender.Draw.Register(gui, event, buttonEvent)
    Blender.Window.WaitCursor(0)
    





