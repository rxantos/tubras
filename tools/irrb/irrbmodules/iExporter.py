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
import Blender,iMesh,iMeshBuffer,bpy,iFilename,iScene,iGUI,time

#-----------------------------------------------------------------------------
#                               E x p o r t e r
#-----------------------------------------------------------------------------
class Exporter:

    #-----------------------------------------------------------------------------
    #                               d o E x p o r t
    #-----------------------------------------------------------------------------
    def __init__(self,SceneDir, MeshDir, MeshPath, TexDir, TexPath, TexExtension, CreateScene, \
            SelectedMeshesOnly, ExportLights, ExportCameras, CopyTextures, Debug):
        
        if len(MeshDir):
            if MeshDir[len(MeshDir)-1] != Blender.sys.sep:
                MeshDir += Blender.sys.sep
        if len(TexDir):
            if TexDir[len(TexDir)-1] != Blender.sys.sep:
                TexDir += Blender.sys.sep
                
        self.gMeshDir = MeshDir
        self.gMeshPath = MeshPath
        self.gTexDir = TexDir
        self.gTexPath = TexPath
        self.gSceneDir = SceneDir
        self.gTexExtension = TexExtension
        self.gCreateScene = CreateScene
        self.gSelectedMeshesOnly = SelectedMeshesOnly
        self.gCopyTextures = CopyTextures
        self.gExportLights = ExportLights
        self.gExportCameras = ExportCameras
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
    #                              d o E x p o r t
    #-----------------------------------------------------------------------------
    def doExport(self):

        iGUI.updateStatus('Exporting...')
        start = time.clock()
    
        print 'iExport.doExport()'

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

        #
        # initialize .irr scene file if requested
        #
        if self.gCreateScene:
            try:
                self.gSceneFileName = self.gSceneDir + Blender.sys.sep + self.gScene.getName() + '.irr'
                self.sfile = open(self.gSceneFileName,'w')
                self.iScene = iScene.Scene(self)
                self.iScene.writeHeader(self.sfile)
            except IOError,(errno, strerror):
                self.sfile = None
                self.gSceneFileName = None
                errmsg = "IO Error #%s: %s" % (errno, strerror)
            
        if self.gSelectedMeshesOnly == 1:
            self.gRootNodes = self.gScene.objects.selected 
        
        else: 
            for node in self.gScene.objects:
                pNode = node.parent
                if pNode is None:
                    self.gRootNodes.append(node)
        
        if self.gDebug == 1:
            idx = 0
            for bNode in self.gRootNodes:
                type = bNode.getType()
                print 'Node (%d): Name=%s, Type=%s' % (idx,bNode.getName(),type)
                idx += 1

        self.nodeLevel = 0
        self.gNodeCount = 0
        self.gLightCount = 0
        self.gCameraCount = 0
        self.gVertCount = 0
        self.gFaceCount = 0
        self.copiedImages = []
        for bNode in self.gRootNodes:
            self._exportNode(bNode)

        if self.sfile != None:
            self.iScene.writeFooter(self.sfile)
            self.sfile.close()
            self.sfile = None

        if editMode:
            Blender.Window.EditMode(1)

        end = time.clock()
        print 'Export Done'
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

        writeNode = False
        if (self.gSelectedMeshesOnly == 0) or bNode.sel:
            writeNode = True

        if writeNode:
            if type == 'Mesh':
                if self.sfile != None:
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

    #-----------------------------------------------------------------------------
    #                 _ a d d T o M e s h E x p o r t e d L i s t
    #-----------------------------------------------------------------------------
    def _addToMeshExportedList(self, meshName):
        if self._hasMeshBeenExported(meshName):
            return
        
        self.gExportedMeshes.append(meshName)        
        self.gExportedMeshesLC.append(meshName.lower())

    #-----------------------------------------------------------------------------
    #                            _ e x p o r t M e s h 
    #-----------------------------------------------------------------------------
    def _exportMesh(self,bNode):


        # get Mesh
        mesh = bNode.getData(False,True)
        print '[Export Mesh - ob:%s, me:%s]' % (bNode.getName(),mesh.name)

        self.gMeshFileName = self.gMeshDir + mesh.name + '.irrmesh'

        iGUI.updateStatus('Exporting Mesh: ' + mesh.name)

        alreadyExported = self._hasMeshBeenExported(mesh.name)

        #
        # write scene node data to scene (.irr) file
        #
        meshFileName = self.gMeshFileName

        if self.sfile != None:
            mpath = self.gMeshPath.strip()
            if mpath != '':
                meshFileName = mpath + mesh.name + '.irrmesh'
            self.iScene.writeMeshNodeData(self.sfile,meshFileName,bNode,self.nodeLevel)
        
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
        irrMesh.createBuffers()
        irrMesh.write(file)
        
        self.gVertCount += irrMesh.getVertexCount()
        self.gFaceCount += irrMesh.getFaceCount()

        if self.gCopyTextures:
            # write image(s) if any
            for k,v in irrMesh.getMaterials().iteritems():
                if v.getMaterialType() == 'UVMaterial':
                    mat = v.getMaterial()
                    image = mat.getImage()
                    self._copyImage(image)
                    image = mat.getLMImage()
                    if image != None:
                        self._copyImage(image)
                
        file.close()
        file = None

    #-----------------------------------------------------------------------------
    #                           _ c o p y I m a g e
    #-----------------------------------------------------------------------------
    def _copyImage(self,bImage):
        
        filename = bImage.name
        if filename in self.copiedImages:
            return        

        #
        # can't use bpy.data.image here because it _doesn't_ support 32
        # bit images, so the alpha channel would be lost for input
        # images that have one.  this way is also much faster...
        #

        iGUI.updateStatus('Copying image ' + filename + '...')
        self.copiedImages.append(filename)

        saveName = bImage.getFilename()

        fn = iFilename.Filename(filename)
        filename = self.gTexDir + fn.getBaseName() + self.gTexExtension

        bImage.setFilename(filename)
        bImage.save()
        bImage.setFilename(saveName);
        
