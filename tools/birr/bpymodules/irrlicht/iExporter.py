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
import Blender,iMesh,iMeshBuffer,bpy,iFilename

#-----------------------------------------------------------------------------
#                               E x p o r t e r
#-----------------------------------------------------------------------------
class Exporter:

    #-----------------------------------------------------------------------------
    #                               d o E x p o r t
    #-----------------------------------------------------------------------------
    def __init__(self,MeshDir, MeshPath, TexDir, TexPath, TexExtension, CreateScene, \
            SelectedMeshesOnly, CopyTextures, Debug):
        
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
        self.gTexExtension = TexExtension
        self.gCreateScene = CreateScene
        self.gSelectedMeshesOnly = SelectedMeshesOnly
        self.gCopyTextures = CopyTextures
        self.gDebug = Debug
        self.gScene = None
        self.gRootNodes = []
        self.gChildNodes = []
        self.gMeshFileName = ''


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
        # extract the correct nodes from the current scene
        #
        self.gScene = Blender.Scene.GetCurrent()
        print 'Current Scene Name: "%s"' % (self.gScene.getName())

        if self.gSelectedMeshesOnly == 1:
            self.gRootNodes = Blender.Object.GetSelected()
            self.gChildNodes = []
            print 'Selected Only Root Nodes:', len(self.gRootNodes)
        
        else: 
            for node in self.gScene.objects:
                pNode = node.parent
                if pNode is None:
                    self.gRootNodes.append(node)
                else:
                    try:
                        self.gChildNodes[pNode.name].append(node)
                    except:
                        self.gChildNodes[pNode.name] = [node]
            print 'All Root Nodes:', len(self.gRootNodes)
        

        if self.gDebug == 1:
            idx = 0
            for bNode in self.gRootNodes:
                type = bNode.getType()
                print 'Node (%d): Name=%s, Type=%s' % (idx,bNode.getName(),type)
                idx += 1

        for bNode in self.gRootNodes:
            type = bNode.getType()
            if type == 'Mesh':
                self._exportMesh(bNode)

        if editMode:
            Blender.Window.EditMode(1)

    #-----------------------------------------------------------------------------
    #                            _ e x p o r t M e s h 
    #-----------------------------------------------------------------------------
    def _exportMesh(self,bNode):


        self.gMeshFileName = self.gMeshDir + Blender.sys.sep + bNode.getName() + '.irrmesh'

        print 'Creating Mesh:', self.gMeshFileName
        try:
            file = open(self.gMeshFileName,'w')
        except IOError,(errno, strerror):
            errmsg = "IO Error #%s: %s" % (errno, strerror)
    
        print '[Export Mesh - %s]' % (bNode.getName())

        # returns a deprecated "NMesh"
        nMesh = bNode.getData(False,False)
        print 'data type',type(nMesh)

        # returns faster "Mesh"
        mesh = bNode.getData(False,True)
        print 'data type',type(mesh)
        print 'mesh properties',
        

        # sticky UV's?
        bHasUV = mesh.vertexUV
        print 'vertexUV', bHasUV

        # face UV's
        bHasFaceUV = mesh.faceUV
        print 'faceUV', bHasFaceUV

        # face vertexColors?
        print 'vertexColors',mesh.vertexColors

        uvLayerNames = mesh.getUVLayerNames()
        print 'UVLayers', uvLayerNames

        verts = mesh.verts
        print 'len(verts)', len(verts)

        for vert in verts:
            print 'vert',vert
            if bHasUV:
                print 'vert uvco', vert.uvco


        faces = mesh.faces
        print 'len(faces)',len(faces)

        for face in faces:
            print 'face:', face, 'mat idx:', face.mat
            if bHasFaceUV:
                print 'face uv:', face.uv
                print 'face image:', face.image

        print 'mesh materials count:', len(mesh.materials)
        for mat in mesh.materials:
            print 'Material Type:', type(mat)
            if mat != None:
                print 'Material:', mat.getName()


        irrMesh = iMesh.Mesh(bNode,self,True)
        irrMesh.createBuffers()
        irrMesh.write(file)

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
        
        size = bImage.getSize()

        nimage = bpy.data.images.new('temp',size[0],size[1])
        print 'depth', nimage.depth, bImage.depth


        for y in range(size[1]):
            for x in range(size[0]):
                nimage.setPixelI(x,y,bImage.getPixelI(x,y))

        filename = bImage.getFilename()
        if filename == 'Untitled':
            filename = bImage.getName()

        fn = iFilename.Filename(filename)
        filename = self.gTexDir + fn.getBaseName() + self.gTexExtension

        print 'copyImage filename',filename

        nimage.setFilename(filename)
        nimage.save()

        nimage = None
