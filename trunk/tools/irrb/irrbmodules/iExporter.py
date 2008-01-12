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
import Blender,iMesh,iMeshBuffer,bpy,iFilename,iScene

#-----------------------------------------------------------------------------
#                               E x p o r t e r
#-----------------------------------------------------------------------------
class Exporter:

    #-----------------------------------------------------------------------------
    #                               d o E x p o r t
    #-----------------------------------------------------------------------------
    def __init__(self,SceneDir, MeshDir, MeshPath, TexDir, TexPath, TexExtension, CreateScene, \
            SelectedMeshesOnly, ExportLights, CopyTextures, Debug):
        
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
        self.gDebug = Debug
        self.gScene = None
        self.gRootNodes = []
        self.gMeshFileName = ''
        self.nodeLevel = 0
        self.iScene = None
        self.sfile = None


    #-----------------------------------------------------------------------------
    #                              g e t T e x P a t h
    #-----------------------------------------------------------------------------
    def getTexPath(self):
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

        #
        # extract the correct nodes from the current scene
        #
        self.gScene = Blender.Scene.GetCurrent()

        #
        # initialize .irr scene file if requested
        #
        if self.gCreateScene:
            try:
                sfname = self.gSceneDir + Blender.sys.sep + self.gScene.getName() + '.irr'
                self.sfile = open(sfname,'w')
                self.iScene = iScene.Scene(self)
                self.iScene.writeHeader(self.sfile)
            except IOError,(errno, strerror):
                self.sfile = None
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
        for bNode in self.gRootNodes:
            self._exportNode(bNode)


        if self.sfile != None:
            self.iScene.writeFooter(self.sfile)
            self.sfile.close()
            self.sfile = None


        if editMode:
            Blender.Window.EditMode(1)

        print 'Export Done'

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
                    self.iScene.writeMeshNodeHead(self.sfile,self.nodeLevel)
                self._exportMesh(bNode)
            elif (type == 'Lamp'):
                if (self.sfile != None) and self.gExportLights:
                    self.iScene.writeLightNodeHead(self.sfile,self.nodeLevel)
                    self.iScene.writeLightNodeData(self.sfile,bNode,self.nodeLevel)
            
        self.nodeLevel += 1
        cnodes = self._getChildren(bNode)
        for cnode in cnodes:
            self._exportNode(cnode)
        self.nodeLevel -= 1

        if writeNode and (self.sfile != None):
            if type == 'Mesh':
                self.iScene.writeMeshNodeTail(self.sfile,self.nodeLevel)
            elif (type == 'Lamp'):
                if self.gExportLights:
                    self.iScene.writeLightNodeTail(self.sfile,self.nodeLevel)

    #-----------------------------------------------------------------------------
    #                            _ e x p o r t M e s h 
    #-----------------------------------------------------------------------------
    def _exportMesh(self,bNode):


        # get Mesh
        mesh = bNode.getData(False,True)
        print '[Export Mesh - ob:%s, me:%s]' % (bNode.getName(),mesh.name)

        self.gMeshFileName = self.gMeshDir + mesh.name + '.irrmesh'

        alreadyExported = mesh.name in self.gExportedMeshes

        #
        # write scene node data to scene (.irr) file
        #
        meshFileName = self.gMeshFileName

        if self.sfile != None:
            self.iScene.writeMeshNodeData(self.sfile,meshFileName,bNode,self.nodeLevel)
        
        #
        # have we already exported this mesh data block?
        #
        if alreadyExported:
            return
        
        self.gExportedMeshes.append(mesh.name)

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

        self.copiedImages = []
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

        self.copiedImages.append(filename)

        size = bImage.getSize()

        nimage = bpy.data.images.new('temp',size[0],size[1])
        print 'depth', nimage.depth, bImage.depth


        for y in range(size[1]):
            for x in range(size[0]):
                nimage.setPixelI(x,y,bImage.getPixelI(x,y))

        fn = iFilename.Filename(filename)
        filename = self.gTexDir + fn.getBaseName() + self.gTexExtension

        print 'copyImage filename',filename

        nimage.setFilename(filename)
        nimage.save()

        nimage = None
