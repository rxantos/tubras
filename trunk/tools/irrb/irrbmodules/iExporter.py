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

import Blender,iMesh,iMeshBuffer,bpy,iFilename,iUtils
import iScene,iGUI,time,iTGAWriter,os,subprocess

#-----------------------------------------------------------------------------
#                                 d e b u g
#-----------------------------------------------------------------------------
def debug(msg):
    iUtils.debug(msg)
    
#-----------------------------------------------------------------------------
#                               E x p o r t e r
#-----------------------------------------------------------------------------
class Exporter:

    #-----------------------------------------------------------------------------
    #                               _ i n i t _
    #-----------------------------------------------------------------------------
    def __init__(self,CreateScene, BaseDir, SceneDir, MeshDir, TexDir, TexExtension, 
            SelectedMeshesOnly, ExportLights, ExportCameras,
            SavePackedTextures, Binary, Debug):
        
        if len(MeshDir):
            if MeshDir[len(MeshDir)-1] != Blender.sys.sep:
                MeshDir += Blender.sys.sep
        if len(TexDir):
            if TexDir[len(TexDir)-1] != Blender.sys.sep:
                TexDir += Blender.sys.sep
                
        self.gCreateScene = CreateScene
        self.gBaseDir = BaseDir
        self.gBlendFileName = Blender.Get('filename')
        self.gBlendRoot = Blender.sys.dirname(self.gBlendFileName)
        self.gMeshDir = MeshDir
        self.gTexDir = TexDir
        self.gSceneDir = SceneDir
        self.gTexExtension = TexExtension
        self.gSelectedMeshesOnly = SelectedMeshesOnly
        self.gSavePackedTextures = SavePackedTextures
        self.gExportLights = ExportLights
        self.gExportCameras = ExportCameras
        self.gActions = {}
        self.gBinary = Binary
        self.gDebug = Debug
        self.gScene = None
        self.gRootNodes = []
        self.gMeshFileName = ''
        self.gSceneFileName = ''
        self.nodeLevel = 0
        self.iScene = None
        self.sfile = None

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
    #                            d u m p O p t i o n s
    #-----------------------------------------------------------------------------
    def dumpOptions(self):
        debug('\n[options]')
        debug('   Create Scene: ' + ('True' if self.gCreateScene else 'False'))
        debug(' Base Directory: ' + self.gBaseDir)
        debug('Scene Directory: ' + self.gSceneDir)
        debug(' Mesh Directory: ' + self.gMeshDir)
        debug('  Tex Directory: ' + self.gTexDir)
        debug('         Binary: ' + ('True' if self.gBinary else 'False'))
        debug(' Export Cameras: ' + ('True' if self.gExportCameras else 'False'))
        debug('  Export Lights: ' + ('True' if self.gExportLights else 'False'))
        debug('  Copy Textures: ' + ('True' if self.gSavePackedTextures else 'False'))
        debug('  Tex Extension: ' + ('Original' if self.gTexExtension ==
            '.???' else self.gTexExtension))
        debug('  Selected Only: ' + ('True' if self.gSelectedMeshesOnly else
            'False'))

    #-----------------------------------------------------------------------------
    #                              d u m p S t a t s
    #-----------------------------------------------------------------------------
    def dumpStats(self, stats):
        debug('\n[stats]')
        for stat in stats:
            debug(stat)

    #-----------------------------------------------------------------------------
    #                          d u m p B l e n d e r I n f o 
    #-----------------------------------------------------------------------------
    def dumpBlenderInfo(self):
        debug('\n[blender info]')
        debug('.blend File: ' + self.gBlendFileName)
        debug('.blend Root: ' + self.gBlendRoot)        

    #-----------------------------------------------------------------------------
    #                            d u m p N o d e I n f o 
    #-----------------------------------------------------------------------------
    def dumpNodeInfo(self):
        idx = 0
        debug('\n[node info]')
        for bNode in self.gRootNodes:
            type = bNode.getType()
            debug('Node (%d): Name=%s, Type=%s' % (idx,
                bNode.getName(),type))
            idx += 1

    #-----------------------------------------------------------------------------
    #                          d u m p A c t i o n I n f o
    #-----------------------------------------------------------------------------
    def dumpActionInfo(self):
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
    #                          d u m p A c t i o n I n f o
    #-----------------------------------------------------------------------------
    def dumpAnimationInfo(self):
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
        
        iGUI.updateStatus('Exporting...')
        start = time.clock()

        # exit edit mode if necessary
        editMode = Blender.Window.EditMode()
        if editMode:
            Blender.Window.EditMode(0)

        #
        # use this to track exported mesh data.  multiple objects/nodes may 
        # reference the same mesh data. irrb only export's a single copy
        #
        self.gExportedMeshes = []
        self.gExportedMeshesLC = []
        self.gMeshNameConflicts = []

        #
        # extract the correct nodes from the current scene
        #
        self.gScene = Blender.Scene.GetCurrent()

        self.gActions = Blender.Armature.NLA.GetActions()

        #
        # initialize .irr scene file if requested
        #
        logName = ''
        if self.gCreateScene:
            try:
                if not self.gSceneDir.endswith(Blender.sys.sep):
                    self.gSceneDir += Blender.sys.sep
                logName = self.gSceneDir + 'irrb.log'
                self.gSceneFileName = (self.gSceneDir + 
                    self.gScene.getName() + '.irr')
                self.sfile = open(self.gSceneFileName,'w')
                self.iScene = iScene.Scene(self)
                self.iScene.writeHeader(self.sfile)
            except IOError,(errno, strerror):
                self.sfile = None
                self.gSceneFileName = None
                errmsg = "IO Error #%s: %s" % (errno, strerror)
        else:
            logName = self.gMeshDir + 'irrb.log'

        iUtils.openLog(logName)

        debug('irrb log ' + iUtils.iversion)
        self.dumpOptions()
            
        for node in self.gScene.objects:
            pNode = node.parent
            if pNode is None:
                self.gRootNodes.append(node)
        
        if self.gDebug == 1:
            self.dumpBlenderInfo()
            self.dumpNodeInfo()
            self.dumpAnimationInfo()
            self.dumpActionInfo()

        self.nodeLevel = 0
        self.gNodeCount = 0
        self.gLightCount = 0
        self.gCameraCount = 0
        self.gVertCount = 0
        self.gFaceCount = 0
        self.copiedImages = []
        for bNode in self.gRootNodes:
            self._exportNode(bNode)
            if (self.gFatalError != None) or (iGUI.exportCancelled()):
                break

        if self.sfile != None:
            self.iScene.writeFooter(self.sfile)
            self.sfile.close()
            self.sfile = None

        if editMode:
            Blender.Window.EditMode(1)

        end = time.clock()
        etime = time.strftime('%X %x')
        stats = ['Export Complete - %.2f seconds - %s' % (end-start,etime)]
        stats.append('%d Node(s)' % self.gNodeCount)
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

        self.dumpStats(stats)
        iUtils.closeLog()
                
        iGUI.setStatus(stats)

    #-----------------------------------------------------------------------------
    #                            _ g e t C h i l d r e n
    #-----------------------------------------------------------------------------
    def _getChildren(self,obj):	
        obs = self.gScene.objects
        return [ ob for ob in obs if ob.parent == obj ]	

    #-----------------------------------------------------------------------------
    #                            _ e x p o r t N o d e
    #-----------------------------------------------------------------------------
    def _exportNode(self,bNode):
        type = bNode.getType()

        writeNode = True
        if type == 'Mesh' and self.gSelectedMeshesOnly == 1 and not bNode.sel:
            writeNode = False

        if writeNode:
            if type == 'Mesh':
                if self.sfile != None:
                    #
                    # should check if mesh actually contains animations...
                    #
                    self.iScene.writeNodeHead(self.sfile,self.nodeLevel,'mesh')
                self._exportMesh(bNode)
                self.gNodeCount += 1
            elif (type == 'Lamp'):
                if (self.sfile != None) and self.gExportLights:
                    self.iScene.writeNodeHead(self.sfile,self.nodeLevel,'light')
                    self.iScene.writeLightNodeData(self.sfile,bNode,self.nodeLevel)
                    self.gLightCount += 1
            elif (type == 'Camera'):
                if (self.sfile != None) and self.gExportCameras:
                    self.iScene.writeNodeHead(self.sfile,self.nodeLevel,'camera')
                    self.iScene.writeCameraNodeData(self.sfile,bNode,self.nodeLevel)
                    self.gCameraCount += 1
            elif (type == 'Empty' or type == 'Armature'):
                if (self.sfile != None):
                    self.iScene.writeNodeHead(self.sfile,self.nodeLevel,'empty')
                    self.iScene.writeEmptyNodeData(self.sfile,bNode,self.nodeLevel)
            
        self.nodeLevel += 1
        cnodes = self._getChildren(bNode)
        for cnode in cnodes:
            self._exportNode(cnode)
        self.nodeLevel -= 1

        if writeNode and (self.sfile != None):
            if type == 'Mesh':
                self.iScene.writeNodeTail(self.sfile,self.nodeLevel)
            elif (type == 'Lamp'):
                if self.gExportLights:
                    self.iScene.writeNodeTail(self.sfile,self.nodeLevel)
            elif (type == 'Camera'):
                if self.gExportCameras:
                    self.iScene.writeNodeTail(self.sfile,self.nodeLevel)
            elif (type == 'Empty'):
                self.iScene.writeNodeTail(self.sfile,self.nodeLevel)
                    
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

        iGUI.updateStatus('Creating Binary Mesh: ' + oname)
        
        meshcvt = iGUI.gMeshCvtPath
        directory = Blender.sys.dirname(meshcvt)
        bcwd = os.getcwd()

        cmdline =  meshcvt + ' -i ' + iname + '  -o ' + oname 
        cmdline +=  ' -a ' + self.gBaseDir

        retcode = subprocess.call(cmdline, shell=True, cwd=directory)

    #-----------------------------------------------------------------------------
    #                            _ e x p o r t M e s h 
    #-----------------------------------------------------------------------------
    def _exportMesh(self,bNode):


        # get Mesh
        mesh = bNode.getData(False,True)
        debug('\n[Mesh - ob:%s, me:%s]' % (bNode.getName(),mesh.name))

        self.gMeshFileName = self.gMeshDir + mesh.name + '.irrmesh'
        binaryMeshFileName = ''
        if self.gBinary:
            binaryMeshFileName = (self.gMeshDir +
                    mesh.name + '.irrbmesh')

        iGUI.updateStatus('Exporting Mesh: ' + mesh.name)

        alreadyExported = self._hasMeshBeenExported(mesh.name)

        if len(mesh.verts) == 0:            
            msg = 'ignoring mesh: %s, no vertices' % mesh.name
            debug(msg)
            iGUI.addWarning(msg)
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

            self.iScene.writeMeshNodeData(self.sfile,sceneMeshFileName,bNode, 
                    self.nodeLevel)
        
        #
        # have we already exported this mesh data block?
        #
        if alreadyExported:
            return

        self._addToMeshExportedList(mesh.name)

        try:
            file = open(self.gMeshFileName,'w')
        except IOError,(errno, strerror):
            errmsg = "IO Error #%s: %s" % (errno, strerror)
    

        # sticky UV's?
        bHasStickyUV = mesh.vertexUV

        # face UV's
        bHasFaceUV = mesh.faceUV

        uvLayerNames = mesh.getUVLayerNames()

        faces = mesh.faces


        irrMesh = iMesh.Mesh(bNode,self,True)
        if irrMesh.createBuffers() == True:
            if iGUI.exportCancelled():
                file.close()
                return
            
            irrMesh.write(file)
        
            if iGUI.exportCancelled():
                file.close()
                return
            
            self.gVertCount += irrMesh.getVertexCount()
            self.gFaceCount += irrMesh.getFaceCount()

            if self.gSavePackedTextures:
                # write image(s) if any
                for k,v in irrMesh.getMaterials().iteritems():
                    if iGUI.exportCancelled():
                        file.close()
                        return
            
                    if v.getMaterialType() == 'UVMaterial':
                        mat = v.getMaterial()
                        images = mat.getImages()
                        for image in images:
                            if image.packed:
                                self._savePackedTexture(image)
                
        file.close()        
        file = None

        if self.gBinary:
            self._convertMesh(self.gMeshFileName, binaryMeshFileName)

    #-----------------------------------------------------------------------------
    #                       g e t I m a g e F i l e N a m e
    #-----------------------------------------------------------------------------
    # which: 0-texture path, full filename
    def getImageFileName(self,meshName,bImage,which):
        if bImage in self.gImageInfo.keys():
            return self.gImageInfo[bImage][which]

        text = '.???'

        #
        # if copying images, setup extension based on ORG or TGA option.
        #
        imageName = bImage.name
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
        if not self.gSavePackedTextures and not exists and (ext == ''):
            checkName = dirname + Blender.sys.sep + imageName
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

        if bImage.packed and not self.gSavePackedTextures:
            iGUI.addWarning('Mesh "%s", Packed Image "%s" not accessible - Select "Save Packed Textures".' %
                    (meshName, bImage.name))
            debug('Image "%s" not accessible.' % bImage.name)
            self.gImageInfo[bImage] = (None,None)
            return None                
        
        #
        # 
        result = '???'
        ext = fileExt
        if self.gSavePackedTextures and (self.gTexExtension != '.???'):
            ext = self.gTexExtension

        if bImage.packed and self.gSavePackedTextures:
            result = iUtils.relpath(self.gTexDir + fileName + ext,
                     self.gBaseDir)
        else:
            result = iUtils.relpath(fullFileName, self.gBaseDir)
            print 'xyz', fullFileName, self.gBaseDir, result
                
        result0 = result

        result = fullFileName
        if self.gSavePackedTextures:
            if self.gTexExtension != '.???':
                result = self.gTexDir + fileName + ext
            else:
                result = self.gTexDir + fileName + fileExt 
        debug('result0: %s' % result0)
        debug('result1: %s' % result)
        self.gImageInfo[bImage] = (result0,result)
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

        iGUI.updateStatus('Saving Packed Texture ' + filename + '...')
        self.copiedImages.append(bImage)

        source = 'unknown'
        if bImage.source & Blender.Image.Sources['GENERATED']:
            source = 'generated'
        elif bImage.source & Blender.Image.Sources['STILL']:
            source = 'still'
        elif bImage.source & Blender.Image.Sources['MOVIE']:
            source = 'movie'
        elif bImage.source & Blender.Image.Sources['SEQUENCE']:
            source = 'sequence'

        if self.gTexExtension != '.???':
            iTGAWriter.writeTGA(bImage,filename,True)
        else:
            saveName =  bImage.getFilename()
            bImage.setFilename(filename)
            bImage.save()
            bImage.setFilename(saveName);
        
