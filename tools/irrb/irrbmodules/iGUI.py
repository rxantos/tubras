#-----------------------------------------------------------------------------
# This source file is part of the Blender to Irrlicht Exporter (irrb)
# url: http://code.google.com/p/tubras/wiki/irrb
#
# Copyright (C) 2008-2009 Keith Murray -- <pc0der at gmail dot com>
#
# This software is licensed under the zlib/libpng license. See the file
# "irrbmodules/docs/license.html" for detailed information.
#-----------------------------------------------------------------------------
import Blender
import types
import os
import subprocess
import iExporter
import iScene
import iMesh
import iMeshBuffer
import iConfig
import iMaterials
import iUtils
import iFilename
import iTGAWriter
from Blender import Draw, BGL, Window

GModules = [iExporter,iScene,iMesh,iMeshBuffer,iMaterials, iConfig,
        iUtils,iFilename,iTGAWriter]
GRegKey = 'irrbexport'

gVersionList = (0, 16)

gHaveZip = False
try:
    import zipfile
    gHaveZip = True
except:
    pass
        
# config options:
gBaseDir = os.path.expanduser('~') + os.sep
gMeshDir = gBaseDir
gOutDir = gBaseDir
gImageDir = gBaseDir

gWarnings = []
gDisplayWarnings = False
gCreateScene = 1
gLastSceneExported = None
gCreateWorld = 0
gDebug = 1
gObjects = None
gORGOutput = 1
gTGAOutput = 0
gSelectedOnly = 0
gExportLights = 1
gExportCameras = 1
gVisibleLayersOnly = 1
gLastYVal = 0
gBinary = 0
GErrorMsg = None
GConfirmOverWrite = True
GVerbose = True
gWalkTest = 0
gExportCancelled = False
gIrrlichtVersion = 1
gStatus = ['None']

gWorldLogic = False

gHaveWalkTest = False
gWalkTestPath = ''
if 'IWALKTEST' in os.environ:
    gWalkTestPath = os.environ['IWALKTEST']
    gHaveWalkTest = True

gHaveMeshCvt = False
gMeshCvtPath = ''
if 'IMESHCVT' in os.environ:
    gMeshCvtPath = os.environ['IMESHCVT']
    gHaveMeshCvt = True

# buttons
bCreateScene = None
bBaseDir = None
bSceneDir = None
bSelectedOnly = None
bExportLights = None
bExportCameras = None
bVisibleLayers = None
bCopyTex = None
bORG = None
bTGA = None
bWorld = None
bWalkTest = None
bReWalkTest = None
bBinary = None
bIrrlichtVersion = None

# button id's
ID_SELECTDIR    = 2
ID_EXPORT       = 6
ID_CANCEL       = 7
ID_CREATESCENE  = 8
ID_SELECTEDONLY = 9
ID_ORG          = 11
ID_TGA          = 12
ID_WORLD        = 13
ID_EXPLIGHTS    = 14
ID_OUTDIR     = 16
ID_TEXDIR       = 17
ID_WALKTEST     = 18
ID_EXPCAMERAS   = 19
ID_REWALKTEST   = 20
ID_BINARY       = 21
ID_BACK         = 22
ID_SHOWWARNINGS = 23
ID_BASEDIR      = 25
ID_IVERSION     = 26
ID_GENPROPS     = 27

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
    Blender.Redraw()

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
    global mystring, mymsg, toggle, scriptsLocation
    global bSelectedOnly, bBaseDir, gBaseDir
    global gSelectedOnly
    global gImageDir, gORGOutput, gTGAOutput, bTGA, bORG
    global bWorld, gCreateWorld, bImageDir
    global bSceneDir, gOutDir, gExportLights, bExportLights, gLastYVal
    global bWalkTest, gWalkTest, gExportCameras, bExportCameras, bReWalkTest
    global gLastSceneExported, bBinary, gBinary
    global gCreateScene, bCreateScene, bIrrlichtVersion

    if gDisplayWarnings:
        displayWarnings()
        return

    BGL.glClearColor(0.392,0.396,0.549,1) 
    
    BGL.glClear(Blender.BGL.GL_COLOR_BUFFER_BIT)
    size = Blender.Window.GetAreaSize()

    isize = drawHeader(size)

    maxWidth = 440

	# Create File path input
    BGL.glColor3f(1.0,1.0,1.0)

    # starting x&y position values
    xval = 10
    yval = size[1]-isize[1] - 40

    fileWidth = size[0] - (xval+130)

    if fileWidth > maxWidth:
        fileWidth = maxWidth

    # Scene Directory
    Blender.BGL.glRasterPos2i(xval, yval+5)
    Blender.Draw.Text('Output Directory','normal')
    bSceneDir = Blender.Draw.String('', ID_OUTDIR, xval+95,
        yval, fileWidth, 20, gOutDir, 255)

    Blender.Draw.PushButton('...', ID_SELECTDIR, xval+95 + fileWidth,
        yval, 30,20,'Select Output Directory')

    yval -= 40

    # Option Buttons
    bCreateScene = Blender.Draw.Toggle('Create Scene File', 
        ID_CREATESCENE,xval+95, yval, 150, 20, gCreateScene, 
        'Create Scene File (.irr)')

    bSelectedOnly = Blender.Draw.Toggle('Selected Meshes Only',
            ID_SELECTEDONLY,xval+255, yval, 150, 20, gSelectedOnly, 
            'Export Select Meshes Only')

    if gHaveMeshCvt:
        bBinary = Blender.Draw.Toggle('Create Binary Meshes',
                ID_BINARY,xval+415, yval, 150, 20, gBinary, 
                'Export Binary Mesh Format (.irrbmesh)')

    # Scene Directory
    if gCreateScene:

        yval -= 25

        bExportCameras = Blender.Draw.Toggle('Export Camera(s)', 
            ID_EXPCAMERAS,xval+95, yval, 150, 20, gExportCameras, 'Export Scene Camera(s)')

        bExportLights = Blender.Draw.Toggle('Export Light(s)', 
            ID_EXPLIGHTS, xval+255, yval, 150, 20, gExportLights, 'Export Scene Light(s)')

        if gHaveWalkTest:
            bWalkTest = Blender.Draw.Toggle('Walk Test', ID_WALKTEST,xval+415,
                    yval, 150, 20, gWalkTest, 'Run Walk Test After Export')

    yval -= 25

    Blender.Draw.PushButton('Create irrb Props', ID_GENPROPS, xval + 95,
            yval, 150, 20, 'Create irrb ID Properties For Selected Object(s)')


    # Irrlicht Version (target) for imeshcvt
    if gHaveMeshCvt and gBinary:
        yval -= 40
        Blender.BGL.glRasterPos2i(xval+6, yval+4)
        Blender.Draw.Text('Irrlicht Version','normal')
    
        versions = "1.6 %x1"
        bIrrlichtVersion = Draw.Menu(versions, ID_IVERSION, xval+95, yval-1, 150, 20,
                gIrrlichtVersion, 'Irrlicht Version Target')
    
    if gWorldLogic:
        yval -= 40
        bWorld = Blender.Draw.Toggle('Create World File', ID_WORLD, xval+95, 
                yval, 150, 20, gCreateWorld, 
                'Create Compressed .wld File (experimental)')

    # Export Buttons        
    Blender.Draw.PushButton('Export', ID_EXPORT, xval+95, 10, 100, 20, 'Export')
    if gCreateScene and gHaveWalkTest and gLastSceneExported != None:
        bReWalkTest = Blender.Draw.PushButton('Run Walk Test', ID_REWALKTEST,
                xval + 250, 10, 150, 20, 
                'Run Walk Test With Last Exported Scene')            
    Blender.Draw.PushButton('Exit', ID_CANCEL, fileWidth+35, 10, 100, 
            20,'Exit the Exporter')

    yval -= 40
    Blender.BGL.glRasterPos2i(xval+50, yval)
    Blender.Draw.Text('Status:','normal')

    gLastYVal = yval
    
    if type(gStatus) == types.ListType:
        for s in gStatus:
            Blender.BGL.glRasterPos2i(xval+95, yval)
            Blender.Draw.Text(s,'normal')
            yval -= 18
        if len(gWarnings) > 0 :
            BGL.glColor3f(1.0,1.0,0.0)
            Blender.BGL.glRasterPos2i(xval+95, yval)
            Blender.Draw.Text('%d Warning(s)' % len(gWarnings),'normal')
            Blender.Draw.PushButton('Warnings', ID_SHOWWARNINGS,
                    xval+255, yval-3, 75, 20, 
                    'Display Warnings From Last Export')

    else:
        Blender.BGL.glRasterPos2i(xval+95, yval)
        Blender.Draw.Text(gStatus,'normal')
        yval -= 18
    

#-----------------------------------------------------------------------------
#                             d i r S e l e c t e d
#-----------------------------------------------------------------------------
def dirSelected(fileName):
    global gOutDir,bSceneDir

    gOutDir = iUtils.filterDirPath(Blender.sys.dirname(fileName))
    bSceneDir.val = gOutDir

#-----------------------------------------------------------------------------
#                             r u n W a l k T e s t
#-----------------------------------------------------------------------------
def runWalkTest(sceneFileName):


    directory = Blender.sys.dirname(gWalkTestPath)
    bcwd = os.getcwd()

    cmdline = gWalkTestPath.replace('$1',
            iUtils.flattenPath(sceneFileName)).replace('$2',iUtils.filterPath(gBaseDir))

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
#                          c h e c k D i r e c t o r y           
#-----------------------------------------------------------------------------
def checkDirectory(dirVal, ask=True):
    tempDir = iUtils.filterDirPath(dirVal)
    if not os.path.isdir(tempDir):
        if ask:
            result = Draw.PupMenu("Directory Doesn't Exist, Create?%t|Yes%x1|No%x0")
            if(result != 1):
                Draw.Redraw(1)
                return None
        os.makedirs(tempDir)
    return tempDir    

#-----------------------------------------------------------------------------
#                             b u t t o n E v e n t
#-----------------------------------------------------------------------------
def buttonEvent(evt):
    global mymsg, toggle, gSelectedOnly
    global bSelectedOnly, bCreateScene, gCreateScene
    global gMeshDir, gDebug
    global gTGAOutput, gORGOutput, gImageDir, gBaseDir
    global bWorld, gCreateWorld
    global gOutDir, gExportLights, bExportLights
    global gMeshDir, gOutDir, gImageDir, bWalkTest, gWalkTest
    global gExportCameras, bExportCameras, gLastSceneExported
    global gBinary, bBinary, gWarnings, gDisplayWarnings
    global gExportCancelled, gStatus 
    global gIrrlichtVersion

    if evt == ID_SELECTDIR:
        Window.FileSelector(dirSelected,'Select Directory',gOutDir)
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
    elif evt == ID_TEXDIR:
        tempDir = checkDirectory(bImageDir.val)
        if tempDir == None:
            return
        gImageDir = tempDir
        Draw.Redraw(1)
    elif evt == ID_OUTDIR:
        tempDir = checkDirectory(bSceneDir.val)
        if tempDir == None:
            return
        gOutDir = tempDir
        Draw.Redraw(1)
    elif evt == ID_BASEDIR:
        tempDir = checkDirectory(bBaseDir.val)
        if tempDir == None:
            return
        gBaseDir = tempDir
        Draw.Redraw(1)

    elif evt == ID_GENPROPS:
        iUtils.setIDProperties()

    elif evt == ID_EXPORT:
        saveConfig()
        gWarnings = []
        gExportCancelled = False
        gBaseDir = gOutDir
        gMeshDir = gOutDir + iUtils.defScriptOptions['mdlName'] + os.sep
        gImageDir = gOutDir + iUtils.defScriptOptions['texName'] + os.sep
        checkDirectory(gMeshDir, False)
        checkDirectory(gImageDir, False)
        gSavePackedTexture = 1
        exporter = iExporter.Exporter(gCreateScene, gBaseDir, gOutDir, gMeshDir,
                gImageDir, '.???', gSelectedOnly,
                gExportLights, gExportCameras, 
                gBinary, gDebug, gVersionList[gIrrlichtVersion])
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
    elif evt == ID_IVERSION:
        gIrrlichtVersion = bIrrlichtVersion.val
        Draw.Redraw(1)

#-----------------------------------------------------------------------------
#                            s a v e C o n f i g 
#-----------------------------------------------------------------------------
def saveConfig():
    global gMeshDir, GConfirmOverWrite, GVerbose, gImageDir
    global gSelectedOnly, gCreateScene 
    global gTGAOutput, gORGOutput, gCreateWorld
    global gOutDir, gExportLights, gBaseDir
    global gWalkTest, gExportCameras, gBinary, gIrrlichtVersion 
    
    d = {}
    d['gBaseDir'] = gBaseDir
    d['gSelectedOnly'] = gSelectedOnly
    d['gBinary'] = gBinary
    d['GConfirmOverWrite'] = GConfirmOverWrite
    d['GVerbose'] = GVerbose
    d['gCreateWorld'] = gCreateWorld
    d['gOutDir'] = gOutDir
    d['gExportLights'] = gExportLights
    d['gExportCameras'] = gExportCameras
    d['gWalkTest'] = gWalkTest
    d['gCreateScene'] = gCreateScene
    d['gIrrlichtVersion'] = gIrrlichtVersion

    Blender.Registry.SetKey(GRegKey, d, True)
        
    
#-----------------------------------------------------------------------------
#                            l o a d C o n f i g
#-----------------------------------------------------------------------------
def loadConfig():
    global gMeshDir, GConfirmOverWrite, GVerbose, gImageDir
    global gSelectedOnly, gBaseDir
    global gCreateScene
    global gOutDir, gExportLights, gIrrlichtVersion
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
            gOutDir = RegDict['gOutDir']
        except:
            gOutDir = gBaseDir

        try:
            gIrrlichtVersion = RegDict['gIrrlichtVersion']
            if gIrrlichtVersion >= len(gVersionList):
                gIrrlichtVersion = len(gVersionList)-1
        except:
            gIrrlichtVersion = 1 

        try:
            gWalkTest = RegDict['gWalkTest']
        except:
            gWalkTest = 0

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
            print('irrb unable to reload module %s' % (module))

    # Load the default/saved configuration values
    loadConfig()
    
    Blender.Draw.Register(gui, event, buttonEvent)
    Blender.Window.WaitCursor(0)
   
