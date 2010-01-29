#-------------------------------------------------------------------------------
# This source file is part of the Blender to Irrlicht Exporter (irrb)
# url: http://code.google.com/p/tubras/wiki/irrb
#
# This is free and unencumbered software released into the public domain.
# For the full text of the Unlicense, see the file "docs/unlicense.html".
# Additional Unlicense information may be found at http://unlicense.org.
#-------------------------------------------------------------------------------
# Notes:
#
# Coordinate Systems
#
# Irrlicht uses a left-handed coordinate system (y-up):
#
#           +Y  +Z          Positive rotation is clockwise around the
#            |  /           axis of rotation.
#            | /
#            |/             Euler rotation order -> x, y, z.
#  -X--------0--------+X
#           /|
#          / |
#         /  |
#       -Z  -Y
#
#
# Blender uses a right-handed coordinate system (z-up):
#
#           +Z  +Y          Positive rotation is counter-clockwise
#            |  /           around the axis of rotation.
#            | /
#            |/
#  -X--------0---------+X
#           /|
#          / |
#         /  |
#       -Y  -Z
#
import bpy
import os
import time
import irrbmodules.iScene as iScene
import irrbmodules.iMesh as iMesh
import irrbmodules.iMeshBuffer as iMeshBuffer
import irrbmodules.iMaterials as iMaterials
import irrbmodules.iConfig as iConfig
import irrbmodules.iUtils as iUtils
import irrbmodules.iFilename as iFilename
import irrbmodules.iTGAWriter as iTGAWriter
import irrbmodules.iGUIInterface as iGUIInterface

#GIrrbModules = [irrbmodules.iExporter, irrbmodules.iScene, irrbmodules.iMesh,
#    irrbmodules.iMeshBuffer, irrbmodules.iMaterials, irrbmodules.iConfig,
#    irrbmodules.iUtils, irrbmodules.iFilename, irrbmodules.iTGAWriter]
GIrrbModules = [iConfig, iScene, iFilename, iMaterials, iMesh, iMeshBuffer, 
    iScene, iTGAWriter, iUtils, iGUIInterface]


#-------------------------------------------------------------------------------
#                                 d e b u g
#-------------------------------------------------------------------------------
def debug(msg):
    iUtils.debug(msg)

def addWarning(msg):
    iUtils.addWarning(msg)

#-------------------------------------------------------------------------------
#                               E x p o r t e r
#-------------------------------------------------------------------------------
class Exporter:

    #---------------------------------------------------------------------------
    #                               _ i n i t _
    #---------------------------------------------------------------------------
    def __init__(self, Context, GUIInterface,
            CreateScene, BaseDir, SceneDir, MeshDir, TexDir,
            SelectedMeshesOnly, ExportLights, ExportCameras, ExportPhysics,
            Binary, Debug, IrrlichtVersion):


        for module in GIrrbModules:
            try:
                reload(module)
            except NameError:
                print('irrb unable to reload module %s' % (module))

        # Load the default/saved configuration values
        self.loadConfig()

        if len(BaseDir):
            if BaseDir[len(BaseDir)-1] != os.path.sep:
                BaseDir += os.path.sep

        if len(MeshDir):
            if MeshDir[len(MeshDir)-1] != os.path.sep:
                MeshDir += os.path.sep
        if len(TexDir):
            if TexDir[len(TexDir)-1] != os.path.sep:
                TexDir += os.path.sep

        self.gContext = Context
        self.gGUI = GUIInterface
        self.gCreateScene = CreateScene
        self.gBaseDir = BaseDir
        self.gBlendFileName = bpy.data.filename
        self.gBlendRoot = os.path.dirname(self.gBlendFileName)
        self.gMeshDir = MeshDir
        self.gTexDir = TexDir
        self.gSceneDir = SceneDir
        self.gTexExtension = '.???'
        self.gSelectedMeshesOnly = SelectedMeshesOnly
        self.gExportLights = ExportLights
        self.gExportCameras = ExportCameras
        self.gExportPhysics = ExportPhysics
        self.gCopyImages = iUtils.defScriptOptions['copyExternalImages']
        self.gActions = {}
        self.gBinary = Binary
        self.gDebug = Debug
        self.gScene = None
        self.gRootObjects = []
        self.gMeshFileName = ''
        self.gSceneFileName = ''
        self.gObjectLevel = 0
        self.gIrrlichtVersion = IrrlichtVersion
        self.iScene = None
        self.sfile = None

    #---------------------------------------------------------------------------
    #                               l o a d C o n f i g
    #---------------------------------------------------------------------------
    def loadConfig(self):
        pass

    #-----------------------------------------------------------------------------
    #                              g e t T e x P a t h
    #-----------------------------------------------------------------------------
    def getTexPath(self):
        if self.gTexPath.strip() == '':
            return self.gTexDir
        return self.gTexPath

    #-----------------------------------------------------------------------------
    #                              g e t T e x E x t
    #-----------------------------------------------------------------------------
    def getTexExt(self):
        return self.gTexExtension

    #-----------------------------------------------------------------------------
    #                           _ d u m p O p t i o n s
    #-----------------------------------------------------------------------------
    def _dumpOptions(self):
        debug('\n[options]')
        debug('   Create Scene: ' + ('True' if self.gCreateScene else 'False'))
        debug(' Base Directory: ' + self.gBaseDir)
        debug('Scene Directory: ' + self.gSceneDir)
        debug(' Mesh Directory: ' + self.gMeshDir)
        debug('Image Directory: ' + self.gTexDir)
        debug('     meshOutDir: ' + iUtils.defScriptOptions['meshOutDir'])
        debug('      texOutDir: ' + iUtils.defScriptOptions['texOutDir'])
        debug('         Binary: ' + ('True' if self.gBinary else 'False'))
        debug(' Export Cameras: ' + ('True' if self.gExportCameras else 'False'))
        debug('  Export Lights: ' + ('True' if self.gExportLights else 'False'))
        debug(' Export Physics: ' + ('True' if self.gExportPhysics else 'False'))
        debug('    Copy Images: ' + ('True' if self.gCopyImages else 'False'))
        debug('Image Extension: ' + ('Original' if self.gTexExtension ==
            '.???' else self.gTexExtension))
        debug('  Selected Only: ' + ('True' if self.gSelectedMeshesOnly else
            'False'))
        debug('   Irrlicht Ver: ' + str(self.gIrrlichtVersion))
        debug('  iwalktest Env: ' + self.gGUI.gWalkTestPath)
        debug('   imeshcvt Env: ' + self.gGUI.gMeshCvtPath)
        debug('  iwalktest Cmd: ' + self.gGUI.gWalkTestPath.replace('$1',
            iUtils.flattenPath(self.gSceneFileName)).replace('$2',iUtils.filterPath(self.gBaseDir))
)

    #-----------------------------------------------------------------------------
    #                             _ d u m p S t a t s
    #-----------------------------------------------------------------------------
    def _dumpStats(self, stats):
        debug('\n[stats]')
        for stat in stats:
            debug(stat)

    #-----------------------------------------------------------------------------
    #                         _ d u m p B l e n d e r I n f o
    #-----------------------------------------------------------------------------
    def _dumpBlenderInfo(self):
        debug('\n[blender info]')
        if gHavePlatform:
            p = platform.uname()
            debug('             OS: %s %s %s' % (p[0], p[2], p[3]))
        else:
            debug('             OS: [no platform]')
        debug('        Version: %d' % Blender.Get('version'))
        debug('    .blend File: ' + self.gBlendFileName)
        debug('    .blend Root: ' + self.gBlendRoot)
        debug(' Python Version: %d.%d.%d %s' % (sys.version_info[0],
            sys.version_info[1], sys.version_info[2], sys.version_info[3]))

    #-----------------------------------------------------------------------------
    #                       _ d u m p S c e n e I n f o
    #-----------------------------------------------------------------------------
    def _dumpSceneInfo(self):
        debug('\n[scene info]')
        debug('Scene Name:' + self.gScene.getName())
        debug('Visible Layers: ' + str(self.gSceneLayers))

    #-----------------------------------------------------------------------------
    #                         _ d u m p O b j e c t I n f o
    #-----------------------------------------------------------------------------
    def _dumpObjectInfo(self):
        idx = 0
        debug('\n[object info]')
        for bObject in self.gRootObjects:
            type = bObject.getType()
            debug('Object (%d): Name=%s, Type=%s, Layers=%s' % (idx,
                bObject.getName(),type, str(bObject.layers)))
            idx += 1

    #-----------------------------------------------------------------------------
    #                         _ d u m p A c t i o n I n f o
    #-----------------------------------------------------------------------------
    def _dumpActionInfo(self):
        debug('\n[ipo info]')

        ipos = Blender.Ipo.Get()
        debug('IPO\'s: %s' % str(ipos))
        keys = Blender.Key.Get()
        debug('Key\'s: %s' % str(keys))

        for ipo in ipos:
            for cu in ipo:
                debug('curve %s' % str(cu))

        debug('\n[action info]')
        for name in self.gActions.keys():
            action = self.gActions[name]
            debug('\n   Name: %s' % name)
            debug('      Frames: %s' % str(action.getFrameNumbers()))

            ipoDict = action.getAllChannelIpos()
            debug('        IPOS: %s' % str(ipoDict))


            channels = action.getChannelNames()
            for ch in channels:
                debug('          ch: %s' % ch)
                ipo = action.getChannelIpo(ch)

                if ipo == None:
                    debug('         ipo: none')
                    continue

                ipoBlockType = ipo.getBlocktype()
                debug('         ipo: %s' % str(ipo))
                debug('    ipo name: %s' % ipo.name)
                debug('    ipo prop: %s' % str(ipo.properties.keys()))
                debug('    ipo type: %s' % str(type(ipo)))
                bts = 'unknown: %s' % ipoBlockType
                if ipoBlockType == iUtils.ID_KE:
                    bts = 'Key'
                elif ipoBlockType == iUtils.ID_OB:
                    bts = 'Object'
                elif ipoBlockType == iUtils.ID_CA:
                    bts = 'Camera'
                elif ipoBlockType == iUtils.ID_WO:
                    bts = 'World'
                elif ipoBlockType == iUtils.ID_MA:
                    bts = 'Material'
                elif ipoBlockType == iUtils.ID_TE:
                    bts = 'Texture'
                elif ipoBlockType == iUtils.ID_LA:
                    bts = 'Lamp'
                elif ipoBlockType == iUtils.ID_AC:
                    bts = 'Action/Pose'
                elif ipoBlockType == iUtils.ID_CO:
                    bts = 'Constraint'
                elif ipoBlockType == iUtils.ID_SEQ:
                    bts = 'Sequence'
                elif ipoBlockType == iUtils.ID_CU:
                    bts = 'Curve'

                debug('      ipo bt: %s' % bts)
                # debug('     ipo dir: %s' % str(dir(ipo)))
                debug('      ipo ch: %s' % str(ipo.channel))
                debug('      curves: %d' % len(ipo.curves))
                i = 0
                # for curve in ipo:
                    # debug(' curve: ' + str(dir(curve)))

                for curve in ipo.curves:
                    debug('\n      [curve: %d]' % i)
                    debug('            name: %s' % curve.name)
                    debug('           curve: %s' % str(curve))
                    debug('          driver: %s' % str(curve.driver))
                    debug('         drv obj: %s' % str(curve.driverObject))
                    j = 0
                    for bpoint in curve.bezierPoints:
                        triple = bpoint.getTriple()
                        debug(' bezier point[%d]: %s, %s, %s' %
                                (j,str(triple[0]), str(triple[1]),
                                    str(triple[2])))
                        j += 1
                    i += 1


    #-----------------------------------------------------------------------------
    #                       _ d u m p A n i m a t i o n I n f o
    #-----------------------------------------------------------------------------
    def _dumpAnimationInfo(self):
        rctx = self.gScene.getRenderingContext()
        debug('\n[animation info]')
        debug('fpsbase: %.4f' % rctx.fpsBase)
        debug('    fps: %d' % rctx.fps)
        debug(' sFrame: %d' % rctx.sFrame)
        debug(' eFrame: %d' % rctx.eFrame)

    #-----------------------------------------------------------------------------
    #                              d o E x p o r t
    #-----------------------------------------------------------------------------
    def doExport(self):

        self.gFatalError = None
        self.gImageInfo = {}

        self.gGUI.updateStatus('Exporting...')
        start = time.clock()

        # exit edit mode if necessary
        #editMode = Blender.Window.EditMode()
        #if editMode:
        #    Blender.Window.EditMode(0)

        #
        # use this to track exported mesh data.  multiple mesh objects may
        # reference the same mesh data. irrb only export's a single copy
        #
        self.gExportedMeshes = []
        self.gExportedMeshesLC = []
        self.gMeshNameConflicts = []

        #
        # export objects from the current scene
        #
        self.gScene = self.gContext.scene
        self.gSceneLayers = self.gScene.render_data.layers

        #self.gActions = Blender.Armature.NLA.GetActions()

        #
        # initialize .irr scene file if requested
        #
        logName = ''
        if self.gCreateScene:
            try:
                if not self.gSceneDir.endswith(os.path.sep):
                    self.gSceneDir += os.path.sep

                self.gSceneFileName = (self.gSceneDir +
                    self.gScene.name + '.irr')
                self.sfile = open(self.gSceneFileName,'w')
                self.iScene = iScene.Scene(self)
                self.iScene.writeSceneHeader(self.sfile, self.gScene, self.gExportPhysics)
            except IOError as exc:
                self.sfile = None
                self.gSceneFileName = None

        logName = self.gBaseDir
        if not logName.endswith(os.path.sep):
            logName += os.path.sep
        logName += 'irrb.log'


        try:
            iUtils.openLog(logName)
        except:
            self.gFatalError = 'Error Opening (+w) Log File: %s' % logName
            stats = ['Export Failed!']
            stats.append(self.gFatalError)
            self.gGUI.setStatus(stats)
            return

        debug('irrb log ' + iUtils.iversion)

        self._dumpBlenderInfo()
        self._dumpOptions()
        self._dumpSceneInfo()
        iUtils.dumpStartMessages()

        #self._dumpAnimationInfo()
        #self._dumpActionInfo()

        for object in self.gScene.objects:
            pObject = object.parent
            if pObject is None:
                self.gRootObjects.append(object)

        self._dumpObjectInfo()

        self.gObjectLevel = 0
        self.gObjectCount = 0
        self.gLightCount = 0
        self.gCameraCount = 0
        self.gVertCount = 0
        self.gFaceCount = 0
        self.copiedImages = []
        for bObject in self.gRootObjects:
            self._exportObject(bObject)
            if (self.gFatalError != None) or (self.gGUI.exportCancelled()):
                break

        if self.sfile != None:
            self.iScene.writeSceneFooter(self.sfile)
            self.sfile.close()
            self.sfile = None

        if editMode:
            Blender.Window.EditMode(1)

        end = time.clock()
        etime = time.strftime('%X %x')
        stats = ['Export Complete - %.2f seconds - %s' % (end-start,etime)]
        stats.append('%d Object(s)' % self.gObjectCount)
        mcount = len(self.gExportedMeshes)
        if mcount == 1:
            temp = '%d Mesh'
        else:
            temp = '%d Meshes'
        stats.append(temp % mcount)
        stats.append('%d Light(s)' % self.gLightCount)
        stats.append('%d Image(s)' % len(self.copiedImages))
        stats.append('%d/%d Verts/Tris' % (self.gVertCount,self.gFaceCount))
        if len(self.gMeshNameConflicts) > 0:
            stats.append('Error: The following meshes contained naming conflicts:')
            for name in self.gMeshNameConflicts:
                stats.append('   ' + name)

        if self.gFatalError != None:
            stats = ['Export Failed!']
            stats.append(self.gFatalError)

        self._dumpStats(stats)
        iUtils.closeLog()

        self.gGUI.setStatus(stats)

    #-----------------------------------------------------------------------------
    #                            _ g e t C h i l d r e n
    #-----------------------------------------------------------------------------
    def _getChildren(self,obj):
        obs = self.gScene.objects
        return [ ob for ob in obs if ob.parent == obj ]

    #-----------------------------------------------------------------------------
    #                          _ e x p o r t O b j e c t
    #-----------------------------------------------------------------------------
    def _exportObject(self,bObject):

        inVisibleLayer = False
        for l in bObject.layers:
            if l in self.gSceneLayers:
                inVisibleLayer = True
                break;

        if not inVisibleLayer:
           return;

        type = bObject.getType()

        writeObject = True
        if type == 'Mesh' and self.gSelectedMeshesOnly == 1 and not bObject.sel:
            writeObject = False

        itype =  iUtils.getProperty('inodetype',bObject)
        if itype != None:
            itype = itype.lower()
            if itype == 'default':
                itype = None

        writeTail = True

        if writeObject:
            if itype != None:
                if itype == 'skybox':
                    sImages = self._validateSkyBox(bObject)
                    if sImages == None:
                        writeTail = False
                    else:
                        self.iScene.writeNodeHead(self.sfile,self.gObjectLevel,'skyBox')
                        self.iScene.writeSkyBoxNodeData(self.sfile, bObject,
                                sImages, self.gObjectLevel)
                        for image in sImages:
                            self._saveImage(image)

                elif itype == 'billboard':
                    bbImage = self._validateBillboard(bObject)
                    if bbImage == None:
                        writeTail = False
                    else:
                        self.iScene.writeNodeHead(self.sfile,self.gObjectLevel,'billBoard')
                        self.iScene.writeBillboardNodeData(self.sfile, bObject,
                                bbImage, self.gObjectLevel)
                        self._saveImage(bbImage)

                else:
                    # display invalid "inodetype" warning
                    addWarning('Object "%s", has invalid "inodetype."' % bObject.name)
                    writeTail = False
            elif type == 'Mesh':
                if self.sfile != None:
                    #
                    # should check if mesh actually contains animations...
                    #
                    self.iScene.writeNodeHead(self.sfile,self.gObjectLevel,'mesh')
                self._exportMesh(bObject)
                self.gObjectCount += 1
            elif (type == 'Lamp'):
                if (self.sfile != None) and self.gExportLights:
                    self.iScene.writeNodeHead(self.sfile,self.gObjectLevel,'light')
                    self.iScene.writeLightNodeData(self.sfile,bObject,self.gObjectLevel)
                    self.gLightCount += 1
                else:
                    writeTail = False
            elif (type == 'Camera'):
                if (self.sfile != None) and self.gExportCameras:
                    self.iScene.writeNodeHead(self.sfile,self.gObjectLevel,'camera')
                    self.iScene.writeCameraNodeData(self.sfile,bObject,self.gObjectLevel)
                    self.gCameraCount += 1
                else:
                    writeTail = False
            elif (type == 'Empty' or type == 'Armature'):
                if (self.sfile != None):
                    self.iScene.writeNodeHead(self.sfile,self.gObjectLevel,'empty')
                    self.iScene.writeEmptyObject(self.sfile,bObject,self.gObjectLevel)
                else:
                    writeTail = False
            else:
                writeTail = False

        self.gObjectLevel += 1
        cObjects = self._getChildren(bObject)
        for cObject in cObjects:
            self._exportObject(cObject)
        self.gObjectLevel -= 1

        if writeObject and (self.sfile != None) and writeTail:
            self.iScene.writeNodeTail(self.sfile,self.gObjectLevel)


    #-----------------------------------------------------------------------------
    #                     _ v a l i d a t e B i l l b o a r d
    #-----------------------------------------------------------------------------
    def _validateBillboard(self, bObject):
        mesh = bObject.getData(False, True)

        if bObject.getType() != 'Mesh':
            msg = 'Ignoring billboard: %s, not a mesh object.' % mesh.name
            addWarning(msg)
            return None

        if not mesh.faceUV:
            msg = 'Ignoring billboard: %s, no UV Map.' % mesh.name
            addWarning(msg)
            return None

        faces = mesh.faces
        if len(faces) != 1:
            msg = 'Ignoring billboard: %s, invalid face count: %d' % (mesh.name, len(faces))
            addWarning(msg)
            return None

        bImage = faces[0].image
        return bImage

    #-----------------------------------------------------------------------------
    #                        _ v a l i d a t e S k y B o x
    #-----------------------------------------------------------------------------
    def _validateSkyBox(self, bObject):
        mesh = bObject.getData(False, True)

        if bObject.getType() != 'Mesh':
            msg = 'Ignoring skybox: %s, not a mesh object.' % mesh.name
            addWarning(msg)
            return None

        if not mesh.faceUV:
            msg = 'Ignoring skybox: %s, no UV Map.' % mesh.name
            addWarning(msg)
            return None

        faces = mesh.faces
        if len(faces) != 6:
            msg = 'Ignoring skybox: %s, invalid face count: %d' % (mesh.name, len(faces))
            addWarning(msg)
            return None

        topImage = None
        botImage = None
        leftImage = None
        rightImage = None
        frontImage = None
        backImage = None
        for face in faces:
            no = face.no

            no.x = float('%.2f' % no.x)
            no.y = float('%.2f' % no.y)
            no.z = float('%.2f' % no.z)

            # top / bottom?
            if no.x == 0.0 and no.y == 0.0:
                if no.z == -1.0:
                    topImage = face.image
                elif no.z == 1.0:
                    botImage = face.image
            # left / right?
            elif no.y == 0.0 and no.z == 0.0:
                if no.x == -1.0:
                    rightImage = face.image
                elif no.x == 1.0:
                    leftImage = face.image
            #front / back?
            elif no.x == 0.0 and no.z == 0.0:
                if no.y == -1.0:
                    frontImage = face.image
                elif no.y == 1.0:
                    backImage = face.image

        if (topImage == None or botImage == None or
            leftImage == None or rightImage == None or
            frontImage == None or backImage == None):
            msg = 'Ignoring skybox: %s, not all faces assigned images' % mesh.name
            addWarning(msg)
            return None

        return (topImage, botImage, leftImage, rightImage, frontImage,
                backImage)

    #-----------------------------------------------------------------------------
    #                    _ h a s M e s h B e e n E x p o r t e d
    #-----------------------------------------------------------------------------
    # Blender treats object/datablock names that only differ in case as
    # NOT equal.  Therefore 'Cube' is not the same as 'cube'.  This doesn't work
    # for exporters running on windows without internally renaming the mesh
    # to Cube.001.  Our choice is to display an error message - the
    # generated scene/meshes will likely NOT be correct.
    #
    def _hasMeshBeenExported(self, meshName):
        result = meshName in self.gExportedMeshes
        if not result:
            result = meshName.lower() in self.gExportedMeshesLC
            if result:
                self.gMeshNameConflicts.append(meshName)
        return result

    #-----------------------------------------------------------------------------
    #                 _ a d d T o M e s h E x p o r t e d L i s t
    #-----------------------------------------------------------------------------
    def _addToMeshExportedList(self, meshName):
        if self._hasMeshBeenExported(meshName):
            return

        self.gExportedMeshes.append(meshName)
        self.gExportedMeshesLC.append(meshName.lower())

    #-----------------------------------------------------------------------------
    #                           _ c o n v e r t M e s h
    #-----------------------------------------------------------------------------
    def _convertMesh(self,iname,oname):

        self.gGUI.updateStatus('Creating Binary Mesh: ' + oname)

        meshcvt = self.gGUI.gMeshCvtPath
        directory = Blender.sys.dirname(meshcvt)

        cmdline =  meshcvt + ' -v ' + self.gIrrlichtVersion + ' -i ' + iname + '  -o ' + oname
        cmdline +=  ' -a ' + iUtils.filterPath(self.gBaseDir)

        print(cmdline)

        try:
            subprocess.call(cmdline, shell=True, cwd=directory)
        except:
            self.gFatalError = 'Error Converting To Binary Mesh.  Check imeshcvt setup.'

    #-----------------------------------------------------------------------------
    #                            _ e x p o r t M e s h
    #-----------------------------------------------------------------------------
    def _exportMesh(self, bObject):


        # get Mesh
        meshData = bObject.getData(False,True)
        oName = bObject.getName()
        debug('\n[Mesh - ob:%s, me:%s]' % (oName,meshData.name))

        self.gMeshFileName = self.gMeshDir + meshData.name + '.irrmesh'
        binaryMeshFileName = ''
        if self.gBinary:
            binaryMeshFileName = (self.gMeshDir +
                    meshData.name + '.irrbmesh')

        self.gGUI.updateStatus('Exporting Mesh: ' + meshData.name + ', Object: ' + oName)

        alreadyExported = self._hasMeshBeenExported(meshData.name)

        if len(meshData.verts) == 0:
            msg = 'ignoring mesh: %s, no vertices' % meshData.name
            addWarning(msg)
            return

        #
        # write scene node data to scene (.irr) file
        #
        meshFileName = self.gMeshFileName

        if self.sfile != None:
            meshFileName = iUtils.relpath(self.gMeshFileName, self.gBaseDir)

            sceneMeshFileName = meshFileName
            if self.gBinary:
                fname,fext = Blender.sys.splitext(meshFileName)
                sceneMeshFileName = fname + '.irrbmesh'

            self.iScene.writeMeshObject(self.sfile,sceneMeshFileName,bObject,
                    self.gObjectLevel, self.gExportPhysics)

        #
        # have we already exported this mesh data block?
        #
        if alreadyExported:
            return

        self._addToMeshExportedList(meshData.name)

        try:
            file = open(self.gMeshFileName,'w')
        except:
            pass

        irrMesh = iMesh.Mesh(bObject,self,True)
        if irrMesh.createBuffers() == True:
            if self.gGUI.exportCancelled():
                file.close()
                return

            irrMesh.write(file)

            if self.gGUI.exportCancelled():
                file.close()
                return

            self.gVertCount += irrMesh.getVertexCount()
            self.gFaceCount += irrMesh.getFaceCount()

            # write image(s) if any
            for k,v in irrMesh.getMaterials().iteritems():
                if self.gGUI.exportCancelled():
                    file.close()
                    return

                if v.getMaterialType() == 'UVMaterial':
                    mat = v.getMaterial()
                    images = mat.getImages()
                    for image in images:
                        self._saveImage(image)

        file.close()
        file = None

        if self.gBinary:
            self._convertMesh(self.gMeshFileName, binaryMeshFileName)

    #-----------------------------------------------------------------------------
    #                       g e t I m a g e F i l e N a m e
    #-----------------------------------------------------------------------------
    # which: 0-texture path, full filename
    def getImageFileName(self,meshName,bImage,which):
        imageName = bImage.name
        if imageName in self.gImageInfo:
            return self.gImageInfo[imageName][which]

        fullFileName = bImage.getFilename()

        #
        # check for relative path and expand if necessary
        #
        if fullFileName[0:2] == '//':
            fullFileName = Blender.sys.expandpath(fullFileName)
            fullFileName = Blender.sys.cleanpath(fullFileName)
        dirname = Blender.sys.dirname(fullFileName)
        exists = False
        try:
            file = open(fullFileName,'r')
            file.close()
            exists = True
        except:
            pass

        #
        # it is possible that a blender gen'd image was saved without an
        # extension.  in this case the full filename won't contain the
        # extension but the image name will...
        #
        ext = Blender.sys.splitext(fullFileName)[1]
        if not exists and (ext == ''):
            checkName = dirname + os.path.sep + imageName
            try:
                file = open(checkName,'r')
                file.close()
                exists = True
                fullFileName = checkName
            except:
                pass

        if bImage.packed or not exists:
            fileName = bImage.name
            fileExt = ''
        else:
            fileName,fileExt = Blender.sys.splitext(Blender.sys.basename(
                fullFileName))

        debug('\n[Image]')
        debug('imageName: ' + imageName)
        debug('org fullFileName: ' + bImage.getFilename())
        debug('fullFileName: ' + fullFileName)
        debug('dirname: ' + dirname)
        debug('fileName: ' + fileName)
        debug('fileExt: ' + fileExt)

        source = 'unknown'
        if bImage.source & Blender.Image.Sources['GENERATED']:
            source = 'generated'
        elif bImage.source & Blender.Image.Sources['STILL']:
            source = 'still'
        elif bImage.source & Blender.Image.Sources['MOVIE']:
            source = 'movie'
        elif bImage.source & Blender.Image.Sources['SEQUENCE']:
            source = 'sequence'

        try:
            debug('bImage.depth: %d' % bImage.depth)
            debug('bImage.source: %d-%s' % (bImage.source,source))
            debug('bImage.packed: %d' % bImage.packed)
            debug('bImage.lib: %s' % bImage.lib)
            debug('exists on disk: %d' % exists)
        except:
            debug('error accessing image properties for: %s' % bImage.name)
            return None

        #
        #
        result = '???'
        ext = fileExt
        if self.gTexExtension != '.???':
            ext = self.gTexExtension

        if bImage.packed or self.gCopyImages:
            result = iUtils.relpath(self.gTexDir + fileName + ext,
                     self.gBaseDir)
        else:
            result = iUtils.relpath(fullFileName, self.gBaseDir)

        result0 = result

        result = fullFileName
        if self.gTexExtension != '.???':
            result = self.gTexDir + fileName + ext
        else:
            result = self.gTexDir + fileName + fileExt
        debug('result0: %s' % result0)
        debug('result1: %s' % result)
        self.gImageInfo[imageName] = (result0,result)
        if which == 0:
            return result0
        return result

    #-----------------------------------------------------------------------------
    #                      _ s a v e P a c k e d T e x t u r e
    #-----------------------------------------------------------------------------
    def _savePackedTexture(self,bImage):

        if bImage in self.copiedImages:
            return

        #
        # can't use bpy.data.image here because it _doesn't_ support 32
        # bit images, so the alpha channel would be lost for input
        # images that have one.  this way is also much faster...
        #

        filename = self.getImageFileName('',bImage,1)
        if filename == None:
            return

        self.gGUI.updateStatus('Saving Packed Texture ' + filename + '...')
        self.copiedImages.append(bImage)

        if self.gTexExtension != '.???':
            iTGAWriter.writeTGA(bImage,filename,True)
        else:
            saveName =  bImage.getFilename()
            bImage.setFilename(filename)
            bImage.save()
            bImage.setFilename(saveName);

    #-----------------------------------------------------------------------------
    #                      _ c o p y E x t e r n a l I m a g e
    #-----------------------------------------------------------------------------
    def _copyExternalImage(self, bImage):
        if bImage in self.copiedImages:
            return

        self.copiedImages.append(bImage)

        filename = self.getImageFileName('',bImage,1)
        if filename == None:
            return

        ofilename = bImage.getFilename()

        self.gGUI.updateStatus('Copying external image ' + ofilename + '...')
        shutil.copy2(ofilename, filename)

    #-----------------------------------------------------------------------------
    #                            _ s a v e I m a g e
    #-----------------------------------------------------------------------------
    def _saveImage(self, bImage):
        if bImage.packed:
            self._savePackedTexture(bImage)
        elif self.gCopyImages:
            self._copyExternalImage(bImage)

        

